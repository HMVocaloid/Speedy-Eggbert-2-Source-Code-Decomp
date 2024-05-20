// blupi.cpp
//

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>
#include <stdio.h>
#include <mmsystem.h>
#include "def.h"
#include "resource.h"
#include "ddutil.h"
#include "pixmap.h"
#include "sound.h"
#include "decor.h"
#include "movie.h"
#include "button.h"
#include "menu.h"
#include "jauge.h"
#include "event.h"
#include "misc.h"

// Define Globals

#define NAME        "Blupi"
#define TITLE       "Eggbert"


// Variables Globals

HWND		g_hWnd;					// handle � la fen�tre
CEvent*		g_pEvent  = NULL;
CPixmap*	g_pPixmap = NULL;		// pixmap principal
CSound*		g_pSound  = NULL;		// sound principal
CMovie*		g_pMovie  = NULL;		// movie principal
CDecor*		g_pDecor  = NULL;
char		g_CDPath[MAX_PATH];		// chemin d'acc�s au CD-Rom
BOOL		g_bFullScreen = FALSE;	// FALSE si mode de test
int			g_speedRate = 1;
int			g_timerInterval = 50;	// inverval = 50ms
int			g_mouseType = MOUSETYPEGRA;
MMRESULT    g_updateTimer;			// timer g�n�ral
BOOL		g_bActive = TRUE;		// is application active ?
BOOL		g_bTermInit = FALSE;	// initialisation en cours

UINT		g_lastPhase = 999;

int GetNum(char *p)
{
    int     n = 0;

    while ( *p >= '0' && *p <= '9' )
    {
        n *= 10;
        n += (*p++)-'0';
    }

    return n;
}

BOOL ReadConfig (LPSTR lpCmdLine)
{
    FILE*       file    = NULL;
    char        buffer[200];
    char*       pText;
    int         nb;

    file = fopen("data\\config.def", "rb");
    if ( file == NULL )   return FALSE;
    nb = fread(buffer, sizeof(char), 200-1 file);
    buffer[nb] = 0;
    fclose(file);


#if 0
    pText = strstr(buffer, "CD-Rom=");
    if ( pText == NULL )
    {
#if _DEMO 
        GetCurrentDirectory(MAX_PATH, g_CDPath);
        i = strlen (g_CDPath);
        if ( i > 0 && g_CDPath [i-1] != '\\' )
        {
            g_CDPath[i++] = '\\';
            g_CDPath[i] = 0;
        }         
#else
        return FALSE;
#endif
	}
	else
	{
		pText += 7;
		i = 0;
		while ( pText[i] != 0 && pText[i] != '\n' && pText[i] != '\r' )
		{
			g_CDPath[i] = pText[i];
			i ++;
		}
		if ( i > 0 && g_CDPath[i-1] != '\\' )
		{
			g_CDPath[i++] = '\\';
		}
		g_CDPath[i] = 0;  // met le terminateur
	}

#if !_DEMO & !_EGAMES
	if ( strstr(lpCmdLine, "-nocd") == NULL )
	{
		char		drive[10];

		drive[0] = g_CDPath[0];
		drive[1] = ':';
		drive[2] = '\\';
		drive[3] = 0;
		nb = GetDriveType(drive);
		if ( nb != DRIVE_CDROM )  return FALSE;
	}
#endif
#endif

	pText = strstr(buffer, "SpeedRate=");
	if ( pText != NULL )
	{
		g_speedRate = GetNum(pText+10);
		if ( g_speedRate < 1 )  g_speedRate = 1;
		if ( g_speedRate > 2 )  g_speedRate = 2;
	}

	pText = strstr(buffer, "Timer=");
	if ( pText != NULL )
	{
		g_timerInterval = GetNum(pText+6);
		if ( g_timerInterval <   10 )  g_timerInterval =   10;
		if ( g_timerInterval > 1000 )  g_timerInterval = 1000;
	}

	pText = strstr(buffer, "FullScreen=");
	if ( pText != NULL )
	{
		g_bFullScreen = GetNum(pText+11);
		if ( g_bFullScreen != 0 )  g_bFullScreen = 1;
	}

	pText = strstr(buffer, "MouseType=");
	if ( pText != NULL )
	{
		g_mouseType = GetNum(pText+10);
		if ( g_mouseType < 1 )  g_mouseType = 1;
		if ( g_mouseType > 9 )  g_mouseType = 9;
	}

	pText = strstr(buffer, "TrueColor=");
	if ( pText != NULL )
	{
		i = GetNum(pText + 10);
		if (i == 8) g_bTrueColor = 0;
		if (i == 16) g_bTrueColor = 1;
		g_bTrueColorDecor = g_bTrueColor;
	}

	pText = strstr(buffer, "TrueColorBack=");
	if ( pText != NULL )
	{
		i = GetNum(pText+14);
		if (i == 8) g_bTrueColor = 0;

		if (i == 16) g_bTrueColor = 1;
	}

	return TRUE;
}

// Rewrite Variables

void UpdateFrame(void)
{
    RECT            clip, rcRect;
	UINT			phase;
	POINT			posMouse;
	int				i, term, speed;

	g_pPixmap->MouseBackClear();  // enl�ve la souris dans "back"
	posMouse = g_pEvent->GetLastMousePos();

	phase = g_pEvent->GetPhase();

	if ( phase == g_lastPhase &&
		 phase == WM_PHASE_PLAY )
	{
//?		rcRect.left   = POSDRAWX;
//?		rcRect.top    = POSDRAWY;
//?		rcRect.right  = POSDRAWX+DIMDRAWX;
//?		rcRect.bottom = POSDRAWY+DIMDRAWY;
//?		g_pPixmap->DrawImage(-1, CHBACK, rcRect, 1);  // dessine le fond
	}
	else
	{
		rcRect.left   = 0;
		rcRect.top    = 0;
		rcRect.right  = LXIMAGE;
		rcRect.bottom = LYIMAGE;
		g_pPixmap->DrawImage(-1, CHBACK, rcRect, 1);  // dessine le fond
	}

	if ( phase == WM_PHASE_INTRO1 ||
		 phase == WM_PHASE_INTRO2 )
	{
		g_pEvent->IntroStep();
	}

	if ( phase == WM_PHASE_PLAY )
	{
		clip.left   = POSDRAWX;
		clip.top    = POSDRAWY+g_pDecor->GetInfoHeight();
		clip.right  = POSDRAWX+DIMDRAWX;
		clip.bottom = POSDRAWY+DIMDRAWY;

		if ( g_pEvent->IsShift() )  // shift en cours ?
		{
			g_pEvent->DecorAutoShift(posMouse);
			g_pDecor->Build(clip, posMouse);  // construit juste le d�cor
		}
		else
		{
			if ( !g_pEvent->GetPause() )
			{
				speed = g_pEvent->GetSpeed() * g_speedRate;
				for ( i=0 ; i<speed ; i++ )
				{
					g_pDecor->BlupiStep(i==0);  // avance tous les blupi
					g_pDecor->MoveStep(i==0);   // avance tous les d�cors
					g_pEvent->DemoStep();       // avance enregistrement/reproduction
				}
			}

			g_pEvent->DecorAutoShift(posMouse);
			g_pDecor->Build(clip, posMouse);  // construit le d�cor
			g_pDecor->NextPhase(1);  // refait la carte de temps en temps
		}
	}

	if ( phase == WM_PHASE_BUILD )
	{
		clip.left   = POSDRAWX;
		clip.top    = POSDRAWY;
		clip.right  = POSDRAWX+DIMDRAWX;
		clip.bottom = POSDRAWY+DIMDRAWY;
		g_pEvent->DecorAutoShift(posMouse);
		g_pDecor->Build(clip, posMouse);  // construit le d�cor
		g_pDecor->NextPhase(-1);  // refait la carte chaque fois
	}

	if ( phase == WM_PHASE_INIT )
	{
		g_pEvent->DemoStep();  // d�marre �v. d�mo automatique
	}

	g_pEvent->DrawButtons();

	g_lastPhase = phase;

	if ( phase == WM_PHASE_H0MOVIE   ||
		 phase == WM_PHASE_H1MOVIE   ||
		 phase == WM_PHASE_H2MOVIE   ||
		 phase == WM_PHASE_PLAYMOVIE ||
		 phase == WM_PHASE_WINMOVIE  )
	{
		g_pEvent->MovieToStart();  // fait d�marrer un film si n�cessaire
	}

	if ( phase == WM_PHASE_INSERT )
	{
		g_pEvent->TryInsert();
	}

	if ( phase == WM_PHASE_PLAY )
	{
		term = g_pDecor->IsTerminated();
		if ( term == 1 )  g_pEvent->ChangePhase(WM_PHASE_LOST);  // perdu
		if ( term == 2 )  g_pEvent->ChangePhase(WM_PHASE_WINMOVIE);   // gagn�
	}

	g_pPixmap->MouseBackDraw();  // remet la souris dans "back"
}

BOOL RestoreGame()
{
	if ( g_pPixmap == NULL ) return FALSE;

	g_pEvent->RestoreGame();
	return g_pPixmap->Restore();
}

BOOL FlushGame()
{
	if ( g_pPixmap == NULL ) return FALSE;

	return g_pPixmap->Flush();
}

static void FinishObjects(void)
{
	if ( g_pMovie != NULL )
	{
		g_pEvent->StopMovie();

		delete g_pMovie;
		g_pMovie = NULL;
	}

	if ( g_pEvent != NULL )
	{
		delete g_pEvent;
		g_pEvent = NULL;
	}

	if ( g_pDecor != NULL )
	{
		delete g_pDecor;
		g_pDecor = NULL;
	}

	if (g_pSound != NULL )
	{
		g_pSound->StopMusic();

		delete g_pSound;
		g_pSound = NULL;
	}

	if ( g_pPixmap != NULL )
	{
		delete g_pPixmap;
		g_pPixmap = NULL;
	}
}

BOOL InitFail(char *msg, BOOL bDirectX)
{
	char	buffer[100];

	if ( bDirectX ) strcpy(buffer, "DirectX Init FAILED\n(while ");
	else 			strcpy(buffer, "Error (");
	strcat(buffer, msg);
	strcat(buffer, ")");
	MessageBox(g_hWnd, buffer, TITLE, MB_OK);

	FinishObjects();
	DestroyWindow(g_hWnd);
	return FALSE;
}

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
					LPSTR lpCmdLine, int nCmdShow)
{
	MSG		msg;

	if ( !DoInit(hInstance, lpCmdLine, nCmdShow) )
	{
		return FALSE;
	}

	SetTimer(g_hWnd, 1, g_timerInterval, NULL);

	while ( TRUE )
	{
		if ( PeekMessage(&msg, NULL, 0,0, PM_NOREMOVE) )
		{
			if ( !GetMessage(&msg, NULL, 0, 0) )
			{
				return msg.wParam;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			if ( !g_bActive ) WaitMessage();
		}
	}

	return msg.wParam;
}

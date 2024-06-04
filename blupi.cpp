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
#include "network.h"

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
CNetwork*   g_pNetwork;
char		g_CDPath[MAX_PATH];		// chemin d'acc�s au CD-Rom
BOOL		g_bFullScreen = FALSE;	// FALSE si mode de test
int			g_speedRate = 1;
int			g_timerInterval = 50;	// inverval = 50ms
int			g_mouseType = MOUSETYPEGRA;
int 		g_benchmark;
BOOL 		g_bBenchmarkSuccess;
BOOL 		g_bTrueColor;
BOOL 		g_bTrueColorBack;
BOOL 		g_bTrueColorDecor;
MMRESULT    g_updateTimer;			// timer g�n�ral
BOOL		g_bActive = TRUE;		// is application active ?
BOOL		g_bTermInit = FALSE;	// initialisation en cours
int			g_objectMax;
int			g_elementMax;
int			g_blupiMax;
int			g_exploMax;

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
	int 		i;

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

	pText = strstr(buffer, "Benchmark=");
	if ( pText != NULL )
	{
		g_benchmark = GetNum(pText+10);
		if ( g_benchmark < 0 ) g_benchmark = 0;
		if ( g_benchmark > 100000 ) g_benchmark = 100000;
		if ( g_benchmark > 3099 ) g_bBenchmarkSuccess = 1, g_bTrueColor = 1, g_bTrueColorDecor;
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

	pText = strstr(buffer, "TrueColorDecor=");
	if ( pText != NULL )
	{
		i = GetNum(pText + 15);
		if (i == 8) g_bTrueColorDecor = 0;

		if (i == 16) g_bTrueColorDecor = 1;
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
		 phase == WM_PHASE_PLAY || phase == WM_PHASE_PLAYTEST || phase == WM_PHASE_BUILD )
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

	if (phase == WM_PHASE_INIT)
	{
		g_pEvent->DemoStep();  // d�marre �v. d�mo automatique
	}

	if (phase == WM_PHASE_PLAYMOVIE || phase == WM_PHASE_WINMOVIE || WM_PHASE_WINMOVIEDESIGN || WM_PHASE_WINMOVIEMULTI)
	{
		g_pEvent->MovieToStart;
	}

	if (phase == WM_PHASE_INSERT)
	{
		g_pEvent->TryInsert();
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

	if ( phase == WM_PHASE_PLAY )
	{
		term = g_pDecor->IsTerminated();
		if ( term == 1 )  g_pEvent->ChangePhase(WM_PHASE_LOST);  // perdu
		if ( term == 2 )  g_pEvent->ChangePhase(WM_PHASE_WINMOVIE);   // gagn�
	}

	g_pPixmap->MouseBackDraw();  // remet la souris dans "back"
}

void Benchmark()
{
	int	i;
	POINT	pos = { 0, 0 };

	g_pPixmap->DrawIcon(-1, 2, 10, pos, 0);

	pos.x = 300;
	pos.y = 350;
	for (i = 0; i < 10000; i++)
	{
		g_pPixmap->DrawIcon(-1, 2, i % 4, pos, 0);
	}

	g_pPixmap->DrawIcon(-1, 2, 10, pos, 0);
	g_pSound->Play(0);
}

// Incomplete

void SetDecor()
{
	RECT rect;
	UINT phase;
	POINT posMouse;

	g_pPixmap->MouseBackClear();
	g_pEvent->GetLastMousePos(&posMouse);
	phase = g_pEvent->GetPhase;

	if (phase == WM_PHASE_PLAY || phase == WM_PHASE_PLAYTEST || phase == WM_PHASE_BUILD)
	{

	}
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

	if (g_pNetwork != NULL )
	{
		delete g_pNetwork;
		g_pNetwork = NULL;
	}

	if ( g_pPixmap != NULL )
	{
		delete g_pPixmap;
		g_pPixmap = NULL;
	}
}

LRESULT CALLBACK WindowProc (HWND hWnd, UINT message,
							 WPARAM wParam, LPARAM lParam)
{
	static HINSTANCE   hInstance;
	POINT 			   mousePos, totalDim, iconDim;
#if 0
	if ( message != WM_TIMER )
	{
		char s[100];
		sprintf(s, "message=%d,%d\n", message, wParam);
		OutputDebug(s);
	}
#endif

	if ( message == WM_SYSKEYDOWN && wParam == VK_F10 )
	{
		message = WM_KEYDOWN;
	}
	if ( message == WM_SYSKEYUP && wParam == VK_F10 )
	{
		message = WM_KEYUP;
	}

	if ( g_pEvent != NULL &&
		 g_pEvent->TreatEvent(message, wParam, lParam) ) return 0;

	switch( message )
	{
		case WM_TIMER:
		case WM_SYSCOLORCHANGE:
		    OutputDebug("Event WM_SYSCOLORCHANGE\n");
			break;
		case WM_CREATE:
			hInstance = ((LPCREATESTRUCT)lParam)->hInstance;
			return 0;
			break;

        case WM_ACTIVATEAPP:
		    g_bActive = (wParam != 0);
			if (g_pEvent != NULL)
			{
				g_pEvent->SomethingDecor;
			}
			if ( g_bActive )
			{
				if ( g_bFullScreen )
				{
					RestoreGame();
					g_lastPhase = 999;
				}
				if ( !g_bFullScreen && g_bTermInit )
				{
					totalDim.x = 64;
					totalDim.y = 66;
					iconDim.x = 64;
					iconDim.y = 66/2;
					g_pPixmap->Cache(CHLITTLE, "image16\\little.blp", totalDim, iconDim, TRUE);
					g_pPixmap->SetTransparent(CHLITTLE, RGB(0,0,255));

					g_pPixmap->SavePalette();
					g_pPixmap->InitSysPalette();
				}
				SetWindowText(hWnd, "Blupi");
				if ( g_pSound != NULL ) g_pSound->RestartMusic();
			}
			else
			{
				if ( g_bFullScreen )
				{
					FlushGame();
				}
				SetWindowText(hWnd, "Blupi -- stop");
				if ( g_pSound != NULL ) g_pSound->SuspendMusic();
			}
			return 0;

			case WM_KEYDOWN:
				switch( wParam )
				{
					case VK_F5:
						g_pEvent->SetSpeed(1);
						break;
					case VK_F6:
						g_pEvent->SetSpeed(2);
						break;
					case VK_F7:
						g_pEvent->SetSpeed(4);
						break;
					case VK_F8:
						g_pEvent->SetSpeed(8);
						break;
				}
			break;

			case WM_DISPLAYCHANGE:
				OutputDebug("Event WM_DISPLAYCHANGE\n");
				break;
			case WM_QUERYNEWPALETTE:
				OutputDebug("Event WM_QUERYNEWPALETTE\n");
				break;
			case WM_PALETTECHANGED:
				OutputDebug("Event WM_PALLETECHANGED\n");
				break;
			case MM_MCINOTIFY:
				OutputDebug("Event MM_MCINOTIFY\n");
				if ( g_pEvent->IsMovie() )
				{
					if ( wParam == MCI_NOTIFY_SUCCESSFUL )
					{
						g_pEvent->StopMovie();
					}
				}
				else
				{
					g_pSound->SuspendMusic();
					if ( wParam == MCI_NOTIFY_SUCCESSFUL )
					{
						OutputDebug("Event MCI_NOTIFY_SUCCESSFUL\n");
						g_pSound->RestartMusic();
					}
					else
					{
						char s[50];
						sprintf(s, "wParam=%d\n", wParam);
						OutputDebug(s);
					}
				}
				break;

		case WM_LBUTTONDOWN:
			GetCursorPos(&mousePos);
			ScreenToClient(hWnd, &mousePos);
			break;

		case WM_DESTROY:
			KillTimer(g_hWnd, 1);
			FinishObjects();
			PostQuitMessage(0);
			break;
		case WM_SETCURSOR:
//			ChangeSprite();
//			SetCursor(NULL);
			return TRUE;
		case WM_UPDATE:
			if ( !g_pEvent->IsMovie() )
			{
				if ( g_bActive )
				{
					UpdateFrame();
				}
				g_pPixmap->Display();
			}
			break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);

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

//Space for SetTimer


static BOOL DoInit(HINSTANCE hInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS 	   wc;
	POINT		   totalDim, iconDim;
	RECT		   rcRect;
	BOOL 		   bOK;

	bOK = ReadConfig(lpCmdLine);

	InitHInstance(hInstance);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, "IDR_MAINFRAME");
	wc.hCursor = LoadCursor(hInstance, "IDC_POINTER");
	wc.hbrBackground = GetStockBrush(BLACK_BRUSH);
	wc.lpszMenuMane = NAME;
	wc.lpszClassName = NAME;
	RegisterClass(&wc);

	if (g_bFullScreen)
	{
		g_hWnd = CreateWindowEx
		(
			WS_EX_TOPMOST,
			NAME,
			TITLE,
			WS_POPUP,
			0, 0,
			GetSystemMetrics(SM_CXSCREEN),
			GetSystemMetrics(SM_CYSCREEN),
			NULL,
			NULL,
			hInstance,
			NULL
		);
	}
	else
	{
		int 		sx, sy;
		RECT 		WindowRect;

		sx = GetSystemMetrics(SM_CXSCREEN);
		sy = GetSystemMetrics(SM_CYSCREEN);

		SetRect(&WindowRect, (sx - LXIMAGE) / 2, (sy - LYIMAGE) / 2,
			(sx + LXIMAGE) / 2, (sy + LYIMAGE) / 2);
		AdjustWindowRect(&WindowRect, WS_POPUPWINDOW | WS_CAPTION, TRUE);
		WindowRect.top += GetSystemMetrics(SM_CYCAPTION);

		g_hWnd = CreateWindow
		(
			NAME,
			TITLE,
			WS_POPUPWINDOW | WS_CAPTION | WS_VISIBLE,
			(sx - LXIMAGE) / 2, (sy - LYIMAGE) / 2,
			WindowRect.right - WindowRect.left,
			WindowRect.bottom - WindowRect.top,
			HWND_DESKTOP,
			NULL,
			hInstance,
			NULL
		);
	}
	if (!g_hWnd) return FALSE;

	ShowWindow(g_hWnd, nCmdShow);
	UpdateWindow(g_hWnd);
	SetFocus(g_hWnd);

	ChangeSprite(SPRITE_WAIT);

	if (!bOk)
	{
		return InitFail("Game not correctly installed", FALSE);
	}

	g_pPixmap = new CPixmap;
	if (g_pPixmap == NULL) return InitFail("New pixmap", TRUE);

	totalDim.x = LXIMAGE;
	totalDim.y = LYIMAGE;
	if (!g_pPixmap->Create(g_hWnd, totalDim, g_bFullScreen, g_mouseType))
		return InitFail("Create pixmap", TRUE);

	OutputDebug("Image: init\n");
	totalDim.x = LXIMAGE;
	totalDim.y = LYIMAGE;
	iconDim.x = 0;
	iconDim.y = 0;

	if (!g_pPixmap->CacheAll(g_hWnd, g_bFullScreen, g_bTrueColor, g_bTrueColorDecor, g_mouseType, "image16\\init.blp", FALSE))
		return InitFail("CacheAll", TRUE)

#if _INTRO
		if (!g_pPixmap->Cache(CHBACK, "image16\\init.blp", totalDim, iconDim, TRUE))
#else
		if (!g_pPixmap->Cache(CHBACK, "image16\\init.blp", totalDim, iconDim, TRUE))
#endif
			return FALSE;

	OutputDebug("SavePalette\n");
	g_pPixmap->SavePalette();
	OutputDebug("InitSysPalette\n");
	g_pPixmap->InitSysPalette();

	g_pSound = new CSound;
	if (g_pSound == NULL) return InitFail("New sound", TRUE);

	g_pSound->Create(g_hWnd);
	g_pSound->CacheAll();
	g_pSoundSetState(TRUE);

	g_pMovie = new CMovie;
	if (g_pMovie == NULL) return InitFail("New movie", FALSE);

	g_pMovie->Create();

	g_pDecor = new CDecor;
	if (g_pDecor == NULL) return InitFail("New decor", FALSE);

	g_pDecor->Create(g_hWnd, g_pSound, g_pPixmap);
	g_pDecor->MapInitColors();

	g_pEvent = new CEvent;
	if (g_pEvent == NULL) return InitFail("New event", FALSE);

	g_pEvent->Create(g_hWnd, g_pPixmap, g_pDecor, g_pSound, g_pMovie);
	g_pEvent->SetFullScreen(g_bFullScreen);
	g_pEvent->SetMouseType(g_mouseType);
#if _INTRO
	g_pEvent->ChangePhase(WM_PHASE_INTRO1);
#else
	g_pEvent->ChangePhase(WM_PHASE_TESTCD);
#endif

	g_bTermInit = TRUE;
	return TRUE;
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

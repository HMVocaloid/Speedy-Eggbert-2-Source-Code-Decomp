// blupi.cpp
//

#define WIN32_LEAN_AND_MEAN

#pragma once

#pragma comment(lib, "winmm.lib")

using namespace std;

#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>
#include <stdio.h>
#include <mmsystem.h>
#include <time.h>
#include <sys/timeb.h>
#include <mmiscapi2.h>
#include <WinBase.h>
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

#pragma warning (disable : 4996)

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
int			g_bTimer;
int			g_objectMax;
int			g_elementMax;
int			g_blupiMax;
int			g_exploMax;
short		g_object[6];
short		g_element[6];
short		g_blupiCh[6];
short		g_explo[6];

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
	_MEMORYSTATUS memstatus;

    file = fopen("data\\config.def", "rb");
    if ( file == NULL )   return FALSE;
    nb = fread(buffer, sizeof(char), 200-1, file);
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

	memstatus.dwLength = 32;
	GlobalMemoryStatus(&memstatus);
	if (memstatus.dwTotalPhys < 32000000)
	{
		g_bBenchmarkSuccess = FALSE;
	}
	if (g_bBenchmarkSuccess = FALSE)
	{
		g_bTrueColorBack = FALSE;
		g_bTrueColorDecor = FALSE;
	}
	return TRUE;
}

// Rewrite Variables

void UpdateFrame(void)
{
	RECT            clip, rcRect;
	UINT			phase;
	BOOL			type;
	POINT			posMouse;
	int				i, term, speed, targetlevel;

	g_pEvent->ReadInput();
	phase = g_pEvent->GetPhase();

	if (phase == g_lastPhase &&
		phase == WM_PHASE_PLAY || phase == WM_PHASE_PLAYTEST || phase == WM_PHASE_BUILD)
	{
		type = g_pDecor->GetPause();
		if (type == FALSE)
		{
			speed = g_pEvent->GetSpeed();
			term = 0;
			speed = speed * g_speedRate;
			if (0 < speed)
			{
				do {
					g_pDecor->MoveStep();
					g_pEvent->DemoStep();
					term++;
				} while (term < speed);
			}
		}

		if (phase == WM_PHASE_INIT)
		{
			g_pEvent->DemoStep();  // d�marre �v. d�mo automatique
		}

		if (phase == WM_PHASE_PLAYMOVIE || phase == WM_PHASE_WINMOVIE || WM_PHASE_WINMOVIEDESIGN || WM_PHASE_WINMOVIEMULTI)
		{
			g_pEvent->MovieToStart();
		}

		if (phase == WM_PHASE_INSERT)
		{
			g_pEvent->TryInsert();
		}

		if (phase == WM_PHASE_PLAY)
		{
			if (g_pEvent->IsPrivate() == FALSE)
			{
				if (g_pEvent->IsMulti() == FALSE)
				{
					if (g_pDecor->IsTerminated() == -1)
					{
						g_pEvent->GetWorldGroup();
						g_pEvent->SetLives(g_pDecor->GetNbVies());
						g_pEvent->ChangePhase(WM_PHASE_LOST);
					}
					if (g_pDecor->IsTerminated() == -2)
					{
						g_pEvent->SetLives(g_pDecor->GetNbVies());
						g_pEvent->ChangePhase(WM_PHASE_WINMOVIE);
					}
					if (0 < g_pDecor->IsTerminated())
					{
						g_pEvent->SetLives(g_pDecor->GetNbVies());
						g_pEvent->SetMission(g_pDecor->IsTerminated());
						g_pEvent->ChangePhase(WM_PHASE_PLAY);
					}
				}
				else
				{
					if (g_pDecor->IsTerminated() == -1)
					{
						g_pEvent->ChangePhase(WM_PHASE_WINm);
						return;
					}
					if (g_pDecor->IsTerminated() != 0)
					{
						g_pEvent->ChangePhase(WM_PHASE_WINMOVIEm);
						return;
					}
				}
			}
			else
			{
				if (g_pDecor->IsTerminated() == -1)
				{
					g_pEvent->ChangePhase(WM_PHASE_LOSTd);
					return;
				}
				if (g_pDecor->IsTerminated() != 0)
				{
					g_pEvent->ChangePhase(WM_PHASE_WINMOVIEd);
					return;
				}
			}
		}
	}
	return;
}



// Incomplete

void SetDecor()
{
	RECT rect;
	UINT phase;
	POINT posMouse;
	char  test[12];

	g_pPixmap->MouseBackClear();
	g_pEvent->GetLastMousePos();
	phase = g_pEvent->GetPhase();

	if (phase == WM_PHASE_PLAY || phase == WM_PHASE_PLAYTEST || phase == WM_PHASE_BUILD)
	{
		*(char*)test = (LXIMAGE) << 64;
		rect.bottom = LYIMAGE;
		rect.left = LOWORD(test);
		rect.top = HIWORD(test);
		rect.right = HIWORD(test);
		g_pDecor->Build(rect);
	}
	else
	{
		*(char*)test = (LXIMAGE) << 64;
		rect.bottom = LYIMAGE;
		rect.left = LOWORD(test);
		rect.top = HIWORD(test);
		rect.right = HIWORD(test);
		g_pPixmap->DrawImage(-1, 0, rect, 1);
	}
	g_pEvent->DrawButtons();
	g_lastPhase = phase;
	g_pPixmap->MouseBackDraw();
	return;
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
				g_pEvent->FlushInput();
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
					g_pPixmap->Cache2(CHLITTLE, "image16\\little.blp", totalDim, iconDim, TRUE);
					g_pPixmap->SetTransparent(CHLITTLE, RGB(0,0,255));

					g_pPixmap->SavePalette();
					g_pPixmap->InitSysPalette();
				}
				SetWindowTextA(hWnd, "Blupi");
				if ( g_pSound != NULL ) g_pSound->RestartMusic();
			}
			else
			{
				if ( g_bFullScreen )
				{
					FlushGame();
				}
				SetWindowTextA(hWnd, "Blupi -- stop");
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

LPTIMECALLBACK TimerStep()
{
	if ((g_bActive != FALSE) && (g_bTimer == 0))
	{
		g_bTimer = 1;
		PostAppMessageA(g_hWnd, 1025, 0, 0);
	}
	return NULL;
}

BOOL InitFail(const char *msg, BOOL bDirectX)
{
	char	buffer[100];

	if ( bDirectX ) strcpy(buffer, "DirectX Init FAILED\n(while ");
	else 			strcpy(buffer, "Error (");
	strcat(buffer, msg);
	strcat(buffer, ")");
	MessageBoxA(g_hWnd, buffer, TITLE, MB_OK);

	FinishObjects();
	DestroyWindow(g_hWnd);
	return FALSE;
}

int Benchmark()
{
	timeb time[6];
	int num0;
	int num;
	int num2;
	int num3;
	int i;
	short crap[6];
	FILE* open;
	int frame;
	_MEMORYSTATUS buffer;
	char file[100];

	ftime(time);

	num = (int)time;
	frame = 10;

	do
	{
		UpdateFrame();
		SetDecor();
		g_pPixmap->Display();
		frame++;
	} while (frame);

	ftime(time);
	i = (int)time;

	num0 = HIWORD(crap) & 0xFFFF;

	if (num0 < num)
	{
		num0 = num0 + 1000;
	}
	num3 = i - num0;
	buffer.dwLength = 32;
	GlobalMemoryStatus(&buffer);
	sprintf(file, "CheckTime = %d\r\nMemory = %d", num3, buffer.dwTotalPhys);

	if (fopen("data\\time.blp", "wb"))
	{
		fwrite(file, strlen(file), 1, fopen("data\\time.blp", "wb"));
		fclose(fopen("data\\time.blp", "wb"));
	}
	return num3;
}

static BOOL DoInit(HINSTANCE hInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSA 	   wc;
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
	wc.hIcon = LoadIconA(hInstance, "IDR_MAINFRAME");
	wc.hCursor = LoadCursorA(hInstance, "IDC_POINTER");
	wc.hbrBackground = GetStockBrush(BLACK_BRUSH);
	wc.lpszMenuName = NAME;
	wc.lpszClassName = NAME;
	RegisterClassA(&wc);

	if (g_bFullScreen)
	{
		g_hWnd = CreateWindowExA
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

		g_hWnd = CreateWindowA
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

	if (!bOK)
	{
		return InitFail("Game not correctly installed", FALSE);
	}

	g_pPixmap = new CPixmap;
	if (g_pPixmap == NULL) return InitFail("New pixmap", TRUE);

	totalDim.x = LXIMAGE;
	totalDim.y = LYIMAGE;
	if (!g_pPixmap->Create(g_hWnd, totalDim, g_bFullScreen, g_mouseType, g_bTrueColorBack, g_bTrueColorDecor))
		return InitFail("Create pixmap", TRUE);

	OutputDebug("Image: init\n");
	totalDim.x = LXIMAGE;
	totalDim.y = LYIMAGE;
	iconDim.x = 0;
	iconDim.y = 0;

	if (!g_pPixmap->CacheAll(TRUE, g_hWnd, g_bFullScreen, g_bTrueColorBack, g_bTrueColorDecor, g_mouseType, "image08\\init.blp", 0))
		return InitFail("CacheAll", TRUE);

	OutputDebug("SavePalette\n");
	g_pPixmap->SavePalette();
	OutputDebug("InitSysPalette\n");
	g_pPixmap->InitSysPalette();

	g_pSound = new CSound;
	if (g_pSound == NULL) return InitFail("New sound", TRUE);

	g_pSound->Create(g_hWnd);
	g_pSound->CacheAll();
	g_pSound->SetState(TRUE);

	g_pMovie = new CMovie;
	if (g_pMovie == NULL) return InitFail("New movie", FALSE);

	g_pMovie->Create();

	g_pDecor = new CDecor;
	if (g_pDecor == NULL) return InitFail("New decor", FALSE);

	g_pDecor->Create(g_hWnd, g_pSound, g_pPixmap, g_pNetwork);

	g_pEvent = new CEvent;
	if (g_pEvent == NULL) return InitFail("New event", FALSE);

	g_pEvent->Create(g_hWnd, g_pPixmap, g_pDecor, g_pSound, g_pMovie, g_pNetwork);
	g_pEvent->SetFullScreen(g_bFullScreen);
	g_pEvent->SetMouseType(g_mouseType);
	g_pEvent->ChangePhase(WM_PHASE_INIT);

	g_pNetwork = new CNetwork;
	if (g_pNetwork == NULL) return InitFail("New network", FALSE);
	g_pNetwork->CreateProvider(0);

	g_bTermInit = TRUE;
	return TRUE;
}

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
					LPSTR lpCmdLine, int nCmdShow)
{
	MSG		msg;
	LPTIMECALLBACK timeStep;

	if ( !DoInit(hInstance, lpCmdLine, nCmdShow) )
	{
		return FALSE;
	}

	Benchmark();
	g_hWnd = (HWND)timeSetEvent(g_timerInterval, (g_timerInterval + (g_timerInterval >> 31 & 3U)) >> 2, TimerStep(), 0, 1);

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

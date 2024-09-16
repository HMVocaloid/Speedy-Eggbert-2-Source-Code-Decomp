// blupi.cpp
//

#define WIN32_LEAN_AND_MEAN

#pragma once

#include <windows.h>
#include <windowsx.h>
#include <stdlib.h>
#include <stdio.h>
#include <mmsystem.h>
#include <time.h>
#include <sys/timeb.h>
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
#ifdef _EGAMES
#define TITLE       "Eggbert"
#else
#define TITLE		"Blupi"
#endif

#define MMTIMER     FALSE
#define THREAD		FALSE

// Variables Globals

HWND		g_hWnd;					// handle à la fenètre
CEvent*		g_pEvent = NULL;
CPixmap*	g_pPixmap = NULL;		// pixmap principal
CSound*		g_pSound = NULL;		// sound principal
CMovie*		g_pMovie = NULL;		// movie principal
CDecor*		g_pDecor = NULL;
CNetwork*   g_pNetwork = NULL;
char		g_CDPath[MAX_PATH];		// chemin d'accès au CD-Rom
BOOL		g_bFullScreen = FALSE;	// FALSE si mode de test
int			g_speedRate = 1;
int			g_timerInterval = 50;	// inverval = 50ms
int			g_mouseType = MOUSETYPEGRA;
int 		g_benchmark;
BOOL 		g_bBenchmarkSuccess;
BOOL 		g_bTrueColorBack;
BOOL 		g_bTrueColorDecor;
BOOL		g_bCDAudio = FALSE;
int			g_something;
MMRESULT    g_updateTimer;			// timer général
BOOL		g_bActive = TRUE;		// is application active ?
BOOL		g_bTermInit = FALSE;	// initialisation en cours
int			g_timer;

UINT		g_lastPhase = 999;

// Lit un numéro décimal.

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

BOOL ReadConfig(LPSTR lpCmdLine)
{
	FILE*       file = NULL;
	char        buffer[200];
	char*       pText;
	int         nb;
	int 		i;
	MEMORYSTATUS mem;

	file = fopen("data\\config.def", "rb");
	if (file == NULL)   return FALSE;
	nb = fread(buffer, sizeof(char), 200 - 1, file);
	buffer[nb] = 0;
	fclose(file);


#if _CD
	pText = strstr(buffer, "CD-Rom=");
	if (pText == NULL)
	{
#if _DEMO 
		GetCurrentDirectory(MAX_PATH, g_CDPath);
		i = strlen(g_CDPath);
		if (i > 0 && g_CDPath[i - 1] != '\\')
		{
			g_CDPath[i++] = '\\';
			g_CDPath[i] = 0;
		}
#else
		return FALSE;
#endif // _DEMO
	}
	else
	{
		pText += 7;
		i = 0;
		while (pText[i] != 0 && pText[i] != '\n' && pText[i] != '\r')
		{
			g_CDPath[i] = pText[i];
			i++;
		}
		if (i > 0 && g_CDPath[i - 1] != '\\')
		{
			g_CDPath[i++] = '\\';
		}
		g_CDPath[i] = 0;  // met le terminateur
	}

#if !_DEMO && !_EGAMES
	if (strstr(lpCmdLine, "-nocd") == NULL)
	{
		char		drive[10];

		drive[0] = g_CDPath[0];
		drive[1] = ':';
		drive[2] = '\\';
		drive[3] = 0;
		nb = GetDriveType(drive);
		if (nb != DRIVE_CDROM)  return FALSE;
	}
#endif // !_DEMO && !_EGAMES
#endif // _CD

	pText = strstr(buffer, "SpeedRate=");
	if (pText != NULL)
	{
		g_speedRate = GetNum(pText + 10);
		if (g_speedRate < 1)  g_speedRate = 1;
		if (g_speedRate > 2)  g_speedRate = 2;
	}

	pText = strstr(buffer, "Timer=");
	if (pText != NULL)
	{
		g_timerInterval = GetNum(pText + 6);
		if (g_timerInterval <   10)  g_timerInterval = 10;
		if (g_timerInterval > 1000)  g_timerInterval = 1000;
	}

	pText = strstr(buffer, "FullScreen=");
	if (pText != NULL)
	{
		g_bFullScreen = GetNum(pText + 11);
		if (g_bFullScreen != 0)  g_bFullScreen = 1;
	}

	pText = strstr(buffer, "MouseType=");
	if (pText != NULL)
	{
		g_mouseType = GetNum(pText + 10);
		if (g_mouseType < 1)  g_mouseType = 1;
		if (g_mouseType > 9)  g_mouseType = 9;
	}

	pText = strstr(buffer, "Benchmark=");
	if (pText != NULL)
	{
		g_benchmark = GetNum(pText + 10);
		if (g_benchmark < 0) g_benchmark = 0;
		if (g_benchmark > 100000) g_benchmark = 100000;
		if (g_benchmark > 3099)
		{
			g_bBenchmarkSuccess = TRUE;
			g_bTrueColorBack = TRUE;
			g_bTrueColorDecor = TRUE;
		}
	}

	pText = strstr(buffer, "TrueColor=");
	if (pText != NULL)
	{
		i = GetNum(pText + 10);
		if (i == 8) g_bTrueColorBack = FALSE;
		if (i == 16) g_bTrueColorBack = TRUE;
		g_bTrueColorDecor = g_bTrueColorBack;
	}

	pText = strstr(buffer, "TrueColorBack=");
	if (pText != NULL)
	{
		i = GetNum(pText + 14);
		if (i == 8) g_bTrueColorBack = FALSE;
		if (i == 16) g_bTrueColorBack = TRUE;
	}

	pText = strstr(buffer, "TrueColorDecor=");
	if (pText != NULL)
	{
		i = GetNum(pText + 15);
		if (i == 8) g_bTrueColorDecor = FALSE;
		if (i == 16) g_bTrueColorDecor = TRUE;
	}

	pText = strstr(buffer, "CDAudio=");
	if (pText != NULL)
	{
		i = GetNum(pText + 8);
		g_bCDAudio = (i == TRUE);
	}

	mem.dwLength = sizeof(MEMORYSTATUS);
	GlobalMemoryStatus(&mem);

	if (mem.dwTotalPhys < 32000000) g_bBenchmarkSuccess = FALSE;

	if (!g_bBenchmarkSuccess)
	{
		g_bTrueColorBack = FALSE;
		g_bTrueColorDecor = FALSE;
	}

	return TRUE;
}

void UpdateFrame(void)
{
	int phase, term;

	g_pEvent->ReadInput();
	phase = g_pEvent->GetPhase();
	if (phase == WM_PHASE_PLAY || phase == WM_PHASE_PLAYTEST || phase == WM_PHASE_BUILD)
	{
		if (!g_pDecor->GetPause())
		{
			for (int i = 0; i < g_pEvent->GetSpeed() * g_speedRate; i++)
			{
				g_pDecor->MoveStep();
				g_pEvent->DemoStep();
			}
		}
	}

	if (phase == WM_PHASE_INIT)
	{
		g_pEvent->DemoStep();  // d?marre ?v. d?mo automatique
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
					g_pEvent->ChangePhase(WM_PHASE_WINMULTI);
					return;
				}
				if (g_pDecor->IsTerminated() != 0)
				{
					g_pEvent->ChangePhase(WM_PHASE_WINMOVIEMULTI);
					return;
				}
			}
		}
		else
		{
			if (g_pDecor->IsTerminated() == -1)
			{
				g_pEvent->ChangePhase(WM_PHASE_LOSTDESIGN);
				return;
			}
			if (g_pDecor->IsTerminated() != 0)
			{
				g_pEvent->ChangePhase(WM_PHASE_WINMOVIEDESIGN);
				return;
			}
		}
	}
}

// Incomplete

void SetDecor(void)
{
	RECT rect;
	UINT phase;
	POINT posMouse;
	char  test[12];

	g_pPixmap->MouseBackClear();
	posMouse = g_pEvent->GetLastMousePos();

	phase = g_pEvent->GetPhase();

	rect = { 0, 0, LXIMAGE, LYIMAGE };

	if (phase == WM_PHASE_PLAY || phase == WM_PHASE_PLAYTEST || phase == WM_PHASE_BUILD)
	{
		g_pDecor->Build(rect);
	}
	else {
		g_pPixmap->DrawImage(-1, 0, rect, 1);
	}

	g_pEvent->DrawButtons();
	g_lastPhase = phase;
	g_pPixmap->MouseBackDraw();
}

// Restitue le jeu après une activation en mode fullScreen.

BOOL RestoreGame()
{
	if (g_pPixmap == NULL) return FALSE;

	g_pEvent->RestoreGame();
	return g_pPixmap->Restore();
}

// Libère le jeu avant une désactivation en mode fullScreen.

BOOL FlushGame()
{
	if (g_pPixmap == NULL) return FALSE;

	return g_pPixmap->Flush();
}

// Finished with all objects we use; release them.

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

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	static HINSTANCE   hInstance;
	POINT 			   mousePos, totalDim, iconDim;

#if 0
	if (message != WM_TIMER)
	{
		char s[100];
		sprintf(s, "message=%d,%d\n", message, wParam);
		OutputDebug(s);
	}
#endif

	// La touche F10 envoie un autre message pour activer
	// le menu dans les applications Windows standard !
	//[The F10 key sends another message to activate the menu in standard Windows apps!]
	if (message == WM_SYSKEYDOWN && wParam == VK_F10)
	{
		message = WM_KEYDOWN;
	}
	if (message == WM_SYSKEYUP && wParam == VK_F10)
	{
		message = WM_KEYUP;
	}

	if (g_pEvent != NULL &&
		g_pEvent->TreatEvent(message, wParam, lParam)) return 0;

	switch (message)
	{
	case WM_TIMER:
	case WM_UPDATE:
		if (g_pEvent != NULL && !g_pEvent->IsMovie() && !g_pEvent->IsMouseRelease())  // pas de film en cours ?
		{
			g_pEvent->GetPhase(); // ?
			if (g_bActive)
			{
				UpdateFrame();
				SetDecor();
			}
			g_pPixmap->Display();
		}
		if (g_something > 0) g_something--;
		break;
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
		if (g_bActive)
		{
			if (g_bFullScreen)
			{
				RestoreGame();
				g_lastPhase = 999;
			}
			if (!g_bFullScreen && g_bTermInit)
			{
				g_pPixmap->BackgroundCache(CHLITTLE, "little.blp", { 256, 96 }, { DIMLITTLEX , DIMLITTLEY }, TRUE);
				g_pPixmap->SetTransparent(CHLITTLE, RGB(0, 0, 255)); // bleu

				g_pPixmap->SavePalette();
				g_pPixmap->InitSysPalette();
			}
			SetWindowText(hWnd, "Blupi");
			if (g_pSound != NULL) g_pSound->RestartMusic();
		}
		else // désactive ?
		{
			if (g_bFullScreen)
			{
				FlushGame();
			}
			SetWindowText(hWnd, "Blupi -- stop");
			if (g_pSound != NULL) g_pSound->SuspendMusic();
		}
		return 0;

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
		if (g_pEvent->IsMovie()) // film en cours ?
		{
			if (wParam == MCI_NOTIFY_SUCCESSFUL)
			{
				g_pEvent->StopMovie();
			}
		}
		else
		{
			// music over, play it again
			g_pSound->SuspendMusic();
			// if music finished, play it again. Otherwise assume that
			// it was aborted by the user or otherwise
			if (wParam == MCI_NOTIFY_SUCCESSFUL)
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

	case WM_SETCURSOR:
		//			ChangeSprite();
		//			SetCursor(NULL); // pas de souris visible !
		return TRUE;

	case WM_LBUTTONDOWN:
		//?			Benchmark();
		GetCursorPos(&mousePos);
		ScreenToClient(hWnd, &mousePos);
		break;

	case WM_RBUTTONDOWN:
		break;

	case WM_MOUSEMOVE:
		break;

	case WM_KEYDOWN:
		switch (wParam)
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

	case WM_DESTROY:
#if MMTIMER
		timeKillEvent((UINT)g_updateTimer);
#else
		KillTimer(g_hWnd, 1);
#endif
		FinishObjects();
		PostQuitMessage(0);
		break;

	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

void CALLBACK TimerStep(UINT wTimerID, UINT msg,
	DWORD dwUser, DWORD dw1, DWORD dw2)
{
	char buf[20];
	sprintf(buf, "%d", wTimerID);
	OutputDebug(buf);
	if (g_bActive && g_timer == 0)
	{
		g_timer = 1;
		PostMessage(g_hWnd, WM_UPDATE, 0, 0);
	}
}

// Erreur dans DoInit.

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
	struct timeb tstruct;
	int        i, j, t1, t2, time;
	RECT    rect;
	POINT    dest;
	_MEMORYSTATUS mem;

	ftime(&tstruct);
	t1 = tstruct.millitm;

	for (j = 0; j < 10; j++)
	{
		UpdateFrame();
		SetDecor();
		g_pPixmap->Display();
	}

	ftime(&tstruct);
	t2 = tstruct.millitm;

	if (t1 > t2)  t2 += 1000;
	time = t2 - t1;

	mem.dwLength = 32;
	GlobalMemoryStatus(&mem);
	FILE* file = NULL;
	char        string[100];
	sprintf(string, "CheckTime = %d Memory = %d\r\n", time, mem.dwTotalPhys);
	file = fopen("data\\time.blp", "wb");
	if (file == NULL)  return time;
	fwrite(string, strlen(string), 1, file);
	fclose(file);

	return time;
}

static BOOL DoInit(HINSTANCE hInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSA 	   wc;
	POINT		   totalDim, iconDim;
	RECT		   rcRect;
	BOOL 		   bOK;

	bOK = ReadConfig(lpCmdLine);  // lit le fichier config.def

	InitHInstance(hInstance);

	// Set up and register window class.
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	//?	wc.hIcon         = LoadIcon(hInstance, IDI_APPLICATION);
	wc.hIcon = LoadIcon(hInstance, "IDR_MAINFRAME");
	wc.hCursor = LoadCursor(hInstance, "IDC_POINTER");
	wc.hbrBackground = GetStockBrush(BLACK_BRUSH);
	wc.lpszMenuName = NAME;
	wc.lpszClassName = NAME;
	RegisterClassA(&wc);

	// Create a window.
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

	ChangeSprite(SPRITE_WAIT);  // met le sablier maison

	if (!bOK)  // config.def pas correct ?
	{
		return InitFail("Game not correctly installed", FALSE);
	}

	// Crée le pixmap principal.
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

	if (!g_pPixmap->CacheAll(TRUE, g_hWnd, g_bFullScreen, g_bTrueColorBack, g_bTrueColorDecor, g_mouseType, "init.blp", 0))
		return FALSE;
	OutputDebug("SavePalette\n");
	g_pPixmap->SavePalette();
	OutputDebug("InitSysPalette\n");
	g_pPixmap->InitSysPalette();

	g_pSound = new CSound;
	if (g_pSound == NULL) return InitFail("New sound", TRUE);

	g_pSound->Create(g_hWnd);
	g_pSound->CacheAll();
	g_pSound->SetState(TRUE);
	g_pSound->SetCDAudio(g_bCDAudio);

	g_pMovie = new CMovie;
	if (g_pMovie == NULL) return InitFail("New movie", FALSE);

	g_pMovie->Create();

	g_pDecor = new CDecor;
	if (g_pDecor == NULL) return InitFail("New decor", FALSE);

	g_pDecor->Create(g_hWnd, g_pSound, g_pPixmap, g_pNetwork);

	g_pEvent = new CEvent;
	if (g_pEvent == NULL) return InitFail("New event", FALSE);

	g_pEvent->Create(hInstance, g_hWnd, g_pPixmap, g_pDecor, g_pSound, g_pNetwork, g_pMovie);
	g_pEvent->SetFullScreen(g_bFullScreen);
	g_pEvent->SetMouseType(g_mouseType);

	g_pNetwork = new CNetwork;
	if (g_pNetwork == NULL) return InitFail("New network", TRUE);
	g_pNetwork->CreateProvider(0);

#if _INTRO
	g_pEvent->ChangePhase(WM_PHASE_INTRO1);
#else
	g_pEvent->ChangePhase(WM_PHASE_INIT);
#endif

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
	
#if MMTIMER
	g_updateTimer = timeSetEvent(g_timerInterval, g_timerInterval / 4, TimerStep, NULL, TIME_PERIODIC);
#else
	SetTimer(g_hWnd, 1, g_timerInterval, NULL);
#endif

#if THREAD
	g_hScreenMutex = CreateMutex(NULL, FALSE, NULL);
	g_hRunMutex = CreateMutex(NULL, TRUE, NULL);
	g_threadNr = 0;

	g_hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadDisplay, 0, DETACHED_PROCESS, &g_threadID);
#endif

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
			// make sure we go to sleep if we have nothing else to do
			if ( !g_bActive ) WaitMessage();
		}
	}

	return msg.wParam;
}

#if THREAD
// Thread d'affichage.

static void ThreadDisplay(char* MyID)
{
	UINT    phase;

	do
	{
		phase = g_pEvent->GetPhase();
		if (phase == WM_PHASE_PLAY)
		{
			// Wait for display to be available, then lock it.
			WaitForSingleObject(g_hScreenMutex, INFINITE);

			SetDecor();
			g_pPixmap->Display();

			// Clear screen lock.
			ReleaseMutex(g_hScreenMutex);
		}
	}
	// Repeat while RunMutex is still taken.
	while (WaitForSingleObject(g_hRunMutex, 10L) == WAIT_TIMEOUT);
}
#endif
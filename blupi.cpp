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

	return TRUE;
}
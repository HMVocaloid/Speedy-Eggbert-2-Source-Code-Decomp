// Misc.cpp
//


#include <dsound.h>
#include <ddraw.h>
#include <stdio.h>
#include <stdlib.h>
#include "def.h"


// Global Variables

HINSTANCE      g_hInstance;
int            g_lastSprite = 0;
extern BOOL    g_bFullScreen;
extern int     g_mouseType;
extern char    g_CDPath[MAX_PATH];

//Initalize HInstance.

void InitHInstance(HINSTANCE hInstance)
{
    g_hInstance = hInstance;
}

void OutputDebug(char *pMessage)
{
#ifdef _DEBUG
    OutputDebugString(pMessage);
#endif
}

void LoadString(UINT nID, char *pBuffer, int lgBuffer)
{
    LoadString(g_hInstance, nID, pBuffer, lgBuffer);
}

void ChangeSprite(int sprite)
{
	HCURSOR		hCursor = nullptr;

	if ( g_mouseType == MOUSETYPEGRA )  return;
	if ( g_lastSprite == sprite )  return;

	if ( sprite == SPRITE_ARROW   )  hCursor = LoadCursor(g_hInstance, "IDC_ARROW");
	if ( sprite == SPRITE_POINTER )  hCursor = LoadCursor(g_hInstance, "IDC_POINTER");
	if ( sprite == SPRITE_MAP     )  hCursor = LoadCursor(g_hInstance, "IDC_MAP");
	if ( sprite == SPRITE_ARROWU  )  hCursor = LoadCursor(g_hInstance, "IDC_ARROWU");
	if ( sprite == SPRITE_ARROWD  )  hCursor = LoadCursor(g_hInstance, "IDC_ARROWD");
	if ( sprite == SPRITE_ARROWL  )  hCursor = LoadCursor(g_hInstance, "IDC_ARROWL");
	if ( sprite == SPRITE_ARROWR  )  hCursor = LoadCursor(g_hInstance, "IDC_ARROWR");
	if ( sprite == SPRITE_ARROWUL )  hCursor = LoadCursor(g_hInstance, "IDC_ARROWUL");
	if ( sprite == SPRITE_ARROWUR )  hCursor = LoadCursor(g_hInstance, "IDC_ARROWUR");
	if ( sprite == SPRITE_ARROWDL )  hCursor = LoadCursor(g_hInstance, "IDC_ARROWDL");
	if ( sprite == SPRITE_ARROWDR )  hCursor = LoadCursor(g_hInstance, "IDC_ARROWDR");
	if ( sprite == SPRITE_WAIT    )  hCursor = LoadCursor(g_hInstance, "IDC_WAIT");
	if ( sprite == SPRITE_EMPTY   )  hCursor = LoadCursor(g_hInstance, "IDC_EMPTY");
	if ( sprite == SPRITE_FILL    )  hCursor = LoadCursor(g_hInstance, "IDC_FILL");
	SetCursor(hCursor);

	g_lastSprite = sprite;
}

POINT ConvLongToPos(LPARAM lParam)
{
    POINT   pos;

    pos.x = LOWORD(lParam);
    pos.y = HIWORD(lParam);

    return;
}

void InitRandom()
{
    srand(1);
}

int Random(int min, int max)
{
    long    n;

    n = rand();
    n = min+(n%(max-min+1));

    return (int)n;
}

void GetCurrentDir(char *pName, int lg)
{
	int		i;

	strncpy(pName, _pgmptr, lg-1);
	pName[lg-1] = 0;

	lg = strlen(pName);
	if ( lg == 0 )  return;

	for ( i=0 ; i<lg ; i++ )
	{
		pName[i] = tolower(pName[i]);
	}

	while ( lg > 0 )
	{
		lg --;
		if ( pName[lg] == '\\' )
		{
			pName[lg+1] = 0;
			break;
		}
	}

	if ( lg > 6 && strcmp(pName+lg-6, "\\debug\\") == 0 )
	{
		pName[lg-5] = 0;  // ignore le dossier \debug !
	}
}

void AddCDPath(char *pFilename)
{
	char	temp[MAX_PATH];
	int		lg;
	BOOL	bDaniel = FALSE;

	if ( g_CDPath[0] == 0 )  return;

	lg = strlen(g_CDPath);
	if ( lg > 14 && strstr(g_CDPath+lg-14, "\\daniel\\blupi\\") )
	{
		bDaniel = TRUE;
	}

#if _DEMO
	strcpy(temp, g_CDPath);
	strcat(temp, pFilename);
#else
	if ( !bDaniel &&
		 (strstr(pFilename, "image08\\") == pFilename ||
          strstr(pFilename, "data\\") == pFilename    ||
		  strstr(pFilename, "image16\\") == pFilename ||
          strstr(pFileName, "sound\\")) )
	{
		strcpy(temp, g_CDPath);
		strcat(temp, "..\\");
		strcat(temp, pFilename);
	}
	else
	{
		strcpy(temp, g_CDPath);
		strcat(temp, pFilename);
	}
#endif

	strcpy(pFilename, temp);
}
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


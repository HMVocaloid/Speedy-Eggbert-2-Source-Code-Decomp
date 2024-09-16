/*==========================================================================
 *
 *  Copyright (C) 1995 Microsoft Corporation. All Rights Reserved.
 *
 *  File:       ddutil.cpp
 *  Content:    Routines for loading bitmap and palettes from resources
 *
 ***************************************************************************/

#define DIRECTDRAW_VERSION 0x0500

using namespace std;

#pragma once
#include <ddraw.h>

#ifdef __cplusplus
extern "C" {            /* Assume C declarations for C++ */
#endif	/* __cplusplus */

extern void DDSetDebug(BOOL bDebug);
extern IDirectDrawPalette * DDLoadPalette(IDirectDraw *pdd, LPCSTR szBitmap);
extern IDirectDrawSurface * DDLoadBitmap(IDirectDraw *pdd, LPCSTR szBitmap, int dx, int dy);
extern HRESULT              DDReLoadBitmap(IDirectDrawSurface *pdds, LPCSTR szBitmap);
extern HRESULT              DDCopyBitmap(IDirectDrawSurface *pdds, HBITMAP hbm, int x, int y, int dx, int dy);
extern DWORD                DDColorMatch(IDirectDrawSurface *pdds, COLORREF rgb);
extern HRESULT              DDSetColorKey(IDirectDrawSurface *pdds, COLORREF rgb);
extern HRESULT              DDSetColorKey2(IDirectDrawSurface* pdds, COLORREF rgb1, COLORREF rgb2);

#ifdef __cplusplus
}
#endif	/* __cplusplus */

// CPixmap.cpp
//

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <ddraw.h>
#include <time.h>
#include <sys/timeb.h>
#include "def.h"
#include "pixmap.h"
#include "misc.h"
#include "ddutil.h"
#include "pixtables.h"

#define DIRECTDRAW_VERSION 0x0500

#pragma comment(lib, "ddraw.lib")


/////////////////////////////////////////////////////////////////////////////


// Constructeur.

CPixmap::CPixmap()
{
	int		i;
	
	m_bFullScreen  = FALSE;
	m_bBenchmarkSuccess = TRUE;
	m_bTrueColorBack   = FALSE;
	m_bTrueColorDecor = FALSE;
	m_mouseType    = MOUSETYPEGRA;
	m_bDebug       = TRUE;
	m_bPalette     = TRUE;

	m_mouseSprite  = SPRITE_WAIT;
	MouseHotSpot();
	m_mousePos.x   = LXIMAGE/2;
	m_mousePos.y   = LYIMAGE/2;
	m_mouseBackPos = m_mousePos;
	m_bMouseBack   = FALSE;
	m_bMouseShow   = TRUE;
	m_bBackDisplayed = FALSE;

	m_lpDD         = NULL;
	m_lpDDSPrimary = NULL;
	m_lpDDSBack    = NULL;
	m_lpDDSMouse   = NULL;
	m_lpDDPal      = NULL;
	m_lpClipper    = NULL;

	for ( i=0 ; i<MAXIMAGE ; i++ )
	{
		m_lpDDSurface[i] = NULL;
	}

	// initialize special effects structure
	ZeroMemory(&m_DDbltfx, sizeof(m_DDbltfx));
	m_DDbltfx.dwSize = sizeof(m_DDbltfx);   
}

// Destructeur.

CPixmap::~CPixmap()
{
	int		i;

    if ( m_lpDD != NULL )
    {
        if ( m_lpDDSPrimary != NULL )
        {
            m_lpDDSPrimary->Release();
            m_lpDDSPrimary = NULL;
        }

		if ( m_lpDDSBack != NULL )
		{
			m_lpDDSBack->Release();
			m_lpDDSBack = NULL;
		}

		if ( m_lpDDSMouse != NULL )
		{
			m_lpDDSMouse->Release();
			m_lpDDSMouse = NULL;
		}

        if ( m_lpDDPal != NULL )
        {
            m_lpDDPal->Release();
            m_lpDDPal = NULL;
        }

		for ( i=0 ; i<MAXIMAGE ; i++ )
		{
			if ( m_lpDDSurface[i] != NULL )
			{
				m_lpDDSurface[i]->Release();
				m_lpDDSurface[i]= NULL;
			}
		}

		if ( m_lpClipper != NULL )
		{
			m_lpClipper->Release();
			m_lpClipper = NULL;
		}

        m_lpDD->Release();
        m_lpDD = NULL;
    }
}


void CPixmap::SetDebug(BOOL bDebug)
{
	m_bDebug = bDebug;
	DDSetDebug(bDebug);
}


// Cr�e l'objet DirectDraw principal.
// Retourne FALSE en cas d'erreur.

BOOL CPixmap::Create(HWND hwnd, POINT dim,
					 BOOL bFullScreen, int mouseType, BOOL bTrueColorDecor, BOOL bTrueColor)
{
	DDSURFACEDESC		ddsd;
	int					devcap;
	HRESULT				ddrval;
	POINT				pos;
	HDC					hdc;
	DWORD				colorMode;

	hdc = CreateCompatibleDC(NULL);

	if (hdc == NULL)
	{
		bTrueColor = 0;
		bTrueColorDecor = 0;
	}
	else
	{
		devcap = GetDeviceCaps(hdc, SIZEPALETTE);
		if ((devcap != NULL) && (devcap < 257))
		{
			bTrueColor = 0;
			bTrueColorDecor = 0;
		}
		DeleteDC(hdc);
	}

	m_hWnd        = hwnd;
	m_bFullScreen = bFullScreen;
	m_mouseType   = mouseType;
	m_dim         = dim;
	m_bTrueColorDecor = bTrueColorDecor;
	m_bTrueColorBack = bTrueColor;

	if ( m_mouseType == MOUSETYPEGRA )
	{
		// Cache d�finitivement la vilaine souris Windows.
		ShowCursor(FALSE);

		pos = m_mousePos;
		ClientToScreen(m_hWnd, &pos);
		SetCursorPos(pos.x, pos.y);  // met la souris au centre
	}

	m_clipRect.left   = 0;
	m_clipRect.top    = 0;
	m_clipRect.right  = dim.x;
	m_clipRect.bottom = dim.y;

	// Create the main DirectDraw object
    ddrval = DirectDrawCreate(NULL, &m_lpDD, NULL);
    if ( ddrval != DD_OK )
    {
		OutputDebug("Fatal error: DirectDrawCreate\n");
        return FALSE;
    }

    // Get exclusive mode.
	if ( m_bFullScreen )
	{
		ddrval = m_lpDD->SetCooperativeLevel(hwnd, DDSCL_EXCLUSIVE|DDSCL_FULLSCREEN);
	}
	else
	{
	    ddrval = m_lpDD->SetCooperativeLevel(hwnd, DDSCL_NORMAL);
	}
    if ( ddrval != DD_OK )
    {
		OutputDebug("Fatal error: SetCooperativeLevel\n");
        return FALSE;
    }

    // Set the video mode to 640x480x8.
	if ( m_bFullScreen != FALSE)
	{
		if ((bTrueColor != 0) || (colorMode = 8, bTrueColorDecor != FALSE))
		{
			colorMode = 16;
		}

		ddrval = m_lpDD->SetDisplayMode(dim.x, dim.y, colorMode);
		if ( ddrval != DD_OK )
		{
			OutputDebug("Fatal error: SetDisplayMode\n");
			return FALSE;
		}
	}

    // Create the primary surface with 1 back buffer.
	ZeroMemory(&ddsd, sizeof(ddsd));
    ddsd.dwSize         = sizeof(ddsd);
    ddsd.dwFlags        = DDSD_CAPS;
	ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;

    ddrval = m_lpDD->CreateSurface(&ddsd, &m_lpDDSPrimary, NULL);
    if ( ddrval != DD_OK )
    {
		TraceErrorDD(ddrval, "pixmap", 0);
		OutputDebug("Fatal error: CreateSurface\n");
        return FALSE;
    }
	
	// Create the back buffer.
	ZeroMemory(&ddsd, sizeof(ddsd));
	ddsd.dwSize         = sizeof(ddsd);
	ddsd.dwFlags        = DDSD_CAPS|DDSD_HEIGHT|DDSD_WIDTH;
//?	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
	ddsd.ddsCaps.dwCaps = DDSCAPS_SYSTEMMEMORY;
	ddsd.dwWidth        = dim.x;
	ddsd.dwHeight       = dim.y;

	ddrval = m_lpDD->CreateSurface(&ddsd, &m_lpDDSBack, NULL);
	if ( ddrval != DD_OK )
	{
		TraceErrorDD(ddrval, "pixmap", 0);
		OutputDebug("Fatal error: CreateBackSurface\n");
		return FALSE;
	}

	// Create the mouse buffer.
	ZeroMemory(&ddsd, sizeof(ddsd));
	ddsd.dwSize         = sizeof(ddsd);
	ddsd.dwFlags        = DDSD_CAPS|DDSD_HEIGHT|DDSD_WIDTH;
//?	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
	ddsd.ddsCaps.dwCaps = DDSCAPS_SYSTEMMEMORY;
	ddsd.dwWidth        = DIMBLUPIX;
	ddsd.dwHeight       = DIMBLUPIY;

	ddrval = m_lpDD->CreateSurface(&ddsd, &m_lpDDSMouse, NULL);
	if ( ddrval != DD_OK )
	{
		TraceErrorDD(ddrval, "pixmap", 0);
		OutputDebug("Fatal error: CreateMouseSurface\n");
		return FALSE;
	}

	// Create a DirectDrawClipper object. The object enables clipping to the 
	// window boundaries in the IDirectDrawSurface::Blt function for the 
	// primary surface.
	if ( !m_bFullScreen )
	{
		ddrval = m_lpDD->CreateClipper(0, &m_lpClipper, NULL);
		if ( ddrval != DD_OK )
		{
			TraceErrorDD(ddrval, "pixmap", 0);
			OutputDebug("Can't create clipper\n");
			return FALSE;
		}

		ddrval = m_lpClipper->SetHWnd(0, hwnd);
		if ( ddrval != DD_OK )
		{
			TraceErrorDD(ddrval, "pixmap", 0);
			OutputDebug("Can't set clipper window handle\n");
			return FALSE;
		}

		ddrval = m_lpDDSPrimary->SetClipper(m_lpClipper);
		if ( ddrval != DD_OK )
		{
			TraceErrorDD(ddrval, "pixmap", 0);
			OutputDebug("Can't attach clipper to primary surface\n");
			return FALSE;
		}
    }

    return TRUE;
}

// Lib�re les bitmaps.

BOOL CPixmap::Flush()
{
	return TRUE;
}

// Restitue les bitmaps.

BOOL CPixmap::Restore()
{
	RestoreAll();
	return TRUE;
}

void CPixmap::QuickIcon(int channel, int rank, POINT pos)
{
	int num;
	RECT rect;

	if (channel == CHOBJECT)
	{
		if (table_icon_object[0] <= rank) return;
		rect.left = table_icon_object[rank * 6 + 0 + 1];
		rect.top = table_icon_object[rank * 6 + 1 + 1];
		rect.right = rect.left + table_icon_object[rank * 6 + 4 + 1];
		rect.bottom = rect.top + table_icon_object[rank * 6 + 5 + 1];
		pos.x += table_icon_object[rank * 6 + 2 + 1];
		pos.y += table_icon_object[rank * 6 + 3 + 1];
	}
	else if (channel == CHELEMENT)
	{
		if (table_icon_element[0] <= rank) return;
		rect.left = table_icon_element[rank * 6 + 0 + 1];
		rect.top = table_icon_element[rank * 6 + 1 + 1];
		rect.right = rect.left + table_icon_element[rank * 6 + 4 + 1];
		rect.bottom = rect.top + table_icon_element[rank * 6 + 5 + 1];
		pos.x += table_icon_element[rank * 6 + 2 + 1];
		pos.y += table_icon_element[rank * 6 + 3 + 1];
	}
	else if (IsBlupiChannel(channel))
	{
		if (table_icon_blupi[0] <= rank) return;
		rect.left = table_icon_blupi[rank * 6 + 0 + 1];
		rect.top = table_icon_blupi[rank * 6 + 1 + 1];
		rect.right = rect.left + table_icon_blupi[rank * 6 + 4 + 1];
		rect.bottom = rect.top + table_icon_blupi[rank * 6 + 5 + 1];
		pos.x += table_icon_blupi[rank * 6 + 2 + 1];
		pos.y += table_icon_blupi[rank * 6 + 3 + 1];
	}
	else if (channel == CHEXPLO)
	{
		if (table_icon_explo[0] <= rank) return;
		rect.left = table_icon_explo[rank * 6 + 0 + 1];
		rect.top = table_icon_explo[rank * 6 + 1 + 1];
		rect.right = rect.left + table_icon_explo[rank * 6 + 4 + 1];
		rect.bottom = rect.top + table_icon_explo[rank * 6 + 5 + 1];
		pos.x += table_icon_explo[rank * 6 + 2 + 1];
		pos.y += table_icon_explo[rank * 6 + 3 + 1];
	}
	else
	{
		rect.right = m_iconDim[channel].x;
		num = m_totalDim[channel].x / rect.right;
		rect.bottom = m_iconDim[channel].y;
		if (rank < 0)
		{
			return;
		}
		if ((m_totalDim[channel].y / rect.bottom) * num <= rank)
		{
			return;
		}
		rect.left = (rank % num) * rect.right;
		rect.right = rect.left + rect.right;
		rect.top = (rank / num) * rect.bottom;
		rect.bottom = rect.top + rect.bottom;
	}

	num = m_clipRect.left;
	if (pos.x < num)
	{
		num -= pos.x;
		pos.x = m_clipRect.left;
		rect.left += num;
	}
	num = (m_clipRect.right + rect.left) - pos.x;
	if (num < rect.right)
	{
		rect.right = num;
	}
	num = m_clipRect.top;
	if (pos.y < num)
	{
		num -= pos.y;
		pos.y = m_clipRect.top;
		rect.top += num;
	}
	num = (m_clipRect.bottom + rect.top) - pos.y;
	if (num < rect.bottom)
	{
		rect.bottom = num;
	}
	if (rect.left < rect.right && rect.top < rect.bottom)
	{
		while (TRUE)
		{
			num = m_lpDDSBack->BltFast(pos.x, pos.y, m_lpDDSurface[channel], &rect, 1);
			if (num == DD_OK) return;
			if (num == DDERR_SURFACELOST && RestoreAll() != DD_OK) return;
			if (num != DDERR_WASSTILLDRAWING) return;
		}
	}
	return;
}


// Initialise la palette syst�me.

BOOL CPixmap::InitSysPalette()
{
    HDC			hdc;
	int			caps;

    hdc = CreateCompatibleDC(NULL);
    if ( hdc == NULL )  return FALSE;

	if ( !m_bFullScreen )
	{
		caps = GetDeviceCaps(hdc, SIZEPALETTE);
		if ( caps == 0 )  m_bPalette = FALSE;
		else              m_bPalette = TRUE;
	}

	GetSystemPaletteEntries(hdc, 0, 256, m_sysPal);
    DeleteDC(hdc);
	return TRUE;
}

BOOL CPixmap::GetTrueColor()
{
	return m_bTrueColorBack;
}

BOOL CPixmap::GetTrueColorDecor()
{
	return m_bTrueColorDecor;
}

void CPixmap::SetBenchmarkSuccess(BOOL bSuccess)
{
	m_bBenchmarkSuccess = bSuccess;
}

void CPixmap::SetTrueColor(BOOL bTrueColor)
{
	m_bTrueColorBack = bTrueColor;
}

void CPixmap::SetTrueColorDecor(BOOL bTrueColorDecor)
{
	m_bTrueColorDecor = bTrueColorDecor;
}
/*
void CPixmap::DrawChar(int rank, POINT pos, double size)
{
	pos.x = (int)((double)pos.x + originX);
	pos.y = (int)((double)pos.y + originY);
	RECT rect;
	rect.left = pos.x,
		rect.top = pos.y,
		rect.right = pos.x + (int)(32.0 * size),
		rect.bottom = pos.y + (int)(32.0 * size);
	DrawIcon(6, rank, rect, 1.0, FALSE);
}
*/

// Indique si l'on utilise une palette.

BOOL CPixmap::IsPalette()
{
	return m_bPalette;
}


// Rempli une zone rectangulaire avec une couleur uniforme.

void CPixmap::Fill(RECT rect, COLORREF color)
{
	// � faire si n�cessaire ...
}


// Restore all lost objects.

HRESULT CPixmap::RestoreAll()
{
	if ( m_bDebug )  OutputDebug("CPixmap::RestoreAll\n");
	int			i;
	HRESULT     ddrval;

	if ( m_lpDDSPrimary && m_lpDDSPrimary->IsLost() )
	{
		ddrval = m_lpDDSPrimary->Restore();
//		if( ddrval != DD_OK )  return ddrval;
	}

	if ( m_lpDDSBack && m_lpDDSBack->IsLost() )
	{
		ddrval = m_lpDDSBack->Restore();
//		if( ddrval != DD_OK )  return ddrval;
	}

	if ( m_lpDDSMouse && m_lpDDSMouse->IsLost() )
	{
		ddrval = m_lpDDSMouse->Restore();
//		if( ddrval != DD_OK )  return ddrval;
	}

	for ( i=0 ; i<MAXIMAGE ; i++ )
	{
		if ( m_lpDDSurface[i] && m_lpDDSurface[i]->IsLost() )
		{
			ddrval = m_lpDDSurface[i]->Restore();
			if( ddrval == DD_OK )
			{
				DDReLoadBitmap(m_lpDDSurface[i], m_filename[i]);
			}
		}
	}
	return DD_OK;
}

// Effectue un appel BltFast.
// Les modes sont 0=transparent, 1=opaque.

HRESULT CPixmap::BltFast(int chDst, int channel,
						 POINT dst, RECT rcRect, int mode)
{
	DWORD		dwTrans;
    HRESULT		ddrval;
	int			limit;

	if ( mode == 0 )  dwTrans = DDBLTFAST_SRCCOLORKEY;
	else              dwTrans = DDBLTFAST_NOCOLORKEY;

	// Effectue un peu de clipping.
	if ( dst.x < m_clipRect.left )
	{
		rcRect.left += m_clipRect.left-dst.x;
		dst.x = m_clipRect.left;
	}
	limit = (m_clipRect.right-dst.x)+rcRect.left;
	if ( rcRect.right > limit )
	{
		rcRect.right = limit;
	}
	if ( dst.y < m_clipRect.top )
	{
		rcRect.top += m_clipRect.top-dst.y;
		dst.y = m_clipRect.top;
	}
	limit = (m_clipRect.bottom-dst.y)+rcRect.top;
	if ( rcRect.bottom > limit )
	{
		rcRect.bottom = limit;
	}

	if ( rcRect.left >= rcRect.right ||
		 rcRect.top  >= rcRect.bottom )  return DD_OK;

    while( TRUE )
    {
		if ( chDst < 0 )
		{
			ddrval = m_lpDDSBack->BltFast(dst.x, dst.y,
										  m_lpDDSurface[channel],
										  &rcRect, dwTrans);
		}
		else
		{
			ddrval = m_lpDDSurface[chDst]->BltFast(dst.x, dst.y,
										  m_lpDDSurface[channel],
										  &rcRect, dwTrans);
		}
        if ( ddrval == DD_OK )  break;
        
        if ( ddrval == DDERR_SURFACELOST )
        {
            ddrval = RestoreAll();
            if ( ddrval != DD_OK )  break;
        }

        if ( ddrval != DDERR_WASSTILLDRAWING )  break;
    }

	return ddrval;
}

// Effectue un appel BltFast.
// Les modes sont 0=transparent, 1=opaque.

HRESULT CPixmap::BltFast(LPDIRECTDRAWSURFACE lpDD,
						 int channel, POINT dst, RECT rcRect, int mode)
{
	DWORD		dwTrans;
    HRESULT		ddrval;

	if ( mode == 0 )  dwTrans = DDBLTFAST_SRCCOLORKEY;
	else              dwTrans = DDBLTFAST_NOCOLORKEY;

    while( TRUE )
    {
		ddrval = lpDD->BltFast(dst.x, dst.y,
							   m_lpDDSurface[channel],
							   &rcRect, dwTrans);
        if ( ddrval == DD_OK )  break;
        
        if ( ddrval == DDERR_SURFACELOST )
        {
            ddrval = RestoreAll();
            if ( ddrval != DD_OK )  break;
        }

        if ( ddrval != DDERR_WASSTILLDRAWING )  break;
    }

	return ddrval;
}

BOOL CPixmap::DrawMap(int channel, RECT src, RECT dest)
{
	HRESULT hErr;

	if ((channel < 0) || (channel > MAXIMAGE))
	{
		return FALSE;
	}

	

	while (TRUE)
	{
		hErr = DDERR_WASSTILLDRAWING;
		hErr = m_lpDDSurface[channel]->Blt(&dest, m_lpDDSBack, &src, DDBLT_WAIT, NULL);
		if (hErr == DD_OK) break;
		if (hErr == DDERR_SURFACELOST) hErr = RestoreAll(); if (hErr != DD_OK) break;;
	}
	return (hErr == DD_OK);
}

// Sauve toute la palette de couleurs.

BOOL CPixmap::SavePalette()
{
    HRESULT     ddrval;

	if ( m_lpDDPal == NULL )  return FALSE;

    ddrval = m_lpDDPal->GetEntries(0, 0, 256, m_pal);

	if ( ddrval != DD_OK )  return FALSE;
	return TRUE;
}

// Restitue toute la palette de couleurs.

BOOL CPixmap::RestorePalette()
{
    HRESULT     ddrval;

    ddrval = m_lpDDPal->SetEntries(0, 0, 256, m_pal);

	if ( ddrval != DD_OK )  return FALSE;
	return TRUE;
}

// Cherche une couleur dans la palette principale.
// En mode plein �cran, il faut chercher dans la palette
// correspondant aux images (obtenue avec SavePalette),
// alors qu'en mode fen�tre, il faut chercher dans la
// palette syst�me (obtenue avec InitSysPalette) !!!

int CPixmap::SearchColor(int red, int green, int blue)
{
	int		i, j, delta, min;

	if ( m_bFullScreen )
	{
		for ( i=0 ; i<256 ; i++ )
		{
			if ( red   == m_pal[i].peRed   &&
				 green == m_pal[i].peGreen &&
				 blue  == m_pal[i].peBlue  )  return i;
		}

		// Cherche la couleur la plus proche.
		min = 10000;
		j   = -1;
		for ( i=0 ; i<256 ; i++ )
		{
			delta = abs(red   - m_pal[i].peRed  )+
					abs(green - m_pal[i].peGreen)+
					abs(blue  - m_pal[i].peBlue );

			if ( delta < min )
			{
				min = delta;
				j = i;
			}
		}
	}
	else
	{
		if ( m_bPalette )
		{
			for ( i=0 ; i<256 ; i++ )
			{
				if ( red   == m_sysPal[i].peRed   &&
					 green == m_sysPal[i].peGreen &&
					 blue  == m_sysPal[i].peBlue  )  return i;
			}

			// Cherche la couleur la plus proche.
			min = 10000;
			j   = -1;
			for ( i=0 ; i<256 ; i++ )
			{
				delta = abs(red   - m_sysPal[i].peRed  )+
						abs(green - m_sysPal[i].peGreen)+
						abs(blue  - m_sysPal[i].peBlue );

				if ( delta < min )
				{
					min = delta;
					j = i;
				}
			}
		}
		else
		{
			j  =  (blue >>3)     &0x001F;
			j |= ((green>>2)<< 5)&0x07E0;
			j |= ((red  >>3)<<11)&0xF800;  // mode 5-6-5
//?			j  =  (blue >>3)     &0x001F;
//?			j |= ((green>>3)<< 5)&0x03E0;
//?			j |= ((red  >>3)<<10)&0x7C00;  // mode 5-5-5
		}
	}
	return j;
}


// Cache une image contenant des ic�nes.

/*
BOOL CPixmap::Cache(int channel, char *pFilename, POINT totalDim, POINT iconDim,
					BOOL bUsePalette)
{
    HRESULT     ddrval;

	if ( channel < 0 || channel >= MAXIMAGE )  return FALSE;

	if ( m_lpDDSurface[channel] != NULL )
	{
		Flush(channel);
	}

    // Create and set the palette.
	if ( bUsePalette )
	{
		if ( m_bDebug )  OutputDebug("Use palette\n");
		if ( m_lpDDPal != NULL )
		{
			if ( m_bDebug )  OutputDebug("Release palette\n");
			m_lpDDPal->Release();
			m_lpDDPal = NULL;
		}

		m_lpDDPal = DDLoadPalette(m_lpDD, pFilename);

		if ( m_lpDDPal )
		{
			if ( m_bDebug )  OutputDebug("Set palette\n");
			m_lpDDSPrimary->SetPalette(NULL);  // indispensable !
			ddrval = m_lpDDSPrimary->SetPalette(m_lpDDPal);
			if ( ddrval != DD_OK )
			{
				TraceErrorDD(ddrval, pFilename, 1);
			}
		}
	}

    // Create the offscreen surface, by loading our bitmap.
    m_lpDDSurface[channel] = DDLoadBitmap(m_lpDD, pFilename, 0, 0);

    if ( m_lpDDSurface[channel] == NULL )
    {
		OutputDebug("Fatal error: DDLoadBitmap\n");
        return FALSE;
    }

    // Set the color key to white
	if ( m_bDebug )  OutputDebug("DDSetColorKey\n");
    DDSetColorKey(m_lpDDSurface[channel], RGB(255,255,255));  // blanc
	
	strcpy(m_filename[channel], pFilename);

	m_totalDim[channel] = totalDim;
	m_iconDim[channel]  = iconDim;

	return TRUE;
}
*/

// Cache une image globale.

BOOL CPixmap::Cache2(int channel, LPCSTR pFilename, POINT totalDim, POINT iconDim, BOOL bUsePalette)
{
	HRESULT		hErr;


	if ((channel < 0) || (channel >= MAXIMAGE))
	{
		return FALSE;
	}

	if (m_lpDDSurface[channel] != NULL)
	{
		Flush(channel);
	}

	if ( bUsePalette )
	{
		if ( m_bDebug ) OutputDebug("Use Palette\n");
		if (m_lpDDPal != NULL)
		{
			if ( m_bDebug ) OutputDebug("Release palette\n");
			m_lpDDPal->Release();
			m_lpDDPal = NULL;
		}
	}
	m_lpDDPal = DDLoadPalette(m_lpDD, pFilename);
	
	if ( m_lpDDPal )
	{
		if ( m_bDebug ) OutputDebug("Set palette\n");
		m_lpDDSPrimary->SetPalette(NULL);
		hErr = (m_lpDDSPrimary->SetPalette(m_lpDDPal));
		if (hErr != DD_OK)
		{
			TraceErrorDD(hErr, pFilename, 1);
		}
	}
	m_lpDDSurface[channel] = DDLoadBitmap(m_lpDD, pFilename, 0, 0);
	if (m_lpDDSurface[channel] == NULL)
	{
		OutputDebug("Fatal error: DDLoadBitmap\n");
		return FALSE;
	}
	if ( m_bDebug ) OutputDebug("DDSetColorKey\n");
	DDSetColorKey(m_lpDDSurface[channel], RGB(255, 255, 255));

	strcpy(m_filename[channel], pFilename);

	m_totalDim[channel] = totalDim;
	m_iconDim[channel] = iconDim;

	return TRUE;
}

// Cache une image provenant d'un bitmap.

// Probably not needed?


/*
BOOL CPixmap::Cache(int channel, HBITMAP hbm, POINT totalDim)
{
	if ( channel < 0 || channel >= MAXIMAGE )  return FALSE;

	if ( m_lpDDSurface[channel] != NULL )
	{
		Flush(channel);
	}

    // Create the offscreen surface, by loading our bitmap.
    m_lpDDSurface[channel] = DDConnectBitmap(m_lpDD, hbm);

    if ( m_lpDDSurface[channel] == NULL )
    {
		OutputDebug("Fatal error: DDLoadBitmap\n");
        return FALSE;
    }

    // Set the color key to white
    DDSetColorKey(m_lpDDSurface[channel], RGB(255,255,255));  // blanc
	
	m_totalDim[channel] = totalDim;
	m_iconDim[channel]  = totalDim;

	return TRUE;
}
*/

BOOL CPixmap::BackgroundCache(int channel, const char* pFilename, POINT totalDim, POINT iconDim, BOOL bUsePalette)
{	
	BOOL decor;
	char file[100];

	decor = strstr(pFilename, "blupi") != pFilename &&
		strstr(pFilename, "element") != pFilename &&
		strstr(pFilename, "explo") != pFilename &&
		strstr(pFilename, "object") != pFilename;
	if (!bUsePalette && (!decor || m_bTrueColorBack))
	{
		strcpy(file, "image16\\");
		strcat(file, pFilename);
		if (Cache2(channel, file, totalDim, iconDim, FALSE))
		{
			return TRUE;
		}
	}
	strcpy(file, "image08\\");
	strcat(file, pFilename);
	return Cache2(channel, file, totalDim, iconDim, bUsePalette);
}

BOOL CPixmap::CacheAll(BOOL cache, HWND hWnd, BOOL bFullScreen, BOOL bTrueColor, BOOL bTrueColorDecor, int mouseType, const char* pFilename, int region)
{
	SetDebug(TRUE);
	char filename[100];
	char image[12];
	POINT totalDim;
	POINT iconDim;
	RECT rect;
	POINT dim;


	totalDim.x = 640;
	totalDim.y = 480;
	iconDim.x = 0;
	iconDim.y = 0;

	dim.x = LXIMAGE;
	dim.y = LYIMAGE;

	if (cache == FALSE)
	{
		delete this;
		hWnd = m_hWnd;
		bFullScreen = m_bFullScreen;
		bTrueColor = m_bTrueColorBack;
		bTrueColorDecor = m_bTrueColorDecor;
		mouseType = m_mouseType;
	}

	if (Create(hWnd, dim, bFullScreen, mouseType, bTrueColorDecor, bTrueColor) == FALSE)
	{
		return FALSE;
	}

	OutputDebug("Image:_init\n");
	if (BackgroundCache(0, "init.blp", totalDim, iconDim, TRUE) == FALSE)
	{
		return FALSE;
	}

	OutputDebug("SavePalette\n");
	SavePalette();
	OutputDebug("InitSysPalette\n");
	InitSysPalette();

	if (cache == FALSE)
	{
		if (BackgroundCache(0, pFilename, totalDim, iconDim, FALSE) == FALSE)
		{
			return FALSE;
		}
	}
	else
	{
		*(char*)image = (LXIMAGE) << 64;
		rect.bottom = LYIMAGE;
		rect.left = LOWORD(image);
		rect.top = HIWORD(image);
		rect.right = HIWORD(image);
		DrawImage(0, 0, rect, 1);
		Display();
	}
	totalDim.x = 1024;
	totalDim.y = 1280;
	iconDim.x = 64;
	iconDim.y = 64;
	if (!BackgroundCache(CHOBJECT, "object.blp", totalDim, iconDim, FALSE) )
	{
		return FALSE;
	}
	SetTransparent(CHOBJECT, RGB(0, 0, 255));
	totalDim.x = 960;
	totalDim.y = 1200;
	iconDim.x = 60;
	iconDim.y = 60;
	if (BackgroundCache(CHBLUPI, "blupi000.blp", totalDim, iconDim, FALSE) == FALSE)
	{
		return FALSE;
	}
	SetTransparent(CHBLUPI, RGB(0, 0, 255));
	totalDim.x = 960;
	totalDim.y = 1200;
	iconDim.x = 60;
	iconDim.y = 60;
	if (BackgroundCache(CHBLUPI1, "blupi001.blp", totalDim, iconDim, FALSE) == FALSE)
	{
		return FALSE;
	}
	SetTransparent(CHBLUPI1, RGB(0, 0, 255));
	totalDim.x = 960;
	totalDim.y = 1200;
	iconDim.x = 60;
	iconDim.y = 60;
	if (BackgroundCache(CHBLUPI2, "blupi002.blp", totalDim, iconDim, FALSE) == FALSE)
	{
		return FALSE;
	}
	SetTransparent(CHBLUPI2, RGB(0, 0, 255));
	totalDim.x = 960;
	totalDim.y = 1200;
	iconDim.x = 60;
	iconDim.y = 60;
	if (BackgroundCache(CHBLUPI3, "blupi003.blp", totalDim, iconDim, FALSE) == FALSE)
	{
		return FALSE;
	}
	SetTransparent(CHBLUPI3, RGB(0, 0, 255));
	totalDim.x = 64;
	totalDim.y = 64;
	iconDim.x = 64;
	iconDim.y = 64;
	if (BackgroundCache(CHTEMP, "temp.blp", totalDim, iconDim, FALSE) == FALSE)
	{
		return FALSE;
	}
	SetTransparent(CHTEMP, RGB(0, 0, 255));
	totalDim.x = 208;
	totalDim.y = 160;
	iconDim.x = 208;
	iconDim.y = 160;
	if (BackgroundCache(CHMAP, "map.blp", totalDim, iconDim, FALSE) == FALSE)
	{
		return FALSE;
	}
	SetTransparent(CHMAP, RGB(0, 0, 255));
	totalDim.x = 960;
	totalDim.y = 1200;
	iconDim.x = 60;
	iconDim.y = 60;
	if (BackgroundCache(CHELEMENT, "element.blp", totalDim, iconDim, FALSE) == FALSE)
	{
		return FALSE;
	}
	SetTransparent(CHELEMENT, RGB(0, 0, 255));
	totalDim.x = 2048;
	totalDim.y = 640;
	iconDim.x = 128;
	iconDim.y = 128;
	if (BackgroundCache(CHEXPLO, "explo.blp", totalDim, iconDim, FALSE) == FALSE)
	{
		return FALSE;
	}
	SetTransparent(CHEXPLO, RGB(0, 0, 255));
	sprintf(filename, "decor%.3d.blp", region);
	totalDim.x = LXIMAGE;
	totalDim.y = LYIMAGE;
	iconDim.x = 0;
	iconDim.y = 0;
	if (BackgroundCache(CHDECOR, filename, totalDim, iconDim, FALSE) == FALSE)
	{
		return FALSE;
	}
	totalDim.x = 240;
	totalDim.y = 1040;
	iconDim.x = 40;
	iconDim.y = 40;
	if (BackgroundCache(CHBUTTON, "button00.blp", totalDim, iconDim, FALSE) == FALSE)
	{
		return FALSE;
	}
	SetTransparent(CHBUTTON, RGB(0, 0, 255));
	totalDim.x = 124;
	totalDim.y = 88;
	iconDim.x = 124;
	iconDim.y = 22;
	if (BackgroundCache(CHJAUGE, "jauge.blp", totalDim, iconDim, FALSE) == FALSE)
	{
		return FALSE;
	}
	SetTransparent(CHJAUGE, RGB(0, 0, 255));
	totalDim.x = 256;
	totalDim.y = 384;
	iconDim.x = 16;
	iconDim.y = 16;
	if (BackgroundCache(CHTEXT, "text.blp", totalDim, iconDim, FALSE) != FALSE)
	{
		SetTransparent(CHTEXT, RGB(0, 0, 255));
		totalDim.x = 256;
		totalDim.y = 96;
		iconDim.x = 16;
		iconDim.y = 12;
		if (BackgroundCache(CHLITTLE, "little.blp", totalDim, iconDim, FALSE) != FALSE)
		{
			SetTransparent(CHLITTLE, RGB(0, 0, 255));
			Benchmark();
			return TRUE;
		}
		return FALSE;
	}
	return FALSE;
}

int CPixmap::Benchmark()
{
	timeb tstruct;
	int        i, j, t1, t2, time;
	RECT    rect;
	POINT    dest;

	ftime(&tstruct);
	t1 = tstruct.millitm;

	for (j = 0; j < 10; j++)
	{
		dest.x = POSDRAWX;
		dest.y = POSDRAWY;
		rect.left = 29;
		rect.right = 29 + LXIMAGE;
		rect.top = 29;
		rect.bottom = 29 + LYIMAGE;
		DrawPart(-1, CHDECOR, dest, rect, 1);

		dest.x = 13;  // position quelconque non-multiple de 16
		dest.y = 13;
		for (i = 0; i < 120; i++)
		{
			QuickIcon(CHOBJECT, 1, dest);
		}
	}

	ftime(&tstruct);
	t2 = tstruct.millitm;

	if (t1 > t2)  t2 += 1000;
	time = t2 - t1;

	FILE* file = NULL;
	char        string[100];
	sprintf(string, "Benchmark = %d\r\n", time);
	file = fopen("data\\bench.blp", "wb");
	if (file == NULL)  return time;
	fwrite(string, strlen(string), 1, file);
	fclose(file);

	return time;
}


// Purge une image.

void CPixmap::Flush(int channel)
{
	if ( channel < 0 || channel >= MAXIMAGE )  return;
	if (  m_lpDDSurface[channel] == NULL )     return;

	m_lpDDSurface[channel]->Release();
	m_lpDDSurface[channel]= NULL;
}

// D�finition de la couleur transparente.

void CPixmap::SetTransparent(int channel, COLORREF color)
{
	if ( channel < 0 || channel >= MAXIMAGE )  return;
	if (  m_lpDDSurface[channel] == NULL )     return;

    DDSetColorKey(m_lpDDSurface[channel], color);
	m_colorSurface[2*channel+0] = color;
	m_colorSurface[2*channel+1] = color;
}

// D�finition de la couleur transparente.

void CPixmap::SetTransparent2(int channel, COLORREF color1, COLORREF color2)
{
	if ( channel < 0 || channel >= MAXIMAGE )  return;
	if (  m_lpDDSurface[channel] == NULL )     return;

    DDSetColorKey2(m_lpDDSurface[channel], color1, color2);
	m_colorSurface[2*channel+0] = color1;
	m_colorSurface[2*channel+1] = color2;
}


// Modifie la r�gion de clipping.

void CPixmap::SetClipping(RECT clip)
{
	m_clipRect.left   = clip.left;
	m_clipRect.top    = clip.top;
	m_clipRect.right  = clip.right;
	m_clipRect.bottom = clip.bottom;
}

// Retourne la r�gion de clipping.

RECT CPixmap::GetClipping()
{
	return m_clipRect;
}


// Teste si un point fait partie d'une ic�ne.
//Rough rewritten code, might need improvement




// Dessine une partie d'image rectangulaire.
// Les modes sont 0=transparent, 1=opaque.

BOOL CPixmap::DrawIcon(int chDst, int channel, int rank, POINT pos,
					   int mode, BOOL bMask)
{
	int			nbx, nby;
	RECT		rect;
	HRESULT		ddrval;
	COLORREF	oldColor1, oldColor2;

	switch (channel)
	{
	case CHOBJECT:
		if (table_icon_object[0] <= rank) return FALSE;
		rect.left = table_icon_object[rank * 6 + 0 + 1];
		rect.top = table_icon_object[rank * 6 + 1 + 1];
		rect.right = rect.left + table_icon_object[rank * 6 + 4 + 1];
		rect.bottom = rect.top + table_icon_object[rank * 6 + 5 + 1];
		pos.x += table_icon_object[rank * 6 + 2 + 1];
		pos.y += table_icon_object[rank * 6 + 3 + 1];
		break;
	case CHELEMENT:
		if (table_icon_element[0] <= rank) return FALSE;
		rect.left = table_icon_element[rank * 6 + 0 + 1];
		rect.top = table_icon_element[rank * 6 + 1 + 1];
		rect.right = rect.left + table_icon_element[rank * 6 + 4 + 1];
		rect.bottom = rect.top + table_icon_element[rank * 6 + 5 + 1];
		pos.x += table_icon_element[rank * 6 + 2 + 1];
		pos.y += table_icon_element[rank * 6 + 3 + 1];
		break;
	
	case CHEXPLO:
		if (table_icon_explo[0] <= rank) return FALSE;
		rect.left = table_icon_explo[rank * 6 + 0 + 1];
		rect.top = table_icon_explo[rank * 6 + 1 + 1];
		rect.right = rect.left + table_icon_explo[rank * 6 + 4 + 1];
		rect.bottom = rect.top + table_icon_explo[rank * 6 + 5 + 1];
		pos.x += table_icon_explo[rank * 6 + 2 + 1];
		pos.y += table_icon_explo[rank * 6 + 3 + 1];
		break;
	}
	if (IsBlupiChannel(channel))
	{
		if (table_icon_blupi[0] <= rank) return FALSE;
		rect.left = table_icon_blupi[rank * 6 + 0 + 1];
		rect.top = table_icon_blupi[rank * 6 + 1 + 1];
		rect.right = rect.left + table_icon_blupi[rank * 6 + 4 + 1];
		rect.bottom = rect.top + table_icon_blupi[rank * 6 + 5 + 1];
		pos.x += table_icon_blupi[rank * 6 + 2 + 1];
		pos.y += table_icon_blupi[rank * 6 + 3 + 1];
	}
	else
	{
		if (channel < 0 || channel >= MAXIMAGE) return FALSE;
		if (m_lpDDSurface[channel] == NULL) return FALSE;
		if (m_iconDim[channel].x == 0 ||
			m_iconDim[channel].y == 0) return FALSE;

		nbx = m_totalDim[channel].x / m_iconDim[channel].x;
		nby = m_totalDim[channel].y / m_iconDim[channel].y;

		if (rank < 0 || rank >= nbx * nby) return FALSE;
	}

	rect.left   = (rank%nbx)*m_iconDim[channel].x;
	rect.top    = (rank/nbx)*m_iconDim[channel].y;
	rect.right  = rect.left + m_iconDim[channel].x;
	rect.bottom = rect.top  + m_iconDim[channel].y;

	oldColor1 = m_colorSurface[2*channel+0];
	oldColor2 = m_colorSurface[2*channel+1];
	if ( bMask )  SetTransparent(channel, RGB(255,255,255));  // blanc
	ddrval = BltFast(chDst, channel, pos, rect, mode);
	if ( bMask )  SetTransparent2(channel, oldColor1, oldColor2);

	if ( ddrval != DD_OK )  return FALSE;
	return TRUE;
}

// Dessine une partie d'image rectangulaire.
// Les modes sont 0=transparent, 1=opaque.
//
// Correspondances in,out :
//	 0,0	 2,1	...
//	 1,16	 3,17
//
//	32,32	34,33
//	33,48	35,49

BOOL CPixmap::DrawIconDemi(int chDst, int channel, int rank, POINT pos,
						   int mode, BOOL bMask)
{
	int			nbx, nby;
	RECT		rect;
	HRESULT		ddrval;
	COLORREF	oldColor1, oldColor2;

	if ( channel < 0 || channel >= MAXIMAGE )  return FALSE;
	if (  m_lpDDSurface[channel] == NULL )     return FALSE;

	if ( m_iconDim[channel].x == 0 ||
		 m_iconDim[channel].y == 0 )  return FALSE;

	nbx = m_totalDim[channel].x /  m_iconDim[channel].x;
	nby = m_totalDim[channel].y / (m_iconDim[channel].y/2);

	rank = (rank/32)*32+((rank%32)/2)+((rank%2)*16);

	if ( rank < 0 || rank >= nbx*nby )  return FALSE;

	rect.left   = (rank%nbx)* m_iconDim[channel].x;
	rect.top    = (rank/nbx)*(m_iconDim[channel].y/2);
	rect.right  = rect.left + m_iconDim[channel].x;
	rect.bottom = rect.top  +(m_iconDim[channel].y/2);

	oldColor1 = m_colorSurface[2*channel+0];
	oldColor2 = m_colorSurface[2*channel+1];
	if ( bMask )  SetTransparent(channel, RGB(255,255,255));  // blanc
	ddrval = BltFast(chDst, channel, pos, rect, mode);
	if ( bMask )  SetTransparent2(channel, oldColor1, oldColor2);

	if ( ddrval != DD_OK )  return FALSE;
	return TRUE;
}

// Dessine une partie d'image rectangulaire.
// Les modes sont 0=transparent, 1=opaque.

BOOL CPixmap::DrawIconPart(int chDst, int channel, int rank, POINT pos,
						   int startY, int endY,
						   int mode, BOOL bMask)
{
	int			nbx, nby;
	RECT		rect;
	HRESULT		ddrval;
	COLORREF	oldColor1, oldColor2;

	if ( channel < 0 || channel >= MAXIMAGE )  return FALSE;
	if (  m_lpDDSurface[channel] == NULL )     return FALSE;

	if ( m_iconDim[channel].x == 0 ||
		 m_iconDim[channel].y == 0 )  return FALSE;

	nbx = m_totalDim[channel].x / m_iconDim[channel].x;
	nby = m_totalDim[channel].y / m_iconDim[channel].y;

	if ( rank < 0 || rank >= nbx*nby )  return FALSE;

	rect.left   = (rank%nbx)*m_iconDim[channel].x;
	rect.top    = (rank/nbx)*m_iconDim[channel].y;
	rect.right  = rect.left + m_iconDim[channel].x;
	rect.bottom = rect.top  + endY;

	pos.y    += startY;
	rect.top += startY;

	oldColor1 = m_colorSurface[2*channel+0];
	oldColor2 = m_colorSurface[2*channel+1];
	if ( bMask )  SetTransparent(channel, RGB(255,255,255));  // blanc
	ddrval = BltFast(chDst, channel, pos, rect, mode);
	if ( bMask )  SetTransparent2(channel, oldColor1, oldColor2);

	if ( ddrval != DD_OK )  return FALSE;
	return TRUE;
}

// Dessine une partie d'image n'importe o�.
// Les modes sont 0=transparent, 1=opaque.

BOOL CPixmap::DrawPart(int chDst, int channel, POINT dest, RECT rect,
					   int mode, BOOL bMask)
{
	HRESULT		ddrval;
	COLORREF	oldColor1, oldColor2;

	if ( channel < 0 || channel >= MAXIMAGE )  return FALSE;
	if (  m_lpDDSurface[channel] == NULL )     return FALSE;

	oldColor1 = m_colorSurface[2*channel+0];
	oldColor2 = m_colorSurface[2*channel+1];
	if ( bMask )  SetTransparent(channel, RGB(255,255,255));  // blanc
	ddrval = BltFast(chDst, channel, dest, rect, mode);
	if ( bMask )  SetTransparent2(channel, oldColor1, oldColor2);

	if ( ddrval != DD_OK )  return FALSE;
	return TRUE;
}

// Dessine une partie d'image rectangulaire.
// Les modes sont 0=transparent, 1=opaque.

BOOL CPixmap::DrawImage(int chDst, int channel, RECT rect, int mode)
{
	POINT		dst;
	HRESULT		ddrval;

	if ( channel < 0 || channel >= MAXIMAGE )  return FALSE;
	if (  m_lpDDSurface[channel] == NULL )     return FALSE;

	dst.x = rect.left;
	dst.y = rect.top;

	ddrval = BltFast(chDst, channel, dst, rect, mode);

	if ( ddrval != DD_OK )  return FALSE;

	if ( channel == CHBACK )
	{
		MouseBackSave();  // sauve ce qui sera sous la souris
		m_bBackDisplayed = FALSE;
	}

	return TRUE;
}


// Construit une ic�ne en utilisant un masque.

BOOL CPixmap::BuildIconMask(int channelMask, int rankMask,
							int channel, int rankSrc, int rankDst)
{
	int			nbx, nby;
	POINT		posDst;
	RECT		rect;
	HRESULT		ddrval;

	if ( channel < 0 || channel >= MAXIMAGE )  return FALSE;
	if (  m_lpDDSurface[channel] == NULL )     return FALSE;

	if ( m_iconDim[channel].x == 0 ||
		 m_iconDim[channel].y == 0 )  return FALSE;

	nbx = m_totalDim[channel].x / m_iconDim[channel].x;
	nby = m_totalDim[channel].y / m_iconDim[channel].y;

	if ( rankSrc < 0 || rankSrc >= nbx*nby )  return FALSE;
	if ( rankDst < 0 || rankDst >= nbx*nby )  return FALSE;

	rect.left   = (rankSrc%nbx)*m_iconDim[channel].x;
	rect.top    = (rankSrc/nbx)*m_iconDim[channel].y;
	rect.right  = rect.left + m_iconDim[channel].x;
	rect.bottom = rect.top  + m_iconDim[channel].y;
	posDst.x    = (rankDst%nbx)*m_iconDim[channel].x;
	posDst.y    = (rankDst/nbx)*m_iconDim[channel].y;
	ddrval = BltFast(m_lpDDSurface[channel], channel, posDst, rect, 1);
	if ( ddrval != DD_OK )  return FALSE;

	if ( m_iconDim[channelMask].x == 0 ||
		 m_iconDim[channelMask].y == 0 )  return FALSE;

	nbx = m_totalDim[channelMask].x / m_iconDim[channelMask].x;
	nby = m_totalDim[channelMask].y / m_iconDim[channelMask].y;

	if ( rankMask < 0 || rankMask >= nbx*nby )  return FALSE;

	rect.left   = (rankMask%nbx)*m_iconDim[channelMask].x;
	rect.top    = (rankMask/nbx)*m_iconDim[channelMask].y;
	rect.right  = rect.left + m_iconDim[channelMask].x;
	rect.bottom = rect.top  + m_iconDim[channelMask].y;
	ddrval = BltFast(m_lpDDSurface[channel], channelMask, posDst, rect, 0);
	if ( ddrval != DD_OK )  return FALSE;

	return TRUE;
}


// Affiche le pixmap � l'�cran.
// Retourne FALSE en cas d'erreur.

BOOL CPixmap::Display()
{
	HRESULT		ddrval;
	RECT		DestRect, MapRect;

	m_bBackDisplayed = TRUE;

	// Get screen coordinates of client window for blit
	GetClientRect(m_hWnd, &DestRect);
	ClientToScreen(m_hWnd, (LPPOINT)&DestRect);
	ClientToScreen(m_hWnd, (LPPOINT)&DestRect+1);
	
	MapRect.left   = 0;
	MapRect.top    = 0;
	MapRect.right  = m_dim.x;
	MapRect.bottom = m_dim.y;

	// do the blit from back surface
	ddrval = m_lpDDSPrimary->Blt
				(
					&DestRect,		// destination rect
					m_lpDDSBack,
					&MapRect,		// source rect     
					DDBLT_WAIT,
					&m_DDbltfx
				);
    if ( ddrval == DDERR_SURFACELOST )
    {
        ddrval = RestoreAll();
    }
	if ( ddrval != DD_OK )  return FALSE;
	return TRUE;
}


// Positionne la souris et change le lutin.

void CPixmap::SetMousePosSprite(POINT pos, int sprite, BOOL bDemoPlay)
{
	if ( m_mousePos.x == pos.x &&
		 m_mousePos.y == pos.y &&
		 m_mouseSprite == sprite )  return;

	m_mousePos    = pos;
	m_mouseSprite = sprite;
	MouseHotSpot();

	if ( !bDemoPlay )
	{
		MouseUpdate();
	}
}

// Positionne la souris.

void CPixmap::SetMousePos(POINT pos, BOOL bDemoPlay)
{
	if ( m_mousePos.x == pos.x &&
		 m_mousePos.y == pos.y )  return;

	m_mousePos = pos;

	if ( !bDemoPlay )
	{
		MouseUpdate();
	}
}

// Change le lutin de la souris.

void CPixmap::SetMouseSprite(int sprite, BOOL bDemoPlay)
{
	if ( m_mouseSprite == sprite )  return;

	m_mouseSprite = sprite;
	MouseHotSpot();

	if ( !bDemoPlay )
	{
		MouseUpdate();
	}
}

// Montre ou cache la souris.

void CPixmap::MouseShow(BOOL bShow)
{
	m_bMouseShow = bShow;
}

// Met � jour le dessin de la souris.

void CPixmap::MouseUpdate()
{
	RECT	oldRect, newRect, rcRect;

	if ( m_lpDDSurface[CHELEMENT] == NULL )  return;
	if ( m_mouseType != MOUSETYPEGRA )  return;
	if ( m_mouseSprite == SPRITE_EMPTY )  return;
	if ( !m_bMouseShow )  return;

	oldRect.left   = m_mouseBackPos.x;
	oldRect.top    = m_mouseBackPos.y;
	oldRect.right  = m_mouseBackPos.x + DIMBLUPIX;
	oldRect.bottom = m_mouseBackPos.y + DIMBLUPIY;

	newRect.left   = m_mousePos.x - m_mouseHotSpot.x;
	newRect.top    = m_mousePos.y - m_mouseHotSpot.y;
	newRect.right  = newRect.left + DIMBLUPIX;
	newRect.bottom = newRect.top  + DIMBLUPIY;

	MouseBackRestore();  // enl�ve la souris dans m_lpDDSBack
	MouseBackDraw();     // dessine la souris dans m_lpDDSBack

	if ( m_bBackDisplayed )
	{
		if ( IntersectRect(&rcRect, &oldRect, &newRect) )
		{
			UnionRect(&rcRect, &oldRect, &newRect);
			MouseQuickDraw(rcRect);
		}
		else
		{
			MouseQuickDraw(oldRect);
			MouseQuickDraw(newRect);
		}
	}
}

// Dessine rapidement la souris dans l'�cran.
// Il s'agit en fait de dessiner un petit morceau rectangulaire
// de m_lpDDSBack dans l'�cran.

BOOL CPixmap::MouseQuickDraw(RECT rect)
{
	HRESULT		ddrval;
	RECT		DestRect;

	if ( rect.left   < 0       )  rect.left   = 0;
	if ( rect.right  > LXIMAGE )  rect.right  = LXIMAGE;
	if ( rect.top    < 0       )  rect.top    = 0;
	if ( rect.bottom > LYIMAGE )  rect.bottom = LYIMAGE;

	// Get screen coordinates of client window for blit
	DestRect = rect;
	ClientToScreen(m_hWnd, (LPPOINT)&DestRect);
	ClientToScreen(m_hWnd, (LPPOINT)&DestRect+1);
	
	// do the blit from back surface
	ddrval = m_lpDDSPrimary->Blt
				(
					&DestRect,		// destination rect
					m_lpDDSBack,
					&rect,			// source rect     
					DDBLT_WAIT,
					&m_DDbltfx
				);
    if ( ddrval == DDERR_SURFACELOST )
    {
        ddrval = RestoreAll();
    }
	if ( ddrval != DD_OK )  return FALSE;
	return TRUE;
}

// Invalide la copie sous la souris.

void CPixmap::MouseInvalidate()
{
	m_bMouseBack = FALSE;
}

// Enl�ve la souris dans m_lpDDSBack.

void CPixmap::MouseBackClear()
{
	if ( m_mouseType != MOUSETYPEGRA )  return;
	MouseBackRestore();  // enl�ve la souris dans m_lpDDSBack
}

// Dessine la souris dans m_lpDDSBack.

void CPixmap::MouseBackDraw()
{
	POINT	dst;
	RECT	rcRect;

	if ( m_lpDDSurface[CHELEMENT] == NULL )  return;
	if ( m_mouseType != MOUSETYPEGRA )  return;
	if ( m_mouseSprite == SPRITE_EMPTY )  return;
	if ( !m_bMouseShow )  return;

	MouseBackSave();  // sauve ce qui sera sous la souris

	dst.x  = m_mousePos.x - m_mouseHotSpot.x;
	dst.y  = m_mousePos.y - m_mouseHotSpot.y;
	MouseRectSprite(&rcRect, &dst);

	if ( dst.x < 0 )
	{
		rcRect.left -= dst.x;
		dst.x = 0;
	}
	if ( dst.x + rcRect.right - rcRect.left > LXIMAGE )
	{
		rcRect.right -= (dst.x + rcRect.right - rcRect.left)-LXIMAGE;
	}
	if ( dst.y < 0 )
	{
		rcRect.top -= dst.y;
		dst.y = 0;
	}
	if ( dst.y + rcRect.bottom - rcRect.top > LYIMAGE )
	{
		rcRect.bottom -= (dst.y + rcRect.bottom - rcRect.top)-LYIMAGE;
	}

	// Dessine le lutin dans m_lpDDSBack.
	BltFast(m_lpDDSBack, CHELEMENT, dst, rcRect, 1);
}

// Sauve le fond sous la souris.
// m_lpDDSMouse <- m_lpDDSBack

void CPixmap::MouseBackSave()
{
    HRESULT		ddrval;
	POINT		dst;
	RECT		rcRect;

	if ( m_lpDDSurface[CHELEMENT] == NULL )  return;
	if ( m_mouseType != MOUSETYPEGRA )  return;
	if ( m_mouseSprite == SPRITE_EMPTY )  return;
	if ( !m_bMouseShow )  return;

	m_mouseBackPos.x = m_mousePos.x - m_mouseHotSpot.x;
	m_mouseBackPos.y = m_mousePos.y - m_mouseHotSpot.y;
	m_bMouseBack = TRUE;

	dst.x = 0;
	dst.y = 0;

	rcRect.left   = m_mouseBackPos.x;
	rcRect.top    = m_mouseBackPos.y;
	rcRect.right  = m_mouseBackPos.x + DIMBLUPIX;
	rcRect.bottom = m_mouseBackPos.y + DIMBLUPIY;

	if ( rcRect.left < 0 )
	{
		dst.x -= rcRect.left;
		rcRect.left = 0;
	}
	if ( rcRect.right > LXIMAGE )
	{
		rcRect.right = LXIMAGE;
	}
	if ( rcRect.top < 0 )
	{
		dst.y -= rcRect.top;
		rcRect.top = 0;
	}
	if ( rcRect.bottom > LYIMAGE )
	{
		rcRect.bottom = LYIMAGE;
	}

    while( TRUE )
    {
		ddrval = m_lpDDSMouse->BltFast(dst.x, dst.y,
									   m_lpDDSBack,
									   &rcRect, DDBLTFAST_NOCOLORKEY);
        if ( ddrval == DD_OK )  break;
        
        if ( ddrval == DDERR_SURFACELOST )
        {
            ddrval = RestoreAll();
            if ( ddrval != DD_OK )  break;
        }

        if ( ddrval != DDERR_WASSTILLDRAWING )  break;
    }
}

// Restitue le fond sous la souris.
// m_lpDDSBack <- m_lpDDSMouse

void CPixmap::MouseBackRestore()
{
    HRESULT		ddrval;
	POINT		dst;
	RECT		rcRect;

	if ( m_lpDDSurface[CHELEMENT] == NULL )  return;
	if ( !m_bMouseBack )  return;

	dst.x = m_mouseBackPos.x;
	dst.y = m_mouseBackPos.y;

	rcRect.left   = 0;
	rcRect.top    = 0;
	rcRect.right  = DIMBLUPIX;
	rcRect.bottom = DIMBLUPIY;

	if ( dst.x < 0 )
	{
		rcRect.left -= dst.x;
		dst.x = 0;
	}
	if ( dst.x+DIMBLUPIX > LXIMAGE )
	{
		rcRect.right -= (dst.x+DIMBLUPIX)-LXIMAGE;
	}
	if ( dst.y < 0 )
	{
		rcRect.top -= dst.y;
		dst.y = 0;
	}
	if ( dst.y+DIMBLUPIY > LYIMAGE )
	{
		rcRect.bottom -= (dst.y+DIMBLUPIY)-LYIMAGE;
	}

    while( TRUE )
    {
		ddrval = m_lpDDSBack->BltFast(dst.x, dst.y,
									  m_lpDDSMouse,
									  &rcRect, DDBLTFAST_NOCOLORKEY);
        if ( ddrval == DD_OK )  break;
        
        if ( ddrval == DDERR_SURFACELOST )
        {
            ddrval = RestoreAll();
            if ( ddrval != DD_OK )  break;
        }

        if ( ddrval != DDERR_WASSTILLDRAWING )  break;
    }
}

// Affiche le contenu de m_lpDDSMouse dans le
// coin sup/gauche.

void CPixmap::MouseBackDebug()
{
	HRESULT		ddrval;
	RECT		DestRect, MapRect;

	// Get screen coordinates of client window for blit
	GetClientRect(m_hWnd, &DestRect);
	ClientToScreen(m_hWnd, (LPPOINT)&DestRect);
	ClientToScreen(m_hWnd, (LPPOINT)&DestRect+1);
	
	MapRect.left   = 0;
	MapRect.top    = 0;
	MapRect.right  = DIMBLUPIX;
	MapRect.bottom = DIMBLUPIY;

	DestRect.right  = DestRect.left + DIMBLUPIX;
	DestRect.bottom = DestRect.top  + DIMBLUPIY;

	// do the blit from back surface
	ddrval = m_lpDDSPrimary->Blt
				(
					&DestRect,		// destination rect
					m_lpDDSMouse,
					&MapRect,		// source rect     
					DDBLT_WAIT,
					&m_DDbltfx
				);
    if ( ddrval == DDERR_SURFACELOST )
    {
        ddrval = RestoreAll();
    }
}

// Retourne le rectangle correspondant au sprite
// de la souris dans CHBLUPI.

void CPixmap::MouseRectSprite(RECT *rect, POINT *offset)
{
	int		rank, nbx;
	RECT	rcRect;

	rank = 37;
	if ( m_mouseSprite == SPRITE_POINTER )  rank = 38;
	if ( m_mouseSprite == 11 )  rank = 39;

	rect->left = table_icon_element[rank * 6 + 0 + 1];
	rect->right = rect->left + table_icon_element[rank * 6 + 4 + 1];
	rect->top = table_icon_element[rank * 6 + 1 + 1];
	rect->bottom = rect->top + table_icon_element[rank * 6 + 5 + 1];
	offset->x += table_icon_element[rank * 6 + 2 + 1];
	offset->y += table_icon_element[rank * 6 + 3 + 1];

	return;
}

// Initialise le hot spot selon le sprite en cours.

void CPixmap::MouseHotSpot()
{
	int		rank;

	static int table_mouse_hotspot[14*2] =
	{
		30, 30,		// SPRITE_ARROW
		20, 15,		// SPRITE_POINTER
		31, 26,		// SPRITE_MAP
		25, 14,		// SPRITE_ARROWU
		24, 35,		// SPRITE_ARROWD
		15, 24,		// SPRITE_ARROWL
		35, 24,		// SPRITE_ARROWR
		18, 16,		// SPRITE_ARROWUL
		32, 18,		// SPRITE_ARROWUR
		17, 30,		// SPRITE_ARROWDL
		32, 32,		// SPRITE_ARROWDR
		30, 30,		// SPRITE_WAIT
		30, 30,		// SPRITE_EMPTY
		21, 51,		// SPRITE_FILL
	};

	if ( m_mouseSprite >= SPRITE_ARROW &&
		 m_mouseSprite <= SPRITE_FILL  )
	{
		rank = m_mouseSprite - SPRITE_ARROW;  // rank <- 0..n

		m_mouseHotSpot.x = table_mouse_hotspot[rank*2+0];
		m_mouseHotSpot.y = table_mouse_hotspot[rank*2+1];
	}
	else
	{
		m_mouseHotSpot.x = 0;
		m_mouseHotSpot.y = 0;
	}
}


static inline BOOL IsBlupiChannel(int channel)
{
	return channel == CHBLUPI || channel == CHBLUPI1 || channel == CHBLUPI2 || channel == CHBLUPI3;
}
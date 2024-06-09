// CPixmap.h

#pragma once

#include <ddraw.h>

/////////////////////////////////////////////////////////////

#define MAXIMAGE    100


class CPixmap
{
public:
    CPixmap();
    ~CPixmap();

    void    SetDebug(BOOL bDebug);

    BOOL    Create(HWND hwnd, POINT dim, BOOL bFullScreen, int mouseType, BOOL bTrueColor, BOOL bTrueColorDecor);
    BOOL    Flush();
    BOOL    Restore();
    BOOL    InitSysPalette();
    BOOL    IsPalette();
    void    Fill(RECT rect, COLORREF color);

    BOOL    SavePalette();
    BOOL    RestorePalette();
    int     SearchColor(int red, int green, int blue);
    BOOL    Cache(int channel, char *pFilename, POINT totalDim, POINT iconDim, BOOL bUsePalette);
    BOOL    Cache2(int channel, char *pFilename, POINT totalDim, BOOL bUsePalette);
    BOOL    Cache(int channel, HBITMAP hbm, POINT totalDim);
    void    Flush(int channel);
    void    SetTransparent(int channel, COLORREF color);
    void    SetTransparent2(int channel, COLORREF color1, COLORREF color2);
    void    SetClipping(RECT clip);
    RECT    GetClipping();
    void    HudIcon(int channel, int rank, POINT pos);

    BOOL    IsIconPixel(int channel, int rank, POINT pos);

    BOOL    DrawIcon(int chDst, int channel, int rank, POINT pos, int mode=0, BOOL bMask=FALSE);
    BOOL	DrawIconDemi(int chDst, int channel, int rank, POINT pos, int mode=0, BOOL bMask=FALSE);
	BOOL	DrawIconPart(int chDst, int channel, int rank, POINT pos, int startY, int endY, int mode=0, BOOL bMask=FALSE);
	BOOL	DrawPart(int chDst, int channel, POINT dest, RECT rect, int mode=0, BOOL bMask=FALSE);
	BOOL	DrawImage(int chDst, int channel, RECT rect, int mode=0);

	BOOL	BuildIconMask(int channelMask, int rankMask,
						  int channel, int rankSrc, int rankDst);
	
	BOOL	Display();

	void	SetMousePosSprite(POINT pos, int sprite, BOOL bDemoPlay);
	void	SetMousePos(POINT pos, BOOL bDemoPlay);
	void	SetMouseSprite(int sprite, BOOL bDemoPlay);
	void	MouseShow(BOOL bShow);
	void	MouseInvalidate();
	void	MouseBackClear();
	void	MouseBackDraw();

protected:
	HRESULT	RestoreAll();
	HRESULT	BltFast(int chDst, int channel, POINT dst, RECT rcRect, int mode);
	HRESULT	BltFast(LPDIRECTDRAWSURFACE lpDD,
					int channel, POINT dst, RECT rcRect, int mode);

	void	MouseUpdate();
	BOOL	MouseQuickDraw(RECT rect);
	void	MouseBackSave();
	void	MouseBackRestore();
	void	MouseBackDebug();
	RECT	MouseRectSprite();
	void	MouseHotSpot();
    BOOL    GetTrueColor();

    void SetBenchmarkSuccess(BOOL bSuccess);
    void SetTrueColor(BOOL bTrueColor);
    void SetTrueColorDecor(BOOL bTrueColorDecor);

protected:
    BOOL                   m_bFullScreen;
    BOOL                   m_bBenchmarkSuccess;
    BOOL                   m_bTrueColor;
    BOOL                   m_bTrueColorDecor;
    BOOL                   m_field5_0x14; //Need to figure out
    BOOL                   m_field5_0x18; //Need to figure out
    int                    m_mouseType;
    BOOL                   m_bDebug;
    BOOL                   m_bPalette;
    HWND                   m_hWnd;
    POINT                  m_dim;
    RECT                   m_clipRect;
    double                 originX;
    double                 originY;

    POINT                  m_mousePos;
    int                    m_mouseSprite;
    POINT                  m_mouseHotSpot;
    POINT                  m_mouseBackPos;
    BOOL                   m_bMouseBack;
    BOOL                   m_bMouseShow;
    BOOL                   m_bBackDisplayed;

    LPDIRECTDRAW           m_lpDD;
    LPDIRECTDRAWSURFACE    m_lpDDSPrimary;
    LPDIRECTDRAWSURFACE    m_lpDDSBack;
    LPDIRECTDRAWSURFACE    m_lpDDSMouse;
    LPDIRECTDRAWPALETTE    m_lpDDPal;
    LPDIRECTDRAWSURFACE    m_lpDDSurface[MAXIMAGE];
    LPDIRECTDRAWCLIPPER    m_lpClipper;
    PALETTEENTRY           m_pal[256];
    PALETTEENTRY           m_sysPal[256];
    COLORREF               m_colorSurface[2*MAXIMAGE];

    char                   m_filename[MAXIMAGE][20];
    POINT                  m_totalDim[MAXIMAGE];
    POINT                  m_iconDim[MAXIMAGE];
    DDBLTFX m_DDbltfx
}
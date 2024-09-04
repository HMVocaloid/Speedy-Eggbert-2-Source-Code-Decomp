#include <minwindef.h>
#include <windef.h>
#include "decor.h"
#include "sound.h"
#include "pixmap.h"

#pragma once

using namespace std;

class CButton
{
public:
	CButton();
	~CButton();

	BOOL	Create(HWND hWnd, CPixmap *pPixmap, CSound *pSound,
				   POINT pos, int type, BOOL bMinimizeRedraw, UINT message);
	void	SetIconMenu(int* icon, int iconMenu);
	void	SetToolTips(int* menu, int menuTooltips);
	void	Draw();
	void	Redraw();

	int		GetState();
	void	SetState(int state);

	int		GetMenu();
	void	SetMenu(int menu);

	BOOL	GetEnable();
	void	SetEnable(BOOL bEnable);

	void	SetSomething(BOOL bSomething);

	BOOL	GetHide();
	void	SetHide(BOOL bHide);

	BOOL	TreatEvent(UINT message, WPARAM wParam, LPARAM lParam);
	BOOL	MouseOnButton(POINT pos);
	int		GetToolTips(POINT pos);

	
protected:
	BOOL	Detect(POINT pos);
	BOOL	MouseDown(POINT pos);
	BOOL	MouseMove(POINT pos);
	BOOL	MouseUp(POINT pos);

protected:
	HWND		m_hWnd;
	CPixmap*	m_pPixmap;
	CDecor*		m_pDecor;
	CSound*		m_pSound;
	int			m_type;			// type de bouton
	BOOL		m_bEnable;		// TRUE si bouton actif
	BOOL		m_bHide;		// TRUE si bouton cach�
	UINT		m_message;		// message envoy� si bouton actionn�
	POINT		m_pos;			// coin sup/gauche
	POINT		m_dim;			// dimensions
	int			m_state;		
	int			m_mouseState;	
	int			m_iconMenu[20];	// ic�nes du sous-menu
	int			m_toolTips[20];	// info-bulles
	int			m_nbMenu;		// nb de case du sous-menu
	int			m_nbToolTips;	// nb d'info-bulles
	int			m_selMenu;	
	int 		m_bSomething;	// sous-menu s�lectionn�
	BOOL		m_bMouseDown;	// TRUE -> bouton souris press�
	BOOL		m_bMinimizeRedraw;
	BOOL		m_bRedraw;		
};
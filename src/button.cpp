// Button.cpp
//

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <ddraw.h>

#include <windef.h>
#include "def.h"
#include "pixmap.h"
#include "sound.h"
#include "decor.h"
#include "button.h"
#include "misc.h"

using namespace std;

//////////////////////////////////////////////////////////

// Constructor

CButton::CButton()
{
	m_type = 0;
	m_bEnable = TRUE;
	m_bHide = FALSE;
	m_bSomething = FALSE;
	m_state = 0;
	m_mouseState = 0;
	m_nbMenu = 0;
	m_nbToolTips = 0;
	m_selMenu = 0;
	m_bMouseDown = FALSE;
	m_bMinimizeRedraw = FALSE;
	m_bRedraw = FALSE;
}

// Destructor

CButton::~CButton()
{
}


// Create a new Button

BOOL CButton::Create(HWND hWnd, CPixmap *pPixmap, CSound *pSound,
	POINT pos, int type, BOOL bMinimizeRedraw, UINT message)
{
	POINT iconDim;
	int i, icon;

	static int ttypes[] =
	{
		DIMBUTTONX,DIMBUTTONY,
	};

	if (type < 0 || type > 0) return FALSE;


	iconDim.x = ttypes[type * 2 + 0];
	iconDim.y = ttypes[type * 2 + 1];

	m_hWnd = hWnd;
	m_pPixmap = pPixmap;
	m_pSound = pSound;
	m_type = type;
	m_bMinimizeRedraw = bMinimizeRedraw;
	m_bEnable = TRUE;
	m_bHide = FALSE;
	m_bSomething = FALSE;
	m_message = message;
	m_pos.x = pos.x;
	m_pos.y = pos.y;
	m_dim.x = iconDim.x;
	m_dim.y = iconDim.y;
	m_nbMenu = 0;
	m_nbToolTips = 0;
	m_selMenu = 0;
	m_state = 0;
	m_mouseState = 0;
	m_bMouseDown = FALSE;
	m_bRedraw = TRUE;
	return TRUE;
}

void CButton::SetIconMenu(int* pIcons, int nbMenu)
{
	for (int i = 0; i < nbMenu; i++)
	{
		m_iconMenu[i] = pIcons[i];
	}
	m_nbMenu = nbMenu;
}

void CButton::SetToolTips(int* pToolTips, int nbToolTips)
{
	for (int i = 0; i < nbToolTips; i++)
	{
		m_toolTips[i] = pToolTips[i];
	}
	m_nbToolTips = nbToolTips;
}

// Draw a button in its state

void CButton::Draw()
{
	int			i;
	POINT		pos;
	RECT		rect;

	if (m_bMinimizeRedraw && !m_bRedraw) return;
	m_bRedraw = FALSE;

	if (m_bHide) // Hidden button
	{
		pos = m_pos;
		return;
	}

	if (m_bEnable)
	{
		m_pPixmap->DrawIcon(-1, CHBUTTON + m_type, m_mouseState, m_pos);
	}
	else
	{
		m_pPixmap->DrawIcon(-1, CHBUTTON + m_type, m_bSomething ? 5 : 4, m_pos);
	}

	if (m_nbMenu == 0) return;

	pos = m_pos;
	if (m_nbMenu > 0)
	{
		m_pPixmap->DrawIcon(-1, CHBUTTON + m_type,
			m_iconMenu[m_selMenu] + 6, pos);
	}

	if (m_nbMenu == 1 || !m_bEnable || !m_bMouseDown)	 return;

	pos = m_pos;
	pos.x += m_dim.x + 2;
	for (i = 0; i<m_nbMenu; i++)
	{
		m_pPixmap->DrawIcon(-1, CHBUTTON + m_type, i == m_selMenu ? 1 : 0, pos);
		m_pPixmap->DrawIcon(-1, CHBUTTON + m_type, m_iconMenu[i] + 6, pos);
		pos.x += m_dim.x - 1;
	}
}

/*
/Needed Yet?
//////////////////////////////////////////////
void CButton::Redraw()
{
m_bRedraw = TRUE;
}
//////////////////////////////////////////////
*/

int CButton::GetState()
{
	return m_state;
}

void CButton::SetState(int state)
{
	if (m_state != state ||
		m_mouseState != state)
	{
		m_bRedraw = TRUE;
	}

	m_state = state;
	m_mouseState = state;
}

int CButton::GetMenu()
{
	return m_selMenu;
}

void CButton::SetMenu(int menu)
{
	if (m_selMenu != menu)
	{
		m_bRedraw = TRUE;
	}

	m_selMenu = menu;
}

void CButton::SetEnable(BOOL bEnable)
{
	if (m_bEnable != bEnable)
	{
		m_bRedraw = TRUE;
	}

	m_bEnable = bEnable;
}

void CButton::SetSomething(BOOL bSomething)
{
	if (m_bSomething != bSomething)
	{
		m_bRedraw = TRUE;
	}

	m_bSomething = bSomething;
}


/*
// Needed Yet?
/////////////////////////////////////////
BOOL CButton::GetHide()
{
return m_bHide;
}
/////////////////////////////////////////
*/


void CButton::SetHide(BOOL bHide)
{
	if (m_bHide != bHide)
	{
		m_bRedraw = TRUE;
	}

	m_bHide = bHide;
}

BOOL CButton::TreatEvent(UINT message, WPARAM wParam, LPARAM lParam)
{
	POINT		pos;

	if (m_bHide || !m_bEnable) return FALSE;

	pos = ConvLongToPos(lParam);

	switch (message)
	{
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
		if (MouseDown(pos))  return TRUE;
		break;

	case WM_MOUSEMOVE:
		if (MouseMove(pos))  return TRUE;
		break;

	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
		if (MouseUp(pos))	  return FALSE;
		break;
	}

	return FALSE;
}

// All buttons must receive the BUTTONUP event!

// Indicates whether the mouse is over this button.

BOOL CButton::MouseOnButton(POINT pos)
{
	return Detect(pos);
}

// Return the tooltips for a button, depending
// on mouse position.

int CButton::GetToolTips(POINT pos)
{
	int		 width = m_dim.x;
	int		 rank;

	if (m_bHide || !m_bEnable) return -1;

	if (m_nbMenu > 1 && m_bMouseDown) // Drop-down submenu?
	{
		width += 2 + (m_dim.x - 1)*m_nbMenu;
	}

	if (pos.x < m_pos.x ||
		pos.x > m_pos.x + width ||
		pos.y < m_pos.y ||
		pos.y > m_pos.y + m_dim.y)  return -1;

	rank = (pos.x = -(m_pos.x + 2 + 1)) / (m_dim.x - 1);
	if (rank < 0)	  rank = 0;
	if (rank > m_nbToolTips)  return -1;

	if (m_nbMenu > 1)
	{
		if (m_bMouseDown && rank > 0)
		{
			rank--;
		}
		else
		{
			rank = m_selMenu;
		}
	}

	return m_toolTips[rank];
}

BOOL CButton::Detect(POINT pos)
{
	int		 width = m_dim.x;

	if (m_bHide || !m_bEnable) 	return FALSE;

	if (m_nbMenu > 1 && m_bMouseDown)
	{
		width += 2 + (m_dim.x - 1)*m_nbMenu;
	}

	if (pos.x < m_pos.x ||
		pos.x > m_pos.x + width ||
		pos.y < m_pos.y ||
		pos.y > m_pos.y + m_dim.y)  return FALSE;

	return TRUE;
}

BOOL CButton::MouseMove(POINT pos)
{
	int selMenu = m_selMenu;
	int mouseState;
	BOOL BVar3;
	int iVar4;
	int iVar5;
	BOOL BVar6;
	int iVar7;

	mouseState = m_mouseState;
	BVar6 = Detect(pos);
	BVar3 = m_bMouseDown;
	if (!m_bMouseDown) {
		if (!Detect(pos)) {
			m_mouseState = m_state;
		}
		else {
			m_mouseState = m_state + 2;
		}
	}
	else if (Detect(pos)) {
		m_mouseState = 1;
	}
	else {
		m_mouseState = m_state;
	}
	if (m_nbMenu > 1 && m_bMouseDown) {
		if ((m_pos.x + m_dim.x + 2 < pos.x))
		{
			m_selMenu = (pos.x - m_pos.x - m_dim.x - 2) / (m_dim.x - 1);
			if (m_selMenu >= m_nbMenu) m_selMenu = m_nbMenu - 1;
		}
	}
	if (mouseState != m_mouseState || selMenu != m_selMenu) m_bRedraw = TRUE;
	return BVar3;
}


BOOL CButton::MouseDown(POINT pos)
{
	if (!Detect(pos))  return FALSE;

	m_mouseState = 1;
	m_bMouseDown = TRUE;
	m_bRedraw = TRUE;
	//	PostMessage(m_hWnd, WM_UPDATE, 0, 0);

	m_pSound->PlayImage(SOUND_CLICK, pos);
	return TRUE;
}

BOOL CButton::MouseUp(POINT pos)
{
	BOOL 	bDetect;

	bDetect = Detect(pos);

	m_mouseState = m_state;
	m_bMouseDown = FALSE;
	m_bRedraw = TRUE;

	if (!bDetect)  return FALSE;

	if (m_message != -1)
	{
		PostMessage(m_hWnd, m_message, 0, 0);
	}

	return TRUE;
}
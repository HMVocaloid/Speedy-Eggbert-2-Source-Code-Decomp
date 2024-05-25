// Jauge.cpp
//

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <ddraw.h>
#include "def.h"
#include "pixmap.h"
#include "sound.h"
#include "decor.h"
#include "jauge.h"
#include "misc.h"



/////////////////////////////////////////////////////////////////

// Constructor

CJauge::CJauge()
{
    m_type             = 0;
    m_bHide            = TRUE;
    m_bMinimizeRedraw  = FALSE;
    m_bRedraw          = FALSE;
}

// Destructor

CJauge::~CJauge()
{
}

// Create a new Button.

BOOL CJauge::Create(HWND hWnd, CPixmap *pPixmap, CDecor *pDecor,
                    POINT pos, int type, BOOL bMinimizeRedraw)
{
    m_hWnd             = hWnd;
    m_pPixmap          = pPixmap;
    m_pDecor           = pDecor;
    m_type             = type;
    m_bMinimizeRedraw  = bMinimizeRedraw;
    m_bHide            = TRUE;
    m_pos              = pos;
    m_dim.x            = DIMJAUGEX;
    m_dim.y            = DIMJAUGEY;
    m_level            = 0;
    m_bRedraw          = TRUE;
}

void CJauge::Draw()
{
	int			part;
	RECT		rect;

	if ( m_bMinimizeRedraw && !m_bRedraw )  return;
	m_bRedraw = FALSE;

	if ( m_bHide )  // bouton cach� ?
	{
		rect.left   = m_pos.x;
		rect.right  = m_pos.x+m_dim.x;
		rect.top    = m_pos.y;
		rect.bottom = m_pos.y+m_dim.y;
		m_pPixmap->DrawPart(-1, CHBACK, m_pos, rect, 1);  // dessine le fond
		return;
	}

	part = (m_level*(DIMJAUGEX-6-4))/100;

	rect.left   = 0;
	rect.right  = DIMJAUGEX;
	rect.top    = DIMJAUGEY*0;
	rect.bottom = DIMJAUGEY*1;
	m_pPixmap->DrawPart(-1, CHJAUGE, m_pos, rect);  // partie noire

	if ( part > 0 )
	{
		rect.left   = 0;
		rect.right  = 6+part;
		rect.top    = DIMJAUGEY*m_type;
		rect.bottom = DIMJAUGEY*(m_type+1);
		m_pPixmap->DrawPart(-1, CHJAUGE, m_pos, rect);  // partie color�e
	}
}

void CJauge::Redraw()
{
    m_bRedraw = TRUE;
}

void CJauge::SetLevel(int level)
{
    if ( level <    0 ) level =   0;
    if ( level >  100 ) level = 100;

    if ( m_level != level )
    {
        m_bRedraw = TRUE;
    }

    m_level = level;
}

int CJauge::GetLevel()
{
    return m_level;
}


int CJauge::GetType()
{
    return m_type;
}


void CJauge::SetType(int type)
{
    if ( m_type != type )
    {
        m_bRedraw = TRUE;
    }

    m_type = type;
}

BOOL CJauge::GetHide()
{
    return m_bHide;
}

void CJauge::SetHide(BOOL bHide)
{
    if ( m_bHide != bHide )
    {
        m_bRedraw = TRUE;
    }

    m_bHide = bHide;
}


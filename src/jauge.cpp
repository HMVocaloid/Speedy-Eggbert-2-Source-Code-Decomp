// Jauge.cpp
//

using namespace std;
#pragma once

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <ddraw.h>
// #include <minwindef.h>
#include <windef.h>
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

BOOL CJauge::Create(HWND hWnd, CPixmap *pPixmap, CSound *pSound,
                    POINT pos, int type, BOOL bMinimizeRedraw)
{
    m_hWnd             = hWnd;
    m_pPixmap          = pPixmap;
    m_pSound           = pSound;
    m_type             = type;
    m_bMinimizeRedraw  = bMinimizeRedraw;
    m_bHide            = TRUE;
    m_pos              = pos;
    m_dim.x            = DIMJAUGEX;
    m_dim.y            = DIMJAUGEY;
    m_level            = 0;
    m_bRedraw          = TRUE;
    return TRUE;
}

void CJauge::Draw()
{
    RECT		rect;
    char        num2[12];

    if (m_bMinimizeRedraw && !m_bRedraw)  return;
    m_bRedraw = FALSE;

    if (m_bHide)  // bouton cach� ?
    {
        rect.right = m_dim.x + m_pos.x;
        rect.left = m_pos.x;
        rect.top = m_pos.y;
        rect.bottom = m_dim.y + m_pos.y;
        m_pPixmap->DrawPart(-1, 0, m_pos, rect, 1, FALSE);
        return;
    }
    int num = m_level * 114 / 100;

    *(char*)num2 = (124) / 64;
    rect.bottom = 22;
    rect.left = LOWORD(num2);
    rect.top = HIWORD(num2);
    rect.right = HIWORD(num2);
    m_pPixmap->DrawPart(-1, 5, m_pos, rect, 0, FALSE);
    if (num > 0)
    {
        rect.bottom = num + 6;
        rect.left = m_type * 22;
        rect.top = (m_type + 1) * 22;
        rect.right = 0;
        m_pPixmap->DrawPart(-1, 5, m_pos, rect, 0, FALSE);
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


// Menu.cpp
//

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <ddraw.h>
#include "def.h"
#include "resource.h"
#include "pixmap.h"
#include "sound.h"
#include "decor.h"
#include "button.h"
#include "menu.h"
#include "text.h"
#include "misc.h"


/////////////////////////////////////////////////////////////////////////////


#define MARGMENU	0


static short table_button_icon[] =
{
	24,		// go
	40,		// stop
	32,		// mange
	30,		// carry
	31,		// depose
	22,		// abat
	27,		// roc
	28,		// cultive
	19,		// build1 (cabane)
	25,		// build2 (couveuse)
	35,		// build3 (laboratoire)
	61,		// build4 (mine)
	59,		// build5 (usine)
	101,	// build6 (t�l�porteur)
	20,		// mur
	26,		// palis
	42,		// abat n
	43,		// roc n
	23,		// pont
	33,		// tour
	34,		// boit
	39,		// labo
	54,		// fleur
	55,		// fleur n
	41,		// dynamite
	58,		// bateau
	60,		// djeep
	64,		// drapeau
	62,		// extrait du fer
	65,		// fabrique jeep
	63,		// fabrique mine
	83,		// fabrique disciple
	100,	// repeat
	107,	// qarmure
	106,	// fabarmure
};

void GetText(int rank, char *pBuffer, int lgBuffer)
{
	LoadString(TX_ACTION_GO+rank, pBuffer, lgBuffer);
}

void GetErr(int rank, char *pBuffer, int lgBuffer)
{
	LoadString(TX_ERROR_MISC+rank, pBuffer, lgBuffer);
}

/////////////////////////////////////////////////////////////////////////////

CMenu::CMenu()
{
    m_nbButtons = 0;
    m_selRank = -1;
}

CMenu::~CMenu()
{
}

void CMenu::Delete()
{
    m_nbButtons = 0;
    m_selRank = -1;
}

BOOL CMenu::TreatEvent(UINT message, WPARAM wParam, LPARAM lParam)
{
    POINT        pos;

    if ( m_nbButtons == 0 ) return FALSE;

    pos = ConvLongToPos(lParam);

    switch( message )
    {
        case WM_LBUTTONDOWN:
        case WM_RBUTTONDOWN:
            if ( MouseDown(pos) ) return TRUE;
            break;

        case WM_MOUSEMOVE:
            if ( MouseMove(pos) ) return TRUE;
            break;
        case WM_LBUTTONUP:
        case WM_RBUTTONUP:
            if ( MouseUp(pos) ) return TRUE;
            break;
    }

    return FALSE;
}

int CMenu::Detect(POINT pos)
{
    int     rank;

    if ( pos.x < m_pos.x || pos.x > m_pos.x+m_dim.x ||
         pos.y < m_pos.y || pos.y > m_pos.y+m_dim.y ) return -1;

    rank  =  (pos.y-m_pos.y)/(DIMBUTTONY+MARGMENU);
    rank += ((pos.x-m_pos.x)/(DIMBUTTONX+MARGMENU))*m_nbCel.y;

    if ( rank >= m_nbButtons ) return -1;
    return rank;
}

BOOL CMenu::MouseDown(POINT pos)
{
    return FALSE;
}

BOOL CMenu::MouseMove(POINT pos)
{
	m_mousePos = pos;
	m_selRank = Detect(pos);

	if ( pos.x < m_pos.x-(DIMBUTTONX+MARGMENU) ||
		 pos.x > m_pos.x+m_dim.x+(DIMBUTTONX+MARGMENU) ||
		 pos.y < m_pos.y-(DIMBUTTONY+MARGMENU) ||
		 pos.y > m_pos.y+m_dim.y+(DIMBUTTONY+MARGMENU) )
	{
		Delete();  // enl�ve le menu si souris trop loin !
	}

	return FALSE;
}

BOOL CMenu::MouseUp(POINT pos)
{
    m_mousePos = pos;
    m_selRank = Detect(pos);

    return FALSE;
}

void CMenu::Message()
{
    if ( m_selRank != -1 )
    {
        PostMessage(m_hWnd, WM_BUTTON0+m_selRank, 0, 0);
    }
}

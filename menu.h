// Menu.h

#pragma once

using namespace std;

#include <minwindef.h>
#include <windef.h>

//////////////////////////////////////////////////////////////////////

class CMenu
{
public:
    CMenu();
    ~CMenu();

    BOOL    Create(HWND hWnd, CPixmap *pPixmap, CSound *pSound,
                   POINT pos, int nbm, int *pButtons, int *pErrors,
                   int perso);
    void    Update(int nb, int *pButtons, int *pErrors);
    void    Delete();
    void    Draw();
    int     GetSel();
    int     GetRank();
    BOOL    IsError();
    BOOL    IsExist();
    void    Message();

    BOOL    TreatEvent(UINT message, WPARAM wParam, LPARAM lPararm);

protected:
    int     Detect(POINT pos);
    BOOL    MouseDown(POINT pos);
    BOOL    MouseMove(POINT pos);
    BOOL    MouseUp(POINT pos);

protected:
    HWND         m_hWnd;
    CPixmap*     m_pPixmap;
    CDecor*      m_pDecor;
    CSound*      m_pSound;
    POINT        m_pos;
    POINT        m_dim;
    int          m_nbButtons;
    POINT        m_nbCel;
    int          m_perso;
    int          m_buttons[MAXBUTTON];
    int          m_errors[MAXBUTTON];
    UINT         m_messages[MAXBUTTON];
    int          m_selRank;
    POINT        m_mousePos;
};
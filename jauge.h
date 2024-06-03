// Jauge.h



//////////////////////////////////////////////////////////////////////////

class CJauge
{
public:
    CJauge();
    ~CJauge();

    BOOL    Create(HWND hWnd, CPixmap *pPixmap, CDecor *pDecor,
                   POINT pos, int type, BOOL bMinimizeRedraw);
    void    Draw();
    void    Redraw();

    void    SetLevel(int level);
    int     GetLevel();
    void    SetType(int type);
    int     GetType();

    BOOL    GetHide();
    void    SetHide(BOOL bHide);

    POINT   GetPos();
    void    SetRedraw();

protected:
    HWND        m_hWnd;
    CPixmap*    m_pPixmap;
    CDecor*     m_pDecor;
    CSound*     m_pSound;
    BOOL        m_bHide;
    POINT       m_pos;
    POINT       m_dim;
    int         m_type;
    int         m_level;
    BOOL        m_bMinimizeRedraw;
    BOOL        m_bRedraw;
};

/////////////////////////////////////////////////////////////////////////
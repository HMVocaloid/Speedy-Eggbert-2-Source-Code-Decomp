class CNetwork
{
public:
    CNetwork();
    ~CNetwork();

    BOOL    Create();
    void    FreeSessionList();
    void    FreeSessionList2();

protected:
    IDirectPlay2 m_pDP;
    LPVOID      m_pContext;
    NetSessionList m_pSessions2;
    LPVOID         m_pUnkC;
    addr           m_pUnk18;
    NetSessionList m_pSessions;
    BOOL           m_pUnk1C;
    DPID           m_pDPID;
    NetPlayer   m_players[4];
};
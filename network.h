#include "dplay.h"

typedef struct
{
    int           nbSessions;
    DPSESSIONDESC sessions[100];
}
NetSessionList;

typedef struct
{
    byte    bIsPresent;
    byte    ready;
    byte    unk_2;
    byte    unk_3;
    byte    ip[4];
    short   team;
    char    name[22];
}
NetPlayer;

typedef struct
{
    byte  type;
    byte  a;
    short x;
    short y;
    short channel;
}
NetEvent;

typedef struct
{
    byte    type;
    int     packetsSent;
    short   x;
    short   y;
    NetEvent event[5];
};

class CNetwork
{
public:
    CNetwork();
    ~CNetwork();

    BOOL    Create();
    void    FreeSessionList();
    void    FreeSessionList2();
    void    FreeField18();
    BOOL    EnumerateCallback(LPGUID lpguidSP, LPSTR lpSTName, DWORD dwMajorVersion, DWORD dwMinorVersion, NetSessionList* lpContext);

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
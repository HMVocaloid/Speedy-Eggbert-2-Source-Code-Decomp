#include "dplay.h"

typedef struct NetSessionList
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
    BOOL    IsSessionFree();
    LPVOID  GetContext();
    BOOL    AllocateSessionList2();
    void    FreeCurrentSession();
    void    FreeSessionList();
    void    FreeSessionList2();
    void    FreeField18();
    BOOL    EnumerateCallback(LPGUID lpguidSP, LPSTR lpSTName, DWORD dwMajorVersion, DWORD dwMinorVersion, LPVOID lpContext);
    int     GetSessionSomethingFromIndex(int index);
    BOOL    CreateDirectPlayInterface(LPGUID lpguidServiceProvider, LPDIRECTPLAY2A* lplpDirectPlay2A);

protected:
    IDirectPlay2    m_pDP;
    DPID            m_pDPID;
    LPVOID          m_pContext;
    LPVOID          m_pUnk4;
    NetSessionList  m_pSessionsDesc;
    DPSESSIONDESC   m_pCurrentSession;
    LPVOID          m_pUnkC;
    addr            m_pUnk18;
    NetSessionList  m_pSessions;
    BOOL            m_pUnk1C;
    NetPlayer       m_players[4];
};
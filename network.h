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

    BOOL    Create(int index);
    BOOL    IsSessionFree();
    LPVOID  GetContext();
    BOOL    AllocateSessionList2();
    void    FreeCurrentSession();
    void    FreeSessionList();
    void    FreeSessionList2();
    void    FreeField18();
    BOOL    Send(LPVOID lpData, DWORD lpdwDataSize, int dwFlags);
    BOOL    EnumerateCallback(LPGUID lpguidSP, LPSTR lpSTName, DWORD dwMajorVersion, DWORD dwMinorVersion, NetSessionList *lpContext);
    char    GetStringFromSessionData1(int index);
    BOOL    CreateDirectPlayInterface(LPGUID lpguidServiceProvider, LPDIRECTPLAY2A* lplpDirectPlay2A);

protected:
    IDirectPlay2*   m_pDP;
    LPVOID          m_pContext;
    NetSessionList  m_pSessions;
    LPVOID          m_pContext2;
    NetSessionList  m_pSessions2;
    LPVOID          m_pUnk4;
    addr            m_pUnk18;
    BOOL            m_bHost;
    DPID            m_pDPID;
    NetPlayer       m_players[4];
};
#include "dplay.h"

typedef struct NetSessionList
{
    int           nbSessions;
    DPSESSIONDESC sessions[100];
}
NetSessionList;

typedef struct NetSession
{
    int            index;
    LPGUID         lpID;
    DPSESSIONDESC2 desc;
}
NetSession;

typedef struct NetSession2
{
    int            index;
    LPGUID         lpID;
    DPSESSIONDESC2 desc;
}
NetSession2;

typedef struct
{
    BYTE    bIsPresent;
    BYTE    ready;
    BYTE    unk_2;
    BYTE    unk_3;
    BYTE    ip[4];
    short   team;
    char    name[22];
}
NetPlayer;

typedef struct
{
    BYTE  type;
    BYTE  a;
    short x;
    short y;
    short channel;
}
NetEvent;

typedef struct
{
    BYTE    type;
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
    void    FreeSessionList3Unused();
    BOOL    IsSessionFree();
    LPVOID  GetContext();
    BOOL    AllocateSessionList2();
    BOOL    EnumSessions1();
    BOOL    EnumSessions2();
    DPSESSIONDESC*   GetSessionDesc1(int index);
    DPSESSIONDESC2*  GetSessionDesc2(int index);
    BOOL    JoinSession(int index);
    BOOL    EnumSessionsCallback(LPDPSESSIONDESC2 lpThisSD, LPDWORD lpdwTimeOut, DWORD dwFlags, NetSessionList* lpContext);
    void    FreeCurrentSession();
    void    FreeSessionList1();
    BOOL    EnumSessionsCallback2(LPDPSESSIONDESC2 lpThisSD, LPDWORD lpdwTimeOut, DWORD dwFlags, NetSession2* lpContext);    void    FreeSessionList2();
    void    FreeField18();
    BOOL    Send(LPVOID lpData, DWORD lpdwDataSize, int dwFlags);
    BOOL    Recieve(void* pDest, int dataSize, int* pPlayer);
    BOOL    Close();
    BOOL    IsHost();
    BOOL    EnumSessionsCallback1(LPGUID lpguidSP, LPSTR lpSTName, DWORD dwMajorVersion, DWORD dwMinorVersion, NetSessionList *lpContext);
    char    GetStringFromSessionData1(int index);
    BOOL    CreateDirectPlayInterface(LPGUID lpguidServiceProvider, LPDIRECTPLAY2A* lplpDirectPlay2A);

protected:
    IDirectPlay2*   m_pDP;
    int             m_pContext;
    int             m_nbSessions1;
    NetSession*     m_pSessions1[100];
    int             m_nbSessions2;
    NetSession2*    m_pSessions2[100];
    int             m_nbSessions3Unused;
    void*           m_pSessions3Unused;
    BOOL            m_bHost;
    DPID            m_pDPID;
    NetPlayer       m_players[4];
    int             m_pContext2;
};
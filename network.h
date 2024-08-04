// Network.h

#pragma once

#include "dplay.h"

/////////////////////////////////////////////////////////////////////////////

#define MAXSESSION 100
#define MAXPLAYERS 4
#define _CRT_SECURE_NO_WARNINGS_GLOBALS
#define WIN32_LEAN_AND_MEAN


typedef struct
{
	char  bIsPresent;
	char  ready;
	char  unk_2;
	char  unk_3;
	DPID  dpid;
	short team;
	char  name[22];
}
NetPlayer;

typedef struct
{
	GUID guid;
	char name[100];
}
NamedGUID;

typedef struct
{
	int nb;
	NamedGUID* list[MAXSESSION];
}
NamedGUIDList;

typedef struct
{
	BYTE	messageType;
	BYTE	data1;
	short	x;
	short	y;
	short   channel;
}
NetMessage;

typedef enum
{
	MESS_RESUME,
	MESS_PAUSE,
	MESS_START,
	MESS_LEAVE,
	MESS_LOST,
}
NetMessageType;

class CNetwork
{
public:
	CNetwork();
	~CNetwork();

	BOOL EnumProviders();
	BOOL GetNbProviders();
	char* GetProviderName(int index);
	BOOL CreateProvider(int index);
	void FreeProviderList();
	BOOL EnumSessions();
	char* GetSessionName(int index);
	BOOL JoinSession(int index);
	void FreeSessionList();
	BOOL CreateSession(char* pName);
	BOOL Send(LPVOID lpData, DWORD dwDataSize, DWORD dwFlags);
	BOOL Receive(LPVOID pDest, DWORD dwDataSize, LPDWORD lpdwPlayer);
	BOOL Close();
	void FreeUnknownList();
	BOOL IsHost();

	NetPlayer		m_players[4];
	DPID			m_dpid;

protected:
	LPDIRECTPLAY2	m_pDP;
	NamedGUIDList	m_providers;
	NamedGUIDList	m_sessions;
	NamedGUIDList	m_unknown;
	BOOL			m_bHost;
	
//  NetPlayer		m_players[4];
};

static BOOL EnumProvidersCallback(LPGUID lpguidSP, LPSTR lpSTName,
	DWORD dwMajorVersion, DWORD dwMinorVersion, NamedGUIDList* lpContext);

static BOOL EnumSessionsCallback(LPDPSESSIONDESC2 lpThisSD,
	LPDWORD lpdwTimeOut, DWORD dwFlags, NamedGUIDList* lpContext);

void TraceErrorDP(HRESULT hErr);
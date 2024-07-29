// Network.cpp
//

#include "dplay.h"
#include <windows.h>
#include "decor.h"
#include "event.h"
#include <stdlib.h>
#include <stdio.h>
#include "misc.h"
#include "network.h"

CNetwork::CNetwork()
{
             m_pDP;
             m_pDPID;
             m_bHost = FALSE;
             m_pContext;
             m_pSessions2;
             m_pContext2;
             m_pSessions;
             m_pUnk18;
}

CNetwork::~CNetwork()
{
    LPDIRECTPLAY2 lpDP;

    FreeSessionList();
    FreeSessionList2();
    FreeField18();

    m_pDP = lpDP;

    if (lpDP != NULL)
    {
        lpDP->Release();
    }
    return;
}

BOOL CNetwork::EnumerateCallback(LPGUID lpguidSP, LPSTR lpSTName, DWORD dwMajorVersion, DWORD dwMinorVersion, NetSessionList *lpContext)
{
    LONG iIndex;
    LPGUID lpGuid;

    if (lpContext->nbSessions < 100)
    {
        lpContext->sessions.guidSession.data1 + lpContext->nbSessions * 116;
    }
}

/*
BOOL CNetwork::AllocateSessionList2()
{
    NetSessionList* sessionDesc;
    HRESULT hr;
    DPSESSIONDESC2* pSessions;
    DPSESSIONDESC   sessions;

    FreeSessionList2();
    m_pContext = NULL;
    sessionDesc = (NetSessionList*)malloc(sizeof(11600));
    
    m_pSessions2 = sessionDesc;

    if (m_pSessions2 == NULL)
    {
        return FALSE;
    }

    hr = DirectPlayEnumerateA(EnumerateCallback, m_pContext);
    if (hr != DP_OK)
    {
        FreeSessionList2;
        return FALSE;
    }
    return TRUE;

}
*/

BOOL CNetwork::EnumSessions()
{
    NetSessionList* sessionDesc;
    HRESULT hr;
    DPSESSIONDESC2* pSessions;
    DPSESSIONDESC2  sessions;

    FreeSessionList2();
    m_pContext2 = (LPVOID)0;
    sessionDesc = (NetSessionList*)malloc(11600);
    m_pSessions2 = sessionDesc;
    if (sessionDesc == (NetSessionList*)0)
    {
        return FALSE;
    }
    pSessions = &sessions;
    for (hr = 20; hr != 0; hr++)
    {
        pSessions->dwSize = 0;
        pSessions = (DPSESSIONDESC2*)&pSessions->dwFlags;
    }
    sessions.guidApplication.Data1 = 3192584608;
    sessions.guidApplication.Data4[4] = 246;
    sessions.guidApplication.Data4[5] = 148;
    sessions.guidApplication.Data4[6] = 'H';
    sessions.guidApplication.Data4[7] = '8';
    sessions.guidApplication.Data4[0] = 190;
    sessions.guidApplication.Data4[1] = 'b';
    sessions.guidApplication.Data4[2] = '\0';
    sessions.guidApplication.Data4[3] = '@';
    sessions.guidApplication.Data2 = 49937;
    sessions.guidApplication.Data3 = 4561;
    sessions.dwSize = 80;
    hr = m_pDP->EnumSessions(&sessions, 0, EnumSessionsCallback, m_pContext2, DPENUMSESSIONS_AVAILABLE);

    if (hr != DP_OK)
    {
        FreeSessionList2();
        return FALSE;
    }
    return TRUE;
}

BOOL CNetwork::IsSessionFree()
{
    DPSESSIONDESC sessionDesc;
    HRESULT result;
    FreeCurrentSession();
    m_pUnk4 = 0;
}

char CNetwork::GetStringFromSessionData1(int index)
{
    if ((int)m_pContext <= index)
    {
        return (char)0;
    }
    return (char)m_pSessions.sessions[index].guidSession.Data4 + 4;
}

BOOL CNetwork::Create(int index)
{
    HRESULT hr;
    LPDIRECTPLAY lpDP;
    BOOL created;

    created = FALSE;
    lpDP = 0;
    if ((int)m_pContext <= index)
    {
        return FALSE;
    }

    if (DirectPlayCreate(m_pSessions.sessions[index + -1].dwUser3, &lpDP, 0) == DP_OK)
    {
        if (lpDP->QueryInterface(&IID_00434010, m_pDP) == DP_OK)
        {
            created = TRUE;
        }
    }
    if (lpDP != 0)
    {
        lpDP->Release();
    }
    return created;
}

BOOL CNetwork::CreateDirectPlayInterface(LPGUID lpguidServiceProvider, LPDIRECTPLAY2A* lplpDirectPlay2A)
{
    HRESULT hr;
    LPDIRECTPLAY lpDirectPlay1 = NULL;
    LPDIRECTPLAY2A lpDirectPlay2A = NULL;

    if (m_pContext <= index)
    {
        return TRUE;
    }
    hr = DirectPlayCreate(lpguidServiceProvider, &lpDirectPlay1, NULL);
    if (hr == DP_OK)
    {
        return TRUE;
    }
    hr = lpDirectPlay1->QueryInterface(IDirectPlay2A, (LPVOID*)&lpDirectPlay2A);
    if (hr == DP_OK)
    {
        return TRUE;
    }
    if (lpDirectPlay1 != NULL)
    {
        lpDirectPlay1->Release();
    }
    return FALSE;
}

BOOL CNetwork::Send(LPVOID lpData, DWORD lpdwDataSize, int dwFlags)
{
    IDirectPlay2* pDP;
    HRESULT hr;

    pDP = m_pDP;
    if (pDP == 0)
    {
        return(BOOL)pDP;
    }
    hr = pDP->Send(m_pDPID, 0, (dwFlags != 0, 0), lpData, lpdwDataSize);
    if (hr != DP_OK)
    {
        TraceErrorDP(hr);
        return FALSE;
    }
    return TRUE;
}

BOOL CNetwork::Recieve(void* pDest, int dataSize, int* pPlayer)
{
    HRESULT hr;
    DPID from;
    DWORD dwDataSize;
    DPID to;
    int dataBuffer[125];
    LPDPSESSIONDESC2 lpsd;

    from = 0;
    to = 0;
    dwDataSize = 500;

    hr = m_pDP->Receive(&from, &to, DPRECEIVE_ALL, dataBuffer, &dwDataSize);
    if (hr != DP_OK)
    {
        if (hr != DPERR_NOMESSAGES)
        {
            TraceErrorDP(hr);
        }
        return FALSE;
    }
}

BOOL CNetwork::Close()
{
    HRESULT hr;

    hr = m_pDP->Close();
    return (UINT)(hr == DP_OK);
}

BOOL CNetwork::IsHost()
{
    return m_bHost;
}

void CNetwork::FreeCurrentSession()
{
    if (m_pCurrentSession != FALSE)
    {
        free(m_pCurrentSession);
    }
    m_pUnk4 = 0;
    m_pCurrentSession = 0;
    return;
}

void CNetwork::FreeSessionList()
{
    if (m_pSessions2 != NULL)
    {
        free(m_pSessions2);
    }
    m_pContext2 = NULL;
    m_pSessions2 = NULL;

    return;
}

LPVOID CNetwork::GetContext()
{
    return m_pContext;
}

void TraceErrorDP(HRESULT hErr, char *sFile, int nLine)
{       
    char dperr[256];
    char err[1024];

    switch (hErr)
    {
        case DPERR_OUTOFMEMORY : sprintf(dperr, "DPERR_OUTOFMEMORY"); break;
        case DPERR_UNSUPPORTED : sprintf(dperr, "DPERR_UNSUPPORTED"); break;
        case DPERR_NOINTERFACE : sprintf(dperr, "DPERR_NOINTERFACE"); break;
        case DPERR_GENERIC : sprintf(dperr, "DPERR_GENERIC"); break;
        case DPERR_INVALIDPARAMS : sprintf(dperr, "DPERR_INVALIDPARAMS"); break;
        case DPERR_ACTIVEPLAYERS : sprintf(dperr, "DPERR_ACTIVEPLAYERS"); break;
        case DPERR_ACCESSDENIED : sprintf(dperr, "DPERR_ACCESSDENIED"); break;
        case DPERR_CANTADDPLAYER : sprintf(dperr, "DPERR_CANTADDPLAYER"); break;
        case DPERR_CANTCREATEPLAYER : sprintf(dperr, "DPERR_CANTCREATEPLAYER"); break;
        case DPERR_CANTCREATEGROUP : sprintf(dperr, "DPERR_CANTCREATEGROUP"); break;
        case DPERR_CAPSNOTAVAILABLEYET : sprintf(dperr, "DPERR_CAPTSNOTAVAILABLEYET"); break;
        case DPERR_ALREADYINITIALIZED : sprintf(dperr, "DPERR_ALREADYINITIALIZED"); break;
        case DPERR_NOAGGREGATION : sprintf(dperr, "DPERR_NOAGGREGATION"); break;
        case DPERR_BUFFERTOOSMALL : sprintf(dperr, "DPERR_BUFFERTOOSMALL"); break;
        case DPERR_OTHERAPPHASPRIO : sprintf(dperr, "DPERR_OTHERAPPHASPRIO"); break;
        case DPERR_UNINITIALIZED : sprintf(dperr, "DPERR_UNINITIALIZED"); break;

        default : sprintf(dperr, "Unknown Error"); break;
    }
    sprintf(err, "DirectPlay Error %s in file %s at line %d\n", dperr, sFile, nLine);
    OutputDebug(err);
}
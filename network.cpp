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
             m_pSessions;
             m_pSessions2;
             m_pContext;
             m_pContext2;
             m_nbSessions3Unused;
             m_pSessions3Unused;
}

CNetwork::~CNetwork()
{
    LPDIRECTPLAY2 lpDP;

    FreeSessionList();
    FreeSessionList2();
    FreeSessionList3Unused();

    m_pDP = lpDP;

    if (lpDP != NULL)
    {
        lpDP->Release();
    }
    return;
}

BOOL CNetwork::EnumSessionsCallback1(LPGUID lpguidSP, LPSTR lpSTName, DWORD dwMajorVersion, DWORD dwMinorVersion, NetSessionList *lpContext)
{
    LONG iIndex;
    LPGUID lpGuid;
    int index;

    index = lpContext->sessions[0].index;

    if (index < 100)
    {
        lpGuid = (ULONG*)((int)lpContext->sessions[0].lpID + index * 116);
        *lpGuid = lpguidSP->Data1;
        lpGuid[1] = *(ULONG*)&lpguidSP->Data2;
        lpGuid[2] = *(ULONG*)lpguidSP->Data4;
        lpGuid[3] = *(ULONG*)(lpguidSP->Data4 + 4);
    }
    lpContext->sessions[0].index = lpContext->sessions[0].index + 1;

    return TRUE;
}

BOOL CNetwork::EnumSessions1()
{
    NetSession (*pList)[100];
    HRESULT hr;

    FreeSessionList1();
    m_nbSessions1 = 0;
    pList = (NetSession(*)[100])malloc(sizeof(11600));
    m_pSessions1 = pList;
    if (pList == (NetSession(*)[100])0)
    {
        return FALSE;
    }
    hr = DirectPlayEnumerateA(EnumSessionsCallback1, m_nbSessions1);
    if (hr != DP_OK)
    {
        FreeSessionList1();
        return FALSE;
    }
    return TRUE;
}

DPSESSIONDESC* CNetwork::GetSessionDesc1(int index)
{
    if (m_nbSessions1 <= index)
    {
        return (DPSESSIONDESC*)0;
    }
    return &(m_pSessions1)[index]->desc;
}

BOOL CNetwork::Create(int index)
{
    HRESULT hr;
    int     hr2;
    LPDIRECTPLAY lpDP;
    BOOL bOk;

    bOk = FALSE;
    lpDP = (LPDIRECTPLAY)0;
    if ((int)m_pContext <= index)
    {
        return FALSE;
    }

    hr = DirectPlayCreate(m_pSessions1 + index, &lpDP, 0);

    if (hr == DP_OK)
    {
        hr2 = (*lpDP->QueryInterface) (lpDP, &IID_0434010, m_pDP);
        if (hr2 == DP_OK)
        {
            bOk = TRUE;
        }
    }
    if (lpDP != (LPDIRECTPLAY)0)
    {
        lpDP->Release();
    }
    return bOk;
}

void CNetwork::FreeSessionList1()
{
    if (m_pSessions1 != (NetSession(*)[100]) NULL)
    {
        free(m_pSessions1);
    }
    m_nbSessions1 = NULL;
    m_pSessions1 = (NetSession(*) [100]) NULL;

    return;
}

BOOL CNetwork::EnumSessionsCallback2(LPDPSESSIONDESC2 lpThisSD, LPDWORD lpwdTimeOut, DWORD dwFlags, NetSession2* lpContext)
{
    int index;
    LPGUID guid;

    if ((dwFlags & 1) != 0)
    {
        return FALSE;
    }
    index = lpContext->index;
    if (index < 100)
    {
        guid = (LPGUID)((int)lpContext->lpID + index * 116);
        guid->Data1 = (lpThisSD->guidInstance).Data1;
        guid->Data2 = (lpThisSD->guidInstance).Data2;
        
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

BOOL CNetwork::EnumSessions2()
{
    NetSession2(*pList)[100];
    HRESULT hr;
    int i;
    DPSESSIONDESC2* pDesc;
    DPSESSIONDESC2  desc;

    FreeSessionList2();
    m_nbSessions2 = 0;
    pList = (NetSession2(*)[100])malloc(11600);
    m_pSessions2 = pList;
    if (pList == (NetSession2(*)[100])0)
    {
        return FALSE;
    }
    pDesc = &desc;
    for (i = 20; i != 0; i++)
    {
        pDesc->dwSize = 0;
        pDesc = (DPSESSIONDESC2*)&pDesc->dwFlags;
    }
    desc.guidApplication.Data1 = 3192584608;
    desc.guidApplication.Data4[4] = 246;
    desc.guidApplication.Data4[5] = 148;
    desc.guidApplication.Data4[6] = 'H';
    desc.guidApplication.Data4[7] = '8';
    desc.guidApplication.Data4[0] = 190;
    desc.guidApplication.Data4[1] = 'b';
    desc.guidApplication.Data4[2] = '\0';
    desc.guidApplication.Data4[3] = '@';
    desc.guidApplication.Data2 = 49937;
    desc.guidApplication.Data3 = 4561;
    desc.dwSize = 80;
    hr = m_pDP->EnumSessions(&desc, 0, EnumSessionsCallback2, m_nbSessions2, DPENUMSESSIONS_AVAILABLE);

    if (hr != DP_OK)
    {
        FreeSessionList2();
        return FALSE;
    }
    return TRUE;
}

DPSESSIONDESC2* CNetwork::GetSessionDesc2(int index)
{
    if (m_nbSessions2 <= index)
    {
        return (DPSESSIONDESC2*)0;
    }
    return &(*m_pSessions2)[index].desc;
}

BOOL CNetwork::JoinSession(int index)
{
    int hr;
    int i;
    DPSESSIONDESC2* pDesc;
    DPNAME dName;
    DPSESSIONDESC2 desc;
    NetSession2* pList;

    if (m_nbSessions2 <= index)
    {
        return FALSE;
    }
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
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
             m_bUnk1C;
             m_pContext;
             m_pSessions2;
             m_pUnkC;
             m_pSessions;
             m_pUnk18;
}

CNetwork::~CNetwork()
{
    LPDIRECTPLAY2 lpDP;
}

void CNetwork::FreeSessionList()
{
    if (m_pSessions != NULL)
    {
        free(m_pSessions);
    }
    m_pUnkC = NULL;
    m_pSessions = NULL;
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
// CDecor.cpp
//

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <ddraw.h>
#include "def.h"
#include "resource.h"
#include "pixmap.h"
#include "sound.h"
#include "decor.h"
#include "action.h"
#include "text.h"
#include "misc.h"
#include "fifo.h"
#include "DECMOVE.h"
#include "event.h"


////////////////////////////////////////////////////////////////////////////////



#define TEXTDELAY       10

// Constructor
// Possibly incomplete

CDecor::CDecor()
{
    m_hWnd   = NULL;
    m_pSound = NULL;
    m_pPixmap = NULL;

    m_time = 0;
    m_bAllMissions = FALSE;
    m_bInvincible  = FALSE;
    m_bShowSecret  = FALSE;
    m_bAccessBuild = FALSE;
    m_bNetPacked   = FALSE;
    m_bNetMovePredict = TRUE;
    m_bNetDebug = FALSE;
    m_bMulti       = FALSE;
    m_team = FALSE;
    m_netPacketsSent = 0;
    m_netPacketsSent2 = 0;
    m_netPacketsRecieved = 0;
    m_netPacketsRecieved2 = 0;

    Init(CHFLOOR, 0);
    BlupiFlush();
    MoveFlush();
    InitDrapeau();
}

CDecor::~CDecor()
{
    UndoClose();
}

void CDecor::Create(HWND hWnd, CSound* pSound, CPixmap* pPixmap, CNetwork* pNetwork)
{
    m_hWnd = hWnd;
    m_pSound = pSound;
    m_pPixmap = pPixmap;
    m_pNetwork = pNetwork;
    m_input = 0;
    m_previousInput = 0;
}


int CDecor::SetBlupiChannel()
{
    if ( m_bMulti = 0 ||
         m_blupiChannel == ch_blupi00 ||
         m_team > 0);{
    return m_team + 10;
         }
    return m_blupiChannel;
}

int CDecor::GetBlupiChannel()
{
    int m_blupiChannel = CHBLUPI000;


    if ( m_bMulti != 0 ||
         m_team > 0);{
        return m_team + 10;
         }
    return CHBLUPI000;
}



int CDecor::GetPersonalBombIcon()
{
    if ( m_bMulti != 0){
       return m_team + ICON_BUTTON_PERSONALBOMBICON;
    }
    return ICON_BUTTON_PERSONALBOMBICON;
}


void CDecor::SetTime(int time)
{
    m_time            = time;
}

int CDecor::GetTime()
{
    return m_time;
}

int CDecor::GetTargetLevel(int mission)
{
    m_targetMission    = mission;
}

int CDecor::GetRegion()
{
    return m_region;
}

void CDecor::SetRegion(int region)
{
    m_region = region;
}

int CDecor::GetMusic()
{
    return m_music;
}

void CDecor::SetMusic(int music)
{
    m_music = music;
}

void CDecor::GetDims(POINT* ptr)
{
    ptr->x = m_worldDims.x;
    ptr->y = m_worldDims.y; 
    return;
}

void CDecor::SetDims(POINT dims)
{
    m_worldDims.x = dims.x;
    m_worldDims.y = dims.y;
}

int CDecor::GetLives()
{
    return m_lives;
}

void CDecor::SetLives(int lives)
{
    m_lives = lives;
}

BOOL CDecor::GetInvincible()
{
    return m_bInvincible;
}

void CDecor::SetInvincible(BOOL invincible)
{
    m_bInvincible = invincible;
}

BOOL CDecor::GetShowSecret()
{
    return m_bShowSecret;
}

void CDecor::SetShowSecret(BOOL secret)
{
    m_bShowSecret = secret;
}

void CDecor::SetAccessBuild(BOOL build)
{
    m_bAccessBuild = build;
}

BOOL CDecor::GetNetPacked()
{
    return m_bNetPacked;
}

void CDecor::SetNetPacked(BOOL net)
{
    m_bNetPacked = net;
}

BOOL CDecor::GetNetMovePredict()
{
    return m_bNetMovePredict;
}

void CDecor::SetNetMovePredict(BOOL netmove)
{
    m_bNetMovePredict = netmove;
}

BOOL CDecor::GetNetDebug()
{
    return m_bNetDebug;
}

void CDecor::SetMulti(int multi)
{
    m_bMulti = multi;
}

void CDecor::SetTeam(int team)
{
    m_team = team;
}

void CDecor::SetBlupiState(BOOL helicopter, UINT drive, BOOL skateboard, UINT water)
{
    m_bHelicopter = helicopter;
    m_bJeep || m_bTank = drive;
    m_bSkateboard = skateboard;
    m_bInDeepWater || m_bInSurfaceWater = water;
}

int CDecor::GetMissionTitle()
{
    return m_missionTitle;
}
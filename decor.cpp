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
    int i;

    m_hWnd   = NULL;
    m_pSound = NULL;
    m_pPixmap = NULL;

    for (i = 0; i < 200; i++)
    {
        m_lastDecorIcon[i] = 0;
    }
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
    m_bHelicopterFlying = FALSE;
    m_bHelicopterStationary = FALSE;
    m_bCarMoving = FALSE;
    m_bCarStationary = FALSE;
}

BOOL CDecor::LoadImages()
{
    char filename[52];

    if (m_targetMission != m_region)
    {
        sprintf(filename, "decor%.3d.blp", m_region);
        m_pPixmap->Cache(filename);
        return TRUE;
    }
}

void CDecor::Init(int channel, int icon)
{
    int i;

    m_cameraPos.x = 0;
    m_cameraPos.y = 0;
    m_worldDims.x = 100;
    m_worldDims.y = 100;
    m_music = 1;
    m_region = 2;
    m_missionTitle[0] = '\0';
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            m_decor[i, j]->icon = -1;
            m_bigDecor[i, j]->icon = 1;
        }
    }
    m_decor[3, 4]->icon = 40;
    m_decor[4, 4]->icon = 38;
    m_decor[5, 4]->icon = 39;
    for (int k = 0; k < Decor.MAXMOVEOBJECT; k++)
    {
        m_moveObject[k]->type = 0;
    }
    FlushBalleTraj();
    FlushMoveTraj();
    m_moveObject[0]->type = 5;
    m_moveObject[0]->stepAdvance = 1;
    m_moveObject[0]->stepRecede = 1;
    m_moveObject[0]->timeStopStart = 0;
    m_moveObject[0]->timeStopEnd = 0;
    m_moveObject[0]->posStart.x = 258;
    m_moveObject[0]->posStart.y = 196;
    m_moveObject[0]->posEnd = m_moveObject[0]->posStart;
    m_moveObject[0]->posCurrent = m_moveObject[0]->posStart;
    m_moveObject[0]->phase = 0;
    m_moveObject[0]->step = 1;
    m_moveObject[0]->time = 0;
    m_moveObject[0]->channel = 10;
    m_moveObject[0]->icon = 0;
    m_moveObject[1]->type = 7;
    m_moveObject[1]->stepAdvance = 1;
    m_moveObject[1]->timeStopStart = 0;
    m_moveObject[1]->timeStopEnd = 0;
    m_moveObject[1]->posStart.x = 450;
    m_moveObject[1]->posStart.y = 196;
    m_moveObject[1]->posEnd = m_moveObject[1]->posStart;
    m_moveObject[1]->posCurrent = m_moveObject[1]->posStart;
    m_moveObject[1]->phase = 0;
    m_moveObject[1]->step = 1;
    m_moveObject[1]->time = 0;
    m_moveObject[1]->channel = 10;
    m_moveObject[1]->icon = 29;
    m_blupiStartPos.x = 66;
    m_blupiStartPos.y = 192 + Decor.BLUPIOFFY;
    m_blupiStartDir = 2;
    m_blupiAction = 1;
    m_blupiPhase = 0;
    m_blupiIcon = 0;
    m_blupiChannel = 2;
    m_blupiFocus = TRUE;
    m_blupiAir = FALSE;
    m_blupiHelico = FALSE;
    m_blupiOver = FALSE;
    m_blupiJeep = FALSE;
    m_blupiTank = FALSE;
    m_blupiSkate = FALSE;
    m_blupiNage = FALSE;
    m_blupiSurf = FALSE;
    m_blupiSuspend = FALSE;
    m_blupiJumpAie = FALSE;
    m_blupiShield = FALSE;
    m_blupiPower = FALSE;
    m_blupiCloud = FALSE;
    m_blupiHide = FALSE;
    m_blupiInvert = FALSE;
    m_blupiBalloon = FALSE;
    m_blupiEcrase = FALSE;
    m_blupiMotorHigh = FALSE;
    m_blupiPosHelico.x = -1;
    m_blupiActionOuf = 0;
    m_blupiTimeNoAsc = 0;
    m_blupiTimeMockery = 0;
    m_blupiVitesseX = 0.0;
    m_blupiVitesseY = 0.0;
    m_blupiValidPos = m_blupiStartPos;
    m_blupiFront = FALSE;
    m_blupiBullet = 0;
    m_blupiCle = 0;
    m_blupiPerso = 0;
    m_blupiDynamite = 0;
    m_nbTresor = 0;
    m_totalTresor = 1;
    m_goalPhase = 0;
    m_scrollPoint = m_blupiStartPos;
    m_scrollAdd.x = 0;
    m_scrollAdd.y = 0;
    m_term = 0;
    byeByeObjects.Clear();
}

void CDecor::SetTime(int time)
{
    m_time = time;
}

int CDecor::GetTime()
{
    return m_time;
}

void CDecor::PlayPrepare(BOOL bTest)
{
    if (bTest)
    {
        m_nbVies = 3;
    }
    m_blupiPos = m_blupiStartPos;
    m_blupiDir = m_blupiStartDir;
    if (m_blupiDir == 1)
    {
        m_blupiIcon = 4;
    }
    else
    {
        m_blupiIcon = 0;
    }
    m_blupiAction = 1;
    m_blupiPhase = 0;
    m_blupiFocus = TRUE;
    m_blupiAir = FALSE;
    m_blupiHelico = FALSE;
    m_blupiOver = FALSE;
    m_blupiJeep = FALSE;
    m_blupiTank = FALSE;
    m_blupiSkate = FALSE;
    m_blupiNage = FALSE;
    m_blupiSurf = FALSE;
    m_blupiSuspend = FALSE;
    m_blupiJumpAie = FALSE;
    m_blupiShield = FALSE;
    m_blupiPower = FALSE;
    m_blupiCloud = FALSE;
    m_blupiHide = FALSE;
    m_blupiInvert = FALSE;
    m_blupiBalloon = FALSE;
    m_blupiEcrase = FALSE;
    m_blupiMotorHigh = FALSE;
    m_blupiActionOuf = 0;
    m_blupiTimeNoAsc = 0;
    m_blupiTimeMockery = 0;
    m_blupiValidPos = m_blupiPos;
    m_blupiBullet = 0;
    m_blupiCle = 0;
    m_blupiPerso = 0;
    m_blupiDynamite = 0;
    m_nbTresor = 0;
    m_totalTresor = 0;
    for (int i = 0; i < Decor.MAXMOVEOBJECT; i++)
    {
        if (m_moveObject[i]->type == 5)
        {
            m_totalTresor++;
        }
        m_moveObject[i]->posCurrent = m_moveObject[i]->posStart;
        m_moveObject[i]->step = 1;
        m_moveObject[i]->phase = 0;
        m_moveObject[i]->time = 0;
        if (m_moveObject[i]->type == 5 ||
            m_moveObject[i]->type == 6 ||
            m_moveObject[i]->type == 25 ||
            m_moveObject[i]->type == 26 ||
            m_moveObject[i]->type == 40 ||
            m_moveObject[i]->type == 2 ||
            m_moveObject[i]->type == 3 ||
            m_moveObject[i]->type == 96 ||
            m_moveObject[i]->type == 97)
        {
            m_moveObject[i]->phase = m_random.Next(23);
        }
        if (m_moveObject[i]->type == 23)
        {
            m_moveObject[i]->type = 0;
        }
    }
    m_goalPhase = 0;
    MoveObjectSort();
    m_scrollPoint = m_blupiPos;
    m_scrollAdd.x = 0;
    m_scrollAdd.y = 0;
    m_blupiPosHelico.x = -1;
    m_blupiMotorSound = 0;
    m_blupiFront = FALSE;
    m_blupiNoBarre = 0;
    m_blupiValidPos = m_blupiPos;
    m_blupiFifoNb = 0;
    m_blupiTimeFire = 0;
    m_voyageIcon = -1;
    m_jauges[0].SetHide(TRUE);
    m_jauges[1].SetHide(TRUE);
    m_bFoundCle = FALSE;
    m_term = 0;
    m_time = 0;
    m_bPause = FALSE;
    MoveStep();
    m_scrollPoint.x = m_blupiPos.x + 30 + m_scrollAdd.x;
    m_scrollPoint.y = m_blupiPos.y + 30 + m_scrollAdd.y;
}

void CDecor::BuildPrepare()
{
    for (int i = 0; i < MAXMOVEOBJECT; i++)
    {
        m_moveObject[i]->posCurrent = m_moveObject[i]->posStart;
        m_moveObject[i]->step = 1;
        m_moveObject[i]->time = 0;
        m_moveObject[i]->phase = 0;
        if (m_moveObject[i]->type == 23)
        {
            m_moveObject[i]->type = 0;
        }
    }
    m_voyageIcon = -1;
    m_time = 0;
    m_bPause = FALSE;
}

void CDecor::Build()
{
    POINT posDecor = DecorNextAction();
    POINT pos;
    pos.x = posDecor.x * 2 / 3;
    pos.y = posDecor.y * 2 / 3;
    int num = 1;
    POINT tinyPoint;
    tinyPoint.x = m_drawBounds.left;
    RECT rect;
    rect.left = pos.x % 640;
    rect.right = 640;

    for (int i = 0; i < 3; i++)
    {
        tinyPoint.y = m_drawBounds.top;
        rect.top = pos.y % 480;
        rect.bottom = 480;
        for (int j = 0; j < 2; j++)
        {
            m_pPixmap->DrawPart(3, tinyPoint, rect);
            tinyPoint.y += (rect.bottom - rect.top) - num;
            rect.top = 0;
            rect.bottom = 480;
        }
        tinyPoint.x += (rect.right - rect.left) - num;
        rect.left = 0;
        rect.right = 640;
        if (tinyPoint.x > m_drawBounds.right)
        {
            break;
        }
        tinyPoint.x = m_drawBounds.left - posDecor.x % 64 - 64;
        for (int i = posDecor.x / 64 - 1; i < posDecor.x / 64 + (m_drawBounds.right - m_drawBounds.left) / 64 + 3; i++) {
            tinyPoint.y = m_drawBounds.top - posDecor.y % 64 + 2 - 64;
            for (int j = posDecor.y / 64 - 1; j < posDecor.y / 64 + (m_drawBounds.bottom - m_drawBounds.top) / 64 + 2; j++)
            {
                if (i >= 0 && i < 100 && j >= 0 && j < 100)
                {
                    int num2 = m_bigDecor[i, j].icon;
                }
            }
        }
    }
}

void CDecor::DrawInfo()
{
    POINT pos;
    char text[100];

    pos.x = 210;
    pos.y = 417;

    for (int i = 0; i < m_nbVies; i++)
    {
        m_pPixmap->HudIcon(2, 48, pos);
        pos.x += 16;
    }
    pos.x = 570;
    pos.y = 442;
    for (int i = 0; i < m_blupiBullet; i++)
    {
        m_pPixmap->HudIcon(10, 176, pos);
        pos.x += 4;
    }
    if (m_blupiPerso > 0)
    {
        pos.x = 0;
        pos.y = 438;
        m_pPixmap->HudIcon(4, 108, pos);
        m_blupiPerso->sprintf(text, "=_%d");
        pos.x = 32;
        pos.y = 452;
        m_pPixmap->DrawText(pos, text, 0.7);
    }
    if (m_blupiDynamite > 0)
    {
        pos.x = 505;
        pos.y = 414;
        m_pPixmap->HudIcon(10, 252, pos);
    }
    if (m_blupiDynamite > 0)
    {
        pos.x = 505;
        pos.y = 414;
        m_pPixmap->HudIcon(10, 252, pos);
    }
    if ((m_blupiCle & 1) != 0)
    {
        pos.x = 520;
        pos.y = 418;
        m_pPixmap->HudIcon(10, 215, pos);
    }
    if ((m_blupiCle & 2) != 0)
    {
        pos.x = 530;
        pos.y = 418;
        m_pPixmap->HudIcon(10, 222, pos);
    }
    if ((m_blupiCle & 4) != 0)
    {
        pos.x = 540;
        pos.y = 418;
        m_pPixmap->HudIcon(10, 229, pos);
    }
    if (m_mission != 1 && m_mission % 10 != 0 || m_bPrivate)
    {
        RECT rect;

        rect.left = 410 + m_pPixmap->Origin.x;
        rect.right = 510 + m_pPixmap->Origin.x;
        rect.top = 445;
        rect.bottom = 480;
        m_pPixmap->DrawIcon(14, 15, rect, 0.6, FALSE);
        
    }
}

POINT CDecor::DecorNextAction()
{
    int num = 0;
    if (m_decorAction == 0 || m_bPause)
    {
        m_posDecor;
    }
    POINT posDecor = m_posDecor;
    while (tables->table_decor_action[num] != 0)
    {
        if (m_decorAction == tables->table_decor_action[num])
    }
}

BOOL CDecor::LoadBackgroundImages()
{
    char filename[52];
    POINT totalDim, iconDim;
    
    if (m_region == m_lastRegion) return TRUE;
    m_lastRegion == m_region;

    totalDim.x = DIMCELX * 2 * 16;
    totalDim.y = DIMCELY * 2 * 6;
    iconDim.x = DIMCELX * 2;
    iconDim.y = DIMCELY * 2;
    sprintf(filename, "image\\decor%.3d.blp", m_region);
    if (!m_pPixmap->Cache(CHFLOOR, filename, totalDim, iconDim, FALSE))
        return FALSE;

    return TRUE;
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

void CDecor::GetBlupiInfo(BOOL bHelico, BOOL bJeep, BOOL bSkate, BOOL bNage)
{
    bHelico = m_blupiHelico;
    bJeep = (m_blupiJeep | m_blupiTank);
    bSkate = m_blupiSkate;
    bNage = (m_blupiNage | m_blupiSurf);
}

void CDecor::MoveObjectSort()
{
    CDecor.MoveObject src = default(CDecor->MoveObject);
    int num = 0;
    for (int i = 0; i < Decor.MAXMOVEOBJECT; i++)
}

int CDecor::GetMissionTitle()
{
    return m_missionTitle;
}

void CDecor::GetMissionsCleared()
{

}

void CDecor::SetDemoState(BOOL demoState)
{
    m_demoState = demoState;
}
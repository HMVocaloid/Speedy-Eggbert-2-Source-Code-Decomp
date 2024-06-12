// CDecor.cpp
//

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
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
    m_team = 0;
    m_netPacketsSent = 0;
    m_netPacketsSent2 = 0;
    m_netPacketsRecieved = 0;
    m_netPacketsRecieved2 = 0;
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
    InitDecor();
    m_jauges->Create(m_hWnd, m_pPixmap, m_pSound, 169, 450, 1, FALSE);
    m_jauges->SetHide(TRUE);
    m_jauges->Create(m_hWnd, m_pPixmap, m_pSound, 295, 450, 3, FALSE);
    m_jauges->SetHide(TRUE);
}

// The only seemingly sane function.

BOOL CDecor::LoadImages()
{
    POINT totalDim, iconDim;
    char filename[52];

    if (m_lastRegion == m_region) return TRUE;
    m_lastRegion = m_region;

    totalDim.x = DIMCELX * 2 * 16;
    totalDim.y = DIMCELY * 2 * 6;
    iconDim.x = DIMCELX * 2;
    iconDim.y = DIMCELY * 2;
        sprintf(filename, "decor%.3d.blp", m_region);
        if (!m_pPixmap->Cache2(CHBACK, filename, totalDim, iconDim, FALSE)) return FALSE;
        if (m_region == 0)
        {
            return FALSE;
    }
        return TRUE;
}

void CDecor::InitGamer()
{
    m_nbVies = 3;

}

// The fuck does this even do?

void CDecor::InitDecor(int channel, int icon)
{
    int i;

    m_cameraPos.x = 0;
    m_cameraPos.y = 0;
    m_worldDims.x = 100;
    m_worldDims.y = 100;
    m_music = 1;
    m_region = 2;
    m_missionTitle[0] = '\0';
    m_decorAction = 0;
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
    for (int k = 0; k < MAXMOVEOBJECT; k++)
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

// Basically the same as the other fucking function

void CDecor::PlayPrepare(BOOL bTest)
{
    if (bTest)
    {
        m_nbVies = 3;
    }

    if (m_bMulti == 0) {
        m_blupiPos = m_blupiStartPos;
        m_blupiDir = m_blupiStartDir;
    }
    else
    {
        m_nbVies = 10;
        m_blupiPos = m_blupiStartPos;
        m_blupiDir = m_blupiStartDir;

    }
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
        if (m_moveObject[i]->type == TYPE_BALLE)
        {
            m_moveObject[i]->type = TYPE_empty;
        }
        if ((m_bMulti != FALSE) && (m_moveObject[i] == TYPE_CAISSE) || (m_moveObject[i] == TYPE_GOAL) || (m_moveObject[i] == TYPE_CLE) || (m_moveObject[i] == TYPE_BLUPIHELICO) || (m_moveObject[i] == TYPE_BLUPITANK))
        {
            m_moveObject[i]->type = TYPE_empty;
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

// Sort of makes sense.

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

// Fuck this function. That's all I can say.

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
                    int channel = 9;
                    if (num2 != -1)
                    {
                        pos.x = tinyPoint.x;
                        pos.y = tinyPoint.y;
                        if (num2 == 203)
                        {
                            num2 = table[m_index].table_marine[m_time / 3 % 11];
                            channel = 1;
                        }
                        if (num2 >= 66 && num2 <= 68)
                        {
                            pos.y -= 13;
                        }
                        if (num2 >= 87 && num <= 89)
                        {
                            pos.y -= 2;
                        }
                        m_pPixmap->QuickIcon(channel, num2, pos);
                    }
                }
            }   tinyPoint.y += 64;
            tinyPoint.x += 64;
        }
    }
    tinyPoint.x = m_drawBounds.left - posDecor.x % 64;
    for (int i = posDecor.x / 64; i < posDecor.x / 64 + (m_drawBounds.right - m_drawBounds.left) / 64 + 2; i++)
    {
        tinyPoint.y = m_drawBounds.top - posDecor.y % 64;
        for (int j = posDecor.y / 64; j < posDecor.y / 64 + (m_drawBounds.bottom - m_drawBounds.top) / 64 + 2; j++)
            if (i >= 0 && i < 100 && j >= 0 && j < 100 && m_decor[i, j]->icon != -1)
            {
                int num2 = m_decor[i, j]->icon;
                if (num2 == 384 || num2 == 385)
                {
                    m_pPixmap->QuickIcon(1, num2, tinyPoint);
                }
            }

    }
}

BOOL CDecor::BlitzActif(int celx, int cely)
{
    POINT pos;
    pos.x = celx * 64;
    pos.y = cely * 64;

    int num = m_time % 100;

    if (m_decor[celx, cely - 1]->icon == 304 && (num == 0 || num == 7 || num == 18 || num == 25 || num == 33 || num == 44) && cely > 0)
    {
        PlaySound(69, pos);
    }
    return num % 2 == 0 && num < 50;
}


void CDecor::DrawInfo()
{
    POINT pos;
    char text[100];

    if (m_phase == WM_PHASE_PLAY || WM_PHASE_PLAYTEST)
    {

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

void CDecor::TreatInput(UINT input)
{
    m_keyPress = input;
    if (m_blupiInvert != 0)
    {
        if ((input & INPUT_LEFT) != 0)
        {
            m_keyPress = input & ~INPUT_LEFT | INPUT_RIGHT;
        }
        if ((input & INPUT_RIGHT) != 0)
        {
            m_keyPress = m_keyPress & ~INPUT_RIGHT | INPUT_LEFT;
        }
    }
}

void CDecor::SetSpeedX(double speed)
{
    if (m_blupiInvert)
    {
        speed = -speed;
    }
    m_blupiSpeedX = speed;
}

void CDecor::SetSpeedY(double speed)
{
    m_blupiSpeedY = speed;
}

int CDecor::SoundEnviron(int sound, int obstacle)
{
    if ((obstacle >= 32 && obstacle <= 34) || (obstacle >= 41 && obstacle <= 47) || (obstacle >= 139 && obstacle <= 143))
    {
        if (sound == 4)
        {
            return 79;
        }
        if (sound == 3)
        {
            return 78;
        }
    }
    if ((obstacle >= 1 && obstacle <= 28) || (obstacle >= 78 && obstacle <= 90) || (obstacle >= 250 && obstacle <= 260) || (obstacle >= 311 && obstacle <= 316) || (obstacle >= 324 && obstacle <= 329))
    {
        if (sound == 4)
        {
            return 81;
        }
        if (sound == 3)
        {
            return 80;
        }
    }
    if ((obstacle >= 284 && obstacle <= 303) || obstacle == 338)
    {
        if (sound == 4)
        {
            return 83;
        }
        if (sound == 3)
        {
            return 82;
        }
    }
    if (obstacle >= 341 && obstacle <= 363)
    {
        if (sound == 4)
        {
            return 85;
        }
        if (sound == 3)
        {
            return 84;
        }
    }
    if (obstacle >= 215 && obstacle <= 234)
    {
        if (sound == 4)
        {
            return 87;
        }
        if (sound == 3)
        {
            return 86;
        }
    }
    if (obstacle >= 246 && obstacle <= 249)
    {
        if (sound == 4)
        {
            return 89;
        }
        if (sound == 3)
        {
            return 88;
        }
    }
    if (obstacle >= 107 && obstacle <= 109)
    {
        if (sound == 4)
        {
            return 91;
        }
        if (sound == 3)
        {
            return 90;
        }
    }
    return sound;
}

void CDecor::PlaySound(int sound, POINT pos)
{
    {
        if (m_blupiHide && (sound == 1 || sound == 2 || sound == 3 || sound == 4 || sound == 5 || sound == 6 || sound == 7 || sound == 20 || sound == 21 || sound == 22 || sound == 23 || sound == 24 || sound == 25 || sound == 27 || sound == 32 || sound == 34 || sound == 35 || sound == 36 || sound == 37 || sound == 38 || sound == 39 || sound == 40 || sound == 46 || sound == 47 || sound == 48 || sound == 49 || sound == 64 || sound == 65 || sound == 78 || sound == 79 || sound == 80 || sound == 81 || sound == 82 || sound == 83 || sound == 84 || sound == 85 || sound == 86 || sound == 87 || sound == 88 || sound == 89 || sound == 90 || sound == 91))
        {
            return;
        }
        pos.x -= m_posDecor.y;
        pos.y -= m_posDecor.y;
        m_pSound->PlayImage(sound, pos);
    }
}

void CDecor::StopSound(CSound sound)
{
    m_pSound->StopSound(sound);
    if (sound == SOUND_16_HELICOHIGH)
    {
        m_bHelicopterFlying = FALSE;
    }
    if (sound == SOUND_18_HELICOLOW)
    {
        m_bHelicopterStationary = FALSE;
    }
    if (sound == SOUND_29_JEEPHIGH)
    {
        m_bCarMoving = FALSE;
    }
    if (sound == SOUND_31_JEEPLOW)
    {
        m_bCarStationary = FALSE;
    }
    return;
}

void CDecor::AdaptMotorVehicleSound()
{
    POINT blupiPos = m_blupiPos;
    blupiPos.x -= m_posDecor.x;
    blupiPos.y -= m_posDecor.y;

    if (m_bHelicopterFlying != FALSE)
    {
        m_pSound->PlayImage(16, blupiPos);
    }
    if (m_bHelicopterStationary != FALSE)
    {
        m_pSound->PlayImage(18, blupiPos);
    }
    if (m_bCarMoving != FALSE)
    {
        m_pSound->PlayImage(29, blupiPos);
    }
    if (m_bCarStationary != FALSE)
    {
        m_pSound->PlayImage(31, blupiPos);
    }
    return;
}

// TODO: Add VehicleSoundsPhase

void CDecor::UpdateCaisse()
{
    m_nbRankCaisse = 0;
    for (int i = 0; i < MAXMOVEOBJECT; i++)
    {
        if (m_moveObject[i]->type == 12)
        {
            m_rankCaisse[m_nbRankCaisse++] = i;
        }
    }
}

BOOL CDecor::TestPushCaisse(int i, POINT pos, BOOL bPop)
{
    POINT move;

    move.x = pos.x - m_moveObject[i]->posCurrent.x;
    move.y = 0;
    SearchLinkCaisse(i, bPop);
    int y = m_moveObject[i]->posCurrent.y;
    for (int j = 0; j < m_nbLinkCaisse; j++)
    {
        i = m_linkCaisse[j];
        if (!TestPushOneCaisse(i, move, y))
        {
            return FALSE;
        }
    }
    for (int j = 0; j < m_nbLinkCaisse; j++)
    {
        i = m_linkCaisse;
        int num = i;
        m_moveObject[num]->posCurrent.x = m_moveObject[num]->posCurrent.x + move.x;
        m_moveObject[num]->posStart.x = m_moveObject[num]->posStart.x + move.x;
        int num2 = i;
        m_moveObject[num]->posEnd.x = m_moveObject[num]->posEnd.x + move.x;
    }
    return TRUE;
}

BOOL CDecor::TestPushOneCaisse(int i, POINT move, int b)
{

}

void CDecor::SearchLinkCaisse(int rank, BOOL bPop)
{
    m_nbLinkCaisse = 0;
    AddLinkCaisse(rank);
    POINT posCurrent = m_moveObject;

    BOOL flag;
    do
    {
        flag = FALSE;
        for (int i = 0; i < m_nbLinkCaisse; i++)
        {
            int num = m_linkCaisse[i];
            if (m_moveObject[num]->posCurrent.y <=
                posCurrent.y && (!bPop || (m_moveObject
                    [num]->posCurrent.x >= posCurrent.x - 32 &&
                    m_moveObject[num]->posCurrent.x <=
                    posCurrent.x + 32)))
            {

            }
        }
    }
}

BOOL CDecor::AddLinkCaisse(int rank)
{

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
         m_blupiChannel == CHBLUPI ||
         m_team > 0);{
    return m_team + 10;
         }
    return m_blupiChannel;
}

int CDecor::GetBlupiChannel()
{
    int m_blupiChannel = CHBLUPI;


    if ( m_bMulti != 0 ||
         m_team > 0);{
        return m_team + 10;
         }
    return CHBLUPI;
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

int CDecor::GetNbVies()
{
    return m_nbVies;
}

void CDecor::SetNbVies(int lives)
{
    m_nbVies = lives;
}

BOOL CDecor::GetPause()
{
    return m_bPause;
}

void CDecor::SetPause(BOOL bPause)
{
    m_bPause = bPause;
}


void CDecor::GetDoors(int doors)
{
    for (int i = 0; i < m_doors; i++)
    {
        doors[i] = (int)
    }
}


void CDecor::SetAllMissions(BOOL CheatDoors)
{
    m_bCheatDoors = CheatDoors;
    m_bPrivate, m_mission->AdaptDoors;
    return;
}

void CDecor::CheatAction(int cheat, MoveObject moveObject)
{
    if (cheat == cheat_cleanall)
    {
        for (int i = 0; i < MAXMOVEOBJECT; i++)
        {
            if (m_moveObject[i]->type == 2 || m_moveObject[i]->type == 3 || m_moveObject[i]->type == 96 ||
                m_moveObject[i]->type == 97 || m_moveObject[i]->type == 4 || m_moveObject[i]->type == 16 ||
                m_moveObject[i]->type == 17 || m_moveObject[i]->type == 20 || m_moveObject[i]->type == 44 ||
                m_moveObject[i]->type == 54 || m_moveObject[i]->type == 32 || m_moveObject[i]->type == 33)
            {
                m_decorAction = 1;
                m_decorPhase = 0;
                m_moveObject[i]->type = 8;
                m_moveObject[i]->phase = 0;

               MoveObject[] moveObject = m_moveObject;
               int num = i;
               moveObject[num]->posCurrent.x = moveObject[num].posCurrent.x - 34;
               MoveObject[] moveObject2 = m_moveObject;
               int num2 = i;
               moveObject2[num2]->posCurrent.y = moveObject2[num2].posCurrent.y - 34;
               m_moveObject[i]->posStart = m_moveObject[i]->posCurrent;
               m_moveObject[i]->posEnd = m_moveObject[i]->posCurrent;
               MoveObjectStepIcon(i);
               m_moveObject[i]->posCurrent->PlaySound(10);

            }
        }
    }
    if (cheat == cheat_funskate)
    {
        m_blupiAir = FALSE;
        m_blupiHelico = FALSE;
        m_blupiOver = FALSE;
        m_blupiJeep = FALSE;
        m_blupiTank = FALSE;
        m_blupiSkate = TRUE;
        m_blupiNage = FALSE;
        m_blupiSurf = FALSE;
        m_blupiVent = FALSE;
        m_blupiSuspend = FALSE;
        StopSound(16);
        StopSound(18);
        StopSound(29);
        StopSound(31);
    }
    if (cheat == cheat_givecopter)
    {
        m_blupiAir = FALSE;
        m_blupiHelico = TRUE;
        m_blupiOver = FALSE;
        m_blupiJeep = FALSE;
        m_blupiTank = FALSE;
        m_blupiSkate = FALSE;
        m_blupiNage = FALSE;
        m_blupiSurf = FALSE;
        m_blupiVent = FALSE;
        m_blupiSuspend = FALSE;
    }
    if (cheat == cheat_jeepdrive)
    {
        m_blupiAir = FALSE;
        m_blupiHelico = FALSE;
        m_blupiOver = FALSE;
        m_blupiJeep = TRUE;
        m_blupiTank = FALSE;
        m_blupiSkate = FALSE;
        m_blupiNage = FALSE;
        m_blupiSurf = FALSE;
        m_blupiVent = FALSE;
        m_blupiSuspend = FALSE;
    }
    if (cheat == cheat_alltreasure)
    {
        for (int i = 0; i < MOVEOBJECT; i++)
        {
            if (m_moveObject[i]->type == 5)
            {
                m_moveObject[i]->type == 0;
                m_nbTresor++;
                OpenDoorsTresor();
                m_moveObject[i]->posCurrent->PlaySound(11);
            }
        }
    }
    if (cheat == cheat_endgoal)
    {
        for (int i = 0; i < MAXMOVEOBJECT; i++)
        {
            if (m_moveObject[i]->type == 7 || m_moveObject[i]->type == 21)
            {
                m_blupiPos = m_moveObject[i]->posCurrent;
                if (m_nbTresor >= m_totalTresor)
                {
                    if (m_moveObject[i]->type == 21)
                    {
                        m_bFoundCle = TRUE;
                    }
                    StopSound(16);
                    StopSound(18);
                    StopSound(29);
                    StopSound(31);
                    PlaySound(14);
                    m_blupiAction = 13;
                    m_blupiPhase = 0;
                    m_blupiFocus = FALSE;
                    m_blupiFront = TRUE;
                    m_blupiAir = FALSE;
                    m_blupiHelico = FALSE;
                    m_blupiOver = FALSE;
                    m_blupiJeep = TRUE;
                    m_blupiTank = FALSE;
                    m_blupiSkate = FALSE;
                    m_blupiNage = FALSE;
                    m_blupiSurf = FALSE;
                    m_blupiVent = FALSE;
                    m_blupiSuspend = FALSE;
                    m_blupiShield = FALSE;
                    m_blupiPower = FALSE;
                    m_blupiCloud = FALSE;
                    m_blupiHide = FALSE;
                    m_blupiInvert = FALSE;
                    m_blupiBalloon = FALSE;
                    m_blupiEcrase = FALSE;
                }
                else
                {
                    (m_moveObject[i]->posCurrent)->PlaySound(13);
                }
                m_goalPhase = 50;
            }
        }
    }
    if (cheat == cheat_roundshield)
    {
        m_blupiPos->PlaySound(42);
        m_blupiShield = TRUE;
        m_blupiPower = FALSE;
        m_blupiCloud = FALSE;
        m_blupiHide = FALSE;
        m_blupiTimeShield = 100;
        m_blupiPosMagic = m_blupiPos;
        m_jauges[1]->SetHide(FALSE);
    }
    if (cheat == cheat_quicklollipop)
    {
        m_blupiAction = 49;
        m_blupiPhase = 0;
        m_blupiHelico = FALSE;
        m_blupiOver = FALSE;
        m_blupiJeep = FALSE;
        m_blupiTank = FALSE;
        m_blupiSkate = FALSE;
        m_blupiShield = FALSE;
        m_blupiPower = FALSE;
        m_blupiCloud = FALSE;
        m_blupiHide = FALSE;
        m_blupiFocus = FALSE;
        m_blupiPos->PlaySound(50);
    }
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

BOOL CDecor::BlupiIsGround()
{
    if (m_blupiTransport == -1)
    {
        RECT rect = m_blupiPos->BlupiRect;
        rect.top = m_blupiPos.y + 60 - 2;
        rect.bottom = m_blupiPos.y + 60 - 1;
        return DecorDetect(rect);
    }
}

RECT CDecor::BlupiRect(POINT pos)
{
    RECT result;
    if (m_blupiNage || m_blupiSurf)
    {
        result.left = pos.x + 12;
        result.right = pos.x + 60 - 12;
        if (m_blupiAction == 1)
        {
            result.top = pos.y + 5;
            result.bottom = pos.y + 60 - 10;
        }
        else
        {
            result.top = pos.y + 15;
            result.bottom = pos.y + 60 - 10;
        }
    }
    else if (m_blupiJeep)
    {
        result.left = pos.x + 2;
        result.right = pos.x + 60 - 2;
        result.top = pos.y + 10;
        result.bottom = pos.y + 60 - 2;
    }
    else if (m_blupiTank)
    {
        result.left = pos.x + 2;
        result.right = pos.x + 60 - 2;
        result.top = pos.y + 10;
        result.bottom = pos.y + 60 - 2;
    }
    else if (m_blupiOver)
    {
        result.left = pos.x + 2;
        result.right = pos.x + 60 - 2;
        result.top = pos.y + 2;
        result.bottom = pos.y + 60 - 2;
    }
    else if (m_blupiBalloon)
    {
        result.left = pos.x + 10;
        result.right = pos.x + 60 - 10;
        result.top = pos.y + 5;
        result.bottom = pos.y + 60 - 2;
    }
    else if (m_blupiEcrase)
    {
        result.left = pos.x + 5;
        result.right = pos.x + 60 - 5;
        result.top = pos.y + 39;
        result.bottom = pos.y + 60 - 2;
    }
    else
    {
        result.left = pos.x + 12;
        result.right = pos.x + 60 - 12;
        result.top = pos.y + 11;
        result.bottom = pos.y + 60 - 2;
    }
    return result;
}

void CDecor::BlupiAdjust()
{
    RECT tinyRect = m_blupiPos->BlupiRect;

    if (DecorDetect(tinyRect))
    {
        return;
    }
    for (int i = 0; i < 50; i++)
    {
        RECT rect = tinyRect;
        rect.bottom = rect.top + 2;
        rect.left = m_blupiPos.x + 12;
        rect.right = m_blupiPos.x + 60 - 12;
        if (DecorDetect(rect))
        {
            break;
        }
        tinyRect.top += 2;
        tinyRect.bottom += 2;
        m_blupiPos.y = m_blupiPos.y + 2;
    }
    for (int i = 0; i < 50; i++)
    {
        RECT rect = tinyRect;
        rect.right = rect.left + 2;
        rect.top = m_blupiPos.y + 11;
        rect.bottom = m_blupiPos.y + 60 - 2;
        if (DecorDetect(rect))
        {
            break;
        }
        tinyRect.left += 2;
        tinyRect.right += 2;
        m_blupiPos.x = m_blupiPos.x + 2;
    }
    for (int i = 0; i < 50; i++)
    {
        RECT rect = tinyRect;
        rect.left = rect.right - 2;
        rect.top = m_blupiPos.y + 11;
        rect.bottom = m_blupiPos.y + 60 - 2;
        if (DecorDetect(rect))
        {
            break;
        }
        tinyRect.left -= 2;
        tinyRect.right -= 2;
        m_blupiPos.x = m_blupiPos.x - 2;
    }
    for (int i = 0; i < 50; i++)
    {
        RECT rect = tinyRect;
        rect.right = rect.left + 2;
        if (DecorDetect(rect))
        {
            break;
        }
        tinyRect.left += 2;
        tinyRect.right += 2;
        m_blupiPos.x = m_blupiPos.x + 2;
    }
    for (int i = 0; i < 50; i++)
    {
        RECT rect = tinyRect;
        rect.left = rect.right - 2;
        if (DecorDetect(rect))
        {
            return;
        }
        tinyRect.left -= 2;
        tinyRect.right -= 2;
        m_blupiPos.x = m_blupiPos.x - 2;
    }
}

BOOL CDecor::BlupiBloque(POINT pos, int dir)
{
    RECT rect = BlupiRect(pos);
    rect.top = rect.bottom - 20;
    rect.bottom -= 2;
    if (dir > 0)
    {
        rect.left = rect.right - 2;
    }
    if (dir < 0)
    {
        rect.right = rect.left + 2;
    }
    return DecorDetect(rect);
}

void CDecor::BlupiDead(int action1, int action2)
{
    ByeByeHelco();
    if (action2 == -1)
    {
        m_blupiAction = action1;
    }
    else
    {
        m_blupiAction = ((m_random->Next() % 2 == 0) ? action1 : action2);
    }
    m_blupiPhase = 0;
    m_blupiFocus = FALSE;
    m_blupiHelico = FALSE;
    m_blupiOver = FALSE;
    m_blupiJeep = FALSE;
    m_blupiTank = FALSE;
    m_blupiSkate = FALSE;
    m_blupiNage = FALSE;
    m_blupiSurf = FALSE;
    m_blupiVent = FALSE;
    m_blupiSuspend = FALSE;
    m_blupiJumpAie = FALSE;
    m_blupiShield = FALSE;
    m_blupiPower = FALSE;
    m_blupiCloud = FALSE;
    m_blupiHide = FALSE;
    m_blupiInvert = FALSE;
    m_blupiBalloon = FALSE;
    m_blupiEcrase = FALSE;
    m_blupiRestart = FALSE;
    m_blupiActionOuf = 0;
    m_jauges[0]->SetHide(TRUE);
    m_jauges[1]->SetHide(TRUE);
    StopSound(16);
    StopSound(18);
    StopSound(29);
    StopSound(31);
    
    POINT pos;
    POINT pos2;
    if (m_blupiAction == 75)
    {
        pos.x = m_blupiPos.x - m_posDecor.x;
        pos.y = m_blupiPos.y - m_posDecor.y;
        pos2.x = m_blupiPos.x - m_posDecor.x;
        pos2.y = m_blupiPos.y - m_posDecor.y - 300;
        VoyageInit(m_pPixmap->HotSpotToHud(pos), m_pPixmap->HotSpotToHud(pos2), 230, 10);
        m_blupiPos->PlaySound(74);
    }
    if (m_blupiAction == 76)
    {
        pos.x = m_blupiPos.x - m_posDecor.x;
        pos.y = m_blupiPos.y - m_posDecor.y;
        pos2.x = m_blupiPos.x - m_posDecor.x;
        pos2.y = m_blupiPos.y - m_posDecor.y - 2000;
        VoyageInit(m_pPixmap->HotSpotToHud(pos), m_pPixmap->HotSpotToHud(pos2), 40, 10);
        m_blupiPos->PlaySound(74);
    }
    if (m_blupiAction == 77)
    {
        m_blupiPos->ObjectStart(41, -70);
        m_blupiPos->ObjectStart(41, 20);
        m_blupiPos->ObjectStart(41, -20);
        m_blupiPos->PlaySound(75);
    }
}

POINT CDecor::GetPosDecor(POINT pos)
{
    POINT result;
    if (m_dimDecor.x == 0)
    {
        result.x = 0;
    }
    else
    {
        result.x = pos.x - (m_drawBounds.right - m_drawBounds.left) / 2;
        result.x = (result.x < 0);
        result.x = (result.x > 5760) - (m_drawBounds.right - m_drawBounds.left);
    }
    if (m_dimDecor.y == 0)
    {
        result.y = 0;
    }
    else
    {
        result.y = pos.y - (m_drawBounds.bottom - m_drawBounds.top) / 2;
        result.y = (result.y < 0);
        result.y = (result.y > 5920) - (m_drawBounds.bottom - m_drawBounds.top) / 2;
    }
    return result;
}

void CDecor::BlupiAddFifo(POINT pos)
{
    if (m_blupiFifoNb < 10)
    {
        if (m_blupiFifoNb > 0 && pos.x == m_blupiFifoPos[m_blupiFifoNb - 1] && pos.y == m_blupiFifoPos[m_blupiFifoNb - 1].y)
        {
            return;
        }
        m_blupiFifoPos[m_blupiFifoNb] = pos;
        m_blupiFifoNb++;
        return;
    }
    else
    {
        if (pos.x == m_blupiFifoPos[9].x && pos.y == m_blupiFifoPos[9].y)
        {
            return;
        }
        for (int i = 0; i < 9; i++)
        {
            m_blupiFifoPos[i] = m_blupiFifoPos[i + 1];
        }
        m_blupiFifoPos[9] = pos;
        return;
    }
}

BOOL CDecor::DecorDetect(RECT rect)
{
    return DecorDetect(rect, TRUE);
}

BOOL CDecor::DecorDetect(RECT rect, BOOL bCaisse)
{
    m_detectIcon = -1;
    if (rect.left < 0 || rect.top < 0)
    {
        return TRUE;
    }
    int num;
    if (m_dimDecor.x == 0)
    {
        num = 640;
    }
    else
    {
        num = 6400;
    }
    if (rect.right > num)
    {
        return TRUE;
    }
    if (m_blupiHelico ||
        m_blupiOver ||
        m_blupiBalloon ||
        m_blupiEcrase ||
        m_blupiNage ||
        m_blupiSurf)
    {
        if (m_dimDecor.y == 0)
        {
            num = 480;
        }
        else
        {
            num = 6400;
        }
        if (rect.bottom > num)
        {
            return TRUE;
        }
    }
    int num2 = rect.left / 16;
    int num3 = (rect.right + 16 - 1) / 16;
    int num4 = rect.top / 16;
    int num5 = (rect.bottom + 16 - 1) / 16;
    RECT src;
    for (int i = num4; i <= num5; i++)
    {
        for (int j = num2; j <= num3; j++)
        {
            int num6 = j / 4;
            int num7 = i / 4;
            if (num6 >= 0 && num6 < 100 && num7 >= 0 && num7 < 100)
            {
                int icon = m_decor[num6, num7]->icon;
                if (icon >= 0 && icon < MAXQUART && (!m_blupiHelico || icon != 214) && (m_blupiOver || icon != 214) && (icon != 324 || m_time / 4 % 20 < 18))
                {
                    num6 = j % 4;
                    num7 = i % 4;
                    if (table_decor_quart[icon * 16 + num7 * 4 + num6] != 0)
                    {
                        src.left = j * 16;
                        src.right = src.left + 16;
                        src.top = i * 16;
                        src.bottom = src.top + 16;
                        RECT tinyRect;
                        if (IntersectRect(out tinyRect, src, rect))
                        {
                            m_detectIcon = icon;
                            return TRUE;
                        }
                    }

                }
            }
        }
    }
    if (!bCaisse)
    {
        return FALSE;
    }
    for (int k = 0; k < m_nbRankCaisse; k++)
    {
        int num8 = m_rankCaisse[k];
        src.left = m_moveObject[num8]->posCurrent.x;
        src.right = m_moveObject[num8]->posCurrent.x + 64;
        src.top = m_moveObject[num8]->posCurrent.y;
        src.bottom = m_moveObject[num8]->posCurrent.y + 64;
        RECT tinyRect;
        if (IntersectRect(out tinyRect, src, rect))
        {
            m_detectIcon = m_moveObject[num8]->icon;
            return TRUE;
        }
    }
    return FALSE;
}

BOOL CDecor::TestPath(RECT rect, POINT start, POINT end)
{
    int num = abs(end.x - start.x);
    int num2 = abs(end.y - start.y);

    POINT tinyPoint = start;
    if (num > num2)
    {
        RECT rect2;
        if (end.x > start.x)
        {
            for (int i = 0; i <= num; i++)
            {
                int j = i * (end.y - start.y) / num;
                rect2.left = rect.left + i;
                rect2.right = rect.right + i;
                rect2.top = rect.top + j;
                rect2.bottom = rect.bottom + j;
                if (DecorDetect(rect2))
                {
                    end = tinyPoint;
                    return FALSE;
                }
                tinyPoint.x = start.x + i;
                tinyPoint.y = start.y + j;
            }
        }
        if (end.x < start.x)
        {
            for (int i = 0; i >= -num; i--)
            {
                int j = i * (start.y - end.y) / num;
                rect2.left = rect.left + i;
                rect2.right = rect.right + i;
                rect2.top = rect.top + j;
                rect2.bottom = rect.bottom + j;
                if (DecorDetect(rect2))
                {
                    end = tinyPoint;
                    return FALSE;
                }
                tinyPoint.x = start.x + i;
                tinyPoint.y = start.y + j;
            }
        }
    }
    else
    {
        RECT rect2;
        if (end.y > start.y)
        {
            for (int j = 0; j <= num2; j++)
            {
                int i = j * (end.x - start.x) / num2;
                rect2.left = rect.left + i;
                rect2.right = rect.right + i;
                rect2.top = rect.top + j;
                rect2.bottom = rect.bottom + j;
                if (DecorDetect(rect2))
                {
                    end = tinyPoint;
                    return FALSE;
                }
                tinyPoint.x = start.x + i;
                tinyPoint.y = start.y + j;
            }
        }
        if (end.y < start.y)
        {
            for (int j = 0; j >= -num2; j--)
            {
                int i = j * (start.x - end.x) / num2;
                rect2.left = rect.left + i;
                rect2.right = rect.right + i;
                rect2.top = rect.top + j;
                rect2.bottom = rect.bottom + j;
                if (DecorDetect(rect2))
                {
                    end = tinyPoint;
                    return FALSE;
                }
                tinyPoint.x = start.x + i;
                tinyPoint.y = start.y + j;
            }
        }
    }
    return TRUE;
}

int CDecor::IsWorld(POINT pos)
{
    pos.x += 30;
    pos.y += 30;
    if (pos.x < 0 || pos.x >= 6400 || pos.y < 0 || pos.y >= 6400)
    {
        return -1;
    }
    int icon = m_decor[pos.x / 64, pos.y / 64]->icon;
    if (icon >= 158 && icon <= 165)
    {
        return icon - 158 + 1;
    }
    if (icon >= 166 && icon <= 173)
    {
        return icon - 166 + 1;
    }
    if (icon == 309 || icon == 310)
    {
        return 9;
    }
    if (icon >= 411 && icon <= 415)
    {
        return icon - 411 + 10;
    }
    if (icon >= 416 && icon <= 420)
    {
        return icon - 416 + 10;
    }
    if (icon >= 174 && icon <= 181)
    {
        return icon - 174 + 1;
    }
    if (icon == 184)
    {
        return 199;
    }
    return -1;
}

BOOL CDecor::SearchDoor(int n, POINT cel, POINT blupi)
{
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            int icon = m_decor[i, j]->icon;
            if (icon >= 174 && icon <= 181 && icon - 174 + 1 == n)
            {
                if (i > 0 && m_decor[i - 1, j]->icon == 182)
                {
                    cel.x = i - 1;
                    cel.y = j;
                    blupi.x = (i - 2) * 64 + 2;
                    blupi.y = j * 64 + BLUPIOFFY;
                    return TRUE;
                }
                if (i > 1 && m_decor[i - 2, j]->icon == 182)
                {
                    cel.x = i - 2;
                    cel.y = j;
                    blupi.x = (i - 3) * 64 + 2;
                    blupi.y = j * 64 + BLUPIOFFY;
                    return TRUE;
                }
                if (i < 99 && m_decor[i + 1, j]->icon == 182)
                {
                    cel.x = i + 1;
                    cel.y = j;
                    blupi.x = (i + 2) * 64 + 2;
                    blupi.y = j * 64 + BLUPIOFFY;
                    return TRUE;
                }
                if (i < 98 && m_decor[i + 2, j]->icon == 182)
                {
                    cel.x = i + 2;
                    cel.y = j;
                    blupi.x = (i + 3) * 64 + 2;
                    blupi.y = j * 64 + BLUPIOFF;
                    return TRUE;
                }
            }
        }
    }
    return FALSE;
}

BOOL SearchGold(int n, POINT cel)
{
    for (int i = 99; i >= 0; i--)
    {
        for (int j = 99; j >= 0; j--)
        {
            if (m_decor[j, i]->icon == 183)
            {
                cel.x = j;
                cel.y = i;
                return TRUE;
            }
        }
    }
    return FALSE;
}

void CDecor::OpenDoorsTresor()
{
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            int icon = m_decor[i, j]->icon;
            if (icon >= 421 && icon <= 421 + m_nbTresor - 1)
            {
                POINT cel;
                cel.x = i;
                cel.y = j;
                OpenDoor(cel);
            }
        }
    }
}

void CDecor::OpenDoor(POINT cel)
{
    int icon = m_decor[cel.x, cel.y]->icon;
    m_decor[cel.x, cel.y]->icon = -1;
    int num = MoveObjectFree();
    m_moveObject[num]->type = 22;
    m_moveObject[num]->stepAdvance = 50;
    m_moveObject[num]->stepRecede = 1;
    m_moveObject[num]->timeStopStart = 0;
    m_moveObject[num]->timeStopEnd = 0;
    m_moveObject[num]->posStart.x = 64 * cel.x;
    m_moveObject[num]->posStart.y = 64 * cel.y;
    m_moveObject[num]->posEnd.x = 64 * cel.x;
    m_moveObject[num]->posEnd.y = 64 * (cel.y - 1);
    m_moveObject[num]->posCurrent = m_moveObject[num]->posStart;
    m_moveObject[num]->step = 1;
    m_moveObject[num]->time = 0;
    m_moveObject[num]->phase = 0;
    m_moveObject[num]->channel = 1;
    m_moveObject[num]->icon = icon;
    PlaySound(33, m_moveObject[num]->posStart);
}

void CDecor::OpenDoorsWin()
{
    m_doors[m_mission + 1] = 1;
}

void CDecor::OpenGoldsWin()
{
    m_doors[180 + m_mission / 10] = 1;
}

void CDecor::DoorsLost()
{
    m_nbVies = 3;
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

char CDecor::GetMissionTitle()
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
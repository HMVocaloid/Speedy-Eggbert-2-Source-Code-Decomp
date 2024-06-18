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
#include "dectables.h"


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
		{
			if (i >= 0 && i < 100 && j >= 0 && j < 100 && m_decor[i, j]->icon != -1)
			{
				int num2 = m_decor[i, j]->icon;
				if (num2 == 384 || num2 == 385)
				{
					m_pPixmap->QuickIcon(1, num2, tinyPoint);
				}
			}
		}	tinyPoint.y += 64;
		tinyPoint.x += 64;
    }
	m_blupiSec = 0;
	if (m_blupiFront)
	{
		double rotation = 0.0;
		if (m_blupiNage || m_blupiSurf || m_blupiHelico || m_blupiJeep)
		{
			rotation = (double)m_blupiRealRotation;
		}
		tinyPoint.x = m_drawBounds.left + m_blupiPos.x - posDecor.x;
		tinyPoint.y = m_drawBounds.top + m_blupiPos.y - posDecor.y;
		if (m_blupiJeep)
		{
			tinyPoint.y += m_blupiOffsetY;
		}
		if (m_blupiShield)
		{
			m_blupiSec = 1;
			if (m_blupiTimeShield > 25 || m_time % 4 < 2)
			{
				int num2 = table_shield_blupi[m_time / 2 % 16];
				tinyPoint.y -= 2;
				QuickIcon(10, num2, tinyPoint, m_pPixmap);
				tinyPoint.y += 2;
				QuickIcon(10, num2, tinyPoint, m_pPixmap);
			}
			QuickIcon(m_blupiChannel, m_blupiIcon, tinyPoint, 1.0, rotation, m_pPixmap);
		}
		else if (m_blupiPower)
		{
			m_blupiSec = 2;
			if (m_blupiTimeShield > 25 || m_time % 4 < 2)
			{
				int num2 = table_magicloop[m_time / 2 % 5];
				QuickIcon(10, num2, tinyPoint);
			}
			QuickIcon(m_blupiChannel, m_blupiIcon, tinyPoint, 1.0, rotation, m_pPixmap);
		}
		else if (m_blupiCloud)
		{
			m_blupiSec = 3;
			if (m_blupiTimeShield > 25 || m_time % 4 < 2)
			{
				for (int k = 0; k < 3; k++)
				{
					int num2 = 48 + (m_time + k) / 1 % 6;
					pos.x = tinyPoint.x - 34;
					pos.y = tinyPoint.y - 34;
					QuickIcon(9, num2, pos, m_pPixmap);
				}
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
               PlaySound(10, m_moveObject[i]->posCurrent);

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
                PlaySound(11, m_moveObject[i]->posCurrent);
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
        PlaySound(42, m_blupiPos);
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
        PlaySound(50, m_blupiPos);
    }
    if (cheat == cheat_tenbombs)
    {
        m_blupiPerso = 10;
        PlaySound(60, m_blupiPos);
    }
    if (cheat == cheat_birdlime)
    {
        m_blupiBullet = 10;
    }
    if (cheat == cheat_drivetank)
    {
        m_blupiAir = FALSE;
        m_blupiHelico = FALSE;
        m_blupiOver = FALSE;
        m_blupiJeep = FALSE;
        m_blupiTank = TRUE;
        m_blupiSkate = FALSE;
        m_blupiNage = FALSE;
        m_blupiSurf = FALSE;
        m_blupiVent = FALSE;
        m_blupiSuspend = FALSE;
        m_blupiCloud = FALSE;
        m_blupiHide = FALSE;
    }
    if (cheat == cheat_powercharge)
    {
        m_blupiAction = 56;
        m_blupiPhase = 0;
        m_blupiHelico = FALSE;
        m_blupiOver = FALSE;
        m_blupiJeep = FALSE;
        m_blupiTank = TRUE;
        m_blupiSkate = FALSE;
        m_blupiShield = FALSE;
        m_blupiPower = FALSE;
        m_blupiCloud = FALSE;
        m_blupiHide = FALSE;
        m_blupiJumpAie = FALSE;
        m_blupiFocus = FALSE;
        PlaySound(58, m_blupiPos);
    }
    if (cheat == cheat_hidedrink)
    {
        m_blupiAction = 55;
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
        m_blupiJumpAie = FALSE;
        m_blupiFocus = FALSE;
        PlaySound(57, m_blupiPos);
    }
    if (cheat == cheat_iovercraft)
    {
        m_blupiAir = FALSE;
        m_blupiHelico = FALSE;
        m_blupiOver = TRUE;
        m_blupiJeep = FALSE;
        m_blupiTank = FALSE;
        m_blupiSkate = FALSE;
        m_blupiNage = FALSE;
        m_blupiSurf = FALSE;
        m_blupiVent = FALSE;
        m_blupiSuspend = FALSE;
    }
    if (cheat == cheat_dynamite)
    {
        m_blupiDynamite = 1;
        PlaySound(60, m_blupiPos);
    }
    if (cheat == cheat_wellkeys)
    {
        m_blupiCle |= 7;
    }
    if (m_blupiShield && m_blupiHide && m_blupiCloud && m_blupiPower)
    {
        m_jauges[1]->SetHide(TRUE);
    }
    if (m_blupiHelico && m_blupiOver)
    {
        m_pSound->StopSound(SOUND_HELICOHIGH);
        StopSound(18);
    }
    if (m_blupiJeep && m_blupiTank)
    {
        StopSound(29);
        StopSound(31);
    }
}

/*
void CDecor::BlupiStep()
{
    POINT tinyPoint;
    POINT tinyPoint2;
    BlupiAdjust();
    m_blupiLastPos = m_blupiPos;
    POINT tinyPoint3 = m_blupiPos;
    BOOL flag = m_blupiAir;
    int blupiAction = m_blupiAction;
    BOOL flag2 = FALSE;
    BOOL flag3 = FALSE;
    tinyPoint3.x += m_blupiVector.x;
    tinyPoint3.y += m_blupiVector.y;
    if (m_blupiFocus && (tinyPoint3.y + 30) / 64 >= 99)
    {
        BlupiDead(75, -1);
        m_blupiRestart = TRUE;
        m_blupiAir = TRUE;
        m_blupiPos.y = m_blupiPos.y / 64 * 64 + BLUPIOFFY;
        PlaySound(8, m_blupiPos);
        return;
    }
    RECT rect;
    if (m_blupiVector.x != 0 || m_blupiVector.y != 0)
    {
        rect = BlupiRect(m_blupiPos);
        rect.top = m_blupiPos.y + 11;
        rect.bottom = m_blupiPos.y + 60 - 2;
        TestPath(rect, m_blupiPos, tinyPoint3);
    }
    m_blupiVent = FALSE;
    int num;
    if (m_blupiTransport == -1 && !m_blupiJeep && !m_blupiTank && !m_blupiSkate
        && m_blupiFocus)
    {
        num = m_decor[(tinyPoint3.x + 30) / 64, (tinyPoint3.y + 30) / 64]->icon;
        if (num == 110)
        {
            tinyPoint3.x -= 9;
        }
        if (num == 114)
        {
            tinyPoint3.x += 9;
        }
        if (num == 118)
        {
            tinyPoint3.y -= 20;
        }
        if (num == 122)
        {
            tinyPoint3.y += 20;
        }
        if (num >= 110 && num <= 125)
        {
            m_blupiVent = TRUE;
            rect.left = m_blupiPos.x + 12;
            rect.right = m_blupiPos.x + 60 - 12;
            rect.top = m_blupiPos.y + 11;
            rect.bottom = m_blupiPos.y + 60 - 2;
            TestPath(rect, m_blupiPos, tinyPoint3);
        }
    }
    BOOL flag4;
    if (m_blupiTransport == -1)
    {
        rect = BlupiRect(tinyPoint3);
        rect.top = tinyPoint3.y + 60 - 2;
        rect.bottom = tinyPoint3.y + 60 - 1;
        flag = !DecorDetect(rect);
    }
    else
    {
        flag4 = FALSE;
    }
    rect = BlupiRect(tinyPoint3);
    rect.top = tinyPoint3.y + 10;
    rect.bottom = tinyPoint3.y + 20;
    BOOL flag5 = DecorDetect(rect);
	int detectIcon = m_detectIcon;
	if (!m_blupiAir && !m_blupiHelico && !m_blupiOver && !m_blupiBalloon && !m_blupiEcrase && !m_blupiJeep && !m_blupiTank && !m_blupiNage && !m_blupiSurf && !m_blupiSuspend && flag4 && m_blupiFocus)
	{
		if (m_blupiFocus)
		{
			m_blupiAction = 5;
			m_blupiPhase = 0;
		}
		m_blupiVitesseY = 1.0;
		m_blupiAir = true;
		flag = true;
	}
	if (!m_blupiNage && !m_blupiSurf && !m_blupiSuspend && !m_blupiAir && IsRessort(tinyPoint3))
	{
		if ((m_blupiHelico || m_blupiOver) && !m_blupiShield && !m_blupiHide && !m_bSuperBlupi)
		{
			m_blupiHelico = false;
			m_blupiOver = false;
			tinyPoint.X = tinyPoint3.X - 34;
			tinyPoint.Y = tinyPoint3.Y - 34;
			ObjectStart(tinyPoint, 9, 0);
			m_decorAction = 1;
			m_decorPhase = 0;
			StopSound(16);
			StopSound(18);
			StopSound(29);
			StopSound(31);
			PlaySound(10, m_blupiPos);
		}
		if (m_blupiJeep && !m_blupiShield && !m_blupiHide && !m_bSuperBlupi)
		{
			m_blupiJeep = false;
			tinyPoint.X = tinyPoint3.X - 34;
			tinyPoint.Y = tinyPoint3.Y - 34;
			ObjectStart(tinyPoint, 9, 0);
			m_decorAction = 1;
			m_decorPhase = 0;
			StopSound(16);
			StopSound(18);
			StopSound(29);
			StopSound(31);
			PlaySound(10, m_blupiPos);
		}
		if (m_blupiTank && !m_blupiShield && !m_blupiHide && !m_bSuperBlupi)
		{
			m_blupiTank = false;
			tinyPoint.X = tinyPoint3.X - 34;
			tinyPoint.Y = tinyPoint3.Y - 34;
			ObjectStart(tinyPoint, 9, 0);
			m_decorAction = 1;
			m_decorPhase = 0;
			StopSound(16);
			StopSound(18);
			StopSound(29);
			StopSound(31);
			PlaySound(10, m_blupiPos);
		}
		if (m_blupiSkate && !m_blupiShield && !m_blupiHide && !m_bSuperBlupi)
		{
			m_blupiSkate = false;
			tinyPoint.X = tinyPoint3.X - 34;
			tinyPoint.Y = tinyPoint3.Y - 34;
			ObjectStart(tinyPoint, 9, 0);
			m_decorAction = 1;
			m_decorPhase = 0;
			StopSound(16);
			StopSound(18);
			StopSound(29);
			StopSound(31);
			PlaySound(10, m_blupiPos);
		}
		if (m_blupiFocus && m_blupiAction != 11 && m_blupiAction != 75 && m_blupiAction != 76 && m_blupiAction != 77 && m_blupiAction != 78 && m_blupiAction != 79 && m_blupiAction != 80 && m_blupiAction != 81)
		{
			m_blupiAction = 5;
			m_blupiPhase = 0;
		}
		if ((m_keyPress & 1) != 0 && m_blupiFocus)
		{
			m_blupiVitesseY = (double)(m_blupiPower ? -25 : -19);
		}
		else
		{
			m_blupiVitesseY = (double)(m_blupiPower ? -16 : -10);
		}
		m_blupiAir = true;
		flag = true;
		PlaySound(41, tinyPoint3);
	}
	if ((m_keyPress & 1) != 0 && !m_blupiHelico && !m_blupiOver && !m_blupiBalloon && !m_blupiEcrase && !m_blupiJeep && !m_blupiTank && !m_blupiNage && !m_blupiSurf && !m_blupiSuspend && m_blupiFocus)
	{
		if (m_blupiAction != 4 && m_blupiAction != 3 && !m_blupiAir)
		{
			m_blupiAction = 4;
			m_blupiPhase = 0;
		}
		if (m_blupiAction == 4 && m_blupiPhase == 3)
		{
			m_blupiAction = 5;
			m_blupiPhase = 0;
			if (m_blupiSkate)
			{
				PlaySound(1, tinyPoint3);
				m_blupiVitesseY = (double)(m_blupiPower ? -17 : -13);
			}
			else
			{
				PlaySound(1, tinyPoint3);
				if (IsNormalJump(tinyPoint3))
				{
					m_blupiVitesseY = (double)(m_blupiPower ? -26 : -16);
				}
				else
				{
					m_blupiVitesseY = (double)(m_blupiPower ? -16 : -12);
				}
			}
			m_blupiAir = true;
			flag = true;
		}
	}
	if (m_blupiAir)
	{
		if (flag5 && m_blupiVitesseY < 0.0)
		{
			if (m_blupiVitesseY < -14.0 && m_blupiAction != 11 && m_blupiAction != 75 && m_blupiAction != 76 && m_blupiAction != 77 && m_blupiAction != 78 && m_blupiAction != 79 && m_blupiAction != 80 && m_blupiAction != 81 && !m_blupiSkate)
			{
				m_blupiJumpAie = true;
				PlaySound(40, tinyPoint3);
			}
			else
			{
				PlaySound(SoundEnviron(4, detectIcon), tinyPoint3);
			}
			m_blupiVitesseY = 1.0;
		}
		tinyPoint3.Y += (int)(m_blupiVitesseY * 2.0);
		if (m_blupiVitesseY < 20.0)
		{
			m_blupiVitesseY += 2.0;
		}
		rect = BlupiRect(tinyPoint3);
		rect.Top = tinyPoint3.Y + 60 - 30;
		rect.Bottom = tinyPoint3.Y + 60 - 1;
		if (m_blupiVitesseY >= 0.0 && DecorDetect(rect))
		{
			tinyPoint3.Y = tinyPoint3.Y / 32 * 32 + Decor.BLUPIOFFY;
			if (!IsRessort(tinyPoint3))
			{
				PlaySound(SoundEnviron(3, m_detectIcon), tinyPoint3);
			}
			if (m_blupiFocus)
			{
				if (m_blupiVitesseY > 20.0)
				{
					m_blupiAction = 61;
				}
				else
				{
					m_blupiAction = 61;
				}
				m_blupiPhase = 0;
			}
			m_blupiAir = false;
			if (m_blupiJumpAie)
			{
				m_blupiJumpAie = false;
				m_blupiAction = 36;
				m_blupiPhase = 0;
			}
		}
		rect.Left = tinyPoint3.X + 20;
		rect.Right = tinyPoint3.X + 60 - 20;
		rect.Top = tinyPoint3.Y + 60 - 33;
		rect.Bottom = tinyPoint3.Y + 60 - 1;
		num = AscenseurDetect(rect, m_blupiPos, tinyPoint3);
		if (m_blupiVitesseY >= 0.0 && num != -1)
		{
			m_blupiTransport = num;
			flag4 = false;
			PlaySound(3, tinyPoint3);
			tinyPoint3.Y = m_moveObject[num].posCurrent.Y - 64 + Decor.BLUPIOFFY;
			if (m_blupiFocus)
			{
				if (m_blupiVitesseY > 20.0)
				{
					m_blupiAction = 61;
				}
				else
				{
					m_blupiAction = 61;
				}
				m_blupiPhase = 0;
			}
			m_blupiAir = false;
			if (m_blupiJumpAie)
			{
				m_blupiJumpAie = false;
				m_blupiAction = 36;
				m_blupiPhase = 0;
			}
		}
	}
	if (m_blupiAction == 36 && m_blupiPhase == 30)
	{
		m_blupiAction = 1;
		m_blupiPhase = 0;
		m_blupiFocus = true;
	}
	if (m_blupiAction == 56 && m_blupiPhase == 64)
	{
		m_blupiAction = 1;
		m_blupiPhase = 0;
		m_blupiFocus = true;
		m_blupiCloud = true;
		m_blupiTimeShield = 100;
		m_jauges[1].SetHide(false);
		PlaySound(55, tinyPoint3);
	}
	if (m_blupiAction == 58)
	{
		if (m_blupiPhase == 8)
		{
			tinyPoint.X = m_blupiPos.X;
			tinyPoint.Y = m_blupiPos.Y + 40;
			if (m_blupiVitesseY > 0.0)
			{
				tinyPoint.Y += (int)(m_blupiVitesseY * 4.0);
			}
			m_blupiVitesseY -= 10.0;
			if (ObjectStart(tinyPoint, 23, 55) != -1)
			{
				PlaySound(52, m_blupiPos);
				m_blupiTimeFire = 10;
				m_blupiBullet--;
			}
		}
		if (m_blupiPhase == 14)
		{
			m_blupiAction = 1;
			m_blupiPhase = 0;
			m_blupiFocus = true;
		}
	}
	if ((m_blupiAction == 44 || m_blupiAction == 45) && m_blupiPhase == 29)
	{
		m_blupiAction = 1;
		m_blupiPhase = 0;
		m_blupiFocus = true;
	}
	if (m_blupiAction == 46 && m_blupiPhase == 32)
	{
		m_blupiAction = 1;
		m_blupiPhase = 0;
		m_blupiFocus = true;
	}
	if (m_blupiAction == 47 && m_blupiPhase == 34)
	{
		m_blupiAction = 1;
		m_blupiPhase = 0;
		m_blupiFocus = true;
	}
	bool flag6;
	if (m_blupiAction == 48 && m_blupiPhase == 40)
	{
		m_blupiAction = 1;
		m_blupiPhase = 0;
		m_blupiFocus = true;
		num = MoveObjectDetect(tinyPoint3, out flag6);
		if (num != -1 && !flag6 && tinyPoint3.Y - Decor.BLUPIFLOOR == m_moveObject[num].posCurrent.Y)
		{
			if (m_blupiDir == 2 && tinyPoint3.X < m_moveObject[num].posCurrent.X)
			{
				tinyPoint.X = tinyPoint3.X - 16;
				tinyPoint.Y = tinyPoint3.Y;
				int num2 = MoveObjectDetect(tinyPoint, out flag6);
				if (num2 == -1)
				{
					m_blupiAction = 9;
					m_blupiPhase = 0;
				}
			}
			if (m_blupiDir == 1 && tinyPoint3.X > m_moveObject[num].posCurrent.X)
			{
				tinyPoint.X = tinyPoint3.X + 16;
				tinyPoint.Y = tinyPoint3.Y;
				int num2 = MoveObjectDetect(tinyPoint, out flag6);
				if (num2 == -1)
				{
					m_blupiAction = 9;
					m_blupiPhase = 0;
				}
			}
		}
	}
	if (m_blupiAction == 65)
	{
		if (m_blupiPhase == 4)
		{
			PlaySound(47, m_blupiPos);
		}
		if (m_blupiPhase == 44)
		{
			m_blupiAction = 1;
			m_blupiPhase = 0;
			m_blupiFocus = true;
		}
	}
	if (m_blupiAction == 63)
	{
		if (m_blupiPhase == 1)
		{
			PlaySound(65, m_blupiPos);
			m_blupiTimeMockery = 300;
		}
		if (m_blupiPhase == 92)
		{
			m_blupiAction = 1;
			m_blupiPhase = 0;
			m_blupiFocus = true;
		}
	}
	if (m_blupiAction == 64)
	{
		if (m_blupiPhase == 6)
		{
			PlaySound(65, m_blupiPos);
			m_blupiTimeMockery = 300;
		}
		if (m_blupiPhase == 104)
		{
			m_blupiAction = 1;
			m_blupiPhase = 0;
			m_blupiFocus = true;
		}
	}
	if (m_blupiAction == 83)
	{
		if (m_blupiPhase == 4)
		{
			PlaySound(47, m_blupiPos);
		}
		if (m_blupiPhase == 60)
		{
			m_blupiAction = 1;
			m_blupiPhase = 0;
			m_blupiFocus = true;
		}
	}
	if (m_blupiAction == 84 && m_blupiPhase == 18)
	{
		m_blupiAction = 1;
		m_blupiPhase = 0;
		m_blupiFocus = true;
	}
	if (m_blupiAction == 60 && m_blupiPhase == 3)
	{
		m_blupiAction = 1;
		m_blupiPhase = 0;
	}
	if (m_blupiAction == 61 && m_blupiPhase == 5)
	{
		m_blupiAction = 1;
		m_blupiPhase = 0;
	}
	if (m_blupiAction == 62 && m_blupiPhase == 2)
	{
		m_blupiAction = 5;
		m_blupiPhase = 0;
		m_blupiVitesseY = -12.0;
		m_blupiAir = true;
		flag = true;
	}
	if (m_blupiAction == 49 && m_blupiPhase == 32)
	{
		ObjectStart(m_sucettePos, m_sucetteType, 0);
		m_blupiAction = 1;
		m_blupiPhase = 0;
		m_blupiFocus = true;
		m_blupiPower = true;
		m_blupiTimeShield = 100;
		m_blupiPosMagic = m_blupiPos;
		m_jauges[1].SetHide(false);
		PlaySound(44, tinyPoint3);
	}
	if (m_blupiAction == 55 && m_blupiPhase == 36)
	{
		ObjectStart(m_sucettePos, m_sucetteType, 0);
		m_blupiAction = 1;
		m_blupiPhase = 0;
		m_blupiFocus = true;
		m_blupiHide = true;
		m_blupiTimeShield = 100;
		m_blupiPosMagic = m_blupiPos;
		m_jauges[1].SetHide(false);
		PlaySound(62, tinyPoint3);
	}
	if (m_blupiSpeedY < 0.0 && m_blupiLastSpeedY == 0.0 && m_blupiAction != 3 && m_blupiAction != 4 && m_blupiAction != 5 && m_blupiAction != 8 && m_blupiAction != 10 && m_blupiAction != 9 && !m_blupiAir && !m_blupiHelico && !m_blupiOver && !m_blupiBalloon && !m_blupiEcrase && !m_blupiJeep && !m_blupiTank && !m_blupiSkate && !m_blupiNage && !m_blupiSurf && !m_blupiSuspend && m_blupiFocus)
	{
		m_blupiAction = 7;
		m_blupiPhase = 0;
	}
	if (m_blupiSpeedY == 0.0 && m_blupiLastSpeedY < 0.0 && m_blupiAction != 3 && m_blupiAction != 4 && m_blupiAction != 5 && m_blupiAction != 8 && m_blupiAction != 10 && m_blupiAction != 9 && !m_blupiAir && !m_blupiHelico && !m_blupiOver && !m_blupiBalloon && !m_blupiEcrase && !m_blupiJeep && !m_blupiTank && !m_blupiSkate && !m_blupiNage && !m_blupiSurf && !m_blupiSuspend && m_blupiFocus)
	{
		m_blupiAction = 1;
		m_blupiPhase = 0;
	}
	if (m_blupiSpeedY > 0.0 && m_blupiLastSpeedY == 0.0 && m_blupiAction != 3 && m_blupiAction != 4 && m_blupiAction != 5 && m_blupiAction != 6 && m_blupiAction != 28 && m_blupiAction != 8 && m_blupiAction != 10 && m_blupiAction != 9 && !m_blupiAir && !m_blupiHelico && !m_blupiOver && !m_blupiBalloon && !m_blupiEcrase && !m_blupiJeep && !m_blupiTank && !m_blupiSkate && !m_blupiNage && !m_blupiSurf && !m_blupiSuspend && m_blupiFocus)
	{
		m_blupiAction = 6;
		m_blupiPhase = 0;
	}
	if (m_blupiSpeedY > 0.0 && m_blupiSpeedX == 0.0 && (m_keyPress & 1) == 0 && m_blupiAction != 3 && m_blupiAction != 4 && m_blupiAction != 5 && m_blupiAction != 6 && m_blupiAction != 28 && m_blupiAction != 8 && m_blupiAction != 10 && m_blupiAction != 9 && !m_blupiAir && !m_blupiHelico && !m_blupiOver && !m_blupiBalloon && !m_blupiEcrase && !m_blupiJeep && !m_blupiTank && !m_blupiSkate && !m_blupiNage && !m_blupiSurf && !m_blupiSuspend && m_blupiFocus)
	{
		m_blupiAction = 6;
		m_blupiPhase = 0;
	}
	if (m_blupiSpeedY == 0.0 && m_blupiLastSpeedY > 0.0 && m_blupiAction != 3 && m_blupiAction != 4 && m_blupiAction != 5 && m_blupiAction != 8 && m_blupiAction != 10 && m_blupiAction != 9 && !m_blupiAir && !m_blupiHelico && !m_blupiOver && !m_blupiBalloon && !m_blupiEcrase && !m_blupiJeep && !m_blupiTank && !m_blupiSkate && !m_blupiNage && !m_blupiSurf && !m_blupiSuspend && m_blupiFocus)
	{
		m_blupiAction = 1;
		m_blupiPhase = 0;
	}
	if (m_blupiAction == 7 && m_blupiPhase == 4)
	{
		m_scrollAdd.Y = -150;
		PlaySound(21, tinyPoint3);
	}
	if (m_blupiAction == 6 && m_blupiPhase == 4)
	{
		m_scrollAdd.Y = 150;
		PlaySound(7, tinyPoint3);
	}
	if (!m_blupiHelico && !m_blupiOver && !m_blupiBalloon && !m_blupiEcrase && !m_blupiJeep && !m_blupiTank && !m_blupiSkate && !m_blupiNage && !m_blupiSurf && !m_blupiSuspend && m_blupiFocus)
	{
		if (m_blupiSpeedY > 0.0 && m_blupiSpeedX == 0.0 && (m_keyPress & 1) == 0 && m_blupiAction != 28 && m_blupiDir == 1 && (num = CaisseInFront()) != -1)
		{
			tinyPoint3.X = m_moveObject[num].posCurrent.X + 64 - 5;
			m_blupiAction = 28;
			m_blupiPhase = 0;
			m_scrollAdd.Y = 0;
			PlaySound(39, tinyPoint3);
		}
		if (m_blupiSpeedY > 0.0 && m_blupiSpeedX > 0.0 && (m_keyPress & 1) == 0 && m_blupiAction != 29 && m_blupiDir == 1 && CaisseInFront() != -1)
		{
			m_blupiAction = 29;
			m_blupiPhase = 0;
			m_scrollAdd.Y = 0;
			PlaySound(39, tinyPoint3);
		}
		if (m_blupiSpeedY > 0.0 && m_blupiSpeedX == 0.0 && (m_keyPress & 1) == 0 && m_blupiAction != 28 && m_blupiDir == 2 && (num = CaisseInFront()) != -1)
		{
			tinyPoint3.X = m_moveObject[num].posCurrent.X - 60 + 5;
			m_blupiAction = 28;
			m_blupiPhase = 0;
			m_scrollAdd.Y = 0;
			PlaySound(39, tinyPoint3);
		}
		if (m_blupiSpeedY > 0.0 && m_blupiSpeedX < 0.0 && (m_keyPress & 1) == 0 && m_blupiAction != 29 && m_blupiDir == 2 && CaisseInFront() != -1)
		{
			m_blupiAction = 29;
			m_blupiPhase = 0;
			m_scrollAdd.Y = 0;
			PlaySound(39, tinyPoint3);
		}
		if (m_blupiAction == 29 && m_blupiActionOuf != 47)
		{
			m_blupiActionOuf = 47;
			m_blupiTimeOuf = 0;
		}
	}
	if (m_blupiAction != 28 && m_blupiAction != 29 && m_blupiFocus)
	{
		if (m_blupiSpeedX < 0.0 && m_blupiLastSpeedX == 0.0 && !m_blupiAir && m_blupiSpeedY != 0.0)
		{
			m_blupiAction = 1;
			m_blupiPhase = 0;
		}
		if (m_blupiSpeedX == 0.0 && m_blupiLastSpeedX < 0.0 && m_blupiSpeedY != 0.0)
		{
			m_blupiAction = 1;
			m_blupiPhase = 0;
		}
		if (m_blupiSpeedX > 0.0 && m_blupiLastSpeedX == 0.0 && !m_blupiAir && m_blupiSpeedY != 0.0)
		{
			m_blupiAction = 1;
			m_blupiPhase = 0;
		}
		if (m_blupiSpeedX == 0.0 && m_blupiLastSpeedX > 0.0 && m_blupiSpeedY != 0.0)
		{
			m_blupiAction = 1;
			m_blupiPhase = 0;
		}
	}
	int num3;
	int num4;
	if (m_blupiSpeedX < 0.0 && m_blupiFocus)
	{
		if (m_blupiDir == 2 && m_blupiAction != 3 && m_blupiAction != 59 && m_blupiAction != 7 && m_blupiAction != 6 && m_blupiAction != 29 && ((!m_blupiJeep && !m_blupiTank && !m_blupiSkate) || Math.Abs(m_blupiVitesseX) <= 8.0))
		{
			if (m_blupiAir)
			{
				PlaySound(5, tinyPoint3);
				m_blupiAction = 59;
				m_blupiPhase = 0;
				m_blupiDir = 1;
			}
			else
			{
				PlaySound(5, tinyPoint3);
				m_blupiAction = 3;
				m_blupiPhase = 0;
			}
		}
		if (m_blupiDir == 1 && m_blupiAction != 2 && m_blupiAction != 14 && m_blupiAction != 4 && m_blupiAction != 7 && m_blupiAction != 6 && m_blupiAction != 29 && !m_blupiAir)
		{
			m_blupiAction = 2;
			m_blupiPhase = 0;
		}
		if (m_blupiDir == 1 && m_blupiAction != 3 && m_blupiAction != 4 && m_blupiAction != 7 && m_blupiAction != 6 && m_blupiAction != 29 && !m_blupiHelico && !m_blupiOver && !m_blupiBalloon && !m_blupiEcrase && !m_blupiJeep && !m_blupiTank && !m_blupiSkate && !m_blupiNage && !m_blupiSurf && !m_blupiSuspend)
		{
			if (m_blupiAction == 14)
			{
				tinyPoint3.X -= CaisseGetMove(5);
			}
			else
			{
				num3 = m_blupiPhase;
				if (num3 > 3 || m_blupiAir)
				{
					num3 = 3;
				}
				num4 = Tables.table_vitesse_march[num3];
				if (m_blupiPower)
				{
					num4 *= 3;
					num4 /= 2;
				}
				tinyPoint3.X += Misc.Speed(m_blupiSpeedX, num4);
			}
		}
		if (m_blupiDir == 2 && m_blupiAction == 29)
		{
			tinyPoint3.X -= CaisseGetMove(3);
		}
	}
	if (m_blupiSpeedX > 0.0 && m_blupiFocus)
	{
		if (m_blupiDir == 1 && m_blupiAction != 3 && m_blupiAction != 59 && m_blupiAction != 7 && m_blupiAction != 6 && m_blupiAction != 29 && ((!m_blupiJeep && !m_blupiTank && !m_blupiSkate) || Math.Abs(m_blupiVitesseX) <= 8.0))
		{
			if (m_blupiAir)
			{
				PlaySound(5, tinyPoint3);
				m_blupiAction = 59;
				m_blupiPhase = 0;
				m_blupiDir = 2;
			}
			else
			{
				PlaySound(5, tinyPoint3);
				m_blupiAction = 3;
				m_blupiPhase = 0;
			}
		}
		if (m_blupiDir == 2 && m_blupiAction != 2 && m_blupiAction != 14 && m_blupiAction != 4 && m_blupiAction != 7 && m_blupiAction != 6 && m_blupiAction != 29 && !m_blupiAir)
		{
			m_blupiAction = 2;
			m_blupiPhase = 0;
		}
		if (m_blupiDir == 2 && m_blupiAction != 3 && m_blupiAction != 4 && m_blupiAction != 7 && m_blupiAction != 6 && m_blupiAction != 29 && !m_blupiHelico && !m_blupiOver && !m_blupiBalloon && !m_blupiEcrase && !m_blupiJeep && !m_blupiTank && !m_blupiSkate && !m_blupiNage && !m_blupiSurf && !m_blupiSuspend)
		{
			if (m_blupiAction == 14)
			{
				tinyPoint3.X += CaisseGetMove(5);
			}
			else
			{
				num3 = m_blupiPhase;
				if (num3 > 3 || m_blupiAir)
				{
					num3 = 3;
				}
				num4 = Tables.table_vitesse_march[num3];
				if (m_blupiPower)
				{
					num4 *= 3;
					num4 /= 2;
				}
				tinyPoint3.X += Misc.Speed(m_blupiSpeedX, num4);
			}
		}
		if (m_blupiDir == 1 && m_blupiAction == 29)
		{
			tinyPoint3.X += CaisseGetMove(3);
		}
	}
	if (m_blupiHelico)
	{
		if (m_blupiAction == 3 && m_blupiPhase == 10)
		{
			m_blupiAction = 2;
			if (m_blupiDir == 1)
			{
				m_blupiDir = 2;
			}
			else
			{
				m_blupiDir = 1;
			}
		}
	}
	else if (m_blupiOver)
	{
		if (m_blupiAction == 3 && m_blupiPhase == 7)
		{
			m_blupiAction = 2;
			if (m_blupiDir == 1)
			{
				m_blupiDir = 2;
			}
			else
			{
				m_blupiDir = 1;
			}
		}
	}
	else if (m_blupiJeep)
	{
		if (m_blupiAction == 3 && m_blupiPhase == 7)
		{
			m_blupiAction = 1;
			m_blupiPhase = 0;
			if (m_blupiDir == 1)
			{
				m_blupiDir = 2;
			}
			else
			{
				m_blupiDir = 1;
			}
		}
	}
	else if (m_blupiTank)
	{
		if (m_blupiAction == 3 && m_blupiPhase == 12)
		{
			m_blupiAction = 1;
			m_blupiPhase = 0;
			if (m_blupiDir == 1)
			{
				m_blupiDir = 2;
			}
			else
			{
				m_blupiDir = 1;
			}
		}
	}
	else if (m_blupiSkate)
	{
		if (m_blupiAction == 3 && m_blupiPhase == 14)
		{
			m_blupiAction = 1;
			m_blupiPhase = 0;
			if (m_blupiDir == 1)
			{
				m_blupiDir = 2;
			}
			else
			{
				m_blupiDir = 1;
			}
		}
	}
	else if (m_blupiNage || m_blupiSurf)
	{
		if (m_blupiAction == 3 && m_blupiPhase == 10)
		{
			m_blupiAction = 2;
			if (m_blupiDir == 1)
			{
				m_blupiDir = 2;
			}
			else
			{
				m_blupiDir = 1;
			}
		}
	}
	else if (m_blupiSuspend)
	{
		if (m_blupiAction == 3 && m_blupiPhase == 10)
		{
			m_blupiAction = 1;
			m_blupiPhase = 0;
			if (m_blupiDir == 1)
			{
				m_blupiDir = 2;
			}
			else
			{
				m_blupiDir = 1;
			}
		}
	}
	else
	{
		if (m_blupiAction == 3 && m_blupiPhase == 6)
		{
			m_blupiAction = 1;
			m_blupiPhase = 0;
			if (m_blupiDir == 1)
			{
				m_blupiDir = 2;
			}
			else
			{
				m_blupiDir = 1;
			}
		}
		if (m_blupiAction == 59 && m_blupiPhase == 6)
		{
			m_blupiAction = 5;
			m_blupiPhase = 0;
		}
	}
	if (!m_blupiSuspend && m_blupiAction == 4 && m_blupiPhase == 3)
	{
		m_blupiAction = 1;
		m_blupiPhase = 0;
	}
	if (m_blupiSpeedX == 0.0 && m_blupiSpeedY == 0.0 && !m_blupiHelico && !m_blupiOver && !m_blupiBalloon && !m_blupiEcrase && !m_blupiJeep && !m_blupiTank && !m_blupiSkate && !m_blupiNage && !m_blupiSurf && m_blupiFocus)
	{
		if (m_blupiAction == 14 || m_blupiAction == 7)
		{
			m_blupiAction = 1;
			m_blupiPhase = 0;
		}
		if (m_blupiAction == 2)
		{
			if (m_blupiSuspend || m_blupiPhase < 10)
			{
				m_blupiAction = 1;
			}
			else
			{
				m_blupiAction = 60;
			}
			m_blupiPhase = 0;
		}
		if (m_blupiAction == 6)
		{
			m_blupiAction = 1;
			m_blupiPhase = 0;
			PlaySound(20, tinyPoint3);
		}
		m_scrollAdd.Y = 0;
		if (blupiAction == 14)
		{
			StopSound(38);
		}
		if (blupiAction == 29 || blupiAction == 28)
		{
			StopSound(39);
		}
	}
	if (!m_blupiBalloon && !m_blupiEcrase && !m_blupiJeep && !m_blupiTank && !m_blupiSkate && !m_blupiNage && !m_blupiSurf && m_blupiFocus)
	{
		if (m_blupiAction == 9 && m_blupiDir == 1)
		{
			tinyPoint3.X += 4;
		}
		if (m_blupiAction == 9 && m_blupiDir == 2)
		{
			tinyPoint3.X -= 4;
		}
		if (m_blupiAction == 10 && m_blupiDir == 1)
		{
			tinyPoint3.X -= 4;
		}
		if (m_blupiAction == 10 && m_blupiDir == 2)
		{
			tinyPoint3.X += 4;
		}
	}
	if ((m_keyPress & -3) == 0 && m_blupiSpeedX == 0.0 && m_blupiSpeedY == 0.0 && (m_blupiJeep || m_blupiTank || m_blupiSkate) && m_blupiFocus)
	{
		if (m_blupiAction == 10 && m_blupiDir == 1)
		{
			tinyPoint3.X -= 5;
		}
		if (m_blupiAction == 10 && m_blupiDir == 2)
		{
			tinyPoint3.X += 5;
		}
	}
	if ((m_keyPress & -3) == 0 && m_blupiSpeedX == 0.0 && m_blupiSpeedY == 0.0 && m_blupiNage && m_blupiFocus && m_blupiAction == 2)
	{
		m_blupiAction = 1;
		m_blupiPhase = 0;
	}
	if ((m_keyPress & -3) == 0 && m_blupiSpeedX == 0.0 && m_blupiSpeedY == 0.0 && m_blupiSurf && m_blupiFocus && m_blupiAction == 2)
	{
		m_blupiAction = 1;
		m_blupiPhase = 0;
	}
	if (m_blupiHelico && (m_blupiFocus || m_blupiAction == 58))
	{
		if ((m_keyPress & 2) != 0 && m_blupiTimeFire == 0 && m_blupiAction != 3 && m_blupiAction != 58 && flag4)
		{
			if (m_blupiBullet == 0)
			{
				PlaySound(53, m_blupiPos);
			}
			else
			{
				m_blupiAction = 58;
				m_blupiPhase = 0;
				m_blupiFocus = false;
			}
		}
		m_blupiMotorHigh = flag4;
		if (m_blupiAction != 3 && m_blupiAction != 58)
		{
			if (flag4)
			{
				m_blupiAction = 2;
			}
			else
			{
				m_blupiAction = 1;
				m_blupiPhase = 0;
				m_blupiVitesseY = 0.0;
			}
		}
		if (Def.EasyMove)
		{
			if (m_blupiSpeedY <= -1.0 || (m_keyPress & 1) != 0)
			{
				if (m_blupiVitesseY > -7.0)
				{
					m_blupiVitesseY -= 0.5;
				}
				if (m_blupiVitesseY == -0.5)
				{
					m_blupiVitesseY = -1.0;
				}
			}
			else if (m_blupiSpeedY >= 1.0)
			{
				if (m_blupiVitesseY < 8.0)
				{
					m_blupiVitesseY += 0.5;
				}
			}
			else
			{
				if (m_blupiVitesseY > 1.0)
				{
					m_blupiVitesseY -= 1.0;
				}
				if (m_blupiVitesseY < 1.0)
				{
					m_blupiVitesseY += 1.0;
				}
			}
			tinyPoint3.Y += (int)m_blupiVitesseY;
		}
		else
		{
			if (m_blupiSpeedY <= -1.0 || (m_keyPress & 1) != 0)
			{
				if (m_blupiVitesseY > -10.0)
				{
					m_blupiVitesseY -= 0.5;
				}
			}
			else if (m_blupiSpeedY >= 1.0)
			{
				if (m_blupiVitesseY < 12.0)
				{
					m_blupiVitesseY += 0.5;
				}
			}
			else
			{
				if (m_blupiVitesseY > 1.0)
				{
					m_blupiVitesseY -= 1.0;
				}
				if (m_blupiVitesseY < 1.0)
				{
					m_blupiVitesseY += 1.0;
				}
			}
			tinyPoint3.Y += (int)m_blupiVitesseY;
		}
		if (Def.EasyMove)
		{
			if (m_blupiSpeedX <= -1.0)
			{
				int num5 = (int)(m_blupiSpeedX * 12.0);
				if (m_blupiVitesseX > (double)num5)
				{
					m_blupiVitesseX -= 0.5;
				}
				tinyPoint.X = tinyPoint3.X + (int)m_blupiVitesseX;
				tinyPoint.Y = tinyPoint3.Y;
				if (BlupiBloque(tinyPoint, -1))
				{
					m_blupiVitesseX = 0.0;
				}
			}
			else if (m_blupiSpeedX >= 1.0)
			{
				int num6 = (int)(m_blupiSpeedX * 12.0);
				if (m_blupiVitesseX < (double)num6)
				{
					m_blupiVitesseX += 0.5;
				}
				tinyPoint.X = tinyPoint3.X + (int)m_blupiVitesseX;
				tinyPoint.Y = tinyPoint3.Y;
				if (BlupiBloque(tinyPoint, 1))
				{
					m_blupiVitesseX = 0.0;
				}
			}
			else
			{
				if (m_blupiVitesseX > 0.0)
				{
					m_blupiVitesseX -= 2.0;
					if (m_blupiVitesseX < 0.0)
					{
						m_blupiVitesseX = 0.0;
					}
				}
				if (m_blupiVitesseX < 0.0)
				{
					m_blupiVitesseX += 2.0;
					if (m_blupiVitesseX > 0.0)
					{
						m_blupiVitesseX = 0.0;
					}
				}
			}
			tinyPoint3.X += (int)m_blupiVitesseX;
		}
		else
		{
			if (m_blupiSpeedX <= -1.0)
			{
				int num7 = (int)(m_blupiSpeedX * 16.0);
				if (m_blupiVitesseX > (double)num7)
				{
					m_blupiVitesseX -= 1.0;
				}
				tinyPoint.X = tinyPoint3.X + (int)m_blupiVitesseX;
				tinyPoint.Y = tinyPoint3.Y;
				if (BlupiBloque(tinyPoint, -1))
				{
					m_blupiVitesseX = 0.0;
				}
			}
			else if (m_blupiSpeedX >= 1.0)
			{
				int num8 = (int)(m_blupiSpeedX * 16.0);
				if (m_blupiVitesseX < (double)num8)
				{
					m_blupiVitesseX += 1.0;
				}
				tinyPoint.X = tinyPoint3.X + (int)m_blupiVitesseX;
				tinyPoint.Y = tinyPoint3.Y;
				if (BlupiBloque(tinyPoint, 1))
				{
					m_blupiVitesseX = 0.0;
				}
			}
			else
			{
				if (m_blupiVitesseX > 0.0)
				{
					m_blupiVitesseX -= 2.0;
					if (m_blupiVitesseX < 0.0)
					{
						m_blupiVitesseX = 0.0;
					}
				}
				if (m_blupiVitesseX < 0.0)
				{
					m_blupiVitesseX += 2.0;
					if (m_blupiVitesseX > 0.0)
					{
						m_blupiVitesseX = 0.0;
					}
				}
			}
			tinyPoint3.X += (int)m_blupiVitesseX;
		}
		MoveObjectPollution();
		if (ButtonPressed == Def.ButtonGlygh.PlayAction && !flag4 && m_blupiTransport == -1)
		{
			ButtonPressed = Def.ButtonGlygh.None;
			rect.Left = m_blupiPos.X + 20;
			rect.Right = m_blupiPos.X + 22;
			rect.Top = m_blupiPos.Y + 60 - 2;
			rect.Bottom = m_blupiPos.Y + 60;
			flag2 = !DecorDetect(rect);
			rect.Left = m_blupiPos.X + 60 - 22;
			rect.Right = m_blupiPos.X + 60 - 20;
			rect.Top = m_blupiPos.Y + 60 - 2;
			rect.Bottom = m_blupiPos.Y + 60;
			flag3 = !DecorDetect(rect);
			if (!flag2 && !flag3)
			{
				tinyPoint.X = m_blupiPos.X;
				tinyPoint.Y = m_blupiPos.Y - Decor.BLUPIFLOOR;
				ObjectStart(tinyPoint, 13, 0);
				m_blupiHelico = false;
				m_blupiAction = 1;
				m_blupiPhase = 0;
				m_blupiPosHelico = m_blupiPos;
				m_blupiFocus = true;
				StopSound(16);
				StopSound(18);
				PlaySound(17, m_blupiPos);
			}
		}
	}
	if (m_blupiOver && (m_blupiFocus || m_blupiAction == 58))
	{
		m_blupiMotorHigh = flag4;
		if (m_blupiAction != 3)
		{
			if (flag4)
			{
				m_blupiAction = 2;
			}
			else
			{
				if (m_blupiAction != 1)
				{
					m_blupiAction = 1;
					m_blupiPhase = 0;
				}
				m_blupiVitesseY = 0.0;
			}
		}
		rect = BlupiRect(tinyPoint3);
		rect.Top = tinyPoint3.Y + 60 - 2;
		rect.Bottom = tinyPoint3.Y + 60 + Decor.OVERHEIGHT - 1;
		bool flag7 = !DecorDetect(rect);
		num = MoveAscenseurDetect(m_blupiPos, Decor.OVERHEIGHT);
		if (num != -1)
		{
			flag7 = false;
		}
		if ((m_blupiSpeedY < 0.0 || (m_keyPress & 1) != 0) && !flag7)
		{
			if (m_blupiVitesseY == 0.0 && num != -1)
			{
				m_blupiVitesseY = -5.0;
			}
			else if (m_blupiVitesseY > -5.0)
			{
				m_blupiVitesseY -= 1.0;
			}
		}
		else if (m_blupiSpeedY > 0.0)
		{
			if (m_blupiVitesseY < 12.0)
			{
				m_blupiVitesseY += 5.0;
			}
		}
		else if (m_blupiVitesseY < 12.0 && m_time % 2 == 0)
		{
			m_blupiVitesseY += 1.0;
		}
		tinyPoint3.Y += (int)m_blupiVitesseY;
		if (m_blupiSpeedX < 0.0 && flag4)
		{
			int num9 = (int)(m_blupiSpeedX * 12.0);
			if (m_blupiVitesseX > (double)num9)
			{
				m_blupiVitesseX -= 1.0;
			}
			tinyPoint.X = tinyPoint3.X + (int)m_blupiVitesseX;
			tinyPoint.Y = tinyPoint3.Y;
			if (BlupiBloque(tinyPoint, -1))
			{
				m_blupiVitesseX = 0.0;
			}
		}
		else if (m_blupiSpeedX > 0.0 && flag4)
		{
			int num10 = (int)(m_blupiSpeedX * 12.0);
			if (m_blupiVitesseX < (double)num10)
			{
				m_blupiVitesseX += 1.0;
			}
			tinyPoint.X = tinyPoint3.X + (int)m_blupiVitesseX;
			tinyPoint.Y = tinyPoint3.Y;
			if (BlupiBloque(tinyPoint, 1))
			{
				m_blupiVitesseX = 0.0;
			}
		}
		else
		{
			if (m_blupiVitesseX > 0.0)
			{
				m_blupiVitesseX -= 1.0;
			}
			if (m_blupiVitesseX < 0.0)
			{
				m_blupiVitesseX += 1.0;
			}
		}
		tinyPoint3.X += (int)m_blupiVitesseX;
		MoveObjectPollution();
		if (ButtonPressed == Def.ButtonGlygh.PlayAction && !flag4 && m_blupiTransport == -1)
		{
			ButtonPressed = Def.ButtonGlygh.None;
			rect.Left = m_blupiPos.X + 20;
			rect.Right = m_blupiPos.X + 22;
			rect.Top = m_blupiPos.Y + 60 - 2;
			rect.Bottom = m_blupiPos.Y + 60;
			flag2 = !DecorDetect(rect);
			rect.Left = m_blupiPos.X + 60 - 22;
			rect.Right = m_blupiPos.X + 60 - 20;
			rect.Top = m_blupiPos.Y + 60 - 2;
			rect.Bottom = m_blupiPos.Y + 60;
			flag3 = !DecorDetect(rect);
			if (!flag2 && !flag3)
			{
				tinyPoint.X = m_blupiPos.X;
				tinyPoint.Y = m_blupiPos.Y - Decor.BLUPIFLOOR;
				ObjectStart(tinyPoint, 46, 0);
				m_blupiOver = false;
				m_blupiAction = 1;
				m_blupiPhase = 0;
				m_blupiPosHelico = m_blupiPos;
				m_blupiFocus = true;
				StopSound(16);
				StopSound(18);
				PlaySound(17, m_blupiPos);
			}
		}
	}
	if (m_blupiBalloon && m_blupiFocus)
	{
		if (m_blupiSpeedY < 0.0 || (m_keyPress & 1) != 0)
		{
			if (m_blupiVitesseY > -5.0 && m_time % 6 == 0)
			{
				m_blupiVitesseY -= 1.0;
			}
		}
		else if (m_blupiSpeedY > 0.0)
		{
			if (m_blupiVitesseY < 0.0 && m_time % 6 == 0)
			{
				m_blupiVitesseY += 1.0;
			}
		}
		else if (m_blupiVitesseY > -3.0 && m_time % 6 == 0)
		{
			m_blupiVitesseY -= 1.0;
		}
		tinyPoint3.Y += (int)m_blupiVitesseY;
		if (m_blupiSpeedX < 0.0)
		{
			int num11 = (int)(m_blupiSpeedX * 10.0);
			if (m_blupiVitesseX > (double)num11)
			{
				m_blupiVitesseX -= 1.0;
			}
			tinyPoint.X = tinyPoint3.X + (int)m_blupiVitesseX;
			tinyPoint.Y = tinyPoint3.Y;
			if (BlupiBloque(tinyPoint, -1))
			{
				m_blupiVitesseX = 0.0;
			}
		}
		else if (m_blupiSpeedX > 0.0)
		{
			int num12 = (int)(m_blupiSpeedX * 10.0);
			if (m_blupiVitesseX < (double)num12)
			{
				m_blupiVitesseX += 1.0;
			}
			tinyPoint.X = tinyPoint3.X + (int)m_blupiVitesseX;
			tinyPoint.Y = tinyPoint3.Y;
			if (BlupiBloque(tinyPoint, 1))
			{
				m_blupiVitesseX = 0.0;
			}
		}
		else
		{
			if (m_blupiVitesseX > 0.0)
			{
				m_blupiVitesseX -= 2.0;
				if (m_blupiVitesseX < 0.0)
				{
					m_blupiVitesseX = 0.0;
				}
			}
			if (m_blupiVitesseX < 0.0)
			{
				m_blupiVitesseX += 2.0;
				if (m_blupiVitesseX > 0.0)
				{
					m_blupiVitesseX = 0.0;
				}
			}
		}
		tinyPoint3.X += (int)m_blupiVitesseX;
	}
	if (m_blupiEcrase && m_blupiFocus)
	{
		if (flag4)
		{
			if (m_blupiVitesseY < 2.0)
			{
				m_blupiVitesseY += 1.0;
			}
		}
		else
		{
			m_blupiVitesseY = 0.0;
		}
		tinyPoint3.Y += (int)m_blupiVitesseY;
		if (flag4)
		{
			num3 = 7;
		}
		else
		{
			num3 = 4;
		}
		num3 = (int)((double)num3 * m_blupiSpeedX);
		if (m_blupiSpeedX < 0.0)
		{
			if (m_blupiVitesseX > (double)num3)
			{
				m_blupiVitesseX -= 1.0;
			}
			tinyPoint.X = tinyPoint3.X + (int)m_blupiVitesseX;
			tinyPoint.Y = tinyPoint3.Y;
			if (BlupiBloque(tinyPoint, -1))
			{
				m_blupiVitesseX = 0.0;
			}
		}
		else if (m_blupiSpeedX > 0.0)
		{
			if (m_blupiVitesseX < (double)num3)
			{
				m_blupiVitesseX += 1.0;
			}
			tinyPoint.X = tinyPoint3.X + (int)m_blupiVitesseX;
			tinyPoint.Y = tinyPoint3.Y;
			if (BlupiBloque(tinyPoint, 1))
			{
				m_blupiVitesseX = 0.0;
			}
		}
		else
		{
			if (m_blupiVitesseX > 0.0)
			{
				m_blupiVitesseX -= 2.0;
				if (m_blupiVitesseX < 0.0)
				{
					m_blupiVitesseX = 0.0;
				}
			}
			if (m_blupiVitesseX < 0.0)
			{
				m_blupiVitesseX += 2.0;
				if (m_blupiVitesseX > 0.0)
				{
					m_blupiVitesseX = 0.0;
				}
			}
		}
		if (m_blupiVitesseX == 0.0 && !flag4)
		{
			m_blupiAction = 1;
			m_blupiPhase = 0;
		}
		tinyPoint3.X += (int)m_blupiVitesseX;
	}
	if (m_blupiJeep && m_blupiFocus)
	{
		if (m_blupiVitesseX == 0.0 && m_blupiAction == 2)
		{
			m_blupiAction = 1;
			m_blupiPhase = 0;
		}
		m_blupiMotorHigh = (m_blupiAction != 1);
		rect = BlupiRect(tinyPoint3);
		rect.Right -= 40;
		rect.Top = tinyPoint3.Y + 60 - 2;
		rect.Bottom = tinyPoint3.Y + 60 - 1;
		bool flag8 = !DecorDetect(rect);
		rect.Left += 40;
		rect.Right += 40;
		bool flag9 = !DecorDetect(rect);
		if (flag4)
		{
			if (m_blupiVitesseY < 50.0)
			{
				m_blupiVitesseY += 5.0;
			}
		}
		else
		{
			if (m_blupiVitesseY != 0.0)
			{
				PlaySound(3, m_blupiPos);
			}
			m_blupiVitesseY = 0.0;
		}
		tinyPoint3.Y += (int)m_blupiVitesseY;
		if (m_blupiTransport == -1)
		{
			rect.Left = tinyPoint3.X + 20;
			rect.Right = tinyPoint3.X + 60 - 20;
			rect.Top = tinyPoint3.Y + 60 - 35;
			rect.Bottom = tinyPoint3.Y + 60 - 1;
			num = AscenseurDetect(rect, m_blupiPos, tinyPoint3);
			if (m_blupiVitesseY >= 0.0 && num != -1)
			{
				m_blupiTransport = num;
				flag4 = false;
				PlaySound(3, tinyPoint3);
				tinyPoint3.Y = m_moveObject[num].posCurrent.Y - 64 + Decor.BLUPIOFFY;
			}
		}
		if (flag8 && !flag9)
		{
			int num13 = -20;
			if (m_blupiVitesseX > (double)num13)
			{
				m_blupiVitesseX -= 1.0;
			}
		}
		else if (!flag8 && flag9)
		{
			int num14 = 20;
			if (m_blupiVitesseX < (double)num14)
			{
				m_blupiVitesseX += 1.0;
			}
		}
		else if (m_blupiSpeedX < 0.0)
		{
			int num15 = (int)(m_blupiSpeedX * 20.0);
			if (m_blupiVitesseX > (double)num15)
			{
				m_blupiVitesseX -= 1.0;
			}
		}
		else if (m_blupiSpeedX > 0.0)
		{
			int num16 = (int)(m_blupiSpeedX * 20.0);
			if (m_blupiVitesseX < (double)num16)
			{
				m_blupiVitesseX += 1.0;
			}
		}
		else
		{
			if (m_blupiVitesseX > 0.0)
			{
				m_blupiVitesseX -= 2.0;
				if (m_blupiVitesseX < 0.0)
				{
					m_blupiVitesseX = 0.0;
				}
			}
			if (m_blupiVitesseX < 0.0)
			{
				m_blupiVitesseX += 2.0;
				if (m_blupiVitesseX > 0.0)
				{
					m_blupiVitesseX = 0.0;
				}
			}
		}
		if (m_blupiAction == 3)
		{
			m_blupiVitesseX = 0.0;
		}
		tinyPoint3.X += (int)m_blupiVitesseX;
		if (flag8 && !flag9)
		{
			m_blupiRealRotation = Misc.Approch(m_blupiRealRotation, -45, 5);
		}
		else if (!flag8 && flag9)
		{
			m_blupiRealRotation = Misc.Approch(m_blupiRealRotation, 45, 5);
		}
		else if (!flag4)
		{
			m_blupiRealRotation = 0;
		}
		m_blupiOffsetY = Math.Abs(m_blupiRealRotation / 2);
		MoveObjectPollution();
		if (ButtonPressed == Def.ButtonGlygh.PlayAction && !flag4 && m_blupiTransport == -1)
		{
			ButtonPressed = Def.ButtonGlygh.None;
			tinyPoint.X = m_blupiPos.X;
			tinyPoint.Y = m_blupiPos.Y - Decor.BLUPIFLOOR;
			ObjectStart(tinyPoint, 19, 0);
			m_blupiJeep = false;
			m_blupiAction = 1;
			m_blupiPhase = 0;
			m_blupiPosHelico = m_blupiPos;
			StopSound(29);
			StopSound(31);
			PlaySound(30, m_blupiPos);
		}
	}
	if (m_blupiTank && m_blupiFocus)
	{
		if (m_blupiAction == 53 && m_blupiPhase == 6)
		{
			m_blupiAction = 1;
			m_blupiPhase = 0;
		}
		if ((m_keyPress & 2) != 0 && m_blupiTimeFire == 0 && m_blupiAction != 3)
		{
			if (m_blupiBullet == 0)
			{
				PlaySound(53, m_blupiPos);
			}
			else
			{
				if (m_blupiDir == 1)
				{
					tinyPoint.X = m_blupiPos.X - 35;
					tinyPoint.Y = m_blupiPos.Y;
					num4 = -5;
					m_blupiVitesseX += 12.0;
				}
				else
				{
					tinyPoint.X = m_blupiPos.X + 35;
					tinyPoint.Y = m_blupiPos.Y;
					num4 = 5;
					m_blupiVitesseX -= 12.0;
				}
				if (ObjectStart(tinyPoint, 23, num4) != -1)
				{
					m_blupiAction = 53;
					m_blupiPhase = 0;
					PlaySound(52, m_blupiPos);
					m_blupiTimeFire = 10;
					m_blupiBullet--;
				}
			}
		}
		if (m_blupiVitesseX == 0.0 && m_blupiAction == 2)
		{
			m_blupiAction = 1;
			m_blupiPhase = 0;
		}
		m_blupiMotorHigh = (m_blupiAction != 1);
		if (flag4)
		{
			if (m_blupiVitesseY < 50.0)
			{
				m_blupiVitesseY += 5.0;
			}
		}
		else
		{
			if (m_blupiVitesseY != 0.0)
			{
				PlaySound(3, m_blupiPos);
			}
			m_blupiVitesseY = 0.0;
		}
		tinyPoint3.Y += (int)m_blupiVitesseY;
		if (m_blupiTransport == -1)
		{
			rect.Left = tinyPoint3.X + 20;
			rect.Right = tinyPoint3.X + 60 - 20;
			rect.Top = tinyPoint3.Y + 60 - 35;
			rect.Bottom = tinyPoint3.Y + 60 - 1;
			num = AscenseurDetect(rect, m_blupiPos, tinyPoint3);
			if (m_blupiVitesseY >= 0.0 && num != -1)
			{
				m_blupiTransport = num;
				flag4 = false;
				PlaySound(3, tinyPoint3);
				tinyPoint3.Y = m_moveObject[num].posCurrent.Y - 64 + Decor.BLUPIOFFY;
			}
		}
		if (m_blupiSpeedX < 0.0)
		{
			int num17 = (int)(m_blupiSpeedX * 12.0);
			if (m_blupiVitesseX > (double)num17)
			{
				m_blupiVitesseX -= 1.0;
			}
		}
		else if (m_blupiSpeedX > 0.0)
		{
			int num18 = (int)(m_blupiSpeedX * 12.0);
			if (m_blupiVitesseX < (double)num18)
			{
				m_blupiVitesseX += 1.0;
			}
		}
		else
		{
			if (m_blupiVitesseX > 0.0)
			{
				m_blupiVitesseX -= 3.0;
				if (m_blupiVitesseX < 0.0)
				{
					m_blupiVitesseX = 0.0;
				}
			}
			if (m_blupiVitesseX < 0.0)
			{
				m_blupiVitesseX += 3.0;
				if (m_blupiVitesseX > 0.0)
				{
					m_blupiVitesseX = 0.0;
				}
			}
		}
		if (m_blupiAction == 3)
		{
			m_blupiVitesseX = 0.0;
		}
		tinyPoint3.X += (int)m_blupiVitesseX;
		MoveObjectPollution();
		if (ButtonPressed == Def.ButtonGlygh.PlayAction && !flag4 && m_blupiTransport == -1)
		{
			ButtonPressed = Def.ButtonGlygh.None;
			tinyPoint.X = m_blupiPos.X;
			tinyPoint.Y = m_blupiPos.Y;
			ObjectStart(tinyPoint, 28, 0);
			m_blupiTank = false;
			m_blupiAction = 1;
			m_blupiPhase = 0;
			m_blupiPosHelico = m_blupiPos;
			StopSound(29);
			StopSound(31);
			PlaySound(30, m_blupiPos);
		}
	}
	if (m_blupiSkate && m_blupiFocus)
	{
		if (m_blupiVitesseX == 0.0 && m_blupiAction == 2)
		{
			m_blupiAction = 1;
			m_blupiPhase = 0;
		}
		if (m_blupiSpeedX < 0.0)
		{
			int num19 = (int)(m_blupiSpeedX * 15.0);
			if (m_blupiVitesseX > (double)num19)
			{
				m_blupiVitesseX -= 1.0;
			}
		}
		else if (m_blupiSpeedX > 0.0)
		{
			int num20 = (int)(m_blupiSpeedX * 15.0);
			if (m_blupiVitesseX < (double)num20)
			{
				m_blupiVitesseX += 1.0;
			}
		}
		else
		{
			if (m_blupiVitesseX > 0.0)
			{
				m_blupiVitesseX -= 1.0;
				if (m_blupiVitesseX < 0.0)
				{
					m_blupiVitesseX = 0.0;
				}
			}
			if (m_blupiVitesseX < 0.0)
			{
				m_blupiVitesseX += 1.0;
				if (m_blupiVitesseX > 0.0)
				{
					m_blupiVitesseX = 0.0;
				}
			}
		}
		if (m_blupiAction == 3)
		{
			m_blupiVitesseX = 0.0;
		}
		tinyPoint3.X += (int)m_blupiVitesseX;
		if (ButtonPressed == Def.ButtonGlygh.PlayAction && !flag4 && !m_blupiAir && m_blupiTransport == -1 && m_blupiVitesseX < 8.0)
		{
			ButtonPressed = Def.ButtonGlygh.None;
			m_blupiSkate = false;
			m_blupiAction = 43;
			m_blupiPhase = 0;
			m_blupiFocus = false;
			m_blupiPosHelico = m_blupiPos;
		}
	}
	if (m_blupiAction == 42)
	{
		if (m_blupiPhase == 8)
		{
			num = MoveObjectDetect(m_blupiPos, out flag6);
			if (num != -1)
			{
				ObjectDelete(m_moveObject[num].posCurrent, m_moveObject[num].type);
			}
		}
		if (m_blupiPhase == 20)
		{
			m_blupiAction = 1;
			m_blupiPhase = 0;
			m_blupiFocus = true;
		}
	}
	if (m_blupiAction == 43)
	{
		if (m_blupiPhase == 12)
		{
			tinyPoint.X = m_blupiPos.X;
			tinyPoint.Y = m_blupiPos.Y - Decor.BLUPIFLOOR + 1;
			ObjectStart(tinyPoint, 24, 0);
		}
		if (m_blupiPhase == 20)
		{
			m_blupiAction = 1;
			m_blupiPhase = 0;
			m_blupiFocus = true;
		}
	}
	if (m_blupiNage && m_blupiFocus)
	{
		if (m_blupiTransport == -1)
		{
			if (m_blupiSpeedY < 0.0 || (m_keyPress & 1) != 0)
			{
				if (m_blupiVitesseY > -5.0)
				{
					m_blupiVitesseY -= 1.0;
				}
			}
			else if (m_blupiSpeedY > 0.0)
			{
				if (m_blupiVitesseY < 5.0)
				{
					m_blupiVitesseY += 1.0;
				}
			}
			else
			{
				if (m_blupiAction == 1)
				{
					num3 = -1;
				}
				else
				{
					num3 = 0;
				}
				if (m_blupiVitesseY > (double)num3)
				{
					m_blupiVitesseY -= 1.0;
				}
				if (m_blupiVitesseY < (double)num3)
				{
					m_blupiVitesseY += 1.0;
				}
			}
			tinyPoint3.Y += (int)m_blupiVitesseY;
		}
		if (m_blupiSpeedX < 0.0)
		{
			int num21 = (int)(m_blupiSpeedX * 8.0);
			if (m_blupiVitesseX > (double)num21)
			{
				m_blupiVitesseX -= 1.0;
			}
		}
		else if (m_blupiSpeedX > 0.0)
		{
			int num22 = (int)(m_blupiSpeedX * 8.0);
			if (m_blupiVitesseX < (double)num22)
			{
				m_blupiVitesseX += 1.0;
			}
		}
		else
		{
			if (m_blupiVitesseX > 0.0)
			{
				m_blupiVitesseX -= 2.0;
				if (m_blupiVitesseX < 0.0)
				{
					m_blupiVitesseX = 0.0;
				}
			}
			if (m_blupiVitesseX < 0.0)
			{
				m_blupiVitesseX += 2.0;
				if (m_blupiVitesseX > 0.0)
				{
					m_blupiVitesseX = 0.0;
				}
			}
		}
		num = Tables.table_vitesse_nage[m_blupiPhase % 14 / 2];
		tinyPoint3.X += (int)(m_blupiVitesseX * (double)num / 7.0);
		if (m_time % 70 == 0 || m_time % 70 == 28)
		{
			MoveObjectBlup(tinyPoint3);
		}
		if (m_time % 5 == 0)
		{
			if (!m_blupiShield && !m_blupiHide && !m_bSuperBlupi)
			{
				m_blupiLevel--;
			}
			if (m_blupiLevel == 25)
			{
				m_jauges[0].SetMode(1);
			}
			m_jauges[0].SetLevel(m_blupiLevel);
			if (m_blupiLevel == 0)
			{
				m_blupiAction = 24;
				m_blupiPhase = 0;
				m_blupiFocus = false;
				m_blupiHelico = false;
				m_blupiOver = false;
				m_blupiJeep = false;
				m_blupiTank = false;
				m_blupiSkate = false;
				m_blupiNage = false;
				m_blupiSurf = false;
				m_blupiSuspend = false;
				m_blupiJumpAie = false;
				m_blupiShield = false;
				m_blupiPower = false;
				m_blupiCloud = false;
				m_blupiHide = false;
				m_blupiInvert = false;
				m_blupiBalloon = false;
				m_blupiEcrase = false;
				m_blupiAir = false;
				m_blupiRestart = true;
				m_blupiActionOuf = 0;
				m_jauges[0].SetHide(true);
				m_jauges[1].SetHide(true);
				PlaySound(26, tinyPoint3);
			}
		}
	}
	if (m_blupiSurf && m_blupiFocus)
	{
		if (m_blupiTransport == -1)
		{
			if (m_blupiSpeedY < 0.0 || (m_keyPress & 1) != 0)
			{
				if (m_blupiVitesseY > -5.0)
				{
					m_blupiVitesseY -= 1.0;
				}
			}
			else if (m_blupiSpeedY > 0.0)
			{
				if (m_blupiVitesseY < 5.0)
				{
					m_blupiVitesseY += 1.0;
				}
			}
			else
			{
				if (m_blupiVitesseY > -2.0)
				{
					m_blupiVitesseY -= 1.0;
				}
				if (m_blupiVitesseY < -2.0)
				{
					m_blupiVitesseY += 1.0;
				}
			}
			tinyPoint3.Y += (int)m_blupiVitesseY;
			tinyPoint3.Y += Decor.BLUPISURF;
			if (tinyPoint3.Y % 64 > 30)
			{
				tinyPoint3.Y += 64 - tinyPoint3.Y % 64;
			}
			tinyPoint3.Y -= Decor.BLUPISURF;
		}
		if (m_blupiSpeedX < 0.0)
		{
			int num23 = (int)(m_blupiSpeedX * 8.0);
			if (m_blupiVitesseX > (double)num23)
			{
				m_blupiVitesseX -= 1.0;
			}
		}
		else if (m_blupiSpeedX > 0.0)
		{
			int num24 = (int)(m_blupiSpeedX * 8.0);
			if (m_blupiVitesseX < (double)num24)
			{
				m_blupiVitesseX += 1.0;
			}
		}
		else
		{
			if (m_blupiVitesseX > 0.0)
			{
				m_blupiVitesseX -= 2.0;
				if (m_blupiVitesseX < 0.0)
				{
					m_blupiVitesseX = 0.0;
				}
			}
			if (m_blupiVitesseX < 0.0)
			{
				m_blupiVitesseX += 2.0;
				if (m_blupiVitesseX > 0.0)
				{
					m_blupiVitesseX = 0.0;
				}
			}
		}
		num = Tables.table_vitesse_surf[m_blupiPhase % 12 / 2];
		tinyPoint3.X += (int)(m_blupiVitesseX * (double)num / 10.0);
	}
	TinyPoint tinyPoint4;
	if (m_blupiSuspend && m_blupiFocus)
	{
		if (m_blupiSpeedX < 0.0 && m_blupiAction == 2)
		{
			int num25 = (int)(m_blupiSpeedX * 5.0);
			tinyPoint3.X += num25;
		}
		if (m_blupiSpeedX > 0.0 && m_blupiAction == 2)
		{
			int num26 = (int)(m_blupiSpeedX * 5.0);
			tinyPoint3.X += num26;
		}
		num = GetTypeBarre(tinyPoint3);
		if (num == 2)
		{
			tinyPoint4.X = tinyPoint3.X;
			tinyPoint4.Y = tinyPoint3.Y / 64 * 64 + Decor.BLUPIOFFY;
			rect = BlupiRect(tinyPoint4);
			if (!DecorDetect(rect, true))
			{
				m_blupiSuspend = false;
				m_blupiAction = 1;
				m_blupiPhase = 0;
				tinyPoint3 = tinyPoint4;
				m_blupiPos = tinyPoint3;
			}
		}
		if ((m_blupiSpeedY > 0.0 && m_blupiPhase > 5) || num == 0)
		{
			m_blupiSuspend = false;
			m_blupiAir = true;
			m_blupiAction = 5;
			tinyPoint3.Y = tinyPoint3.Y;
			m_blupiVitesseY = 0.0;
			m_blupiNoBarre = 5;
			m_blupiActionOuf = 65;
			m_blupiTimeOuf = 0;
		}
		if (((m_keyPress & 1) != 0 || m_blupiSpeedY < 0.0) && m_blupiAction != 4 && m_blupiAction != 3)
		{
			m_blupiAction = 4;
			m_blupiPhase = 0;
		}
		if ((m_keyPress & 1) == 0 && m_blupiSpeedY == 0.0 && m_blupiAction == 4)
		{
			m_blupiAction = 1;
			m_blupiPhase = 0;
		}
		if (m_blupiAction == 4 && m_blupiPhase == 10)
		{
			m_blupiSuspend = false;
			m_blupiAir = true;
			m_blupiAction = 5;
			m_blupiPhase = 0;
			tinyPoint3.Y -= 2;
			m_blupiVitesseY = -11.0;
			m_blupiNoBarre = 5;
			PlaySound(35, tinyPoint3);
		}
	}
	if (ButtonPressed == Def.ButtonGlygh.PlayAction && !m_blupiHelico && !m_blupiOver && !m_blupiBalloon && !m_blupiEcrase && !m_blupiTank && !m_blupiJeep && !m_blupiSkate && !flag4 && m_blupiTransport == -1 && m_blupiFocus)
	{
		if (m_blupiDynamite > 0)
		{
			ButtonPressed = Def.ButtonGlygh.None;
			rect.Left = tinyPoint3.X + 18;
			rect.Right = tinyPoint3.X + 20;
			rect.Top = tinyPoint3.Y + 60 - 2;
			rect.Bottom = tinyPoint3.Y + 60;
			flag2 = !DecorDetect(rect);
			rect.Left = tinyPoint3.X + 60 - 20;
			rect.Right = tinyPoint3.X + 60 - 18;
			rect.Top = tinyPoint3.Y + 60 - 2;
			rect.Bottom = tinyPoint3.Y + 60;
			flag3 = !DecorDetect(rect);
			if (!flag2 && !flag3 && ObjectStart(tinyPoint3, 56, 0) != -1)
			{
				m_blupiAction = 87;
				m_blupiPhase = 0;
				m_blupiFocus = false;
				PlaySound(61, tinyPoint3);
				m_blupiDynamite--;
			}
		}
		else if (m_blupiPerso > 0)
		{
			ButtonPressed = Def.ButtonGlygh.None;
			num = MoveObjectDetect(tinyPoint3, out flag6);
			if (num == -1 || m_moveObject[num].type != 200)
			{
				rect.Left = tinyPoint3.X + 18;
				rect.Right = tinyPoint3.X + 20;
				rect.Top = tinyPoint3.Y + 60 - 2;
				rect.Bottom = tinyPoint3.Y + 60;
				flag2 = !DecorDetect(rect);
				rect.Left = tinyPoint3.X + 60 - 20;
				rect.Right = tinyPoint3.X + 60 - 18;
				rect.Top = tinyPoint3.Y + 60 - 2;
				rect.Bottom = tinyPoint3.Y + 60;
				flag3 = !DecorDetect(rect);
				num = MoveChargeDetect(tinyPoint3);
				if (num == -1 && !flag2 && !flag3 && ObjectStart(tinyPoint3, 200, 0) != -1)
				{
					m_blupiAction = 46;
					m_blupiPhase = 0;
					m_blupiFocus = false;
					PlaySound(61, tinyPoint3);
					m_blupiPerso--;
				}
			}
			if (m_blupiFocus)
			{
				m_blupiAction = 47;
				m_blupiPhase = 0;
				PlaySound(27, tinyPoint3);
			}
		}
	}
	rect = BlupiRect(m_blupiPos);
	tinyPoint4 = tinyPoint3;
	TestPath(rect, m_blupiPos, ref tinyPoint3);
	if (flag && m_blupiPos.X == tinyPoint3.X && m_blupiPos.X != tinyPoint4.X)
	{
		tinyPoint3.Y = tinyPoint4.Y;
		TestPath(rect, m_blupiPos, ref tinyPoint3);
	}
	if (m_blupiVent && m_blupiPos.Y == tinyPoint3.Y && m_blupiPos.Y != tinyPoint4.Y)
	{
		tinyPoint3.X = tinyPoint4.X;
		TestPath(rect, m_blupiPos, ref tinyPoint3);
	}
	if (m_blupiTransport != -1 && m_blupiPos.X == tinyPoint3.X && m_blupiPos.X != tinyPoint4.X)
	{
		tinyPoint3.Y = tinyPoint4.Y;
		TestPath(rect, m_blupiPos, ref tinyPoint3);
	}
	if (m_blupiHelico || m_blupiOver || m_blupiBalloon || m_blupiEcrase || m_blupiJeep || m_blupiTank || m_blupiSkate || m_blupiNage)
	{
		if (m_blupiPos.X == tinyPoint3.X && m_blupiPos.X != tinyPoint4.X)
		{
			tinyPoint3.Y = tinyPoint4.Y;
			TestPath(rect, m_blupiPos, ref tinyPoint3);
		}
		else if (m_blupiPos.Y == tinyPoint3.Y && m_blupiPos.Y != tinyPoint4.Y)
		{
			tinyPoint3.X = tinyPoint4.X;
			TestPath(rect, m_blupiPos, ref tinyPoint3);
		}
	}
	TinyPoint blupiPos = m_blupiPos;
	m_blupiPos = tinyPoint3;
	if ((m_blupiAction == 1 || m_blupiAction == 60 || m_blupiAction == 7 || m_blupiAction == 6) && !m_blupiAir && !m_blupiBalloon && !m_blupiEcrase && !m_blupiJeep && !m_blupiTank && !m_blupiSkate && !m_blupiNage && !m_blupiSurf && !m_blupiSuspend && m_blupiFocus)
	{
		if (m_blupiTransport != -1)
		{
			AscenseurVertigo(m_blupiTransport, out flag2, out flag3);
		}
		else
		{
			rect.Left = tinyPoint3.X + 24;
			rect.Right = tinyPoint3.X + 26;
			rect.Top = tinyPoint3.Y + 60 - 2;
			rect.Bottom = tinyPoint3.Y + 60;
			flag2 = !DecorDetect(rect);
			rect.Left = tinyPoint3.X + 60 - 26;
			rect.Right = tinyPoint3.X + 60 - 24;
			rect.Top = tinyPoint3.Y + 60 - 2;
			rect.Bottom = tinyPoint3.Y + 60;
			flag3 = !DecorDetect(rect);
		}
		if (m_blupiDir == 1 && flag2 && !flag3)
		{
			if (m_blupiHelico || m_blupiOver || AscenseurShift(m_blupiTransport))
			{
				m_blupiAction = 9;
				m_blupiPhase = 0;
			}
			else
			{
				PlaySound(6, tinyPoint3);
				m_blupiAction = 8;
				m_blupiPhase = 0;
			}
		}
		if (m_blupiDir == 2 && !flag2 && flag3)
		{
			if (m_blupiHelico || m_blupiOver || AscenseurShift(m_blupiTransport))
			{
				m_blupiAction = 9;
				m_blupiPhase = 0;
			}
			else
			{
				PlaySound(6, tinyPoint3);
				m_blupiAction = 8;
				m_blupiPhase = 0;
			}
		}
		if (m_blupiAction != 8 && m_blupiAction != 10 && m_blupiAction != 9 && (flag2 || flag3))
		{
			if (!m_blupiHelico && !m_blupiOver)
			{
				PlaySound(6, tinyPoint3);
			}
			m_blupiAction = 10;
			m_blupiPhase = 0;
		}
	}
	if (m_blupiAction == 1 && m_blupiJeep && !m_blupiHelico && !m_blupiOver && !m_blupiBalloon && !m_blupiEcrase && !m_blupiNage && !m_blupiSurf && !m_blupiSuspend && m_blupiFocus)
	{
		if (m_blupiTransport != -1)
		{
			AscenseurVertigo(m_blupiTransport, out flag2, out flag3);
		}
		else
		{
			rect.Left = tinyPoint3.X + 2;
			rect.Right = tinyPoint3.X + 18;
			rect.Top = tinyPoint3.Y + 60 - 2;
			rect.Bottom = tinyPoint3.Y + 60;
			flag2 = !DecorDetect(rect);
			rect.Left = tinyPoint3.X + 60 - 18;
			rect.Right = tinyPoint3.X + 60 - 2;
			rect.Top = tinyPoint3.Y + 60 - 2;
			rect.Bottom = tinyPoint3.Y + 60;
			flag3 = !DecorDetect(rect);
		}
		if (flag2 && !flag3)
		{
			m_blupiAction = 10;
			m_blupiPhase = 0;
		}
		if (flag3 && !flag2)
		{
			m_blupiAction = 10;
			m_blupiPhase = 0;
		}
	}
	if (m_blupiAction == 1 && m_blupiTank && !m_blupiHelico && !m_blupiOver && !m_blupiBalloon && !m_blupiEcrase && !m_blupiNage && !m_blupiSurf && !m_blupiSuspend && m_blupiFocus)
	{
		if (m_blupiTransport != -1)
		{
			AscenseurVertigo(m_blupiTransport, out flag2, out flag3);
		}
		else
		{
			rect.Left = tinyPoint3.X + 2;
			rect.Right = tinyPoint3.X + 18;
			rect.Top = tinyPoint3.Y + 60 - 2;
			rect.Bottom = tinyPoint3.Y + 60;
			flag2 = !DecorDetect(rect);
			rect.Left = tinyPoint3.X + 60 - 18;
			rect.Right = tinyPoint3.X + 60 - 2;
			rect.Top = tinyPoint3.Y + 60 - 2;
			rect.Bottom = tinyPoint3.Y + 60;
			flag3 = !DecorDetect(rect);
		}
		if (flag2 && !flag3)
		{
			m_blupiAction = 10;
			m_blupiPhase = 0;
		}
		if (flag3 && !flag2)
		{
			m_blupiAction = 10;
			m_blupiPhase = 0;
		}
	}
	if (m_blupiAction == 1 && m_blupiSkate && !m_blupiHelico && !m_blupiOver && !m_blupiBalloon && !m_blupiEcrase && !m_blupiNage && !m_blupiSurf && !m_blupiSuspend && m_blupiFocus)
	{
		if (m_blupiTransport != -1)
		{
			AscenseurVertigo(m_blupiTransport, out flag2, out flag3);
		}
		else
		{
			rect.Left = tinyPoint3.X + 12;
			rect.Right = tinyPoint3.X + 19;
			rect.Top = tinyPoint3.Y + 60 - 2;
			rect.Bottom = tinyPoint3.Y + 60;
			flag2 = !DecorDetect(rect);
			rect.Left = tinyPoint3.X + 60 - 19;
			rect.Right = tinyPoint3.X + 60 - 12;
			rect.Top = tinyPoint3.Y + 60 - 2;
			rect.Bottom = tinyPoint3.Y + 60;
			flag3 = !DecorDetect(rect);
		}
		if (flag2 && !flag3)
		{
			m_blupiAction = 10;
			m_blupiPhase = 0;
		}
		if (flag3 && !flag2)
		{
			m_blupiAction = 10;
			m_blupiPhase = 0;
		}
	}
	if (m_blupiFocus)
	{
		if (m_blupiAction == 8 && m_blupiPhase == 16)
		{
			m_blupiAction = 9;
			m_blupiPhase = 0;
		}
		if (m_blupiAction == 9 && m_blupiPhase == 3)
		{
			m_blupiAction = 1;
			m_blupiPhase = 0;
			m_blupiActionOuf = 0;
		}
		num3 = 5;
		if (m_blupiJeep)
		{
			num3 = 10;
		}
		if (m_blupiTank)
		{
			num3 = 10;
		}
		if (m_blupiSkate)
		{
			num3 = 10;
		}
		if (m_blupiAction == 10 && m_blupiPhase == num3)
		{
			m_blupiAction = 1;
			m_blupiPhase = 0;
		}
	}
	BlupiSearchIcon();
	if (m_blupiShield)
	{
		if (m_blupiTimeShield == 10)
		{
			PlaySound(43, m_blupiPos);
		}
		if (m_blupiTimeShield == 0)
		{
			m_blupiShield = false;
			m_jauges[1].SetHide(true);
		}
		else if (m_time % 5 == 0)
		{
			m_blupiTimeShield--;
			m_jauges[1].SetLevel(m_blupiTimeShield);
		}
	}
	if (m_blupiPower)
	{
		if (m_blupiTimeShield == 20)
		{
			PlaySound(45, m_blupiPos);
		}
		if (m_blupiTimeShield == 0)
		{
			m_blupiPower = false;
			m_jauges[1].SetHide(true);
		}
		else if (m_time % 3 == 0)
		{
			m_blupiTimeShield--;
			m_jauges[1].SetLevel(m_blupiTimeShield);
		}
	}
	if (m_blupiCloud)
	{
		if (m_blupiTimeShield == 25)
		{
			PlaySound(56, m_blupiPos);
		}
		if (m_blupiTimeShield == 0)
		{
			m_blupiCloud = false;
			m_jauges[1].SetHide(true);
		}
		else if (m_time % 4 == 0)
		{
			m_blupiTimeShield--;
			m_jauges[1].SetLevel(m_blupiTimeShield);
		}
	}
	if (m_blupiHide)
	{
		if (m_blupiTimeShield == 20)
		{
			PlaySound(63, m_blupiPos);
		}
		if (m_blupiTimeShield == 0)
		{
			m_blupiHide = false;
			m_jauges[1].SetHide(true);
		}
		else if (m_time % 4 == 0)
		{
			m_blupiTimeShield--;
			m_jauges[1].SetLevel(m_blupiTimeShield);
		}
	}
	if (m_blupiInvert)
	{
		if (m_blupiTimeShield == 0)
		{
			m_blupiInvert = false;
			m_jauges[1].SetHide(true);
			tinyPoint.X = m_blupiPos.X;
			tinyPoint.Y = m_blupiPos.Y + 100;
			ObjectStart(tinyPoint, 42, -60);
			tinyPoint.X = m_blupiPos.X;
			tinyPoint.Y = m_blupiPos.Y - 100;
			ObjectStart(tinyPoint, 42, 60);
			tinyPoint.X = m_blupiPos.X - 100;
			tinyPoint.Y = m_blupiPos.Y;
			ObjectStart(tinyPoint, 42, 10);
			tinyPoint.X = m_blupiPos.X + 100;
			tinyPoint.Y = m_blupiPos.Y;
			ObjectStart(tinyPoint, 42, -10);
			PlaySound(67, tinyPoint3);
		}
		else if (m_time % 3 == 0)
		{
			m_blupiTimeShield--;
			m_jauges[1].SetLevel(m_blupiTimeShield);
		}
	}
	if (m_blupiBalloon)
	{
		if (m_blupiTimeShield == 0)
		{
			m_blupiBalloon = false;
			m_jauges[1].SetHide(true);
			tinyPoint.X = m_blupiPos.X - 34;
			tinyPoint.Y = m_blupiPos.Y - 34;
			ObjectStart(tinyPoint, 91, 0);
			PlaySound(41, m_blupiPos);
		}
		else if (m_time % 2 == 0)
		{
			m_blupiTimeShield--;
			m_jauges[1].SetLevel(m_blupiTimeShield);
		}
	}
	if (m_blupiEcrase)
	{
		if (m_blupiTimeShield == 0)
		{
			m_blupiEcrase = false;
			m_blupiAir = true;
			m_jauges[1].SetHide(true);
			ObjectStart(m_blupiPos, 41, -60);
			ObjectStart(m_blupiPos, 41, 60);
			ObjectStart(m_blupiPos, 41, 10);
			ObjectStart(m_blupiPos, 41, -10);
			tinyPoint.X = m_blupiPos.X - 34;
			tinyPoint.Y = m_blupiPos.Y - 34;
			ObjectStart(tinyPoint, 90, 0);
			PlaySound(41, m_blupiPos);
		}
		else if (m_time % 2 == 0)
		{
			m_blupiTimeShield--;
			m_jauges[1].SetLevel(m_blupiTimeShield);
		}
	}
	if (m_blupiPower && Math.Abs(m_blupiPos.X - m_blupiPosMagic.X) + Math.Abs(m_blupiPos.Y - m_blupiPosMagic.Y) >= 40)
	{
		num = MoveObjectFree();
		if (num != -1)
		{
			m_moveObject[num].type = 27;
			m_moveObject[num].phase = 0;
			m_moveObject[num].posCurrent = m_blupiPos;
			m_moveObject[num].posStart = m_moveObject[num].posCurrent;
			m_moveObject[num].posEnd = m_moveObject[num].posCurrent;
			m_moveObject[num].step = 1;
			m_moveObject[num].time = 0;
			MoveObjectStepIcon(num);
			m_blupiPosMagic = m_blupiPos;
		}
	}
	if (m_blupiShield && Math.Abs(m_blupiPos.X - m_blupiPosMagic.X) + Math.Abs(m_blupiPos.Y - m_blupiPosMagic.Y) >= 40)
	{
		num = MoveObjectFree();
		if (num != -1)
		{
			m_moveObject[num].type = 57;
			m_moveObject[num].phase = 0;
			m_moveObject[num].posCurrent = m_blupiPos;
			m_moveObject[num].posStart = m_moveObject[num].posCurrent;
			m_moveObject[num].posEnd = m_moveObject[num].posCurrent;
			m_moveObject[num].step = 1;
			m_moveObject[num].time = 0;
			MoveObjectStepIcon(num);
			m_blupiPosMagic = m_blupiPos;
		}
	}
	if (m_blupiHide && Math.Abs(m_blupiPos.X - m_blupiPosMagic.X) + Math.Abs(m_blupiPos.Y - m_blupiPosMagic.Y) >= 10)
	{
		num = MoveObjectFree();
		if (num != -1)
		{
			m_moveObject[num].type = 58;
			m_moveObject[num].icon = m_blupiIcon;
			m_moveObject[num].channel = 2;
			m_moveObject[num].phase = 0;
			m_moveObject[num].posCurrent = m_blupiPos;
			m_moveObject[num].posStart = m_moveObject[num].posCurrent;
			m_moveObject[num].posEnd = m_moveObject[num].posCurrent;
			m_moveObject[num].step = 1;
			m_moveObject[num].time = 0;
			MoveObjectStepIcon(num);
			m_blupiPosMagic = m_blupiPos;
		}
	}
	if (m_blupiTimeNoAsc > 0)
	{
		m_blupiTimeNoAsc--;
	}
	if (m_blupiHelico && m_blupiPos.Y > 2 && m_blupiFocus && !m_blupiShield && !m_blupiHide && !m_bSuperBlupi)
	{
		rect = BlupiRect(tinyPoint3);
		rect.Top = tinyPoint3.Y + 4;
		rect.Bottom = tinyPoint3.Y + 20;
		if (DecorDetect(rect))
		{
			ByeByeHelico();
			m_blupiAction = 1;
			m_blupiPhase = 0;
			m_blupiHelico = false;
			tinyPoint.X = m_blupiPos.X - 34;
			tinyPoint.Y = m_blupiPos.Y - 34;
			ObjectStart(tinyPoint, 9, 0);
			m_decorAction = 1;
			m_decorPhase = 0;
			StopSound(16);
			StopSound(18);
			StopSound(29);
			StopSound(31);
			PlaySound(10, m_blupiPos);
		}
	}
	if (!m_blupiHelico && !m_blupiOver && !m_blupiBalloon && !m_blupiEcrase && !m_blupiJeep && !m_blupiTank && !m_blupiSkate && m_blupiFocus)
	{
		if (!m_blupiNage && !m_blupiSurf && IsSurfWater(m_blupiPos))
		{
			m_scrollAdd.X = 0;
			m_scrollAdd.Y = 0;
			m_blupiAir = false;
			m_blupiNage = false;
			m_blupiSurf = true;
			m_blupiAction = 1;
			m_blupiPhase = 0;
			m_blupiVitesseX = 0.0;
			m_blupiVitesseY = 0.0;
			MoveObjectPlouf(m_blupiPos);
			if (m_blupiTransport != -1)
			{
				m_blupiPos.Y = m_blupiPos.Y - 10;
				m_blupiTransport = -1;
			}
			if (m_blupiCloud)
			{
				m_blupiCloud = false;
				m_jauges[1].SetHide(true);
			}
		}
		if (!m_blupiNage && !IsSurfWater(m_blupiPos) && IsDeepWater(m_blupiPos))
		{
			if (!m_blupiSurf)
			{
				m_blupiAction = 1;
				m_blupiPhase = 0;
				m_blupiVitesseX = 0.0;
				m_blupiVitesseY = 0.0;
				MoveObjectPlouf(m_blupiPos);
			}
			m_blupiAir = false;
			m_blupiSurf = false;
			m_blupiNage = true;
			m_blupiLevel = 100;
			m_jauges[0].SetLevel(m_blupiLevel);
			m_jauges[0].SetMode(2);
			m_jauges[0].SetHide(false);
		}
		if (m_blupiNage && IsSurfWater(m_blupiPos))
		{
			m_blupiAir = false;
			m_blupiNage = false;
			m_blupiSurf = true;
			PlaySound(25, m_blupiPos);
			m_jauges[0].SetHide(true);
		}
		tinyPoint4.X = m_blupiPos.X;
		tinyPoint4.Y = m_blupiPos.Y - 60;
		if ((m_blupiSurf || m_blupiNage) && (m_blupiPos.Y % 64 == 64 - Decor.BLUPISURF || m_blupiPos.Y % 64 == 32) && IsOutWater(tinyPoint4) && (m_keyPress & 1) != 0)
		{
			m_blupiNage = false;
			m_blupiSurf = false;
			m_blupiAir = true;
			m_blupiAction = 5;
			m_blupiPhase = 0;
			m_blupiVitesseX = 0.0;
			if (m_blupiPower)
			{
				m_blupiVitesseY = -16.0;
			}
			else
			{
				m_blupiVitesseY = -12.0;
			}
			MoveObjectTiplouf(m_blupiPos);
			PlaySound(22, m_blupiPos);
			m_jauges[0].SetHide(true);
		}
		if ((m_blupiSurf || m_blupiNage) && IsOutWater(m_blupiPos))
		{
			if (m_blupiVitesseY < 0.0)
			{
				if (m_blupiTransport == -1)
				{
					m_blupiPos = blupiPos;
				}
				else
				{
					m_blupiTransport = -1;
					m_blupiNage = false;
					m_blupiSurf = false;
					m_blupiAir = true;
					m_blupiAction = 5;
					m_blupiPhase = 0;
					m_blupiPos.Y = m_blupiPos.Y - 10;
					m_blupiVitesseX = 0.0;
					m_blupiVitesseY = -10.0;
					PlaySound(22, m_blupiPos);
					m_jauges[0].SetHide(true);
				}
			}
			else if (m_blupiVitesseY > 0.0)
			{
				m_blupiNage = false;
				m_blupiSurf = false;
				m_blupiAir = false;
				m_blupiAction = 5;
				m_blupiPhase = 0;
				m_blupiPos.Y = m_blupiPos.Y + 30;
				m_blupiVitesseX = 0.0;
				m_blupiVitesseY = 0.0;
				PlaySound(22, m_blupiPos);
				m_jauges[0].SetHide(true);
			}
			else
			{
				m_blupiNage = false;
				m_blupiSurf = false;
				m_blupiAir = false;
				m_blupiAction = 1;
				m_blupiPhase = 0;
				m_blupiPos.Y = m_blupiPos.Y - 10;
				m_blupiVitesseX = 0.0;
				m_blupiVitesseY = 0.0;
				PlaySound(22, m_blupiPos);
				m_jauges[0].SetHide(true);
			}
		}
		if ((m_blupiSurf || m_blupiNage) && m_blupiActionOuf != 44)
		{
			m_blupiActionOuf = 44;
			m_blupiTimeOuf = 0;
		}
	}
	if ((m_blupiHelico || m_blupiOver || m_blupiJeep || m_blupiTank || m_blupiSkate) && m_blupiFocus && (IsSurfWater(m_blupiPos) || IsDeepWater(m_blupiPos)))
	{
		ByeByeHelico();
		m_blupiAction = 1;
		m_blupiPhase = 0;
		m_blupiHelico = false;
		m_blupiOver = false;
		m_blupiJeep = false;
		m_blupiTank = false;
		m_blupiSkate = false;
		tinyPoint.X = m_blupiPos.X - 34;
		tinyPoint.Y = m_blupiPos.Y - 34;
		ObjectStart(tinyPoint, 9, 0);
		m_decorAction = 1;
		m_decorPhase = 0;
		StopSound(16);
		StopSound(18);
		StopSound(29);
		StopSound(31);
		PlaySound(10, m_blupiPos);
	}
	if (m_blupiFocus && !m_blupiSuspend && !m_blupiHelico && !m_blupiOver && !m_blupiBalloon && !m_blupiEcrase && !m_blupiJeep && !m_blupiTank && !m_blupiSkate && !m_blupiNage && !m_blupiSurf && m_blupiNoBarre == 0 && GetTypeBarre(m_blupiPos) == 1)
	{
		tinyPoint4.X = m_blupiPos.X;
		tinyPoint4.Y = (m_blupiPos.Y + 22) / 64 * 64 + Decor.BLUPISUSPEND;
		rect = BlupiRect(tinyPoint4);
		if (!DecorDetect(rect, true))
		{
			m_blupiPos = tinyPoint4;
			m_blupiSuspend = true;
			m_blupiAir = false;
			m_blupiAction = 1;
			m_blupiPhase = 0;
			m_blupiActionOuf = 0;
			PlaySound(34, m_blupiPos);
		}
	}
	if (m_blupiNoBarre > 0)
	{
		m_blupiNoBarre--;
	}
	if (IsVentillo(m_blupiPos))
	{
		if (m_blupiFocus && !m_blupiShield && !m_blupiHide && !m_bSuperBlupi)
		{
			BlupiDead(11, 75);
		}
		tinyPoint.X = m_blupiPos.X - 34;
		tinyPoint.Y = m_blupiPos.Y - 34;
		ObjectStart(tinyPoint, 11, 0);
		m_decorAction = 2;
		m_decorPhase = 0;
		StopSound(16);
		StopSound(18);
		StopSound(29);
		StopSound(31);
		PlaySound(10, m_blupiPos);
	}
	if (m_blupiAction != 30 && m_blupiFocus)
	{
		num = IsWorld(m_blupiPos);
		if (num != -1)
		{
			StopSound(16);
			StopSound(18);
			StopSound(29);
			StopSound(31);
			PlaySound(32, m_blupiPos);
			m_blupiAction = 30;
			m_blupiPhase = 0;
			m_blupiFocus = false;
			m_blupiFront = true;
		}
	}
	int num27 = MoveObjectDetect(m_blupiPos, out flag6);
	TinyPoint tinyPoint5;
	if (m_blupiAction != 11 && m_blupiAction != 75 && m_blupiAction != 76 && m_blupiAction != 77 && m_blupiAction != 78 && m_blupiAction != 79 && m_blupiAction != 80 && m_blupiAction != 81)
	{
		if (IsLave(m_blupiPos) && !m_blupiShield && !m_blupiHide && !m_bSuperBlupi)
		{
			BlupiDead(76, -1);
			m_blupiRestart = true;
			m_blupiPos.Y = m_blupiPos.Y / 64 * 64 + Decor.BLUPIOFFY;
			PlaySound(8, m_blupiPos);
		}
		if (IsPiege(m_blupiPos) && !m_blupiOver && !m_blupiJeep && !m_blupiTank && !m_blupiShield && !m_blupiHide && !m_bSuperBlupi && m_blupiFocus)
		{
			BlupiDead(54, -1);
			m_blupiRestart = true;
			m_blupiAir = true;
			ObjectStart(m_blupiPos, 53, 0);
			PlaySound(51, m_blupiPos);
		}
		if (IsGoutte(m_blupiPos, false) && !m_blupiOver && !m_blupiJeep && !m_blupiTank && !m_blupiShield && !m_blupiHide && !m_bSuperBlupi && m_blupiFocus)
		{
			BlupiDead(54, -1);
			m_blupiRestart = true;
			m_blupiAir = true;
			PlaySound(51, m_blupiPos);
		}
		if (IsScie(m_blupiPos) && !m_blupiOver && !m_blupiJeep && !m_blupiTank && !m_blupiShield && !m_blupiHide && !m_bSuperBlupi && m_blupiFocus)
		{
			BlupiDead(77, -1);
			m_blupiFront = true;
			m_blupiRestart = true;
			m_blupiAir = true;
		}
		if (ButtonPressed == Def.ButtonGlygh.PlayAction && (num27 == -1 || !flag6) && IsSwitch(m_blupiPos, ref tinyPoint) && !m_blupiOver && !m_blupiBalloon && !m_blupiJeep && !m_blupiTank && !m_blupiSkate && !m_blupiShield && !m_blupiHide && !m_bSuperBlupi && m_blupiFocus)
		{
			ButtonPressed = Def.ButtonGlygh.None;
			ActiveSwitch(m_decor[tinyPoint.X, tinyPoint.Y].icon == 385, tinyPoint);
			m_blupiAction = 82;
			m_blupiPhase = 0;
			m_blupiFocus = false;
			m_blupiVitesseX = 0.0;
			m_blupiVitesseY = 0.0;
		}
		if (IsBlitz(m_blupiPos, false) && !m_blupiShield && !m_blupiHide && !m_bSuperBlupi)
		{
			BlupiDead(11, -1);
			m_blupiRestart = true;
			m_blupiAir = true;
			m_blupiPos.Y = m_blupiPos.Y / 64 * 64 + Decor.BLUPIOFFY;
			PlaySound(8, m_blupiPos);
		}
		if (IsEcraseur(m_blupiPos) && !m_blupiEcrase && !m_blupiShield && !m_blupiHide && !m_bSuperBlupi && m_blupiFocus)
		{
			m_blupiAction = 1;
			m_blupiPhase = 0;
			m_blupiVitesseX = 0.0;
			m_blupiVitesseY = 0.0;
			m_blupiEcrase = true;
			m_blupiBalloon = false;
			m_blupiAir = false;
			m_blupiHelico = false;
			m_blupiOver = false;
			m_blupiJeep = false;
			m_blupiTank = false;
			m_blupiSkate = false;
			m_blupiNage = false;
			m_blupiSurf = false;
			m_blupiSuspend = false;
			m_blupiJumpAie = false;
			m_blupiShield = false;
			m_blupiPower = false;
			m_blupiCloud = false;
			m_blupiHide = false;
			m_blupiTimeShield = 100;
			m_blupiPosMagic = m_blupiPos;
			m_jauges[1].SetHide(false);
			if (!m_blupiJeep && !m_blupiTank)
			{
				StopSound(16);
				StopSound(18);
				StopSound(29);
				StopSound(31);
			}
			PlaySound(70, m_blupiPos);
			ObjectStart(m_blupiPos, 41, -60);
			ObjectStart(m_blupiPos, 41, 60);
			ObjectStart(m_blupiPos, 41, 10);
			ObjectStart(m_blupiPos, 41, -10);
			tinyPoint.X = m_blupiPos.X - 34;
			tinyPoint.Y = m_blupiPos.Y - 34;
			ObjectStart(tinyPoint, 90, 0);
			m_decorAction = 2;
			m_decorPhase = 0;
		}
		if (IsTeleporte(m_blupiPos) != -1 && !m_blupiHelico && !m_blupiOver && !m_blupiBalloon && !m_blupiEcrase && !m_blupiJeep && !m_blupiTank && !m_blupiSkate && !m_blupiAir && m_blupiFocus && m_blupiPosHelico.X == -1)
		{
			m_blupiAction = 74;
			m_blupiPhase = 0;
			m_blupiVitesseX = 0.0;
			m_blupiVitesseY = 0.0;
			m_blupiFocus = false;
			m_blupiPos.X = m_blupiPos.X / 64 * 64;
			PlaySound(71, m_blupiPos);
			tinyPoint.X = m_blupiPos.X;
			tinyPoint.Y = m_blupiPos.Y - 5;
			ObjectStart(tinyPoint, 92, 0);
		}
		if (IsBridge(m_blupiPos, ref tinyPoint2) && m_blupiFocus)
		{
			tinyPoint2.X *= 64;
			tinyPoint2.Y *= 64;
			ObjectStart(tinyPoint2, 52, 0);
		}
		int num2 = IsDoor(m_blupiPos, ref tinyPoint2);
		if (num2 != -1 && (m_blupiCle & 1 << num2 - 334) != 0)
		{
			OpenDoor(tinyPoint2);
			m_blupiCle &= ~(1 << num2 - 334);
			tinyPoint.X = 520;
			tinyPoint.Y = 418;
			tinyPoint5.X = tinyPoint2.X * 64 - m_posDecor.X;
			tinyPoint5.Y = tinyPoint2.Y * 64 - m_posDecor.Y;
			VoyageInit(tinyPoint, m_pixmap.HotSpotToHud(tinyPoint5), 214 + (num2 - 334) * 7, 10);
		}
	}
	if (!m_blupiHelico && !m_blupiSuspend && !m_blupiOver && !m_blupiBalloon && !m_blupiEcrase && !m_blupiSkate && !m_blupiJeep && !m_blupiTank && !m_blupiJeep && m_blupiFocus)
	{
		num = MockeryDetect(m_blupiPos);
		if (num != 0)
		{
			m_blupiActionOuf = num;
			m_blupiTimeOuf = 0;
		}
	}
	MoveObjectFollow(m_blupiPos);
	num = num27;
	if (num != -1 && !flag6 && m_moveObject[num].type == 2 && !m_blupiHelico && !m_blupiOver && !m_blupiBalloon && !m_blupiEcrase && !m_blupiJeep && !m_blupiTank && !m_blupiSkate && !m_blupiNage && !m_blupiSurf && !m_blupiSuspend && !m_blupiShield && !m_bSuperBlupi && m_blupiFocus)
	{
		m_blupiActionOuf = 48;
		m_blupiTimeOuf = 0;
	}
	if (num != -1 && flag6)
	{
		if (m_moveObject[num].type == 13 && (ButtonPressed == Def.ButtonGlygh.PlayAction || IsFloatingObject(num)) && !m_blupiHelico && !m_blupiOver && !m_blupiBalloon && !m_blupiEcrase && !m_blupiJeep && !m_blupiTank && !m_blupiSkate && !m_blupiNage && !m_blupiSurf && !m_blupiSuspend && m_blupiFocus)
		{
			ButtonPressed = Def.ButtonGlygh.None;
			ObjectDelete(m_moveObject[num].posCurrent, m_moveObject[num].type);
			m_scrollAdd.X = 0;
			m_scrollAdd.Y = 0;
			m_blupiAir = false;
			m_blupiHelico = true;
			m_blupiRealRotation = 0;
			m_blupiVitesseX = 0.0;
			if (m_blupiCloud || m_blupiHide)
			{
				m_blupiCloud = false;
				m_blupiHide = false;
				m_jauges[1].SetHide(true);
			}
		}
		if (ButtonPressed == Def.ButtonGlygh.PlayAction && m_moveObject[num].type == 46 && !m_blupiHelico && !m_blupiOver && !m_blupiBalloon && !m_blupiEcrase && !m_blupiJeep && !m_blupiTank && !m_blupiSkate && !m_blupiNage && !m_blupiSurf && !m_blupiSuspend && m_blupiFocus)
		{
			ButtonPressed = Def.ButtonGlygh.None;
			ObjectDelete(m_moveObject[num].posCurrent, m_moveObject[num].type);
			m_scrollAdd.X = 0;
			m_scrollAdd.Y = 0;
			m_blupiAir = false;
			m_blupiOver = true;
			m_blupiVitesseX = 0.0;
			if (m_blupiCloud || m_blupiHide)
			{
				m_blupiCloud = false;
				m_blupiHide = false;
				m_jauges[1].SetHide(true);
			}
		}
		if (ButtonPressed == Def.ButtonGlygh.PlayAction && m_moveObject[num].type == 19 && !m_blupiHelico && !m_blupiOver && !m_blupiBalloon && !m_blupiEcrase && !m_blupiJeep && !m_blupiTank && !m_blupiSkate && !m_blupiNage && !m_blupiSurf && !m_blupiSuspend && m_blupiFocus)
		{
			ButtonPressed = Def.ButtonGlygh.None;
			ObjectDelete(m_moveObject[num].posCurrent, m_moveObject[num].type);
			m_scrollAdd.X = 0;
			m_scrollAdd.Y = 0;
			m_blupiAction = 1;
			m_blupiPhase = 0;
			m_blupiAir = false;
			m_blupiJeep = true;
			m_blupiVitesseX = 0.0;
			if (m_blupiCloud || m_blupiHide)
			{
				m_blupiCloud = false;
				m_blupiHide = false;
				m_jauges[1].SetHide(true);
			}
		}
		if (ButtonPressed == Def.ButtonGlygh.PlayAction && m_moveObject[num].type == 28 && !m_blupiHelico && !m_blupiOver && !m_blupiBalloon && !m_blupiEcrase && !m_blupiJeep && !m_blupiTank && !m_blupiSkate && !m_blupiNage && !m_blupiSurf && !m_blupiSuspend && m_blupiFocus)
		{
			ButtonPressed = Def.ButtonGlygh.None;
			ObjectDelete(m_moveObject[num].posCurrent, m_moveObject[num].type);
			m_scrollAdd.X = 0;
			m_scrollAdd.Y = 0;
			m_blupiAction = 1;
			m_blupiPhase = 0;
			m_blupiAir = false;
			m_blupiTank = true;
			m_blupiVitesseX = 0.0;
			if (m_blupiCloud || m_blupiHide)
			{
				m_blupiCloud = false;
				m_blupiHide = false;
				m_jauges[1].SetHide(true);
			}
		}
		if (m_moveObject[num].type == 29 && m_blupiFocus && m_blupiBullet < 10)
		{
			ObjectDelete(m_moveObject[num].posCurrent, m_moveObject[num].type);
			tinyPoint.X = m_moveObject[num].posCurrent.X - m_posDecor.X;
			tinyPoint.Y = m_moveObject[num].posCurrent.Y - m_posDecor.Y;
			tinyPoint5.X = 570;
			tinyPoint5.Y = 430;
			VoyageInit(m_pixmap.HotSpotToHud(tinyPoint), tinyPoint5, 177, 10);
			m_blupiBullet += 10;
			if (m_blupiBullet > 10)
			{
				m_blupiBullet = 10;
			}
		}
		if (ButtonPressed == Def.ButtonGlygh.PlayAction && m_moveObject[num].type == 24 && !m_blupiHelico && !m_blupiOver && !m_blupiBalloon && !m_blupiEcrase && !m_blupiJeep && !m_blupiTank && !m_blupiSkate && !m_blupiNage && !m_blupiSurf && !m_blupiSuspend && m_blupiFocus)
		{
			ButtonPressed = Def.ButtonGlygh.None;
			m_scrollAdd.X = 0;
			m_scrollAdd.Y = 0;
			m_blupiAction = 42;
			m_blupiPhase = 0;
			m_blupiPos.Y = m_moveObject[num].posCurrent.Y / 64 * 64 + Decor.BLUPIOFFY;
			m_blupiFocus = false;
			m_blupiAir = false;
			m_blupiSkate = true;
			m_blupiVitesseX = 0.0;
			if (m_blupiCloud || m_blupiHide)
			{
				m_blupiCloud = false;
				m_blupiHide = false;
				m_jauges[1].SetHide(true);
			}
		}
		if ((m_moveObject[num].type == 3 || m_moveObject[num].type == 16 || m_moveObject[num].type == 96 || m_moveObject[num].type == 97) && m_blupiBalloon && m_blupiPosHelico.X == -1)
		{
			m_blupiBalloon = false;
			m_blupiAir = true;
			m_blupiTimeShield = 0;
			m_jauges[1].SetHide(true);
			m_decorAction = 0;
			tinyPoint.X = m_blupiPos.X - 34;
			tinyPoint.Y = m_blupiPos.Y - 34;
			ObjectStart(tinyPoint, 91, 0);
			PlaySound(41, m_blupiPos);
			m_blupiPos.Y = m_blupiPos.Y + 4;
			m_blupiVitesseY = 0.0;
			m_blupiPosHelico = m_blupiPos;
		}
		else if ((m_moveObject[num].type == 2 || m_moveObject[num].type == 3 || m_moveObject[num].type == 96 || m_moveObject[num].type == 97 || m_moveObject[num].type == 16 || m_moveObject[num].type == 4 || m_moveObject[num].type == 17 || m_moveObject[num].type == 20) && !m_blupiShield && !m_blupiHide && !m_bSuperBlupi && m_blupiPosHelico.X == -1)
		{
			if (!m_blupiJeep && !m_blupiTank && !m_blupiSkate && (m_blupiFocus || m_blupiAction == 5 || m_blupiAction == 36))
			{
				if (m_blupiHelico || m_blupiOver || m_blupiBalloon || m_blupiEcrase)
				{
					m_blupiAir = true;
				}
				BlupiDead(11, 75);
			}
			if (m_moveObject[num].type == 17 || m_moveObject[num].type == 20)
			{
				tinyPoint = m_moveObject[num].posCurrent;
				ObjectDelete(tinyPoint, m_moveObject[num].type);
				tinyPoint.X -= 34;
				tinyPoint.Y -= 34;
				ObjectStart(tinyPoint, 10, 0);
				m_decorAction = 2;
				m_decorPhase = 0;
			}
			else
			{
				tinyPoint = m_moveObject[num].posCurrent;
				ObjectDelete(tinyPoint, m_moveObject[num].type);
				tinyPoint.X -= 34;
				tinyPoint.Y -= 34;
				ObjectStart(tinyPoint, 8, 0);
				m_decorAction = 1;
				m_decorPhase = 0;
			}
			if (!m_blupiJeep && !m_blupiTank)
			{
				StopSound(16);
				StopSound(18);
				StopSound(29);
				StopSound(31);
			}
			PlaySound(10, m_moveObject[num].posCurrent);
		}
		if (m_moveObject[num].type == 44 && m_blupiFocus && !m_blupiBalloon && !m_blupiShield && !m_blupiHide && !m_bSuperBlupi)
		{
			ByeByeHelico();
			m_blupiAction = 1;
			m_blupiPhase = 0;
			m_blupiVitesseX = 0.0;
			m_blupiVitesseY = 0.0;
			m_blupiBalloon = true;
			m_blupiEcrase = false;
			m_blupiAir = false;
			m_blupiHelico = false;
			m_blupiOver = false;
			m_blupiJeep = false;
			m_blupiTank = false;
			m_blupiSkate = false;
			m_blupiNage = false;
			m_blupiSurf = false;
			m_blupiSuspend = false;
			m_blupiJumpAie = false;
			m_blupiShield = false;
			m_blupiPower = false;
			m_blupiCloud = false;
			m_blupiHide = false;
			m_blupiTimeShield = 100;
			m_blupiPosMagic = m_blupiPos;
			m_jauges[1].SetHide(false);
			if (!m_blupiJeep && !m_blupiTank)
			{
				StopSound(16);
				StopSound(18);
				StopSound(29);
				StopSound(31);
			}
			PlaySound(40, m_moveObject[num].posCurrent);
			tinyPoint.X = m_blupiPos.X - 34;
			tinyPoint.Y = m_blupiPos.Y - 34;
			ObjectStart(tinyPoint, 90, 0);
			m_decorAction = 5;
			m_decorPhase = 0;
		}
		if (m_moveObject[num].type == 54 && m_moveObject[num].step != 2 && m_moveObject[num].step != 4 && m_blupiFocus && !m_blupiBalloon && !m_blupiShield && !m_blupiHide && !m_bSuperBlupi)
		{
			ByeByeHelico();
			tinyPoint.X = m_blupiPos.X;
			tinyPoint.Y = (m_blupiPos.Y + 64 - 10) / 64 * 64 + 4;
			ObjectStart(tinyPoint, 53, 0);
			m_blupiAction = 54;
			m_blupiPhase = 0;
			m_blupiSuspend = false;
			m_blupiJumpAie = false;
			m_blupiFocus = false;
			m_blupiRestart = true;
			if (flag4)
			{
				m_blupiAir = true;
			}
			if (m_blupiHelico || m_blupiOver || m_blupiBalloon || m_blupiEcrase || m_blupiJeep || m_blupiTank || m_blupiSkate)
			{
				m_blupiHelico = false;
				m_blupiOver = false;
				m_blupiBalloon = false;
				m_blupiEcrase = false;
				m_blupiJeep = false;
				m_blupiTank = false;
				m_blupiSkate = false;
				tinyPoint = m_moveObject[num].posCurrent;
				tinyPoint.X -= 34;
				tinyPoint.Y -= 34;
				ObjectStart(tinyPoint, 10, 0);
				StopSound(16);
				StopSound(18);
				StopSound(29);
				StopSound(31);
				PlaySound(10, m_moveObject[num].posCurrent);
				m_decorAction = 1;
				m_decorPhase = 0;
			}
			else
			{
				PlaySound(51, m_moveObject[num].posCurrent);
			}
			m_blupiCloud = false;
			m_blupiHide = false;
			m_jauges[1].SetHide(true);
		}
		if (m_moveObject[num].type == 23 && !m_blupiShield && !m_blupiHide && !m_bSuperBlupi && m_blupiAction != 13 && m_blupiAction != 30 && m_blupiAction != 11 && m_blupiAction != 75 && m_blupiAction != 76 && m_blupiAction != 77 && m_blupiAction != 78 && m_blupiAction != 79 && m_blupiAction != 80 && m_blupiAction != 81 && m_blupiAction != 54 && m_blupiAction != 57 && m_blupiAction != 35)
		{
			ByeByeHelico();
			tinyPoint = m_moveObject[num].posCurrent;
			ObjectDelete(tinyPoint, m_moveObject[num].type);
			m_blupiAction = 54;
			m_blupiPhase = 0;
			m_blupiSuspend = false;
			m_blupiJumpAie = false;
			m_blupiFocus = false;
			m_blupiRestart = true;
			if (flag4)
			{
				m_blupiAir = true;
			}
			if (m_blupiHelico || m_blupiOver || m_blupiBalloon || m_blupiEcrase || m_blupiJeep || m_blupiTank || m_blupiSkate)
			{
				m_blupiHelico = false;
				m_blupiOver = false;
				m_blupiBalloon = false;
				m_blupiEcrase = false;
				m_blupiJeep = false;
				m_blupiTank = false;
				m_blupiSkate = false;
			}
			StartSploutchGlu(m_moveObject[num].posCurrent);
			m_blupiCloud = false;
			m_blupiHide = false;
			m_jauges[1].SetHide(true);
		}
		if (m_moveObject[num].type == 5)
		{
			ObjectDelete(m_moveObject[num].posCurrent, m_moveObject[num].type);
			tinyPoint.X = m_moveObject[num].posCurrent.X - m_posDecor.X;
			tinyPoint.Y = m_moveObject[num].posCurrent.Y - m_posDecor.Y;
			TinyPoint end;
			end.X = 430;
			end.Y = 430;
			VoyageInit(m_pixmap.HotSpotToHud(tinyPoint), end, 6, 10);
			ObjectStart(m_moveObject[num].posCurrent, 39, -60);
			ObjectStart(m_moveObject[num].posCurrent, 39, 60);
			ObjectStart(m_moveObject[num].posCurrent, 39, 10);
			ObjectStart(m_moveObject[num].posCurrent, 39, -10);
		}
		if (m_moveObject[num].type == 49 && (m_voyageIcon != 215 || m_voyageChannel != 10) && (m_blupiCle & 1) == 0)
		{
			ObjectDelete(m_moveObject[num].posCurrent, m_moveObject[num].type);
			tinyPoint.X = m_moveObject[num].posCurrent.X - m_posDecor.X;
			tinyPoint.Y = m_moveObject[num].posCurrent.Y - m_posDecor.Y;
			TinyPoint end2;
			end2.X = 520;
			end2.Y = 418;
			VoyageInit(m_pixmap.HotSpotToHud(tinyPoint), end2, 215, 10);
			ObjectStart(m_moveObject[num].posCurrent, 39, -60);
			ObjectStart(m_moveObject[num].posCurrent, 39, 60);
			ObjectStart(m_moveObject[num].posCurrent, 39, 10);
			ObjectStart(m_moveObject[num].posCurrent, 39, -10);
		}
		if (m_moveObject[num].type == 50 && (m_voyageIcon != 222 || m_voyageChannel != 10) && (m_blupiCle & 2) == 0)
		{
			ObjectDelete(m_moveObject[num].posCurrent, m_moveObject[num].type);
			tinyPoint.X = m_moveObject[num].posCurrent.X - m_posDecor.X;
			tinyPoint.Y = m_moveObject[num].posCurrent.Y - m_posDecor.Y;
			TinyPoint end3;
			end3.X = 530;
			end3.Y = 418;
			VoyageInit(m_pixmap.HotSpotToHud(tinyPoint), end3, 222, 10);
			ObjectStart(m_moveObject[num].posCurrent, 39, -60);
			ObjectStart(m_moveObject[num].posCurrent, 39, 60);
			ObjectStart(m_moveObject[num].posCurrent, 39, 10);
			ObjectStart(m_moveObject[num].posCurrent, 39, -10);
		}
		if (m_moveObject[num].type == 51 && (m_voyageIcon != 229 || m_voyageChannel != 10) && (m_blupiCle & 4) == 0)
		{
			ObjectDelete(m_moveObject[num].posCurrent, m_moveObject[num].type);
			tinyPoint.X = m_moveObject[num].posCurrent.X - m_posDecor.X;
			tinyPoint.Y = m_moveObject[num].posCurrent.Y - m_posDecor.Y;
			TinyPoint end4;
			end4.X = 540;
			end4.Y = 418;
			VoyageInit(m_pixmap.HotSpotToHud(tinyPoint), end4, 229, 10);
			ObjectStart(m_moveObject[num].posCurrent, 39, -60);
			ObjectStart(m_moveObject[num].posCurrent, 39, 60);
			ObjectStart(m_moveObject[num].posCurrent, 39, 10);
			ObjectStart(m_moveObject[num].posCurrent, 39, -10);
		}
		if (m_moveObject[num].type == 6 && m_nbVies < 10 && m_blupiFocus)
		{
			ObjectDelete(m_moveObject[num].posCurrent, m_moveObject[num].type);
			tinyPoint.X = m_moveObject[num].posCurrent.X - m_posDecor.X;
			tinyPoint.Y = m_moveObject[num].posCurrent.Y - m_posDecor.Y;
			VoyageInit(m_pixmap.HotSpotToHud(tinyPoint), VoyageGetPosVie(m_nbVies + 1), 21, 10);
		}
		if (m_moveObject[num].type == 25 && !m_blupiShield && !m_blupiHide && !m_blupiPower && m_blupiFocus)
		{
			PlaySound(42, m_moveObject[num].posCurrent);
			m_blupiShield = true;
			m_blupiPower = false;
			m_blupiCloud = false;
			m_blupiHide = false;
			m_blupiTimeShield = 100;
			m_blupiPosMagic = m_blupiPos;
			m_jauges[1].SetHide(false);
		}
		if (ButtonPressed == Def.ButtonGlygh.PlayAction && m_moveObject[num].type == 26 && !m_blupiShield && !m_blupiHelico && !m_blupiOver && !m_blupiBalloon && !m_blupiEcrase && !m_blupiJeep && !m_blupiTank && !m_blupiSkate && m_blupiFocus)
		{
			ButtonPressed = Def.ButtonGlygh.None;
			m_sucettePos = m_moveObject[num].posCurrent;
			m_sucetteType = m_moveObject[num].type;
			ObjectDelete(m_moveObject[num].posCurrent, m_moveObject[num].type);
			m_blupiAction = 49;
			m_blupiPhase = 0;
			m_blupiCloud = false;
			m_blupiHide = false;
			m_blupiFocus = false;
			PlaySound(50, tinyPoint3);
		}
		if (m_moveObject[num].type == 40 && !m_blupiHide && m_blupiFocus)
		{
			ObjectDelete(m_moveObject[num].posCurrent, m_moveObject[num].type);
			m_blupiInvert = true;
			m_blupiTimeShield = 100;
			m_blupiPosMagic = m_blupiPos;
			m_jauges[1].SetHide(false);
			PlaySound(66, tinyPoint3);
			ObjectStart(m_blupiPos, 41, -60);
			ObjectStart(m_blupiPos, 41, 60);
			ObjectStart(m_blupiPos, 41, 10);
			ObjectStart(m_blupiPos, 41, -10);
		}
		if (ButtonPressed == Def.ButtonGlygh.PlayAction && m_moveObject[num].type == 30 && !m_blupiShield && !m_blupiCloud && !m_blupiHelico && !m_blupiOver && !m_blupiBalloon && !m_blupiEcrase && !m_blupiJeep && !m_blupiTank && !m_blupiSkate && m_blupiFocus)
		{
			ButtonPressed = Def.ButtonGlygh.None;
			m_sucettePos = m_moveObject[num].posCurrent;
			m_sucetteType = m_moveObject[num].type;
			ObjectDelete(m_moveObject[num].posCurrent, m_moveObject[num].type);
			m_blupiAction = 55;
			m_blupiPhase = 0;
			m_blupiShield = false;
			m_blupiPower = false;
			m_blupiJumpAie = false;
			m_blupiFocus = false;
			PlaySound(57, tinyPoint3);
		}
		if (m_moveObject[num].type == 31 && !m_blupiShield && !m_blupiHide && !m_blupiPower && !m_blupiCloud && !m_blupiHelico && !m_blupiOver && !m_blupiBalloon && !m_blupiEcrase && !m_blupiJeep && !m_blupiTank && !m_blupiSkate && m_blupiFocus)
		{
			m_blupiAction = 56;
			m_blupiPhase = 0;
			m_blupiShield = false;
			m_blupiPower = false;
			m_blupiJumpAie = false;
			m_blupiFocus = false;
			m_blupiCloud = true;
			m_blupiTimeShield = 100;
			PlaySound(58, tinyPoint3);
			if (m_blupiHide)
			{
				m_blupiHide = false;
				m_jauges[1].SetHide(true);
			}
		}
		if (m_moveObject[num].type >= 200 && m_moveObject[num].type <= 203 && m_blupiFocus)
		{
			if (m_moveObject[num].type == 200)
			{
				if (m_blupiPerso < 5 && ButtonPressed == Def.ButtonGlygh.PlayAction)
				{
					ButtonPressed = Def.ButtonGlygh.None;
					ObjectDelete(m_moveObject[num].posCurrent, m_moveObject[num].type);
					tinyPoint.X = m_moveObject[num].posCurrent.X - m_posDecor.X;
					tinyPoint.Y = m_moveObject[num].posCurrent.Y - m_posDecor.Y;
					tinyPoint5.X = 0;
					tinyPoint5.Y = 438;
					VoyageInit(m_pixmap.HotSpotToHud(tinyPoint), tinyPoint5, 108, 4);
				}
			}
			else if (!m_blupiShield && !m_blupiHide && !m_bSuperBlupi)
			{
				ObjectDelete(m_moveObject[num].posCurrent, m_moveObject[num].type);
				BlupiDead(11, 75);
				tinyPoint = m_moveObject[num].posCurrent;
				tinyPoint.X -= 34;
				tinyPoint.Y -= 34;
				ObjectStart(tinyPoint, 10, 0);
				PlaySound(10, m_moveObject[num].posCurrent);
				m_decorAction = 1;
				m_decorPhase = 0;
			}
		}
		if (m_moveObject[num].type == 55 && m_blupiFocus && m_blupiDynamite == 0 && (m_voyageIcon != 252 || m_voyageChannel != 10) && ButtonPressed == Def.ButtonGlygh.PlayAction)
		{
			ButtonPressed = Def.ButtonGlygh.None;
			ObjectDelete(m_moveObject[num].posCurrent, m_moveObject[num].type);
			tinyPoint.X = m_moveObject[num].posCurrent.X - m_posDecor.X;
			tinyPoint.Y = m_moveObject[num].posCurrent.Y - m_posDecor.Y;
			tinyPoint5.X = 505;
			tinyPoint5.Y = 414;
			VoyageInit(m_pixmap.HotSpotToHud(tinyPoint), tinyPoint5, 252, 10);
			m_blupiAction = 86;
			m_blupiPhase = 0;
			m_blupiFocus = false;
		}
		if (m_moveObject[num].type == 12 && !m_blupiHelico && !m_blupiOver && !m_blupiBalloon && !m_blupiEcrase && !m_blupiJeep && !m_blupiTank && !m_blupiSkate && !m_blupiNage && !m_blupiSurf && !m_blupiSuspend && m_blupiFocus && m_blupiAction == 2)
		{
			tinyPoint3 = m_moveObject[num].posCurrent;
			if (m_blupiDir == 1 && m_blupiPos.X > tinyPoint3.X)
			{
				tinyPoint3.X = m_blupiPos.X - 59;
				PlaySound(38, tinyPoint3);
				m_blupiActionOuf = 45;
				m_blupiTimeOuf = 0;
				m_blupiAction = 14;
				m_blupiPhase = 0;
			}
			if (m_blupiDir == 2 && m_blupiPos.X < tinyPoint3.X)
			{
				tinyPoint3.X = m_blupiPos.X + 55;
				PlaySound(38, tinyPoint3);
				m_blupiActionOuf = 45;
				m_blupiTimeOuf = 0;
				m_blupiAction = 14;
				m_blupiPhase = 0;
			}
			if (!TestPushCaisse(num, tinyPoint3, false))
			{
				m_blupiPos.X = blupiPos.X;
			}
		}
		if ((m_moveObject[num].type == 7 || m_moveObject[num].type == 21) && m_blupiFocus)
		{
			if (m_goalPhase == 0)
			{
				if (m_nbTresor >= m_totalTresor)
				{
					if (m_moveObject[num].type == 21)
					{
						m_bFoundCle = true;
					}
					ByeByeHelico();
					StopSound(16);
					StopSound(18);
					StopSound(29);
					StopSound(31);
					PlaySound(14, m_moveObject[num].posCurrent);
					m_blupiAction = 13;
					m_blupiPhase = 0;
					m_blupiFocus = false;
					m_blupiFront = true;
					m_blupiPos.Y = m_moveObject[num].posCurrent.Y;
				}
				else
				{
					PlaySound(13, m_moveObject[num].posCurrent);
				}
				m_goalPhase = 50;
			}
			else
			{
				m_goalPhase--;
			}
		}
		else
		{
			m_goalPhase = 0;
		}
	}
	else
	{
		m_goalPhase = 0;
	}
	if (m_blupiAction == 14 && m_blupiFocus)
	{
		num = CaisseInFront();
		if (num != -1)
		{
			tinyPoint3 = m_moveObject[num].posCurrent;
			if (m_blupiDir == 1)
			{
				tinyPoint3.X = m_blupiPos.X - 59;
			}
			else
			{
				tinyPoint3.X = m_blupiPos.X + 55;
			}
			if (!TestPushCaisse(num, tinyPoint3, false))
			{
				m_blupiPos.X = blupiPos.X;
			}
		}
		else
		{
			m_blupiAction = 1;
			m_blupiPhase = 0;
		}
	}
	if (m_blupiAction == 29 && m_blupiFocus)
	{
		num = CaisseInFront();
		if (num != -1)
		{
			tinyPoint3 = m_moveObject[num].posCurrent;
			if (m_blupiDir == 1)
			{
				tinyPoint3.X = m_blupiPos.X - 59;
			}
			else
			{
				tinyPoint3.X = m_blupiPos.X + 55;
			}
			if (!TestPushCaisse(num, tinyPoint3, true))
			{
				m_blupiAction = 1;
				m_blupiPhase = 0;
			}
		}
		else
		{
			m_blupiAction = 1;
			m_blupiPhase = 0;
		}
	}
	if (!m_blupiHelico && !m_blupiOver && !m_blupiBalloon && !m_blupiEcrase && !m_blupiJeep && !m_blupiTank && !m_blupiSkate && !m_blupiNage && !m_blupiSurf && m_blupiFocus)
	{
		if (m_blupiActionOuf == 44 && m_blupiAction == 1)
		{
			if (m_blupiTimeOuf > 50)
			{
				m_blupiAction = m_blupiActionOuf;
				m_blupiPhase = 0;
				PlaySound(46, m_blupiPos);
			}
			m_blupiActionOuf = 0;
		}
		if (m_blupiActionOuf == 45 && m_blupiAction == 1)
		{
			if (m_blupiTimeOuf > 50)
			{
				m_blupiAction = m_blupiActionOuf;
				m_blupiPhase = 0;
			}
			m_blupiActionOuf = 0;
		}
		if (m_blupiAction == 45 && m_blupiPhase == 4)
		{
			PlaySound(46, m_blupiPos);
		}
		if (m_blupiActionOuf == 65 && m_blupiAction == 1)
		{
			if (m_blupiTimeOuf > 10 && m_blupiTimeOuf < 50)
			{
				m_blupiAction = m_blupiActionOuf;
				m_blupiPhase = 0;
			}
			m_blupiActionOuf = 0;
		}
		if (m_blupiActionOuf == 47 && m_blupiAction == 1)
		{
			if (m_blupiTimeOuf > 60)
			{
				m_blupiAction = m_blupiActionOuf;
				m_blupiPhase = 0;
				PlaySound(48, m_blupiPos);
			}
			m_blupiActionOuf = 0;
		}
		if (m_blupiActionOuf == 48 && m_blupiAction == 1)
		{
			if (m_blupiTimeOuf < 10)
			{
				m_blupiAction = m_blupiActionOuf;
				m_blupiPhase = 0;
				PlaySound(49, m_blupiPos);
			}
			m_blupiActionOuf = 0;
		}
		if ((m_blupiActionOuf == 63 || m_blupiActionOuf == 64 || m_blupiActionOuf == 83) && m_blupiAction == 1)
		{
			if (m_blupiTimeOuf < 20)
			{
				m_blupiAction = m_blupiActionOuf;
				m_blupiPhase = 0;
			}
			m_blupiActionOuf = 0;
		}
	}
	if (m_blupiAction == 2 && m_blupiActionOuf != 63 && m_blupiActionOuf != 64 && m_blupiActionOuf != 83 && !m_blupiSurf && !m_blupiNage)
	{
		m_blupiActionOuf = 0;
	}
	if (m_blupiActionOuf != 0)
	{
		m_blupiTimeOuf++;
	}
	if (m_blupiTimeMockery > 0)
	{
		m_blupiTimeMockery--;
	}
	if (m_blupiAction == 86 && m_blupiPhase == 18)
	{
		m_blupiAction = 1;
		m_blupiPhase = 0;
		m_blupiFocus = true;
	}
	if (m_blupiAction == 87 && m_blupiPhase == 26)
	{
		m_blupiAction = 1;
		m_blupiPhase = 0;
		m_blupiFocus = true;
	}
	if (m_blupiPos.X - 30 > m_blupiPosHelico.X || m_blupiPos.X + 30 < m_blupiPosHelico.X || m_blupiPos.Y - 30 > m_blupiPosHelico.Y || m_blupiPos.Y + 30 < m_blupiPosHelico.Y)
	{
		m_blupiPosHelico.X = -1;
	}
	if (m_blupiTimeFire > 0)
	{
		m_blupiTimeFire--;
	}
	if (m_blupiAction == 74 && m_blupiPhase == 128)
	{
		TinyPoint blupiPos2 = default(TinyPoint);
		if (SearchTeleporte(m_blupiPos, ref blupiPos2))
		{
			m_blupiPos = blupiPos2;
			ObjectStart(m_blupiPos, 27, 20);
			ObjectStart(m_blupiPos, 27, -20);
		}
		m_blupiFocus = true;
		m_blupiPosHelico = m_blupiPos;
	}
	if (m_blupiAction == 82 && m_blupiPhase == 10)
	{
		m_blupiAction = 1;
		m_blupiPhase = 0;
		m_blupiFocus = true;
	}
	if (ButtonPressed == Def.ButtonGlygh.PlayAction && m_blupiAction == 1)
	{
		m_blupiAction = 84;
		m_blupiPhase = 0;
		PlaySound(27, m_blupiPos);
	}
	if ((m_blupiAction == 11 && m_blupiPhase == 70) || (m_blupiAction == 75 && m_blupiPhase == 100) || (m_blupiAction == 76 && m_blupiPhase == 70) || (m_blupiAction == 77 && m_blupiPhase == 110) || (m_blupiAction == 78 && m_blupiPhase == 90) || (m_blupiAction == 79 && m_blupiPhase == 90) || (m_blupiAction == 80 && m_blupiPhase == 90) || (m_blupiAction == 81 && m_blupiPhase == 90) || (m_blupiAction == 24 && m_blupiPhase == 90) || (m_blupiAction == 54 && m_blupiPhase == 100) || (m_blupiAction == 57 && m_blupiPhase == 90))
	{
		if (m_nbVies > 0)
		{
			m_blupiAction = 35;
			m_blupiIcon = -1;
			m_blupiPhase = 0;
			if (m_blupiRestart)
			{
				m_blupiPos = m_blupiValidPos;
			}
			TinyPoint posDecor = GetPosDecor(m_blupiPos);
			tinyPoint.X = m_blupiPos.X - posDecor.X - 30;
			tinyPoint.Y = m_blupiPos.Y - posDecor.Y;
			VoyageInit(VoyageGetPosVie(m_nbVies), m_pixmap.HotSpotToHud(tinyPoint), 48, 2);
		}
		else
		{
			m_nbVies = -1;
			m_term = -1;
			DoorsLost();
		}
		m_blupiFront = false;
	}
	if (m_dimDecor.Y == 0)
	{
		num3 = 480;
	}
	else
	{
		num3 = 6400;
	}
	if (m_blupiPos.Y >= num3 + 1 && m_blupiPos.Y <= num3 + 40)
	{
		PlaySound(8, m_blupiPos);
	}
	if (m_blupiPos.Y > num3 + 1000)
	{
		m_term = -1;
		DoorsLost();
	}
	if (m_blupiAction == 13 && m_blupiPhase == 40)
	{
		if (m_bPrivate)
		{
			m_term = 1;
		}
		else if (m_mission == 1)
		{
			m_term = 199;
		}
		else if (m_mission == 199)
		{
			m_term = -2;
		}
		else if (m_bFoundCle)
		{
			OpenGoldsWin();
			m_term = 1;
		}
		else
		{
			OpenDoorsWin();
			m_term = m_mission / 10 * 10;
		}
	}
	if (m_blupiAction == 30 && m_blupiPhase == 30)
	{
		num = IsWorld(m_blupiPos);
		if (num != -1)
		{
			if (m_mission == 1)
			{
				m_term = num * 10;
			}
			else if (num == 199)
			{
				m_term = 1;
			}
			else
			{
				m_term = m_mission / 10 * 10 + num;
			}
		}
	}
	if (blupiAction == 63 && m_blupiAction != 63)
	{
		StopSound(65);
	}
	if (blupiAction == 64 && m_blupiAction != 64)
	{
		StopSound(65);
	}
	if (blupiAction == 83 && m_blupiAction != 83)
	{
		StopSound(47);
	}
	if (m_blupiFocus && !m_blupiAir && (!m_blupiHelico || BlupiIsGround()) && (!m_blupiOver || BlupiIsGround()) && !m_blupiBalloon && !m_blupiEcrase && !m_blupiShield && !m_blupiHide && !flag2 && !flag3 && m_blupiTransport == -1 && !IsLave(m_blupiPos) && !IsPiege(m_blupiPos) && !IsGoutte(m_blupiPos, true) && !IsScie(m_blupiPos) && !IsBridge(m_blupiPos, ref tinyPoint) && IsTeleporte(m_blupiPos) == -1 && !IsBlitz(m_blupiPos, true) && !IsTemp(m_blupiPos) && !IsBalleTraj(m_blupiPos) && !IsMoveTraj(m_blupiPos))
	{
		if (m_blupiFifoNb > 0)
		{
			m_blupiValidPos = m_blupiFifoPos[0];
		}
		BlupiAddFifo(m_blupiPos);
	}
	tinyPoint3.X = m_blupiPos.X + 30 + m_scrollAdd.X;
	tinyPoint3.Y = m_blupiPos.Y + 30 + m_scrollAdd.Y;
	int num28 = Math.Abs(m_scrollPoint.X - tinyPoint3.X);
	int num29 = Math.Abs(m_scrollPoint.Y - tinyPoint3.Y);
	num4 = Decor.SCROLL_SPEED;
	if (num28 > Decor.SCROLL_MARGX * 2)
	{
		num4 += (num28 - Decor.SCROLL_MARGX * 2) / 4;
	}
	if (num29 > Decor.SCROLL_MARGY * 2)
	{
		num4 += (num29 - Decor.SCROLL_MARGY * 2) / 4;
	}
	if (m_scrollPoint.X < tinyPoint3.X)
	{
		m_scrollPoint.X = m_scrollPoint.X + num4;
		if (m_scrollPoint.X >= tinyPoint3.X)
		{
			m_scrollPoint.X = tinyPoint3.X;
		}
	}
	if (m_scrollPoint.X > tinyPoint3.X)
	{
		m_scrollPoint.X = m_scrollPoint.X - num4;
		if (m_scrollPoint.X <= tinyPoint3.X)
		{
			m_scrollPoint.X = tinyPoint3.X;
		}
	}
	if (m_scrollPoint.Y < tinyPoint3.Y)
	{
		m_scrollPoint.Y = m_scrollPoint.Y + num4;
		if (m_scrollPoint.Y >= tinyPoint3.Y)
		{
			m_scrollPoint.Y = tinyPoint3.Y;
		}
	}
	if (m_scrollPoint.Y > tinyPoint3.Y)
	{
		m_scrollPoint.Y = m_scrollPoint.Y - num4;
		if (m_scrollPoint.Y <= tinyPoint3.Y)
		{
			m_scrollPoint.Y = tinyPoint3.Y;
		}
	}
	if (m_blupiAction != 75 && m_blupiAction != 76)
	{
		m_posDecor = GetPosDecor(m_scrollPoint);
	}
	if (m_time % 4 == 0)
	{
		PosSound(m_blupiPos);
	}
	VoyageStep();
	m_blupiLastSpeedX = m_blupiSpeedX;
	m_blupiLastSpeedY = m_blupiSpeedY;
	m_lastKeyPress = m_keyPress;
}
*/

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

void CDecor::MoveObjectPlouf(POINT pos)
{
	for (int i = 0; i < MAXMOVEOBJECT; i++)
	{
		if (m_moveObject[i]-> == 14)
		{
			return;
		}
	}
	pos.y -= 45;
	PlaySound(23, pos);
	ObjectStart(pos, 14, 0);
}

void CDecor::MoveObjectTiplouf(POINT pos)
{
	for (int i = 0; i < MAXMOVEOBJECT; i++)
	{
		if (m_moveObject[i]->type == 35)
		{
			return;
		}
	}
	if (m_blupiDir == 2)
	{
		pos.x += 5;
	}
	else
	{
		pos.x -= 5;
	}
	pos.y -= 45;
	PlaySound(64, pos);
	ObjectStart(pos, 35, 0);
}

void CDecor::MoveObjectBlup(POINT pos)
{
	PlaySound(24, pos);
	pos.y -= 20;
	int num = 0;
	POINT tinyPoint = pos;
	while (tinyPoint.y > 0)
	{
		int icon = m_decor[(tinyPoint.x + 16) / 64, tinyPoint.y / 64]->icon;
		if (icon != 91 && icon != 92)
		{
			break;
		}
		num++;
		tinyPoint.y -= 64;
	}
	num--;
	if (num <= 0)
	{
		return;
	}
	int num2 = MoveObjectFree();
	if (num2 == -1)
	{
		return;
	}
	m_moveObject[num2]->type = 15;
	m_moveObject[num2]->phase = 0;
	m_moveObject[num2]->posCurrent.x = pos.x;
	m_moveObject[num2]->posCurrent.y = pos.y;
	m_moveObject[num2]->posStart = m_moveObject[num2]->posCurrent;
	m_moveObject[num2]->posEnd.x = pos.x;
	m_moveObject[num2]->posEnd.y = pos.y - num * 64;
	m_moveObject[num2]->timeStopStart = 0;
	m_moveObject[num2]->stepAdvance = num * 10;
	m_moveObject[num2]->step = 2;
	m_moveObject[num2]->time = 0;
	MoveObjectStepIcon(num2);
}

void CDecor::ActiveSwitch(BOOL bState, POINT cel)
{
	POINT pos;
	pos.x = cel.x * 64;
	pos.y = cel.y * 64;
	ModifDecor(pos, bState ? 384 : 385);
	PlaySound(bState ? 77 : 76, pos);
	cel.x -= 20;
	for (int i = 0; i < 41; i++)
	{
		if (cel.x >= 0 && cel.x < 100 && m_decor[cel.x, cel.y]->icon == (bState ? 379 : 378))
		{
			pos.x = cel.x * 64;
			pos.y = cel.y * 64;
			ModifDecor(pos, bState ? 378 : 379);
		}
		cel.x++;
	}
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

BOOL CDecor::IsLave(POINT pos)
{
	pos.x += 30;
	return pos.x >= 0 && pos.x < 6400 && pos.y >= 0 && pos.y < 6400 && m_decor[pos.x / 64, pos.y / 64]->icon == 68;
}

BOOL CDecor::IsPiege(POINT pos)
{
	pos.x += 30;
	pos.y += 60;
	return pos.x % 64 >= 15 && pos.x % 64 <= 49 && pos.x >= 0 && pos.x < 6400 && pos.y >= 0 && pos.y < 6400 && m_decor[pos.x / 64, pos.y / 64]->icon == 373;
}

BOOL CDecor::IsGoutte(POINT pos, BOOL bAlways)
{
	pos.x += 30;
	if (pos.x % 64 < 15 || pos.x % 64 > 49)
	{
		return FALSE;
	}
	if (pos.x < 0 || pos.x >= 6400 || pos.y < 0 || pos.y >= 6400)
	{
		return FALSE;
	}
	int icon = m_decor[pos.x / 64, pos.y / 64]->icon;
	if (bAlways)
	{
		return icon == 404 || icon == 410;
	}
	return icon == 404;
}

BOOL CDecor::IsScie(POINT pos)
{
	pos.x += 30;
	return pos.x % 64 >= 4 && pos.x % 64 <= 60 && pos.x >= 0 && pos.x < 6400 && pos.y >= 0 && pos.y < 6400 && m_decor[pos.x / 64, pos.y / 64]->icon == 378;
}

BOOL CDecor::IsSwitch(POINT pos, POINT celSwitch)
{
	pos.x += 30;
	if (pos.x % 64 < 4 || pos.x % 64 > 60)
	{
		return FALSE;
	}
	if (pos.x < 0 || pos.x >= 6400 || pos.y < 0 || pos.y >= 6400)
	{
		return FALSE;
	}
	celSwitch.x = pos.x / 64;
	celSwitch.y = pos.y / 64;
	return m_decor[pos.x / 64, pos.y / 64]->icon == 384 || m_decor[pos.x / 64, pos.y / 64]->icon == 385;
}

BOOL CDecor::IsEcraseur(POINT pos)
{
	if (m_time / 3 % 10 > 2)
	{
		return FALSE;
	}
	pos.x += 30;
	return pos.x >= 0 && pos.x < 6400 && pos.y >= 0 && pos.y < 6400 && m_decor[pos.x / 64, pos.y / 64]->icon == 317;
}

BOOL CDecor::IsBlitz(POINT pos, BOOL bAlways)
{
	pos.x += 30;
	if (pos.x < 0 || pos.x >= 6400 || pos.y < 0 || pos.y >= 6400)
	{
		return FALSE;
	}
	POINT tinyPoint;
	tinyPoint.x = pos.x / 64;
	tinyPoint.y = pos.y / 64;
	return m_decor[tinyPoint.x, tinyPoint.y]->icon == 305 && (bAlways || BlitzActif(tinyPoint.x, tinyPoint.y));
}

BOOL CDecor::IsRessort(POINT pos)
{
	pos.x += 30;
	pos.y += 60;
	return pos.x >= 0 && pos.x < 6400 && pos.y >= 0 && pos.y < 6400 && m_decor[pos.x / 64, pos.y / 64]->icon == 211;
}

BOOL CDecor::IsTemp(POINT pos)
{
	pos.x += 30;
	pos.y += 60;
	return pos.x >= 0 && pos.x < 6400 && pos.y >= 0 && pos.y < 6400 && m_decor[pos.x / 64, pos.y / 64]->icon == 324;
}

BOOL CDecor::IsBridge(POINT pos, POINT celBridge)
{
	pos.x += 30;
	pos.y += 60;
	if (pos.x >= 0 && pos.x < 6400 && pos.y >= 0 && pos.y < 6400 && m_decor[pos.x / 64, pos.y / 64]->icon == 364)
	{
		celBridge.x = pos.x / 64;
		celBridge.y = pos.y / 64;
		return TRUE;
	}
	pos.y -= 60;
	if (pos.x >= 0 && pos.x < 6400 && pos.y >= 0 && pos.y < 6400 && m_decor[pos.x / 64, pos.y / 64]->icon == 364)
	{
		celBridge.x = pos.x / 64;
		celBridge.y = pos.y / 64;
		return TRUE;
	}
	return FALSE;

}

int CDecor::IsDoor(POINT pos, POINT celPorte)
{
	int num;
	if (m_blupiDir == 1)
	{
		num = -60;
	}
	else
	{
		num = 60;
	}
	pos.x += 30;
	for (int i = 0; i < 2; i++)
	{
		if (pos.x >= 0 && pos.x < 6400 && pos.y >= 0 && pos.y < 6400 && m_decor[pos.x / 64, pos.y / 64]->icon >= 334 && m_decor[pos.x / 64, pos.y / 64]->icon <= 336)
		{
			celPorte.x = pos.x / 64;
			celPorte.y = pos.y / 64;
			return m_decor[pos.x / 64, pos.y / 64]->icon;
		}
		pos.x += num;
	}
	return -1;
}

int CDecor::IsTeleporte(POINT pos)
{
	if (pos.x % 64 > 6)
	{
		return -1;
	}
	pos.x += 30;
	pos.y -= 60;
	if (pos.x < 0 || pos.x >= 6400 || pos.y < 0 || pos.y >= 6400)
	{
		return -1;
	}
	if (m_decor[pos.x / 64, pos.y / 64]->icon >= 330 && m_decor[pos.x / 64, pos.y / 64]->icon <= 333)
	{
		return m_decor[pos.x / 64, pos.y / 64]->icon;
	}
	return -1;
}

BOOL CDecor::SearchTeleporte(POINT pos, POINT newpos)
{
	int num = IsTeleporte(pos);
	if (num == -1)
	{
		return FALSE;
	}
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (num == m_decor[i, j]->icon)
			{
				newpos.x = i * 64;
				newpos.y = j * 64 + 60;
				if (newpos.x < pos.x - 40 || newpos.x > pos.x + 40 || newpos.y < pos.y - 40 || newpos.y > pos.y + 40)
				{
					return TRUE;
				}
			}
		}
	}
	return FALSE;
}

BOOL CDecor::IsNormalJump(POINT pos)
{
	pos.x += 32;
	pos.y -= 32;
	if (m_blupiDir == 1)
	{
		pos.x -= 15;
	}
	else
	{
		pos.x += 15;
	}
	for (int i = 0; i < 2; i++)
	{
		int num = pos.x / 64;
		int num2 = pos.y / 64;
		if (num2 < 0)
		{
			return FALSE;
		}
		int icon = m_decor[num, num2]->icon;
		if (!IsPassIcon(icon))
		{
			return FALSE;
		}
		pos.y -= 64;
	}
	return TRUE;
}

BOOL CDecor::IsSurfWater(POINT pos)
{
	if (pos.y % 64 < 64 - BLUPISURF)
	{
		return FALSE;
	}
	int icon = m_decor[(pos.x + 30) / 64, pos.y / 64]->icon;
	int icon2 = m_decor[(pos.x + 30) / 64, (pos.y + BLUPISURF) / 64]->icon;
	return icon != 92 && icon2 == 92;
}

BOOL CDecor::IsDeepWater(POINT pos)
{
	int num = (pos.x + 30) / 64;
	int num2 = pos.y / 64;
	if (num < 0 || num >= 100 || num2 < 0 || num2 >= 100)
	{
		return FALSE;
	}
	int icon = m_decor[num, num2]->icon;
	return icon == 91 || icon == 92;
}

BOOL CDecor::IsOutWater(POINT pos)
{
	int icon = m_decor[(pos.x + 30) / 64, (pos.y + 30) / 64]->icon;
	return icon != 91 && icon != 92 && IsPassIcon(icon);
}

BOOL CDecor::IsPassIcon(int icon)
{
	if (icon == 324 && m_time / 4 % 20 >= 18)
	{
		return TRUE;
	}
	if (icon >= 0 && icon < MAXQUART)
	{
		for (int i = 0; i < 16; i++)
		{
			if (table_decor_quart[icon * 16 + i] != 0)
			{
				return FALSE;
			}
		}
	}
	return TRUE;
}

BOOL CDecor::IsBlocIcon(int icon)
{
	if (icon < 0 || icon >= MAXQUART)
	{
		return FALSE;
	}
	if (icon == 324 && m_decor / 4 % 20 < 18)
	{
		return FALSE;
	}
	for (int i = 0; i < 16; i++)
	{
		if (table_decor_quart[icon * 16 + i] == 0)
		{
			return FALSE;
		}
	}
	return FALSE;
}

void CDecor::FlushBalleTraj()
{
	for (int i = 0; i < 1300; i++)
	{
		m_balleTraj[i] = 0;
	}
}

void CDecor::SetBalleTraj(POINT pos)
{
	if (pos.x < 0 || pos.x >= 100 || pos.y < 0 || pos.y >= 100)
	{
		return;
	}
	int num = pos.y * 13;
	num += pos.x / 8;
	int num2 = pos.x & 7;
	m_balleTraj[num] |= 1 << num2;
}

BOOL CDecor::IsBalleTraj(POINT pos)
{
	pos.x = (pos.x + 32) / 64;
	pos.y = (pos.y + 32) / 64;
	if (pos.x < 0 || pos.x >= 100 || pos.y < 0 || pos.y >= 100)
	{
		return FALSE;
	}
	int num = pos.y * 13;
	num += pos.x / 8;
	int num2 = pos.x & 7;
	return (m_balleTraj[num] & 1 << num2) != 0;
}

void CDecor::FlushMoveTraj()
{
	for (int i = 0; i < 1300; i++)
	{
		m_moveTraj[i] = 0;
	}
}

void CDecor::SetMoveTraj(POINT pos)
{

	if (pos.x < 0 || pos.x >= 100 || pos.y < 0 || pos.y >= 100)
	{
		return;
	}
	int num = pos.y * 13;
	num += pos.x / 8;
	int num2 = pos.x & 7;
	m_moveTraj[num] |= 1 << num2;
}

BOOL CDecor::IsMoveTraj(POINT pos)
{
	pos.x = (pos.x + 32) / 64;
	pos.y = (pos.y + 32) / 64;
	if (pos.x < 0 || pos.x >= 100 || pos.y < 0 || pos.y >= 100)
	{
		return FALSE;
	}
	int num = pos.y * 13;
	num += pos.x / 8;
	int num2 = pos.x & 7;
	return (m_moveTraj[num] & 1 << num2) != 0;
}

int CDecor::SearchDistRight(POINT pos, POINT dir, int type)
{
	int num = 0;
	if (type == 36 || type == 39 || type == 41 || type == 42 || type == 93)
	{
		return 500;
	}
	pos.x = (pos.x + 32) / 64;
	pos.y = (pos.y + 32) / 64;
	while (pos.x >= 0 && pos.x < 100 && pos.y >= 0 && pos.y < 100 && !IsBlocIcon(m_decor[pos.x, pos.y]->icon))
	{
		if (type == 23)
		{
			SetBalleTraj(pos);
		}
		num += 64;
		pos.x += dir.x;
		pos.y += dir.y;
	}
	if ((type == 34 || type == 38) && num >= 64)
	{
		num -= 64;
	}
	if (type == 23 && num >= 10)
	{
		num -= 10;
	}
	return num;
}

BOOL CDecor::IsVentillo(POINT pos)
{
	int num = 0;
	BOOL flag = FALSE;
	POINT tinyPoint;
	pos.x += 30;
	pos.y += 30;
	if (pos.x < 0 || pos.x >= 6400 || pos.y < 0 || pos.y >= 6400)
	{
		return FALSE;
	}
	int icon = m_decor[pos.x / 64, pos.y / 64]->icon;
	if (icon < 126 || icon > 137)
	{
		return FALSE;
	}
	if (icon == 126)
	{
		if (pos.x % 64 <= 16)
		{
			flag = TRUE;
		}
		tinyPoint.x = -64;
		tinyPoint.y = 0;
		num = 110;
	}
	if (icon == 129)
	{
		if (pos.x % 64 >= 48)
		{
			flag = TRUE;
		}
		tinyPoint.x = 64;
		tinyPoint.y = 0;
		num = 114;
	}
	if (icon == 132)
	{
		if (pos.y % 64 <= 32)
		{
			flag = TRUE;;
		}
		tinyPoint.x = 0;
		tinyPoint.y = -64;
		num = 118;
	}
	if (icon == 135)
	{
		if (pos.y % 64 >= 48)
		{
			flag = TRUE;
		}
		tinyPoint.x = 0;
		tinyPoint.y = 64;
		num = 122;
	}
	if (!flag)
	{
		return FALSE;
	}
	ModifDecor(pos, -1);
	do
	{
		pos.x += tinyPoint.x;
		pos.y += tinyPoint.y;
		if (num != m_decor[pos.x / 64, pos.y / 64]->icon)
		{
			break;
		}
		ModifDecor(pos, -1);
	} 
	while (pos.x >= 0 && pos.x < 6400 && pos.y >= 0 && pos.y < 6400);
	return TRUE;
}

void CDecor::NetStopCloud(int rank)
{
}

// Birdlime

void CDecor::StartSploutchGlu(POINT pos)
{
	POINT pos2;
	pos2.x = pos.x;
	pos2.y = pos.y;
	ObjectStart(pos2, 98, 0);
	pos2.x = pos.x + 15;
	pos2.y = pos.y + 20;
	ObjectStart(pos2, 99, 0);
	pos2.x = pos.x - 20;
	pos2.y = pos.y + 18;
	ObjectStart(pos2, 99, 0);
	pos2.x = pos.x + 23;
	pos2.y = pos.y - 18;
	ObjectStart(pos2, 99, 0);
	pos2.x = pos.x - 15;
	pos2.y = pos.y - 18;
	ObjectStart(pos2, 99, 0);
	pos2.x = pos.x + 32;
	pos2.y = pos.y + 10;
	ObjectStart(pos2, 100, 0);
	pos2.x = pos.x - 28;
	pos2.y = pos.y + 15;
	ObjectStart(pos2, 100, 0);
	StopSound(16);
	StopSound(18);
	StopSound(29);
	StopSound(31);
	PlaySound(51, pos);
}

int CDecor::ObjectStart(POINT pos, int type, int speed)
{
	int num = MoveObjectFree();
	if (num == -1)
	{
		return -1;
	}
	m_moveObject[num]->type = type;
	m_moveObject[num]->phase = 0;
	m_moveObject[num]->posCurrent = pos;
	m_moveObject[num]->posStart = pos;
	m_moveObject[num]->posEnd = pos;
	MoveObjectStopIcon(num);
	if (speed != 0)
	{
		POINT tinyPoint = pos;
		int num2 = speed;
		int num3 = 0;
		if (num2 > 50)
		{
			num2 -= 50;
			POINT dir;
			dir.x = 0;
			dir.y = 1;
			num3 = SearchDistRight(tinyPoint, dir, type);
			tinyPoint.y += num3;
		}
		else if (num < -50)
		{
			num2 += 50;
			POINT dir;
			dir.x = 0;
			dir.y = -1;
			num3 = SearchDistRight(tinyPoint, dir, type);
			tinyPoint.y -= num3;
		}
		else if (num2 > 0)
		{
			POINT dir;
			dir.x = 1;
			dir.y = 0;
			num3 = SearchDistRight(tinyPoint, dir, type);
			tinyPoint.x += num3;
		}
		else if (num2 < 0)
		{
			POINT dir;
			dir.x = -1;
			dir.y = 0;
			num3 = SearchDistRight(tinyPoint, dir, type);
			tinyPoint.x -= num3;
		}
		if (num3 == 0)
		{
			if (type == 23)
			{
				m_moveObject[num]->type = 0;
				return num;
			}
		}
		else
		{
			m_moveObject[num]->posEnd = tinyPoint;
			m_moveObject[num]->timeStopStart = 0;
			m_moveObject[num]->stepAdvance = abs(num2 * num3 / 64);
			m_moveObject[num]->step = 2;
			m_moveObject[num]->time = 0;
		}
	}
	MoveObjectPriority(num);
	return num;
}

BOOL CDecor::ObjectDelete(POINT pos, int type)
{
	int num = MoveObjectSearch(pos, type);
	if (num == -1)
	{
		return FALSE;
	}
	if (m_moveObject[num]->type == 4 ||
		m_moveObject[num]->type == 12 ||
		m_moveObject[num]->type == 16 ||
		m_moveObject[num]->type == 17 ||
		m_moveObject[num]->type == 20 ||
		m_moveObject[num]->type == 40 ||
		m_moveObject[num]->type == 96 ||
		m_moveObject[num]->type == 97)
	{
		int num2 = 17;
		double animationSpeed = 1.0;
		if (m_moveObject[num]->type == 4)
		{
			num2 = 7;
		}
		if (m_moveObject[num]->type == 17 || m_moveObject[num]->type == 20)
		{
			num2 = 33;
		}
		if (m_moveObject[num]->type == 40)
		{
			animationSpeed = 0.5;
		}
		ByeByeAdd(m_moveObject[num]->channel, m_moveObject[num]->icon, m_moveObject[num]->posCurrent, (double)num2, animationSpeed);
	}
	m_moveObject[num]->type = 0;
	return TRUE;
}

void CDecor::ModifDecor(POINT pos, int icon)
{
	int icon2 = m_decor[pos.x / 64, pos.y / 64]->icon;
	if (icon == -1 && icon >= 126 && icon2 <= 137)
	{
		ByeByeAdd(1, icon2, pos, 17.0, 1.0);
	}
	m_decor[pos.x / 64, pos.y / 64]->icon = icon;
}

void CDecor::MoveObjectStep()
{
	m_blupiVector.x = 0;
	m_blupiVector.y = 0;
	m_blupiTransport = -1;
	for (int i = 0; i < MAXMOVEOBJECT; i++)
	{
		if (m_moveObject[i]->type != 0)
		{
			MoveObjectStepLine(i);
			MoveObjectStepIcon(i);
			if (m_moveObject[i]->type == 4 ||
				m_moveObject[i]->type == 33 ||
				m_moveObject[i]->type == 32)
				int num = MovePersoDetect(m_moveObject[i]->posCurrent);
			if (num != -1)
			{
				POINT posCurrent = m_moveObject[i]->posCurrent;
				posCurrent.x -= 34;
				posCurrent.y -= 34;
				ObjectStart(posCurrent, 8, 0);
				PlaySound(10, m_moveObject[i]->posCurrent);
				m_decorAction = 1;
				m_decorPhase = 0;
				posCurrent = m_moveObject[i]->posCurrent;
				posCurrent.x += 2;
				posCurrent.y += BLUPIOFFY;
				ObjectDelete(m_moveObject[i]->posCurrent, m_moveObject[i]->type);
				ObjectStart(posCurrent, 37, 0);
				ObjectDelete(m_moveObject[num]->posCurrent, m_moveObject[num]->type);
			}
			if (BlupiElectro(m_moveObject[i]->posCurrent))
			{
				POINT posCurrent = m_moveObject[i]->posCurrent;
				posCurrent.x += 2;
				posCurrent.y += BLUPIOFFY;
				ObjectDelete(m_moveObject[i]->posCurrent, m_moveObject[i]->type);
				ObjectStart(posCurrent, 38, 55);
				PlaySound(59, posCurrent);
			}
		}
	}
}

void CDecor::MoveObjectStepLine(int i)
{
	POINT tinyPoint;
	BOOL flag = FALSE;
	RECT tinyRect;
	if (m_moveObject[i]->type == 1 || m_moveObject[i]->type == 47 || m_moveObject[i]->type == 48 && !m_blupiSuspend)
	{
		RECT src;
		src.left = m_blupiPos.x + 20;
		src.right = m_blupiPos.x + 60 - 20;
		src.top = m_blupiPos.y + 60 - 2;
		src.bottom = m_blupiPos.y + 60 - 1;
		tinyRect.left = m_moveObject[i]->posCurrent.x;
		tinyRect.right = m_moveObject[i]->posCurrent.x + 64;
		tinyRect.top = m_moveObject[i]->posCurrent.y;
		tinyRect.bottom = m_moveObject[i]->posCurrent.y + 16;
		RECT tinyRect2;
		flag = IntersectRect(tinyRect2, tinyRect, src);
		tinyPoint = m_moveObject[i]->posCurrent;
	}
	POINT posCurrent;
	if (m_blupiFocus && !m_blupiHide && m_moveObject[i]->type == 97)
	{
		posCurrent = m_moveObject[i]->posCurrent;
		if (posCurrent.x < m_blupiPos.x)
		{
			posCurrent.x++;
		}
		if (posCurrent.x > m_blupiPos.x)
		{
			posCurrent.x--;
		}
		if (posCurrent.y < m_blupiPos.y)
		{
			posCurrent.y++;
		}
		if (posCurrent.y > m_blupiPos.y)
		{
			posCurrent.y--;
		}
		tinyRect.left = posCurrent.x + 10;
		tinyRect.right = posCurrent.x + 60 - 10;
		tinyRect.top = posCurrent.y + 10;
		tinyRect.bottom = posCurrent.y + 60 - 10;
		if (TestPath(tinyRect, m_moveObject[i]->posCurrent, posCurrent))
		{
			m_moveObject[i]->posCurrent = posCurrent;
			m_moveObject[i]->posStart = posCurrent;
			m_moveObject[i]->posEnd = posCurrent;
		}
		else
		{
			ObjectDelete(m_moveObject[i]->posCurrent, m_moveObject[i]->type);
			posCurrent.x -= 34;
			posCurrent.y -= 34;
			ObjectStart(posCurrent, 9, 0);
			PlaySound(10, posCurrent);
			m_decorAction = 1;
			m_decorPhase = 0;
		}
	}
	if (m_moveObject[i]->posStart.x != m_moveObject[i]->posEnd.x || m_moveObject[i]->posStart.y != m_moveObject[i]->posEnd.y)
	{
		if (m_moveObject[i]->step == 1)
		{
			if (m_moveObject[i]->time < m_moveObject[i]->timeStopStart)
			{
				MoveObject[] moveObject = m_moveObject;
				moveObject[i]->time = moveObject[i]->time + 1;
			}
			else
			{
				m_moveObject[i]->step = 2;
				m_moveObject[i]->time = 0;
			}
		}
		else if (m_moveObject[i]->step == 2)
		{
			if (m_moveObject[i]->posCurrent.x != m_moveObject[i]->posEnd.x || m_moveObject[i]->posCurrent.x != m_moveObject[i]->posEnd.y)
			{
				MoveObject[] moveObject2 = m_moveObject;
				moveObject2[i]->time = moveObject2[i]->time + 1;
				if (m_moveObject[i]->stepAdvance != 0)
				{
					m_moveObject[i]->posCurrent.x = (m_moveObject[i]->posEnd.x - m_moveObject[i]->posStart.x) * m_moveObject[i]->time / m_moveObject[i]->stepAdvance + m_moveObject[i]->posStart.x;
					m_moveObject[i]->posCurrent.y = (m_moveObject[i]->posEnd.y - m_moveObject[i]->posStart.y) * m_moveObject[i]->time / m_moveObject[i]->stepAdvance + m_moveObject[i]->posStart.y;
				}

			}
			else if (m_moveObject[i]->type == 15 || m_moveObject[i]->type == 23)
			{
				m_moveObject[i]->type = 0;
			}
			else if (m_moveObject[i]->type == 34)
			{
				m_moveObject[i]->posStart = m_moveObject[i]->posCurrent;
				m_moveObject[i]->posEnd = m_moveObject[i]->posCurrent;
				m_moveObject[i]->step = 3;
				m_moveObject[i]->time = 0;
			}
			else
			{
				m_moveObject[i]->step = 3;
				m_moveObject[i]->time = 0;
			}
		}
		else if (m_moveObject[i]->step == 3)
		{
			if (m_moveObject[i]->time < m_moveObject[i]->timeStopEnd)
			{
				MoveObject[] moveObject3 = m_moveObject;
				moveObject3[i]->time = moveObject3[i]->time + 1;
			}
			else
			{
				m_moveObject[i]->step = 4;
				m_moveObject[i]->time = 0;
			}
		}
		else if (m_moveObject[i]->step == 4)
		{
			if (m_moveObject[i]->posCurrent.x != m_moveObject[i]->posStart.x || m_moveObject[i]->posCurrent.y != m_moveObject[i]->posStart.y)
			{
				MoveObject[] moveObject4 = m_moveObject;
				moveObject4[i]->time = moveObject4[i]->time + 1;
				if (m_moveObject[i]->stepRecede != 0)
				{
					m_moveObject[i]->posCurrent.x = (m_moveObject[i]->posStart.x - m_moveObject[i]->posEnd.x) *
						m_moveObject[i]->time / m_moveObject[i]->stepRecede + m_moveObject[i]->posEnd.x;
					m_moveObject[i]->posCurrent.y = (m_moveObject[i]->posStart.y - m_moveObject[i]->posEnd.y) *
						m_moveObject[i]->time / m_moveObject[i]->stepRecede + m_moveObject[i]->posEnd.y;
				}
			}
			else
			{
				m_moveObject[i]->step = 1;
				m_moveObject[i]->time = 0;
			}
		}
	}
	if (m_moveObject[i]->type == 22 && m_moveObject[i]->step == 3)
	{
		m_moveObject[i]->type = 0;
	}
	posCurrent = m_moveObject[i]->posCurrent;
	if (m_moveObject[i]->type == 1 || m_moveObject[i]->type == 47 || m_moveObject[i]->type == 48)
	{
		posCurrent.y -= 64;
	}
	posCurrent.x = (posCurrent.x + 32) / 64;
	posCurrent.y = (posCurrent.y + 32) / 64;
	SetMoveTraj(posCurrent);
	if (flag)
	{
		m_blupiVector.x = m_moveObject[i]->posCurrent.x - tinyPoint.x;
		m_blupiVector.y = m_moveObject[i]->posCurrent.y - (m_blupiPos.y + 60 - BLUPIFLOOR);
		if (m_moveObject[i]->type == 47)
		{
			m_blupiVector.x = m_blupiVector.x + 2;
		}
		if (m_moveObject[i]->type == 48)
		{
			m_blupiVector.x = m_blupiVector.x - 2;
		}
		if (m_blupiTimeNoAsc == 0)
		{
			m_blupiTransport = i;
		}
	}
}

void CDecor::DynamiteStart(int i, int dx, int dy)
{
	POINT posStart = m_moveObject[i]->posStart;
	posStart.x -= 34;
	posStart.y -= 34;
	posStart.x += dx;
	posStart.y -= dy;
	ObjectStart(posStart, 8, 0);
	if (dx == 0 && dy == 0)
	{
		PlaySound(10, posStart);
		m_decorAction = 1;
		m_decorPhase = 0;
	}
	RECT src;
	src.left = posStart.x;
	src.right = posStart.x + 128;
	src.top = posStart.y;
	src.bottom = posStart.y + 128;
	POINT tinyPoint;
	for (int j = 0; j < 2; j++)
	{
		tinyPoint.x = posStart.x / 64;
		for (int k = 0; k < 2; j++)
		{
			if (tinyPoint.x >= 0 && tinyPoint.x < 100 && tinyPoint)
			{
				int icon = m_decor[tinyPoint.x, tinyPoint.y]->icon;
				if (icon == 378 || icon == 379 || icon == 404 || icon == 410)
				{
					POINT pos;
					pos.x = tinyPoint.x * 64;
					pos.y = tinyPoint.y * 64;
					ModifDecor(pos, -1);
				}
			}
			tinyPoint.x++;
		}
		tinyPoint.y++;
	}
	for (i = 0; i < MAXMOVEOBJECT; i++)
	{
		if (m_moveObject[i]->type == 2 || m_moveObject[i]->type == 3 || m_moveObject[i]->type == 96 || m_moveObject[i]->type == 97 || m_moveObject[i]->type == 4 ||
			m_moveObject[i]->type == 6 || m_moveObject[i]->type == 12 || m_moveObject[i]->type == 13 || m_moveObject[i]->type == 16 || m_moveObject[i]->type == 17 ||
			m_moveObject[i]->type == 19 || m_moveObject[i]->type == 20 || m_moveObject[i]->type == 24 || m_moveObject[i]->type == 25 || m_moveObject[i]->type == 26 || m_moveObject[i]->type == 28 ||
			m_moveObject[i]->type == 30 || m_moveObject[i]->type == 32 || m_moveObject[i]->type == 33 || m_moveObject[i]->type == 34 || m_moveObject[i]->type == 40 || m_moveObject[i]->type == 44 ||
			m_moveObject[i]->type == 46 || m_moveObject[i]->type == 52 || m_moveObject[i]->type == 54 || m_moveObject[i]->type == 200 || m_moveObject[i]->type == 201 || m_moveObject[i]->type == 202 ||
			m_moveObject[i]->type == 203)
		{
			RECT src2;
			src2.left = m_moveObject[i]->posCurrent.x;
			src2.right = m_moveObject[i]->posCurrent.x + 60;
			src2.top = m_moveObject[i]->posCurrent.y;
			src2.bottom = m_moveObject[i]->posCurrent.y + 20;
			RECT tinyRect;
			if (IntersectRect(tinyRect, src2, src))
			{
				if (m_moveObject[i]->type == 12)
				{
					SearchLinkCaisse(i, TRUE);
					for (int l = 0; l < m_nbLinkCaisse; l++)
					{
						int channel = m_moveObject[m_linkCaisse[l]]->channel;
					}
				}
			}
		}
	}
	
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
    CDecor.MoveObject src = (CDecor->MoveObject);
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
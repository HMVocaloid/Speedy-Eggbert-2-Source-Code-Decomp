// Decor.cpp
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
#include "text.h"
#include "misc.h"
#include "event.h"
#include "dectables.h"
#include "jauge.h"
#include "network.h"



///////////////////////////////////////////////////////////////////////////////

// Constructor

CDecor::CDecor()
{
	int i;

	// FUN_2bd90(m_jauges, sizeof(CJauge), 2, CJauge::CJauge);
	m_hWnd = NULL;
	m_pSound = NULL;
	m_pPixmap = NULL;

	memset(m_lastDecorIndexes, 0, sizeof(m_lastDecorIndexes));
	m_lastRegion = -1;
	m_iconLift = 0;
	m_time = 0;
	m_bCheatDoors = FALSE;
	m_bSuperBlupi = FALSE;
	m_bDrawSecret = FALSE;
	m_bBuildOfficialMissions = FALSE;
	m_bNetPacked = FALSE;
	m_bNetMovePredict = TRUE;
	m_bNetDebug = FALSE;
	m_bMulti = FALSE;
	m_mission = NULL;
	m_blupiLevel = NULL;
	m_bPrivate = NULL;
	m_team = 0;
	m_netPacketsSent = 0;
	m_netPacketsSent2 = 0;
	m_netPacketsReceived = 0;
	m_netPacketsReceived2 = 0;
}

CDecor::~CDecor()
{
	// FUN_2be30(m_jauges, sizeof(CJauge), 2, OutputDebug);
}

void CDecor::Create(HWND hWnd, CSound* pSound, CPixmap* pPixmap, CNetwork* pNetwork)
{
	POINT pos;

	m_hWnd = hWnd;
	m_pSound = pSound;
	m_pPixmap = pPixmap;
	m_pNetwork = pNetwork;
	m_keyPress = 0;
	m_lastKeyPress = 0;
	m_bJoystick = FALSE;
	m_bHelicoMarch = FALSE;
	m_bHelicoStop = FALSE;
	m_bJeepMarch = FALSE;
	m_bJeepStop = FALSE;
	InitDecor();

	m_jauges[0].Create(m_hWnd, m_pPixmap, m_pSound, { 169, 450 }, 1, FALSE);
	m_jauges[0].SetHide(TRUE);
	m_jauges[1].Create(m_hWnd, m_pPixmap, m_pSound, { 171, 450 }, 3, FALSE);
	m_jauges[1].SetHide(TRUE);
	NetMessageIndexFlush();
	NotifFlush();
}

BOOL CDecor::LoadImages()
{
	POINT totalDim, iconDim;
	char filename[52];

	if (m_lastRegion == m_region) return TRUE;
	m_lastRegion = m_region;

	totalDim = { LXIMAGE, LYIMAGE };
	iconDim = { 0, 0 };
	sprintf(filename, "decor%.3d.blp", m_region);

	return m_pPixmap->BackgroundCache(CHDECOR, filename, totalDim, iconDim, FALSE);
}

void CDecor::InitGamer()
{
	m_nbVies = 3;
	FillMemory(m_doors, sizeof(m_doors), 1);
}

void CDecor::InitDecor()
{
	m_posDecor = { 0, 0 };
	m_dimDecor = { 100, 100 };
	m_music = 1;
	m_region = 2;
	m_missionTitle[0] = '\0';
	m_decorAction = 0;
	for (int x = 0; x < MAXCELX; x++)
	{
		for (int y = 0; y < MAXCELY; y++)
		{
			m_decor[x][y].icon = -1;
			m_bigDecor[x][y].icon = -1;
		}
	}
	m_decor[3][4].icon = 40;
	m_decor[4][4].icon = 38;
	m_decor[5][4].icon = 39;
	for (int k = MAXMOVEOBJECT; k != 0; k--)
	{
		m_moveObject[k].type = 0;
	}
	FlushBalleTraj();
	FlushMoveTraj();
	m_moveObject[0].type = TYPE_TRESOR;
	m_moveObject[0].stepAdvance = 1;
	m_moveObject[0].stepRecede = 1;
	m_moveObject[0].timeStopStart = 0;
	m_moveObject[0].timeStopEnd = 0;
	m_moveObject[0].posStart = { 258, 196 };
	m_moveObject[0].posEnd = m_moveObject[0].posStart;
	m_moveObject[0].posCurrent = m_moveObject[0].posStart;
	m_moveObject[0].phase = 0;
	m_moveObject[0].step = STEP_STOPSTART;
	m_moveObject[0].time = 0;
	m_moveObject[0].channel = CHELEMENT;
	m_moveObject[0].icon = 0;

	m_moveObject[1].type = TYPE_GOAL;
	m_moveObject[1].stepAdvance = 1;
	m_moveObject[1].timeStopStart = 0;
	m_moveObject[1].timeStopEnd = 0;
	m_moveObject[1].posStart = { 450, 196 };
	m_moveObject[1].posEnd = m_moveObject[1].posStart;
	m_moveObject[1].posCurrent = m_moveObject[1].posStart;
	m_moveObject[1].phase = 0;
	m_moveObject[1].step = STEP_STOPSTART;
	m_moveObject[1].time = 0;
	m_moveObject[1].channel = CHELEMENT;
	m_moveObject[1].icon = 29;
	//TODO: iterate setting blupi fifo positions
	m_blupiStartPos[0] = { 66, 192 + BLUPIOFFY };
	m_blupiStartDir[0] = DIR_RIGHT;
	m_blupiAction = ACTION_STOP;
	m_blupiPhase = 0;
	m_blupiIcon = 0;
	m_blupiChannel = CHBLUPI;
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
	m_blupiPosHelico.x = -1;
	m_blupiActionOuf = 0;
	m_blupiTimeNoAsc = 0;
	m_blupiTimeMockery = 0;
	m_blupiVitesse = { 0, 0 };
	m_blupiValidPos = m_blupiStartPos[0];
	m_blupiEnergyUnused = 100;
	m_blupiFront = FALSE;
	m_blupiBullet = 0;
	m_blupiCle = 0;
	m_blupiPerso = 0;
	m_blupiDynamite = 0;
	m_nbTresor = 0;
	m_totalTresor = 1;
	m_goalPhase = 0;
	m_scrollPoint = m_blupiStartPos[0];
	m_scrollAdd.x = 0;
	m_scrollAdd.y = 0;
	m_term = 0;
	m_2ndPositionCalculationSlot = -1;
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
	if (bTest) m_nbVies = 3;

	if (m_bMulti)
	{
		m_nbVies = 10;
		m_blupiPos = m_blupiStartPos[m_team];
		m_blupiDir = m_blupiStartDir[m_team];
	}
	else
	{
		m_blupiPos = m_blupiStartPos[0];
		m_blupiDir = m_blupiStartDir[0];
	}

	if (m_blupiDir == DIR_LEFT)
	{
		m_blupiIcon = 4;
	}
	else
	{
		m_blupiIcon = 0;
	}

	m_blupiAction = ACTION_STOP;
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
	m_blupiActionOuf = 0;
	m_blupiTimeNoAsc = 0;
	m_blupiTimeMockery = 0;
	m_blupiValidPos = m_blupiPos;
	m_blupiEnergyUnused = 100;
	m_blupiBullet = 0;
	m_blupiCle = 0;
	m_blupiPerso = 0;
	m_blupiDynamite = 0;
	m_nbTresor = 0;
	m_totalTresor = 0;
	for (int i = MAXMOVEOBJECT; i != 0; i--)
	{
		if (m_moveObject[i].type == TYPE_TRESOR)
		{
			m_totalTresor++;
		}
		m_moveObject[i].posCurrent = m_moveObject[i].posStart;
		m_moveObject[i].step = STEP_STOPSTART;
		m_moveObject[i].phase = 0;
		m_moveObject[i].time = 0;

		if (m_moveObject[i].type == TYPE_TRESOR ||
			m_moveObject[i].type == TYPE_EGG ||
			m_moveObject[i].type == TYPE_SHIELD ||
			m_moveObject[i].type == TYPE_POWER ||
			m_moveObject[i].type == TYPE_INVERT ||
			m_moveObject[i].type == TYPE_BOMBEDOWN ||
			m_moveObject[i].type == TYPE_BOMBEUP ||
			m_moveObject[i].type == TYPE_BOMBEFOLLOW1 ||
			m_moveObject[i].type == TYPE_BOMBEFOLLOW2)
		{
			m_moveObject[i].phase = rand() % 23;
		}

		if (m_moveObject[i].type == TYPE_BALLE)
		{
			m_moveObject[i].type = 0;
		}

		if ((m_bMulti) &&
			(m_moveObject[i].type == TYPE_CAISSE) ||
			(m_moveObject[i].type == TYPE_GOAL) ||
			(m_moveObject[i].type == TYPE_CLE) ||
			(m_moveObject[i].type == TYPE_BLUPIHELICO) ||
			(m_moveObject[i].type == TYPE_BLUPITANK))
		{
			m_moveObject[i].type = 0;
		}
	}
	m_goalPhase = 0;
	MoveObjectSort();
	UpdateCaisse();
	m_scrollPoint = m_blupiPos;
	m_scrollAdd = { 0, 0 };
	m_blupiPosHelico.x = -1;
	m_nbLinkCaisse = 0;
	m_bHelicoMarch = FALSE;
	m_bHelicoStop = FALSE;
	m_bJeepMarch = FALSE;
	m_bJeepStop = FALSE;
	m_blupiFront = FALSE;
	m_blupiNoBarre = 0;
	m_blupiValidPos = m_blupiPos;
	m_blupiFifoNb = 0;
	m_blupiTimeFire = 0;
	NetDataFlush();
	NotifFlush();
	m_voyageIcon = -1;
	m_jauges[0].SetHide(TRUE);
	m_jauges[1].SetHide(TRUE);
	m_bFoundCle = FALSE;
	m_term = 0;
	m_time = 0;
	m_bPause = FALSE;
}

void CDecor::BuildPrepare()
{
	for (int i = 0; i < MAXMOVEOBJECT; i++)
	{
		m_moveObject[i].posCurrent = m_moveObject[i].posStart;
		m_moveObject[i].step = STEP_STOPSTART;
		m_moveObject[i].time = 0;
		m_moveObject[i].phase = 0;
		if (m_moveObject[i].type == TYPE_BALLE)
		{
			m_moveObject[i].type = 0;
		}
	}
	m_voyageIcon = -1;
	m_posCelHili.x = -1;
	m_2ndPositionCalculationSlot = -1;
	m_time = 0;
	m_bPause = FALSE;
	NetDataFlush();
}

int CDecor::IsTerminated()
{
	return m_term;
}

void CDecor::MoveStep()
{
	MoveObjectStep();

	if (m_phase == WM_PHASE_PLAY || m_phase == WM_PHASE_PLAYTEST) {
		BlupiStep();
		NetAdjustToLift();
		NotifStep();
	}

	if (m_phase == WM_PHASE_BUILD) {
		if ((m_keyPress & KEY_RIGHT) != 0) {
			m_posDecor.x += 50;
			int max = (m_dimDecor.x != 0) ? (MAXCELX * DIMOBJX - LXIMAGE) : 0;
			if (m_posDecor.x > max) {
				m_posDecor.x = max;
			}
			m_posCelHili.x = -1;
		}
		if (m_keyPress & KEY_LEFT) {
			m_posDecor.x -= 50;
			if (m_posDecor.x < 0) {
				m_posDecor.x = 0;
			}
			m_posCelHili.x = -1;
		}
		if (m_keyPress & KEY_DOWN) {
			m_posDecor.y += 50;
			int max = (m_dimDecor.y > 0) ? (m_dimDecor.y - LYIMAGE) : 0;
			if (m_posDecor.y > max) {
				m_posDecor.y = max;
			}
			m_posCelHili.x = -1;
		}
		if (m_keyPress & KEY_UP) {
			m_posDecor.x -= 50;
			if (m_posDecor.x < 0) {
				m_posDecor.x = 0;
			}
			m_posCelHili.x = -1;
		}
	}
}

int CDecor::GetIconPerso()
{
	if (m_bMulti) {
		return m_team + 108;
	}
	else {
		return 108;
	}
}

void CDecor::Build(RECT rect)
{
	int num = 1;
	POINT tinyPoint;
	tinyPoint.x = 0;
	RECT lastClip;

	lastClip = m_pPixmap->GetClipping();
	m_pPixmap->SetClipping(rect);

	POINT posDecor = DecorNextAction();
	POINT pos = { posDecor.x * 2 / 3 % LXIMAGE, posDecor.y * 2 };
	//TODO: more^

	for (int i = 0; i < 3; i++)
	{
		tinyPoint.y = 0;
		for (int j = 0; j < 2; j++)
		{
			rect.top = pos.y / 3 % LYIMAGE;
			rect.left = pos.x;
			rect.right = LXIMAGE;
			rect.bottom = LYIMAGE;
			m_pPixmap->DrawPart(-1, 3, tinyPoint, rect, 1, 0);
			tinyPoint.y += LYIMAGE - rect.top;
		}
		tinyPoint.x += LXIMAGE - pos.x;
		pos.x = 0;
	}

	tinyPoint.x = -posDecor.x % 64 - 64;
	for (int i = posDecor.x / 64 - 1; i < posDecor.x / 64 + LXIMAGE / 64 + 3; i++) {
		tinyPoint.y = -posDecor.y % 64 + 2 - 64;
		for (int j = posDecor.y / 64 - 1; j < posDecor.y / 64 + LYIMAGE / 64 + 2; j++)
		{
			if (i >= 0 && i < MAXCELX && j >= 0 && j < MAXCELY)
			{
				int num2 = m_bigDecor[i][j].icon;
				int channel = 9;
				if (num2 != -1)
				{
					pos = tinyPoint;
					if (num2 == 203)
					{
						num2 = table_marine[m_time / 3 % 11];
						channel = 1;
					}
					if (num2 >= 66 && num2 <= 68)
					{
						pos.y -= 13;
					}
					if (num2 >= 87 && num2 <= 89)
					{
						pos.y -= 2;
					}
					m_pPixmap->QuickIcon(channel, num2, pos);
				}
			}
			tinyPoint.y += 64;
		}
		tinyPoint.x += 64;
	}

	tinyPoint.x = -posDecor.x % 64;
	for (int i = posDecor.x / 64; i < posDecor.x / 64 + LXIMAGE / 64 + 2; i++)
	{
		tinyPoint.y = -posDecor.y % 64;
		for (int j = posDecor.y / 64; j < posDecor.y / 64 + LYIMAGE / 64 + 2; j++)
		{
			if (i >= 0 && i < MAXCELX && j >= 0 && j < MAXCELY && m_decor[i][j].icon != -1)
			{
				int num2 = m_decor[i][j].icon;
				if (num2 == 384 || num2 == 385)
				{
					m_pPixmap->QuickIcon(CHOBJECT, num2, tinyPoint);
				}
			}
			tinyPoint.y += 64;
		}
		tinyPoint.x += 64;
	}

	if (m_phase == WM_PHASE_BUILD)
	{
		int* startDir;
		int i, j, h, n;
		LONG* startPos;
		startDir = m_blupiStartDir + 3;
		rect.left = 3;
		startPos = &m_blupiStartPos[3].y;
		do
		{
			i = 2;
			if (0 < rect.left)
			{
				i = rect.left + 10;
			}
			j = 4;
			if (*startDir == 2)
			{
				j = 0;
			}
			h = ((POINT*)(startPos - 1))->x - posDecor.x;
			n = *startPos - posDecor.y;
			pos.x = n;
			pos.y = h;
			m_pPixmap->QuickIcon(i, j, pos);
			if (m_bBuildOfficialMissions != FALSE)
			{
				pos.x = (int)startPos + h - 54294;
				pos.y = n - 20;
				m_pPixmap->QuickIcon(4, rect.left + 120, pos);
			}
			rect.left = rect.left - 1;
			startDir--;
			startPos -= 2;
		} while (-1 < rect.left);
	}

	if (m_bMulti && m_phase != WM_PHASE_BUILD)
	{
		// ...
	}

	m_blupiSec = 0;
	if (!m_blupiFront && m_phase != WM_PHASE_BUILD)
	{
		tinyPoint.x = m_blupiPos.x - posDecor.x;
		tinyPoint.y = m_blupiPos.y - posDecor.y;
		if (m_blupiJeep)
		{
			tinyPoint.y += BLUPIOFFY;
		}
		if (m_blupiShield)
		{
			m_blupiSec = SEC_SHIELD;
			if (m_blupiTimeShield > 25 || m_time % 4 < 2)
			{
				int num2 = table_shield_blupi[m_time / 2 % 16];
				tinyPoint.y -= 2;
				m_pPixmap->QuickIcon(CHELEMENT, num2, tinyPoint);
				tinyPoint.y += 2;
				num2 = table_shieldloop[m_time / 2 % 5];
				m_pPixmap->QuickIcon(CHELEMENT, num2, tinyPoint);
			}
		}
		else if (m_blupiPower)
		{
			m_blupiSec = SEC_POWER;
			if (m_blupiTimeShield > 25 || m_time % 4 < 2)
			{
				int num2 = table_magicloop[m_time / 2 % 5];
				m_pPixmap->QuickIcon(CHELEMENT, num2, tinyPoint);
			}
		}
		else if (m_blupiCloud)
		{
			m_blupiSec = SEC_CLOUD;
			if (m_blupiTimeShield > 25 || m_time % 4 < 2)
			{
				for (int k = 0; k < 3; k++)
				{
					int num2 = 48 + (m_time + k) % 6;
					pos.x = tinyPoint.x - 34;
					pos.y = tinyPoint.y - 34;
					m_pPixmap->QuickIcon(CHEXPLO, num2, pos);
				}
			}
		}
		else if (m_blupiHide)
		{
			m_blupiSec = SEC_HIDE;
			if (m_blupiTimeShield > 25 || m_time % 4 < 2)
			{
				m_pPixmap->DrawIcon(CHTEMP, CHOBJECT, 0xF5, { 0, 0 }, 0, TRUE);
			}
			else
			{
				m_pPixmap->DrawIcon(CHTEMP, GetBlupiChannelStandard(), m_blupiIcon, pos, 1, FALSE);
				m_pPixmap->DrawIcon(CHTEMP, CHOBJECT, 0xED, { 0, 0 }, 0, TRUE);
			}
		}
		m_pPixmap->QuickIcon(GetBlupiChannelStandard(), m_blupiIcon, tinyPoint);
	}

	for (int num3 = MAXMOVEOBJECT - 1; num3 >= 0; num3--)
	{
		if (m_moveObject[num3].type != 0 && m_moveObject[num3].posCurrent.x >= posDecor.x - 64 && m_moveObject[num3].posCurrent.y >= posDecor.y - 64 && m_moveObject[num3].posCurrent.x <= posDecor.x + LXIMAGE && m_moveObject[num3].posCurrent.y <= posDecor.y + LYIMAGE && (m_moveObject[num3].type < 8 || m_moveObject[num3].type > 11) && (m_moveObject[num3].type < 90 || m_moveObject[num3].type > 95) && (m_moveObject[num3].type < 98 || m_moveObject[num3].type > 100) && m_moveObject[num3].type != 53 && m_moveObject[num3].type != 1 && m_moveObject[num3].type != 47 && m_moveObject[num3].type != 48)
		{
			tinyPoint.x = m_moveObject[num3].posCurrent.x - posDecor.x;
			tinyPoint.y = m_moveObject[num3].posCurrent.y - posDecor.y;
			if (m_moveObject[num3].type == TYPE_BULLDOZER || m_moveObject[num3].type == TYPE_BLUPIHELICO || m_moveObject[num3].type == TYPE_BLUPITANK)
			{
				tinyPoint.x += 2;
				tinyPoint.y += BLUPIOFFY;
			}
			if (m_moveObject[num3].type == 54)
			{
				tinyPoint.y += BLUPIOFFY;
			}
			// get the winphone opacity stuff out of here
			m_pPixmap->QuickIcon(m_moveObject[num3].channel, m_moveObject[num3].icon, tinyPoint);
			if (m_moveObject[num3].type == 30)
			{
				for (int l = 0; l < sizeof(table_drinkoffset) / sizeof(int); l++)
				{
					int num4 = (m_time + table_drinkoffset[l]) % 50;
					int rank = table_drinkeffect[num4 % 5];
					POINT tinyPoint2 = { tinyPoint.x + 2, tinyPoint.y - num4 * 3 };
					POINT pos2 = tinyPoint2;
					m_pPixmap->QuickIcon(10, rank, pos2);
				}
			}
			if (m_bDrawSecret && m_moveObject[num3].type == 12 && m_moveObject[num3].icon != 32 && m_moveObject[num3].icon != 33 && m_moveObject[num3].icon != 34)
			{
				m_pPixmap->QuickIcon(1, 214, tinyPoint);
			}
		}
	}
	tinyPoint.x = -posDecor.x % 64;
	for (int i = posDecor.x / 64; i < posDecor.x / 64 + LXIMAGE / 64 + 2; i++)
	{
		tinyPoint.y = 0 - posDecor.y % 64;
		for (int j = posDecor.y / 64; j < posDecor.y / 64 + LYIMAGE / 64 + 2; j++)
		{
			if (i >= 0 && i < 100 && j >= 0 && j < 100 && m_decor[i][j].icon != -1)
			{
				int num2 = m_decor[i][j].icon;
				pos.x = tinyPoint.x;
				pos.y = tinyPoint.y;
				if ((num2 >= 107 && num2 <= 109) || num2 == 157)
				{
					pos.y -= 7;
				}
				if (num2 == 211)
				{
					num2 = table_ressort[(m_time / 2 + i * 7) % 8];
				}
				if (num2 == 214 && !m_bDrawSecret)
				{
					num2 = -1;
				}
				if (num2 == 364)
				{
					pos.y -= 2;
				}
				switch (num2)
				{
				default:
					m_pPixmap->QuickIcon(1, num2, pos);
					break;
				case 68:
				case 91:
				case 92:
				case 110:
				case 111:
				case 112:
				case 113:
				case 114:
				case 115:
				case 116:
				case 117:
				case 118:
				case 119:
				case 120:
				case 121:
				case 122:
				case 123:
				case 124:
				case 125:
				case 126:
				case 127:
				case 128:
				case 129:
				case 130:
				case 131:
				case 132:
				case 133:
				case 134:
				case 135:
				case 136:
				case 137:
				case 305:
				case 317:
				case 324:
				case 373:
				case 378:
				case 384:
				case 385:
				case 404:
				case 410:
					break;
				}
			}
			tinyPoint.y += DIMOBJY;
		}
		tinyPoint.x += DIMOBJX;
	}
	for (int num3 = 0; num3 < MAXMOVEOBJECT; num3++)
	{
		if ((m_moveObject[num3].type == 1 || m_moveObject[num3].type == 47 || m_moveObject[num3].type == 48) && m_moveObject[num3].posCurrent.x >= posDecor.x - 64 && m_moveObject[num3].posCurrent.y >= posDecor.y - 64 && m_moveObject[num3].posCurrent.x <= posDecor.x + LXIMAGE && m_moveObject[num3].posCurrent.y <= posDecor.y + LYIMAGE)
		{
			tinyPoint.x = 0 + m_moveObject[num3].posCurrent.x - posDecor.x;
			tinyPoint.y = 0 + m_moveObject[num3].posCurrent.y - posDecor.y;
			m_pPixmap->QuickIcon(m_moveObject[num3].channel, m_moveObject[num3].icon, tinyPoint);
		}
	}
	tinyPoint.x = 0 - posDecor.x % 64;
	for (int i = posDecor.x / 64; i < posDecor.x / 64 + LXIMAGE / 64 + 2; i++)
	{
		tinyPoint.y = 0 - posDecor.y % 64;
		for (int j = posDecor.y / 64; j < posDecor.y / 64 + LYIMAGE / 64 + 2; j++)
		{
			if (i >= 0 && i < 100 && j >= 0 && j < 100 && m_decor[i][j].icon != -1)
			{
				int num2 = m_decor[i][j].icon;
				pos = tinyPoint;
				if (num2 == 68)
				{
					num2 = table_decor_lave[(i * 13 + j * 7 + m_time / 2) % 8];
					m_pPixmap->QuickIcon(1, num2, pos);
				}
				if (num2 == 373)
				{
					num2 = ((!m_blupiFocus) ? table_decor_piege2[(i * 13 + j * 7 + m_time / 2) % 4] : table_decor_piege1[(i * 13 + j * 7 + m_time / 4) % 16]);
					m_pPixmap->QuickIcon(1, num2, pos);
				}
				if (num2 == 404 || num2 == 410)
				{
					num2 = table_decor_goutte[(i * 13 + j * 7 + m_time / 2) % 48];
					pos.y -= 9;
					m_pPixmap->QuickIcon(1, num2, pos);
					if (num2 >= 404 && num2 <= 407)
					{
						m_decor[i][j].icon = 404;
					}
					else
					{
						m_decor[i][j].icon = 410;
					}
				}
				if (num2 == 317)
				{
					num2 = table_decor_ecraseur[m_time / 3 % 10];
					m_pPixmap->QuickIcon(1, num2, pos);
				}
				if (num2 == 378)
				{
					num2 = table_decor_scie[(i * 13 + j * 7 + m_time / 1) % 6];
					m_pPixmap->QuickIcon(1, num2, pos);
				}
				if (num2 == 324)
				{
					num2 = table_decor_temp[m_time / 4 % 20];
					m_pPixmap->QuickIcon(1, num2, pos);
				}
				if (num2 == 92)
				{
					num2 = table_decor_eau1[(i * 13 + j * 7 + m_time / 3) % 6];
					m_pPixmap->QuickIcon(1, num2, pos);
				}
				if (num2 == 91)
				{
					int num5 = 3 + (i * 17 + j * 13) % 3;
					num2 = table_decor_eau2[(i * 11 + j * 7 + m_time / num5) % 6];
					m_pPixmap->QuickIcon(1, num2, pos);
				}
				if (num2 == 305 && BlitzActif({ i, j }))
				{
					num2 = rand() % 4 + 305;
					m_pPixmap->QuickIcon(1, num2, pos);
				}
				if (num2 == 110)
				{
					num2 = table_decor_ventg[m_time / 1 % 4];
					m_pPixmap->QuickIcon(1, num2, pos);
				}
				if (num2 == 114)
				{
					num2 = table_decor_ventd[m_time / 1 % 4];
					m_pPixmap->QuickIcon(1, num2, pos);
				}
				if (num2 == 118)
				{
					num2 = table_decor_venth[m_time / 1 % 4];
					m_pPixmap->QuickIcon(1, num2, pos);
				}
				if (num2 == 122)
				{
					num2 = table_decor_ventb[m_time / 1 % 4];
					m_pPixmap->QuickIcon(1, num2, pos);
				}
				if (num2 == 126)
				{
					num2 = table_decor_ventillog[m_time / 2 % 3];
					m_pPixmap->QuickIcon(1, num2, pos);
				}
				if (num2 == 129)
				{
					num2 = table_decor_ventillod[m_time / 2 % 3];
					m_pPixmap->QuickIcon(1, num2, pos);
				}
				if (num2 == 132)
				{
					num2 = table_decor_ventilloh[m_time / 2 % 3];
					m_pPixmap->QuickIcon(1, num2, pos);
				}
				if (num2 == 135)
				{
					num2 = table_decor_ventillob[m_time / 2 % 3];
					m_pPixmap->QuickIcon(1, num2, pos);
				}
			}
			tinyPoint.y += 64;
		}
		tinyPoint.x += 64;
	}
	for (int num3 = 0; num3 < MAXMOVEOBJECT; num3++)
	{
		if (m_moveObject[num3].type != 0 && m_moveObject[num3].posCurrent.x >= posDecor.x - 64 && m_moveObject[num3].posCurrent.y >= posDecor.y - 64 && m_moveObject[num3].posCurrent.x <= posDecor.x + LXIMAGE && m_moveObject[num3].posCurrent.y <= posDecor.y + LYIMAGE && ((m_moveObject[num3].type >= 8 && m_moveObject[num3].type <= 11) || (m_moveObject[num3].type >= 90 && m_moveObject[num3].type <= 95) || (m_moveObject[num3].type >= 98 && m_moveObject[num3].type <= 100) || m_moveObject[num3].type == 53))
		{
			tinyPoint.x = 0 + m_moveObject[num3].posCurrent.x - posDecor.x;
			tinyPoint.y = 0 + m_moveObject[num3].posCurrent.y - posDecor.y;
			m_pPixmap->QuickIcon(m_moveObject[num3].channel, m_moveObject[num3].icon, tinyPoint);
		}
	}
	if (m_blupiFront)
	{
		tinyPoint.x = 0 + m_blupiPos.x - posDecor.x;
		tinyPoint.y = 0 + m_blupiPos.y - posDecor.y;
		m_pPixmap->QuickIcon(m_blupiChannel, m_blupiIcon, tinyPoint);
	}
	DrawInfo();
	VoyageDraw();
	m_pPixmap->SetClipping(rect);
	m_time++;
}

void CDecor::DrawInfo()
{
	POINT pos;
	char text[100];

	if (m_phase == WM_PHASE_PLAY || m_phase == WM_PHASE_PLAYTEST)
	{
		for (int i = 4; i != 0; i--) {
			
		}

		if (m_nbVies > 0) {
			pos = { -15, 417 };
			for (int i = 0; i < m_nbVies; i++) {
				m_pPixmap->QuickIcon(GetBlupiChannelActual(), 48, pos);
				pos.x += 16;
			}
		}

		if (m_blupiBullet > 0) {
			pos = { 398, 442 };
			for (int i = 0; i < m_blupiBullet; i++) {
				m_pPixmap->QuickIcon(CHELEMENT, 176, pos);
				pos.x += 4;
			}
		}

		if (m_blupiPerso > 0) {
			m_pPixmap->QuickIcon(CHBUTTON, GetIconPerso(), { 465, 438 });
			sprintf(text, "=_%d", m_blupiPerso);
			DrawText(m_pPixmap, { 497, 452 }, text, FONTWHITE);
		}

		if (m_blupiDynamite > 0) {
			m_pPixmap->QuickIcon(CHELEMENT, 252, { 505, 414 });
		}

		if ((m_blupiCle | CLE_RED) != 0) {
			m_pPixmap->QuickIcon(CHELEMENT, 215, { 520, 418 });
		}

		if ((m_blupiCle | CLE_GREEN) != 0) {
			m_pPixmap->QuickIcon(CHELEMENT, 222, { 530, 418 });
		}

		if ((m_blupiCle | CLE_BLUE) != 0) {
			m_pPixmap->QuickIcon(CHELEMENT, 229, { 540, 418 });
		}

		if ((m_mission != 1 && m_mission % 10 != 0) || m_bPrivate)
		{
			sprintf(text, "%d/%d", m_nbTresor, m_totalTresor);
			DrawText(m_pPixmap, { 590, 452 }, text, FONTWHITE);
		}

		for (int i = 0; i < 2; i++)
		{
			if (!(m_jauges[i].GetHide())) m_jauges[i].Draw();
		}

		if (m_mission == 10 && m_phase == WM_PHASE_PLAY && !m_bPrivate)
		{
			switch (m_nbTresor)
			{
			case 0:
				if (m_blupiPos.x > 212) m_blupiPos.x = 212;
				break;
			case 1:
				if (m_blupiPos.x > 788) m_blupiPos.x = 788;
				break;
			}
			// more...
		}
	}
}

POINT CDecor::DecorNextAction()
{
	int num = 0;
	if (m_decorAction == 0 || m_bPause)
	{
		return m_posDecor;
	}
	POINT posDecor = m_posDecor;
	while (table_decor_action[num] != 0)
	{
		if (m_decorAction == table_decor_action[num])
		{
			if (m_decorPhase < table_decor_action[num + 1])
			{
				posDecor.x += 3 * table_decor_action[num + 2 + m_decorPhase * 2];
				posDecor.y += 3 * table_decor_action[num + 2 + m_decorPhase * 2 + 1];
				int num2;
				if (m_dimDecor.x == 0)
				{
					num2 = 0;
				}
				else
				{
					num2 = DIMOBJX * MAXCELX - LXIMAGE;
				}
				if (posDecor.x < 0)
				{
					posDecor.x = 0;
				}
				if (posDecor.x > num2)
				{
					posDecor.x = num2;
				}
				if (m_dimDecor.y == 0)
				{
					num2 = 0;
				}
				else
				{
					num2 = DIMOBJY * MAXCELY - LYIMAGE;
				}
				if (posDecor.y < 0)
				{
					posDecor.y = 0;
				}
				if (posDecor.y > num2)
				{
					posDecor.y = num2;
				}
				m_decorPhase++;
				break;
			}
			m_decorAction = 0;
			break;
		}
		else
		{
			num += 2 + table_decor_action[num + 1] * 2;
		}
	}
	return posDecor;
}

void CDecor::SetInput(int keys)
{
	m_keyPress = keys;
	if (m_blupiInvert)
	{
		if (keys & KEY_LEFT)
		{
			m_keyPress = keys & ~KEY_LEFT | KEY_RIGHT;
		}
		if (keys & KEY_RIGHT)
		{
			m_keyPress = m_keyPress & ~KEY_RIGHT | KEY_LEFT;
		}
	}
}

void CDecor::SetJoystickEnable(BOOL bJoystick)
{
	m_bJoystick = bJoystick;
}

void CDecor::SetDemoPlay(BOOL param)
{
	m_bD814 = param;
}

void CDecor::InitalizeDoors(BYTE* doors)
{
	int i;

	for (i = 0; i < 200; i++)
	{
		*(BYTE*)(i + doors) = m_doors[i];
	}
	return;
}

void CDecor::PlaySound(int sound, POINT pos, BOOL bLocal)
{
	if (!bLocal) NetPlaySound(sound, pos);

	m_pSound->PlayImage(sound, pos - m_posDecor, -1);

	switch (sound) {
	case SOUND_HELICOHIGH:
		m_bHelicoMarch = TRUE;
		break;
	case SOUND_HELICOLOW:
		m_bHelicoStop = TRUE;
		break;
	case SOUND_JEEPHIGH:
		m_bJeepMarch = TRUE;
		break;
	case SOUND_JEEPLOW:
		m_bJeepStop = TRUE;
		break;
	}
}

void CDecor::PlaySound(int sound, POINT pos)
{
	PlaySound(sound, pos, FALSE);
}

void CDecor::StopSound(int sound)
{
	m_pSound->StopSound(sound);

	switch (sound) {
	case SOUND_HELICOHIGH:
		m_bHelicoMarch = FALSE;
		break;
	case SOUND_HELICOLOW:
		m_bHelicoStop = FALSE;
		break;
	case SOUND_JEEPHIGH:
		m_bJeepMarch = FALSE;
		break;
	case SOUND_JEEPLOW:
		m_bJeepStop = FALSE;
		break;
	}
}

void CDecor::AdaptMotorVehicleSound(POINT pos)
{
	POINT blupiPos = pos - m_posDecor;

	if (m_bHelicoMarch) m_pSound->PlayImage(SOUND_HELICOHIGH, blupiPos);
	if (m_bHelicoStop) m_pSound->PlayImage(SOUND_HELICOLOW, blupiPos);
	if (m_bJeepMarch)  m_pSound->PlayImage(SOUND_JEEPHIGH, blupiPos);
	if (m_bJeepStop) m_pSound->PlayImage(SOUND_JEEPLOW, blupiPos);
}

void CDecor::VehicleSoundsPhase(int phase)
{
	m_phase = phase;

	if (phase == WM_PHASE_PLAY || phase == WM_PHASE_PLAYTEST) {
		int channel = -1;
		if (m_bHelicoMarch) channel = SOUND_HELICOHIGH;
		if (m_bHelicoStop) channel = SOUND_HELICOLOW;
		if (m_bJeepMarch) channel = SOUND_JEEPHIGH;
		if (m_bJeepStop) channel = SOUND_JEEPLOW;
		if (channel != -1) m_pSound->PlayImage(channel, { LXIMAGE / 2, LYIMAGE / 2 }, -1);
	}
	else {
		if (m_bHelicoMarch) m_pSound->StopSound(SOUND_HELICOHIGH);
		if (m_bHelicoStop) m_pSound->StopSound(SOUND_HELICOLOW);
		if (m_bJeepMarch) m_pSound->StopSound(SOUND_JEEPHIGH);
		if (m_bJeepStop) m_pSound->StopSound(SOUND_JEEPLOW);
	}
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

POINT CDecor::GetDim()
{
	return m_dimDecor;
}

void CDecor::SetDim(POINT dim)
{
	m_dimDecor = dim;
}

int CDecor::GetNbVies()
{
	return m_nbVies;
}

void CDecor::SetNbVies(int nbVies)
{
	m_nbVies = nbVies;
}

BOOL CDecor::GetPause()
{
	return m_bPause;
}

void CDecor::SetPause(BOOL bPause)
{
	m_bPause = bPause;
}

void CDecor::InitializeDoors(BYTE* doors)
{
	for (int i = 0; i < 200; i++)
	{
		doors[i] = m_doors[i];
	}
}

void CDecor::MemorizeDoors(BYTE* doors)
{
	for (int i = 0; i < 200; i++)
	{
		m_doors[i] = doors[i];
	}
}

void CDecor::SetAllMissions(BOOL bAllMissions)
{
	m_bCheatDoors = bAllMissions;
	AdaptDoors(m_bPrivate, m_mission);
	return;
}

void CDecor::CheatAction(int cheat)
{
	MoveObject* mob;

	switch (cheat)
	{
	case 2: // cleanall
		for (int i = 0; i < MAXMOVEOBJECT; i++)
		{
			mob = &m_moveObject[i];
			switch (mob->type)
			{
			case TYPE_BOMBEDOWN:
			case TYPE_BOMBEUP:
			case TYPE_BOMBEFOLLOW1:
			case TYPE_BOMBEFOLLOW2:
			case TYPE_BULLDOZER:
			case TYPE_BOMBEMOVE:
			case TYPE_POISSON:
			case TYPE_OISEAU:
			case TYPE_GUEPE:
			case TYPE_CREATURE:
			case TYPE_BLUPIHELICO:
			case TYPE_BLUPITANK:
				m_decorAction = 1;
				m_decorPhase = 0;
				mob->type = TYPE_EXPLO1;
				mob->phase = 0;
				mob->posCurrent -= { 34, 34 };
				mob->posStart = mob->posCurrent;
				mob->posEnd = mob->posCurrent;
				MoveObjectStepIcon(i);
				PlaySound(SOUND_BOUM, mob->posCurrent, FALSE);
			}
		}
		break;
	case 6: // funskate
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
		StopVehicleSound();
		break;
	case 7: // givecopter
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
		StopVehicleSound();
		PlaySound(SOUND_HELICOSTART, m_blupiPos, FALSE);
		PlaySound(SOUND_HELICOLOW, m_blupiPos, TRUE);
		break;
	case 8: // jeepdrive
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
		StopVehicleSound();
		PlaySound(SOUND_JEEPLOW, m_blupiPos, TRUE);
		break;
	case 9: // alltreasure
		for (int i = 0; i < MAXMOVEOBJECT; i++)
		{
			if (m_moveObject[i].type == TYPE_TRESOR)
			{
				m_moveObject[i].type = 0;
				m_nbTresor++;
				OpenDoorsTresor();
				PlaySound(SOUND_TRESOR, m_moveObject[i].posCurrent, FALSE);
			}
		}
		break;
	case 10: // endgoal
		for (int i = 0; i < MAXMOVEOBJECT; i++)
		{
			mob = &m_moveObject[i];
			if (mob->type == TYPE_GOAL || mob->type == TYPE_CLE)
			{
				m_blupiPos = mob->posCurrent;
				if (m_nbTresor >= m_totalTresor)
				{
					if (mob->type == TYPE_CLE)
					{
						m_bFoundCle = TRUE;
					}
					StopVehicleSound();
					PlaySound(SOUND_ENDOK, mob->posCurrent, FALSE);
					m_blupiAction = ACTION_WIN;
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
					PlaySound(SOUND_ENDKO, mob->posCurrent, FALSE);
				}
				m_goalPhase = 50;
			}
		}
		break;
	case 12: // roundshield
		PlaySound(SOUND_STARTSHIELD, m_blupiPos, FALSE);
		m_blupiShield = TRUE;
		m_blupiPower = FALSE;
		m_blupiCloud = FALSE;
		m_blupiHide = FALSE;
		m_blupiTimeShield = 100;
		m_blupiPosMagic = m_blupiPos;
		m_jauges[1].SetHide(FALSE);
		break;
	case 13: // quicklollipop
		m_blupiAction = ACTION_SUCETTE;
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
		PlaySound(SOUND_SUCETTE, m_blupiPos, FALSE);
		break;
	case 14: // tenbombs
		m_blupiPerso = 10;
		PlaySound(SOUND_PERSOTAKE, m_blupiPos, FALSE);
		break;
	case 15: // birdlime
		m_blupiBullet = 10;
		break;
	case 16: // drivetank
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
		PlaySound(SOUND_JEEPLOW, m_blupiPos, TRUE);
		break;
	case 17: // powercharge
		m_blupiAction = ACTION_CHARGE;
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
		PlaySound(SOUND_CHARGE, m_blupiPos, FALSE);
		break;
	case 18: // hidedrink
		m_blupiAction = ACTION_DRINK;
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
		PlaySound(SOUND_DRINK, m_blupiPos, FALSE);
		break;
	case 22: // iovercraft
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
		StopVehicleSound();
		PlaySound(SOUND_HELICOSTART, m_blupiPos, FALSE);
		PlaySound(SOUND_HELICOLOW, m_blupiPos, TRUE);
		break;
	case 23: // udynamite
		m_blupiDynamite = 1;
		PlaySound(SOUND_PERSOTAKE, m_blupiPos, FALSE);
		break;
	case 24: // wellkeys
		m_blupiCle |= CLE_RED | CLE_GREEN | CLE_BLUE;
		break;
	}
	if (!m_blupiShield && !m_blupiHide && !m_blupiCloud && !m_blupiPower)
	{
		m_jauges[1].SetHide(TRUE);
	}
	if (!m_blupiHelico && !m_blupiOver)
	{
		StopSound(SOUND_HELICOHIGH);
		StopSound(SOUND_HELICOLOW);
	}
	if (m_blupiJeep && m_blupiTank)
	{
		StopSound(SOUND_JEEPHIGH);
		StopSound(SOUND_JEEPLOW);
	}
}

BOOL CDecor::GetSuperBlupi()
{
	return m_bSuperBlupi;
}

void CDecor::SetSuperBlupi(BOOL bSuper)
{
	m_bSuperBlupi = bSuper;
}

BOOL CDecor::GetDrawSecret()
{
	return m_bDrawSecret;
}

void CDecor::SetDrawSecret(BOOL bDrawSecret)
{
	m_bDrawSecret = bDrawSecret;
}

void CDecor::SetBuildOfficialMissions(BOOL bBuild)
{
	m_bBuildOfficialMissions = bBuild;
}

BOOL CDecor::GetNetPacked()
{
	return m_bNetPacked;
}

void CDecor::SetNetPacked(BOOL bNetPacked)
{
	m_bNetPacked = bNetPacked;
}

BOOL CDecor::GetNetMovePredict()
{
	return m_bNetMovePredict;
}

void CDecor::SetNetMovePredict(BOOL bNetMovePredict)
{
	m_bNetMovePredict = bNetMovePredict;
}

BOOL CDecor::GetNetDebug()
{
	return m_bNetDebug;
}

void CDecor::SetNetDebug(BOOL bNetDebug)
{
	m_bNetDebug = bNetDebug;
	if (bNetDebug) remove("debug.txt");
}

void CDecor::OutputNetDebug(char* text)
{
	char textbuffer[100];

	if (!m_bNetDebug) return;

	sprintf(textbuffer, "/ snd=%d(%d)_rcv=%d(%d)", m_netPacketsSent, m_netPacketsSent2, m_netPacketsReceived, m_netPacketsReceived2);
	strcat(text, textbuffer);
}

void CDecor::SetMulti(BOOL multi)
{
	m_bMulti = multi;
}

void CDecor::SetTeam(int team)
{
	m_team = team;
}

POINT CDecor::VoyageGetPosVie(int nbVies)
{
	return { nbVies * 20 - 5, 417 };
}

void CDecor::VoyageInit(POINT start, POINT end, int icon, int channel)
{
	if (m_voyageIcon != -1)
	{
		m_voyagePhase = m_voyageTotal;
		VoyageStep();
	}
	m_voyageStart = start;
	m_voyageEnd = end;
	m_voyageIcon = icon;
	m_voyageChannel = channel;
	int num = abs(end.x - start.x);
	int num2 = abs(end.y - start.y);
	m_voyagePhase = 0;
	m_voyageTotal = (num + num2) / 10;
	if (m_voyageIcon == 48 && m_voyageChannel == 2)
	{
		m_voyageTotal = 40;
		m_nbVies--;
		m_pSound->PlayImage(9, end, -1);
	}
	if (m_voyageIcon == 21 && m_voyageChannel == 10)
	{
		m_pSound->PlayImage(12, start, -1);
	}
	if (m_voyageIcon == 6 && m_voyageChannel == 10)
	{
		if (m_nbTresor == m_totalTresor - 1)
		{
			m_pSound->PlayImage(19, start, -1);
		}
		else
		{
			m_pSound->PlayImage(11, start, -1);
		}
	}
	if (m_voyageIcon == 215 && m_voyageChannel == 10)
	{
		m_pSound->PlayImage(11, start, -1);
	}
	if (m_voyageIcon == 222 && m_voyageChannel == 10)
	{
		m_pSound->PlayImage(11, start, -1);
	}
	if (m_voyageIcon == 229 && m_voyageChannel == 10)
	{
		m_pSound->PlayImage(11, start, -1);
	}
	if (m_voyageIcon == 108 && m_voyageChannel == 4)
	{
		m_pSound->PlayImage(60, start, -1);
	}
	if (m_voyageIcon == 252 && m_voyageChannel == 10)
	{
		m_pSound->PlayImage(60, start, -1);
	}
	if (m_voyageIcon == 177 && m_voyageChannel == 10)
	{
		m_pSound->PlayImage(54, start, -1);
	}
	if (m_voyageIcon == 230 && m_voyageChannel == 10)
	{
		m_voyageTotal = 100;
	}
	if (m_voyageIcon == 40 && m_voyageChannel == 10)
	{
		m_voyageTotal = 50;
	}
}

void CDecor::VoyageStep()
{
	if (m_voyageIcon == -1)
	{
		return;
	}
	if (m_voyagePhase < m_voyageTotal)
	{
		if (m_time % 2 == 0 && m_voyageIcon >= 230 && m_voyageIcon <= 241 && m_voyageChannel == 10)
		{
			m_voyageIcon++;
			if (m_voyageIcon > 241)
			{
				m_voyageIcon = 230;
			}
		}
	}
	else
	{
		if (m_voyageIcon == 48 && m_voyageChannel == GetBlupiChannelActual())
		{
			m_blupiAction = ACTION_STOP;
			m_blupiPhase = 0;
			m_blupiFocus = 1;
			//m_energyUnused = 100;
		}
		if (m_voyageIcon == 21 && m_voyageChannel == 10)
		{
			if (m_nbVies < 10)
			{
				m_nbVies++;
			}
			m_pSound->PlayImage(3, m_voyageEnd, -1);
		}
		if (m_voyageIcon == 6 && m_voyageChannel == 10)
		{
			m_nbTresor++;
			OpenDoorsTresor();
			m_pSound->PlayImage(3, m_voyageEnd, -1);
		}
		if (m_voyageIcon == 215 && m_voyageChannel == 10)
		{
			m_blupiCle |= 1;
			m_pSound->PlayImage(3, m_voyageEnd, -1);
		}
		if (m_voyageIcon == 222 && m_voyageChannel == 10)
		{
			m_blupiCle |= 2;
			m_pSound->PlayImage(3, m_voyageEnd, -1);
		}
		if (m_voyageIcon == 229 && m_voyageChannel == 10)
		{
			m_blupiCle |= 4;
			m_pSound->PlayImage(3, m_voyageEnd, -1);
		}
		if (m_voyageIcon == 108 && m_voyageChannel == 10)
		{
			m_blupiPerso++;
			m_pSound->PlayImage(3, m_voyageEnd, -1);
		}
		if (m_voyageIcon == 252 && m_voyageChannel == 10)
		{
			m_blupiDynamite++;
			m_pSound->PlayImage(3, m_voyageEnd, -1);
		}
		if (m_voyageIcon == 177 && m_voyageChannel == 10)
		{
			m_pSound->PlayImage(3, m_voyageEnd, -1);
		}
		m_voyageIcon = -1;
	}
	m_voyagePhase++;
}

void CDecor::VoyageDraw()
{
	if (m_voyageIcon == -1 || m_voyageTotal == 0)
	{
		return;
	}
	int num = m_voyagePhase;
	if (m_voyageIcon == 40 && m_voyageChannel == 10)
	{
		num -= 30;
		if (num < 0)
		{
			num = 0;
		}
	}
	POINT pos;
	pos.x = m_voyageStart.x + (m_voyageEnd.x - m_voyageStart.x) * num / m_voyageTotal;
	pos.y = m_voyageStart.y + (m_voyageEnd.y - m_voyageStart.y) * num / m_voyageTotal;
	if (m_voyageIcon != 40 || m_voyageChannel != 10 || num != 0)
	{
		m_pPixmap->QuickIcon(m_voyageChannel, m_voyageIcon, pos);
	}
	if (m_voyageIcon == 40 && m_voyageChannel == 10)
	{
		pos.x -= 34;
		pos.x += m_posDecor.x;
		pos.y += m_posDecor.y;
		int num2 = speed[Random(0, 6)];
		int num3 = Random(-10, 10);
		if (num == 0)
		{
			num2 /= 2;
			num3 *= 4;
		}
		pos.y += num3;
		ObjectStart(pos, 93, num2);
	}
}

BOOL CDecor::DrawMap(BOOL bPlay, int team)
{
	POINT posDecor;
	POINT scrollPos;
	POINT* pos;
	UINT phase;
	RECT rect, src, dest;
	int  bMulti;
	int* icon;
	int  f, h, n, t;
	int  channel;

	posDecor.x = m_posDecor.x;
	posDecor.y = m_posDecor.y;
	scrollPos.x = m_scrollPoint.x;
	scrollPos.y = m_scrollPoint.y;
	bMulti = m_bMulti;
	phase = m_phase;

	m_blupiChannel = CHBLUPI;
	m_team = 0;
	m_phase = WM_PHASE_PLAY;
	LoadImages();
	if (bPlay != FALSE) PlayPrepare(TRUE);

	if ((0 < team) && (team < 4))
	{
		pos = m_netPos;
		bPlay = FALSE;
		int j = 0;
		icon = m_netIcons;
		for (int i = 0; i < 128; i++)
		{
			if (m_pNetwork->m_players[j].name[j + -10] == '\0')
			{
				*icon = -1;
			}
			else
			{

			}
		}
	}
	f = m_scrollPoint.x - 261;
	h = m_dimDecor.x != 0 ? 5760 : 0;
	m_posDecor.x = f;
	n = h + 118;
	if (f < 0)
	{
		m_posDecor.x = 0;
	}
	h = ((m_dimDecor.x != 0) & 5760) + 118;
	if (m_posDecor.x > n)
	{
		m_posDecor.x = n;
	}
	f = m_scrollPoint.y = -200;
	m_posDecor.y = f;
	h = m_dimDecor.y != 0 ? 5920 : 0;
	m_posDecor.y = n;
	t = h + 80;
	if (f < 0)
	{
		m_posDecor.y = 0;
	}
	if (m_posDecor.y > t)
	{
		m_posDecor.y = t;
	}
	posDecor.y = m_posDecor.y;
	m_scrollPoint.x = m_posDecor.x;
	m_scrollPoint.y = posDecor.y;
	rect.bottom = LYIMAGE;
	rect.left = 0;
	rect.top = 0;
	rect.right = LXIMAGE;
	Build(rect);
	src.bottom = 400;
	src.left = 0;
	src.top = 0;
	src.right = 522;
	
	dest.bottom = 158;
	dest.left = 0;
	dest.top = 0;
	dest.right = 206;
	m_pPixmap->DrawMap(CHMAP, src, dest);
	m_posDecor.x = posDecor.x;
	m_posDecor.y = posDecor.y;
	m_scrollPoint.x = scrollPos.x;
	m_scrollPoint.y = scrollPos.y;
	m_phase = phase;
	m_team = 0;
	m_bMulti = bMulti;
	return TRUE;
}

BOOL CDecor::SearchWorld(int world, POINT *blupi, int *dir)
{
	return FALSE;
}

BOOL CDecor::SearchDoor(int n, POINT *cel, POINT *blupi)
{
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			int icon = m_decor[i][j].icon;
			if (icon >= 174 && icon <= 181 && icon - 174 + 1 == n)
			{
				if (i > 0 && m_decor[i - 1, j]->icon == 182)
				{
					cel->x = i - 1;
					cel->y = j;
					blupi->x = (i - 2) * 64 + 2;
					blupi->y = j * 64 + BLUPIOFFY;
					return TRUE;
				}
				if (i > 1 && m_decor[i - 2, j]->icon == 182)
				{
					cel->x = i - 2;
					cel->y = j;
					blupi->x = (i - 3) * 64 + 2;
					blupi->y = j * 64 + BLUPIOFFY;
					return TRUE;
				}
				if (i < 99 && m_decor[i + 1, j]->icon == 182)
				{
					cel->x = i + 1;
					cel->y = j;
					blupi->x = (i + 2) * 64 + 2;
					blupi->y = j * 64 + BLUPIOFFY;
					return TRUE;
				}
				if (i < 98 && m_decor[i + 2, j]->icon == 182)
				{
					cel->x = i + 2;
					cel->y = j;
					blupi->x = (i + 3) * 64 + 2;
					blupi->y = j * 64 + BLUPIOFFY;
					return TRUE;
				}
			}
		}
	}
	return FALSE;
}

void CDecor::AdaptDoors(BOOL bPrivate, int mission)
{
	POINT* cel;
	POINT blupiStartPos;
	int i;
	POINT blupi;
	int num = MoveObjectFree();

	m_bPrivate = bPrivate;
	m_mission = mission;

	if (!m_bPrivate)
	{
		if (mission == 1)
		{
			for (i = 0; i < 20; i++)
			{
				if (SearchDoor(i, cel, &blupi) && (!m_doors[i + 180] || m_bCheatDoors))
				{
					m_decor[cel->x, cel->y]->icon = -1;
					m_moveObject[num].type = 22;
					m_moveObject[num].stepAdvance = 50;
					m_moveObject[num].stepRecede = 1;
					m_moveObject[num].timeStopStart = 0;
					m_moveObject[num].timeStopEnd = 0;
					m_moveObject[num].posStart.x = 64 * cel->x;
					m_moveObject[num].posStart.y = 64 * cel->y;
					m_moveObject[num].posEnd.x = 64 * cel->x;
					m_moveObject[num].posEnd.y = 64 * (cel->y - 1);
					m_moveObject[num].posCurrent = m_moveObject[num].posStart;
					m_moveObject[num].step = 1;
					m_moveObject[num].time = 0;
					m_moveObject[num].phase = 0;
					m_moveObject[num].channel = 1;
					m_moveObject[num].icon = 183;
					PlaySound(33, m_moveObject[num].posStart, FALSE);
				}
			}
			for (int j = 0; j < 100; j++)
			{
				for (int k = 0; k < 100; k++)
				{
					int icon = m_decor[j, k]->icon;
					if (icon >= 158 && icon <= 165 && (!m_doors[180 + icon - 158 + 1] == 1 || m_bCheatDoors))
					{
						m_decor[j, k]->icon += 8;
					}
				}
			}
		}
	}
	
}

void CDecor::OpenDoorsTresor()
{
	for (int x = 0; x < MAXCELX; x++)
	{
		for (int y = 0; y < MAXCELY; y++)
		{
			int icon = m_decor[x][y].icon;
			if (icon >= 0x1a5 && icon <= 0x1a5 + m_nbTresor - 1)
			{
				OpenDoor({ x, y });
			}
		}
	}
}

void CDecor::OpenDoor(POINT cel)
{
	int icon = m_decor[cel.x][cel.y].icon;
	m_decor[cel.x, cel.y]->icon = -1;
	int num = MoveObjectFree();
	m_moveObject[num].type = TYPE_DOOR;
	m_moveObject[num].stepAdvance = 50;
	m_moveObject[num].stepRecede = 1;
	m_moveObject[num].timeStopStart = 0;
	m_moveObject[num].timeStopEnd = 0;
	m_moveObject[num].posStart.x = DIMOBJX * cel.x;
	m_moveObject[num].posStart.y = DIMOBJY * cel.y;
	m_moveObject[num].posEnd.x = DIMOBJX * cel.x;
	m_moveObject[num].posEnd.y = DIMOBJY * (cel.y - 1);
	m_moveObject[num].posCurrent = m_moveObject[num].posStart;
	m_moveObject[num].step = STEP_STOPSTART;
	m_moveObject[num].time = 0;
	m_moveObject[num].phase = 0;
	m_moveObject[num].channel = CHOBJECT;
	m_moveObject[num].icon = icon;
	PlaySound(33, m_moveObject[num].posStart, FALSE);
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
	// more...
}

// Winphone functions, likely unnecessary
/*
BOOL CDecor::SearchGold(int n, POINT cel)
{
for (int i = 99; i >= 0; i--)
{
for (int j = 99; j >= 0; j--)
{
if (m_decor[j][i].icon == 183)
{
cel.x = j;
cel.y = i;
return TRUE;
}
}
}
return FALSE;
}

BOOL CDecor::IsFloatingObject(int i)
{
POINT posCurrent = m_moveObject[i]->posCurrent;
int num = (posCurrent.x + 32) / 64;
int num2 = posCurrent.y / 64 + 1;
int icon = m_decor[num, num2]->icon;
return IsPassIcon(icon);
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
int num = pos.x / DIMOBJX;
int num2 = pos.y / DIMOBJY;
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
}*/
// DecDesign.cpp
//

#include "def.h"
#include "decor.h"
#include "misc.h"
#include "dectables.h"

POINT CDecor::ScreenPosToCelPos(POINT pos)
{
	if (pos.x >= 0 && pos.x < LXIMAGE && pos.y >= 0 && pos.y < LYIMAGE) {
		return {
			(m_posDecor.x + m_dimCelHili.x * -32 + 32 + pos.x) / 64,
			(m_posDecor.y + m_dimCelHili.y * -32 + 32 + pos.y) / 64
		};
	}
	else return { -1, -1 };
}

void CDecor::SetCelPosFromScreenPos(POINT pos)
{
	m_posCelHili = ScreenPosToCelPos(pos);
}

void CDecor::SetFieldCC38AndStuff(int _foo, int _bar)
{
	m_dimCelHili = { 1, 1 };
	if (_foo == 2 && _bar != 3 && _bar != 9 && _bar != 10) m_dimCelHili = { 2, 2 };
	if (_foo == 3) m_iconLift = _bar;
	if (_foo == 4) m_iconLift = _bar + 20;
	if (_foo == 5) m_iconLift = _bar + 40;
	m_2ndPositionCalculationSlot = -1;
}

void CDecor::DeleteCel(POINT cel)
{
	m_2ndPositionCalculationSlot = -1;

	if (!IsValidCel(cel)) return;

	m_decor[cel.x][cel.y].icon = -1;
	AdaptBorder(cel);
	m_bigDecor[cel.x][cel.y].icon = -1;
	MoveObjectDelete(cel);
}

void CDecor::PlaceMenuItem(short *pCel, int *pTable, int lastIndex, BYTE flags, int currentIcon, BOOL bRand)
{
	if (bRand) {
		*pCel = pTable[rand() % (pTable[0] + 1)];
	}
	else if (!(flags & 8)) {
		if (flags & 1) {
			lastIndex++;
			if (*pCel == pTable[lastIndex] && currentIcon != 0 && pTable[0] <= lastIndex) {
				lastIndex = 0;
			}
			*pCel = pTable[lastIndex + 1];
		}
	}
	else {
		*pCel = pTable[lastIndex + 1];
	}
}

void CDecor::PlaceItemFromMenu1(POINT cel, int index, BYTE flags, int currentIcon)
{
	m_2ndPositionCalculationSlot = -1;

	short *pIcon = &m_decor[cel.x][cel.y].icon;
	short *pIconBig = &m_bigDecor[cel.x][cel.y].icon;

	if (!IsValidCel(cel)) return;

	switch (index) {
	case 0: // Tree
		PlaceMenuItem(pIconBig, table_366b0, m_lastDecorIndexes[0], flags, *pIconBig, TRUE);
		break;
	case 1: // Palmtree
		PlaceMenuItem(pIconBig, table_366c0, m_lastDecorIndexes[1], flags, *pIconBig, TRUE);
		break;
	case 2: // Decorative plant
		PlaceMenuItem(pIconBig, table_366d8, m_lastDecorIndexes[2], flags, *pIconBig, TRUE);
		break;
	case 3: // Marine plant
		*pIcon = Object::Marine_1;
		break;
	case 4: // House
		PlaceMenuItem(pIconBig, table_366e8, m_lastDecorIndexes[3], flags, *pIconBig, TRUE);
		break;
	case 5: // Mechanical background
		PlaceMenuItem(pIconBig, table_366f8, m_lastDecorIndexes[4], flags, *pIconBig, TRUE);
		break;
	case 6: // Kid's stuff background
		PlaceMenuItem(pIconBig, table_36710, m_lastDecorIndexes[5], flags, *pIconBig, TRUE);
		break;
	case 7: // Green slime 2
		PlaceMenuItem(pIconBig, table_36748, m_lastDecorIndexes[6], flags, *pIconBig, TRUE);
		break;
	case 8: // Element for Palace
		PlaceMenuItem(pIconBig, table_36520, m_lastDecorIndexes[7], flags, *pIconBig, TRUE);
		break;
	case 9: // Support
		PlaceMenuItem(pIcon, table_36670, m_lastDecorIndexes[8], flags, *pIcon, TRUE);
		break;
	case 10: // Spider's web
		PlaceMenuItem(pIcon, table_366a0, m_lastDecorIndexes[9], flags, *pIcon, TRUE);
		break;
	}
}

void CDecor::PlaceItemFromMenu2(POINT cel, int index, BYTE flags, int currentIcon)
{
	m_2ndPositionCalculationSlot = -1;

	short *pIcon = &m_decor[cel.x][cel.y].icon;

	if (!IsValidCel(cel)) return;

	m_iconLift = index;

	switch (index) {
	case 0: // Square tech-blocks
		PlaceMenuItem(pIcon, table_36418, m_lastDecorIndexes[10], flags, *pIcon, TRUE);
		break;
	case 1: // Special tech-blocks
		PlaceMenuItem(pIcon, table_36458, m_lastDecorIndexes[11], flags, *pIcon, TRUE);
		break;
	case 2: // Triangular tech-blocks
		PlaceMenuItem(pIcon, table_36488, m_lastDecorIndexes[12], flags, *pIcon, FALSE);
		break;
	case 3: // Secret tech-block
		PlaceMenuItem(pIcon, table_364a0, m_lastDecorIndexes[13], flags, *pIcon, FALSE);
		break;
	case 4: // Mechanical square
		PlaceMenuItem(pIcon, table_364b0, m_lastDecorIndexes[14], flags, *pIcon, TRUE);
		break;
	case 5: // Special mechanical
		PlaceMenuItem(pIcon, table_364d0, m_lastDecorIndexes[15], flags, *pIcon, FALSE);
		break;
	case 6: // Secret mechanical
		PlaceMenuItem(pIcon, table_364e8, m_lastDecorIndexes[16], flags, *pIcon, FALSE);
		break;
	case 7: // Pipes
		*pIcon = Object::Pipes_1;
		break;
	}
	AdaptBorder(cel);
}

void CDecor::PlaceItemFromMenu3(POINT cel, int index, BYTE flags, int currentIcon)
{
	m_2ndPositionCalculationSlot = -1;

	short *pIcon = &m_decor[cel.x][cel.y].icon;

	if (!IsValidCel(cel)) return;

	m_iconLift = index + 20;

	switch (index) {
	case 0: // Square rock
		PlaceMenuItem(pIcon, table_36530, m_lastDecorIndexes[20], flags, *pIcon, FALSE);
		break;
	case 1: // Triangular rock
		PlaceMenuItem(pIcon, table_36538, m_lastDecorIndexes[21], flags, *pIcon, FALSE);
		break;
	case 2: // Secret rock
		PlaceMenuItem(pIcon, table_36548, m_lastDecorIndexes[22], flags, *pIcon, FALSE);
		break;
	case 3: // Cave
			// todo
		break;
	case 4: // Secret cave
		*pIcon = Object::CaveSecret;
		break;
	case 5: // Cheese
		*pIcon = Random(Object::CheeseSquare_1, Object::CheeseSquare_4);
		break;
	case 6: // Secret cheese
		*pIcon = Object::CheeseSecret;
		break;
	case 7: // Green slime 2
		*pIcon = Object::Slime_1;
		break;
	case 8: // Grass
		PlaceMenuItem(pIcon, table_365d0, m_lastDecorIndexes[23], flags, *pIcon, FALSE);
		break;
	case 9: // Water
		PlaceMenuItem(pIcon, table_36630, m_lastDecorIndexes[24], flags, *pIcon, FALSE);
		break;
	}
	AdaptBorder(cel);
}

void CDecor::PlaceItemFromMenu4(POINT cel, int index, BYTE flags, int currentIcon)
{
	m_2ndPositionCalculationSlot = -1;

	short *pIcon = &m_decor[cel.x][cel.y].icon;

	if (!IsValidCel(cel)) return;

	m_iconLift = index + 40;

	switch (index) {
	case 0: // Palace
		break;
	case 1: // Element for Palace
		break;
	case 2: // Building facade
		break;
	case 3: // Roof
		break;
	case 4: // Bricks
		break;
	case 5: // Furniture
		break;
	case 6: // Wooden wall
		break;
	case 7: // Kid's stuff square
		break;
	case 8: // Special Kid's stuff
		break;
	case 9: // Invisible block
		break;
	}
	AdaptBorder(cel);
}

void CDecor::PlaceItemFromMenu5(POINT cel, int index, BYTE flags, int currentIcon)
{
	m_2ndPositionCalculationSlot = -1;

	int mobId;
	MoveObject* pMob;

	short *pIcon = &m_decor[cel.x][cel.y].icon;

	if (!IsValidCel(cel)) return;

	switch (index) {
	case 0: // Bomb
		MoveObjectDelete(cel);
		mobId = MoveObjectFree();
		if (mobId == -1) return;
		pMob = &m_moveObject[mobId];
		pMob->type = TYPE_BOMBEDOWN;
		pMob->stepAdvance = 1;
		pMob->stepRecede = 1;
		pMob->timeStopStart = 0;
		pMob->timeStopEnd = 0;
		pMob->posStart = { cel.x * DIMOBJX + 2, cel.y * DIMOBJY + 4 };
		pMob->posEnd = pMob->posStart;
		pMob->posCurrent = pMob->posStart;
		pMob->step = STEP_STOPSTART;
		pMob->time = 0;
		pMob->phase = 0;
		pMob->channel = CHELEMENT;
		pMob->icon = 0x0c;
		break;
	case 1: // Hanging bomb
		MoveObjectDelete(cel);
		mobId = MoveObjectFree();
		if (mobId == -1) return;
		pMob = &m_moveObject[mobId];
		pMob->type = TYPE_BOMBEUP;
		pMob->stepAdvance = 1;
		pMob->stepRecede = 1;
		pMob->timeStopStart = 0;
		pMob->timeStopEnd = 0;
		pMob->posStart = { cel.x * DIMOBJX + 2, cel.y * DIMOBJY };
		pMob->posEnd = pMob->posStart;
		pMob->posCurrent = pMob->posStart;
		pMob->step = STEP_STOPSTART;
		pMob->time = 0;
		pMob->phase = 0;
		pMob->channel = CHELEMENT;
		pMob->icon = 0x30;
		break;
	case 2: // Homing bomb
		MoveObjectDelete(cel);
		mobId = MoveObjectFree();
		if (mobId == -1) return;
		pMob = &m_moveObject[mobId];
		pMob->type = TYPE_BOMBEFOLLOW1;
		pMob->stepAdvance = 1;
		pMob->stepRecede = 1;
		pMob->timeStopStart = 0;
		pMob->timeStopEnd = 0;
		pMob->posStart = { cel.x * DIMOBJX, cel.y * DIMOBJY };
		pMob->posEnd = pMob->posStart;
		pMob->posCurrent = pMob->posStart;
		pMob->step = STEP_STOPSTART;
		pMob->time = 0;
		pMob->phase = 0;
		pMob->channel = CHELEMENT;
		pMob->icon = 0x100;
		break;
	case 3: // Lava
		PlaceMenuItem(pIcon, table_decor_lave, m_lastDecorIndexes[40], flags, *pIcon, FALSE);
		break;
	case 4: // Fan
		PlaceMenuItem(pIcon, table_decor_ventillog, m_lastDecorIndexes[41], flags, *pIcon, FALSE);
		break;
	case 5: // Wind
		PlaceMenuItem(pIcon, table_decor_ventg, m_lastDecorIndexes[42], flags, *pIcon, FALSE);
		break;
	case 6: // Slime trap (floor)
		*pIcon = Object::SlimeTrapFloor_1;
		break;
	case 7: // Slime trap (ceiling)
		*pIcon = Object::SlimeTrapCeiling_1;
		break;
	case 8: // Circular saw
		PlaceMenuItem(pIcon, table_decor_scie, m_lastDecorIndexes[43], flags, *pIcon, FALSE);
		break;
	case 9: // Inverter
		MoveObjectDelete(cel);
		mobId = MoveObjectFree();
		if (mobId == -1) return;
		pMob = &m_moveObject[mobId];
		pMob->type = TYPE_INVERT;
		pMob->stepAdvance = 1;
		pMob->stepRecede = 1;
		pMob->timeStopStart = 0;
		pMob->timeStopEnd = 0;
		pMob->posStart = { cel.x * DIMOBJX + 2, cel.y * DIMOBJY + 8 };
		pMob->posEnd = pMob->posStart;
		pMob->posCurrent = pMob->posStart;
		pMob->step = STEP_STOPSTART;
		pMob->time = 0;
		pMob->phase = 0;
		pMob->channel = CHELEMENT;
		pMob->icon = 0xBB;
		break;
	case 10: // Lightning
		*pIcon = Object::LightningMachine;
		break;
	case 11: // Crusher
		*pIcon = Object::Crusher_1;
		break;
	}
	AdaptBorder(cel);
}

void CDecor::PlaceItemFromMenu6(POINT cel, int index, BYTE flags, int currentIcon)
{
	m_2ndPositionCalculationSlot = -1;

	short *pIcon = &m_decor[cel.x][cel.y].icon;

	if (!IsValidCel(cel) || currentIcon == 0) return;

	switch (m_iconLift) {

	}

	switch (index) {
	case 0: // Slow lift
	case 1: // Normal lift
	case 2: // Fast lift
	case 3: // Fast/Slow lift
	case 4: // Lift with conveyor belt
	case 5: // Bulldozer
	case 6: // Fish
	case 7: // Bird
	case 8: // Wasp
	case 9: // Slime creature
	case 10: // Moving bomb
	case 11: // Heliported ennemy
	case 12: // Motorized ennemy
		break;
	}
}

void CDecor::PlaceItemFromMenu7(POINT cel, int index, BYTE flags, int currentIcon)
{
	m_2ndPositionCalculationSlot = -1;

	MoveObject* pMob;
	int mobId;

	short *pIcon = &m_decor[cel.x][cel.y].icon;

	if (!IsValidCel(cel)) return;

	switch (index) {
	case 0: // Chest
		MoveObjectDelete(cel);
		mobId = MoveObjectFree();
		if (mobId == -1) return;
		pMob = &m_moveObject[mobId];
		pMob->type = TYPE_TRESOR;
		pMob->stepAdvance = 1;
		pMob->stepRecede = 1;
		pMob->timeStopStart = 0;
		pMob->timeStopEnd = 0;
		pMob->posStart = { cel.x * DIMOBJX + 2, cel.y * DIMOBJY + 4 };
		pMob->posEnd = pMob->posStart;
		pMob->posCurrent = pMob->posStart;
		pMob->step = STEP_STOPSTART;
		pMob->time = 0;
		pMob->phase = 0;
		pMob->channel = CHELEMENT;
		pMob->icon = 0x00;
		break;
	case 1: // Egg
		MoveObjectDelete(cel);
		mobId = MoveObjectFree();
		if (mobId == -1) return;
		pMob = &m_moveObject[mobId];
		pMob->type = TYPE_EGG;
		pMob->stepAdvance = 1;
		pMob->stepRecede = 1;
		pMob->timeStopStart = 0;
		pMob->timeStopEnd = 0;
		pMob->posStart = { cel.x * DIMOBJX + 2, cel.y * DIMOBJY + 8 };
		pMob->posEnd = pMob->posStart;
		pMob->posCurrent = pMob->posStart;
		pMob->step = STEP_STOPSTART;
		pMob->time = 0;
		pMob->phase = 0;
		pMob->channel = CHELEMENT;
		pMob->icon = 0x15;
		break;
	case 2: // Lollipop
		MoveObjectDelete(cel);
		mobId = MoveObjectFree();
		if (mobId == -1) return;
		pMob = &m_moveObject[mobId];
		pMob->type = TYPE_POWER;
		pMob->stepAdvance = 1;
		pMob->stepRecede = 1;
		pMob->timeStopStart = 0;
		pMob->timeStopEnd = 0;
		pMob->posStart = { cel.x * DIMOBJX + 2, cel.y * DIMOBJY + 8 };
		pMob->posEnd = pMob->posStart;
		pMob->posCurrent = pMob->posStart;
		pMob->step = STEP_STOPSTART;
		pMob->time = 0;
		pMob->phase = 0;
		pMob->channel = CHELEMENT;
		pMob->icon = 0x88;
		break;
	case 3: // Shield
		MoveObjectDelete(cel);
		mobId = MoveObjectFree();
		if (mobId == -1) return;
		pMob = &m_moveObject[mobId];
		pMob->type = TYPE_SHIELD;
		pMob->stepAdvance = 1;
		pMob->stepRecede = 1;
		pMob->timeStopStart = 0;
		pMob->timeStopEnd = 0;
		pMob->posStart = { cel.x * DIMOBJX + 2, cel.y * DIMOBJY + 8 };
		pMob->posEnd = pMob->posStart;
		pMob->posCurrent = pMob->posStart;
		pMob->step = STEP_STOPSTART;
		pMob->time = 0;
		pMob->phase = 0;
		pMob->channel = CHELEMENT;
		pMob->icon = 0x90;
		break;
	case 4: // Invisibility potion
		MoveObjectDelete(cel);
		mobId = MoveObjectFree();
		if (mobId == -1) return;
		pMob = &m_moveObject[mobId];
		pMob->type = TYPE_DRINK;
		pMob->stepAdvance = 1;
		pMob->stepRecede = 1;
		pMob->timeStopStart = 0;
		pMob->timeStopEnd = 0;
		pMob->posStart = { cel.x * DIMOBJX + 2, cel.y * DIMOBJY + 6 };
		pMob->posEnd = pMob->posStart;
		pMob->posCurrent = pMob->posStart;
		pMob->step = STEP_STOPSTART;
		pMob->time = 0;
		pMob->phase = 0;
		pMob->channel = CHELEMENT;
		pMob->icon = 0xB2;
		break;
	case 5: // Glue supply
		MoveObjectDelete(cel);
		mobId = MoveObjectFree();
		if (mobId == -1) return;
		pMob = &m_moveObject[mobId];
		pMob->type = TYPE_BULLET;
		pMob->stepAdvance = 1;
		pMob->stepRecede = 1;
		pMob->timeStopStart = 0;
		pMob->timeStopEnd = 0;
		pMob->posStart = { cel.x * DIMOBJX + 2, cel.y * DIMOBJY + 4 };
		pMob->posEnd = pMob->posStart;
		pMob->posCurrent = pMob->posStart;
		pMob->step = STEP_STOPSTART;
		pMob->time = 0;
		pMob->phase = 0;
		pMob->channel = CHELEMENT;
		pMob->icon = 0xB1;
		break;
	case 6: // Recharging device
		MoveObjectDelete(cel);
		mobId = MoveObjectFree();
		if (mobId == -1) return;
		pMob = &m_moveObject[mobId];
		pMob->type = TYPE_CHARGE;
		pMob->stepAdvance = 1;
		pMob->stepRecede = 1;
		pMob->timeStopStart = 0;
		pMob->timeStopEnd = 0;
		pMob->posStart = { cel.x * DIMOBJX + 2, cel.y * DIMOBJY + 4 };
		pMob->posEnd = pMob->posStart;
		pMob->posCurrent = pMob->posStart;
		pMob->step = STEP_STOPSTART;
		pMob->time = 0;
		pMob->phase = 0;
		pMob->channel = CHELEMENT;
		pMob->icon = 0xEE;
		break;
	case 7: // Personal bomb
		int type;
		mobId = MoveObjectSearch(cel, -1);
		if (mobId != -1 && currentIcon != 0) {
			if (mobId >= TYPE_BOMBEPERSO4) {
				m_lastDecorIndexes[60] = 0;
			}
			else {
				m_lastDecorIndexes[60] = m_moveObject[mobId].type - TYPE_BOMBEPERSO1;
			}
		}
		type = m_lastDecorIndexes[60] + TYPE_BOMBEPERSO1;
		MoveObjectDelete(cel);
		mobId = MoveObjectFree();
		if (mobId == -1) return;
		pMob = &m_moveObject[mobId];
		pMob->type = type;
		pMob->stepAdvance = 1;
		pMob->stepRecede = 1;
		pMob->timeStopStart = 0;
		pMob->timeStopEnd = 0;
		pMob->posStart = { cel.x * DIMOBJX + 2, cel.y * DIMOBJY + 6 };
		pMob->posEnd = pMob->posStart;
		pMob->posCurrent = pMob->posStart;
		pMob->step = STEP_STOPSTART;
		pMob->time = 0;
		pMob->phase = 0;
		switch (type) {
		default:
		case TYPE_BOMBEPERSO1:
			pMob->channel = CHBLUPI;
			break;
		case TYPE_BOMBEPERSO2:
			pMob->channel = CHBLUPI1;
			break;
		case TYPE_BOMBEPERSO3:
			pMob->channel = CHBLUPI2;
			break;
		case TYPE_BOMBEPERSO4:
			pMob->channel = CHBLUPI3;
			break;
		}
		pMob->icon = 0x101;
		break;
	case 8: // Dynamite
		MoveObjectDelete(cel);
		mobId = MoveObjectFree();
		if (mobId == -1) return;
		pMob = &m_moveObject[mobId];
		pMob->type = TYPE_DYNAMITE;
		pMob->stepAdvance = 1;
		pMob->stepRecede = 1;
		pMob->timeStopStart = 0;
		pMob->timeStopEnd = 0;
		pMob->posStart = { cel.x * DIMOBJX + 2, cel.y * DIMOBJY + 6 };
		pMob->posEnd = pMob->posStart;
		pMob->posCurrent = pMob->posStart;
		pMob->step = STEP_STOPSTART;
		pMob->time = 0;
		pMob->phase = 0;
		pMob->channel = CHELEMENT;
		pMob->icon = 0xFC;
		break;
	}
	AdaptBorder(cel);
}

void CDecor::PlaceItemFromMenu8(POINT cel, int index, BYTE flags, int currentIcon)
{
	m_2ndPositionCalculationSlot = -1;

	short *pIcon = &m_decor[cel.x][cel.y].icon;

	if (!IsValidCel(cel)) return;

	switch (index) {
	case 0: // Key
	case 1: // Door
	case 2: // Closed while not all chests have been found
	case 3: // Teleporter
	case 4: // Bar to hang from
	case 5: // Spring
	case 6: // Vanishing bloc
	case 7: // Fragile bridge
	case 8: // Wooden case
	case 9: // Secret wooden case
		break;
	}
}

void CDecor::PlaceItemFromMenu9(POINT cel, int index, BYTE flags, int currentIcon)
{
	m_2ndPositionCalculationSlot = -1;

	short *pIcon = &m_decor[cel.x][cel.y].icon;

	if (!IsValidCel(cel)) return;

	switch (index) {
	case 0: // Hovercraft
	case 1: // Helicopter
	case 2: // Skateboard
	case 3: // Jeep
	case 4: // Glue tank
		break;
	}
}

void CDecor::PlaceItemFromMenu10(POINT cel, int index, BYTE flags, int currentIcon)
{
	m_2ndPositionCalculationSlot = -1;

	short *pIcon = &m_decor[cel.x][cel.y].icon;

	if (!IsValidCel(cel)) return;

	switch (index) {
	case 0: // Goal
	case 1: // Yellow Blupi
	case 2: // Orange Blupi
	case 3: // Blue Blupi
	case 4: // Green Blupi
	case 5: // Door
	case 6: // Level start
	case 7: // Key
		break;
	}
}

char* CDecor::GetMissionTitle()
{
	return m_missionTitle;
}

void CDecor::SetMissionTitle(char *str)
{
	strcpy(m_missionTitle, str);
}

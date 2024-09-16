// DecBlock.cpp
//

#include "def.h"
#include "decor.h"
#include "misc.h"
#include "obstacle.h"
#include "dectables.h"

BOOL CDecor::BlitzActif(POINT cel)
{
	if (m_phase == WM_PHASE_BUILD) {
		//TODO: rewrite this like a human
		int foo = m_time >> 31;
		return 1 - (((m_time ^ foo) - foo & 1 ^ foo) == foo);
	}

	POINT pos = { cel.x * DIMOBJX, cel.y * DIMOBJY };

	int num = m_time % 100;

	if (m_blupiPos.x >= pos.x - 80 && m_blupiPos.x <= pos.x + 80 &&
		m_blupiPos.y >= pos.y - 500 && m_blupiPos.y <= pos.y + 500)
	{
		if (m_time % 100 < 70 && cel.y > 0 && m_decor[cel.x][cel.y - 1].icon == 0x130)
		{
			PlaySound(SOUND_BLITZ, pos, 0);
		}

		for (int i = 0; table_blitz[i] != -1; i++)
		{
			if (m_time % 100 == i) return TRUE;
		}
	}

	return FALSE;
}

int CDecor::SoundEnviron(int sound, int obstacle)
{
	if ((obstacle >= 32 && obstacle <= 34) || (obstacle >= 41 && obstacle <= 47) || (obstacle >= 139 && obstacle <= 143))
	{
		if (sound == SOUND_JUMPTOC)
		{
			return 79;
		}
		if (sound == SOUND_JUMPEND)
		{
			return 78;
		}
	}
	if ((obstacle >= 1 && obstacle <= 28) || (obstacle >= 78 && obstacle <= 90) || (obstacle >= 250 && obstacle <= 260) || (obstacle >= 311 && obstacle <= 316) || (obstacle >= 324 && obstacle <= 329))
	{
		if (sound == SOUND_JUMPTOC)
		{
			return 81;
		}
		if (sound == SOUND_JUMPEND)
		{
			return 80;
		}
	}
	if ((obstacle >= 284 && obstacle <= 303) || obstacle == 338)
	{
		if (sound == SOUND_JUMPTOC)
		{
			return 83;
		}
		if (sound == SOUND_JUMPEND)
		{
			return 82;
		}
	}
	if (obstacle >= 341 && obstacle <= 363)
	{
		if (sound == SOUND_JUMPTOC)
		{
			return 85;
		}
		if (sound == SOUND_JUMPEND)
		{
			return 84;
		}
	}
	if (obstacle >= 215 && obstacle <= 234)
	{
		if (sound == SOUND_JUMPTOC)
		{
			return 87;
		}
		if (sound == SOUND_JUMPEND)
		{
			return 86;
		}
	}
	if (obstacle >= 246 && obstacle <= 249)
	{
		if (sound == SOUND_JUMPTOC)
		{
			return 89;
		}
		if (sound == SOUND_JUMPEND)
		{
			return 88;
		}
	}
	if (obstacle >= 107 && obstacle <= 109)
	{
		if (sound == SOUND_JUMPTOC)
		{
			return 91;
		}
		if (sound == SOUND_JUMPEND)
		{
			return 90;
		}
	}
	return sound;
}


int CDecor::IsWorld(POINT pos)
{
	pos.x += 30;
	pos.y += 30;
	if (pos.x < 0 || pos.x >= 6400 || pos.y < 0 || pos.y >= 6400)
	{
		return -1;
	}
	int icon = m_decor[pos.x / DIMOBJX][pos.y / DIMOBJY].icon;
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

void CDecor::ActiveSwitch(BOOL bState, POINT cel)
{
	POINT pos;
	pos.x = cel.x * DIMOBJX;
	pos.y = cel.y * DIMOBJY;
	ModifDecor(pos, bState ? 384 : 385);
	PlaySound(bState ? 77 : 76, pos);
	cel.x -= 20;
	for (int i = 0; i < 41; i++)
	{
		if (cel.x >= 0 && cel.x < 100 && m_decor[cel.x][cel.y].icon == (bState ? 379 : 378))
		{
			pos.x = cel.x * DIMOBJX;
			pos.y = cel.y * DIMOBJY;
			ModifDecor(pos, bState ? 378 : 379);
		}
		cel.x++;
	}
}

int CDecor::GetTypeBarre(POINT pos)
{
	POINT pos2 = pos;
	pos.x += 30;
	pos.y += 22;
	if (pos.y % 64 > 44)
	{
		return 0;
	}
	if (pos.x < 0 || pos.x >= 6400 || pos.y < 0 || pos.y >= 6400)
	{
		return 0;
	}
	int icon = m_decor[pos.x / DIMOBJX][pos.y / DIMOBJY].icon;
	if (icon != 138 && icon != 202)
	{
		return 0;
	}
	if (pos.y >= 6336)
	{
		return 1;
	}
	icon = m_decor[pos.x / DIMOBJX][pos.y / DIMOBJY + 1].icon;
	if (IsPassIcon(icon))
	{
		return 2;
	}
	RECT rect = BlupiRect(pos2);
	rect.top = pos2.y + 60 - 2;
	rect.bottom = pos2.y + 60 - 1;
	if (DecorDetect(rect, TRUE))
	{
		return 2;
	}
	return 1;
}

BOOL CDecor::IsLave(POINT pos)
{
	pos.x += 30;
	return pos.x >= 0 && pos.x < 6400 && pos.y >= 0 && pos.y < 6400 && m_decor[pos.x / DIMOBJX][pos.y / DIMOBJY].icon == 68;
}

BOOL CDecor::IsPiege(POINT pos)
{
	pos.x += 30;
	pos.y += 60;
	return pos.x % 64 >= 15 && pos.x % 64 <= 49 && pos.x >= 0 && pos.x < 6400 && pos.y >= 0 && pos.y < 6400 && m_decor[pos.x / DIMOBJX][pos.y / DIMOBJY].icon == 373;
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
	int icon = m_decor[pos.x / DIMOBJX][pos.y / DIMOBJY].icon;
	if (bAlways)
	{
		return icon == 404 || icon == 410;
	}
	return icon == 404;
}

BOOL CDecor::IsScie(POINT pos)
{
	pos.x += 30;
	return pos.x % 64 >= 4 && pos.x % 64 <= 60 && pos.x >= 0 && pos.x < 6400 && pos.y >= 0 && pos.y < 6400 && m_decor[pos.x / DIMOBJX][pos.y / DIMOBJY].icon == 378;
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
	celSwitch.x = pos.x / DIMOBJX;
	celSwitch.y = pos.y / DIMOBJY;
	return m_decor[pos.x / DIMOBJX][pos.y / DIMOBJY].icon == 384 || m_decor[pos.x / DIMOBJX][pos.y / DIMOBJY].icon == 385;
}

BOOL CDecor::IsEcraseur(POINT pos)
{
	if (m_time / 3 % 10 > 2)
	{
		return FALSE;
	}
	pos.x += 30;
	return pos.x >= 0 && pos.x < 6400 && pos.y >= 0 && pos.y < 6400 && m_decor[pos.x / DIMOBJX][pos.y / DIMOBJY].icon == 317;
}

BOOL CDecor::IsBlitz(POINT pos, BOOL bAlways)
{
	pos.x += 30;
	if (pos.x < 0 || pos.x >= 6400 || pos.y < 0 || pos.y >= 6400)
	{
		return FALSE;
	}
	POINT tinyPoint;
	tinyPoint.x = pos.x / DIMOBJX;
	tinyPoint.y = pos.y / DIMOBJY;
	return m_decor[tinyPoint.x][tinyPoint.y].icon == 305 && (bAlways || BlitzActif(tinyPoint));
}

BOOL CDecor::IsRessort(POINT pos)
{
	pos.x += 30;
	pos.y += 60;
	return pos.x >= 0 && pos.x < 6400 && pos.y >= 0 && pos.y < 6400 && m_decor[pos.x / DIMOBJX][pos.y / DIMOBJY].icon == 211;
}

BOOL CDecor::IsTemp(POINT pos)
{
	pos.x += 30;
	pos.y += 60;
	return pos.x >= 0 && pos.x < 6400 && pos.y >= 0 && pos.y < 6400 && m_decor[pos.x / DIMOBJX][pos.y / DIMOBJY].icon == 324;
}

BOOL CDecor::IsBridge(POINT pos, POINT celBridge)
{
	pos.x += 30;
	pos.y += 60;
	if (pos.x >= 0 && pos.x < 6400 && pos.y >= 0 && pos.y < 6400 && m_decor[pos.x / DIMOBJX][pos.y / DIMOBJY].icon == 364)
	{
		celBridge.x = pos.x / DIMOBJX;
		celBridge.y = pos.y / DIMOBJY;
		return TRUE;
	}
	pos.y -= 60;
	if (pos.x >= 0 && pos.x < 6400 && pos.y >= 0 && pos.y < 6400 && m_decor[pos.x / DIMOBJX][pos.y / DIMOBJY].icon == 364)
	{
		celBridge.x = pos.x / DIMOBJX;
		celBridge.y = pos.y / DIMOBJY;
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
		if (pos.x >= 0 && pos.x < DIMOBJX * MAXCELX && pos.y >= 0 && pos.y < DIMOBJY * MAXCELY && m_decor[pos.x / DIMOBJX][pos.y / DIMOBJY].icon >= 334 && m_decor[pos.x / DIMOBJX][pos.y / DIMOBJY].icon <= 336)
		{
			celPorte.x = pos.x / DIMOBJX;
			celPorte.y = pos.y / DIMOBJY;
			return m_decor[pos.x / DIMOBJX][pos.y / DIMOBJY].icon;
		}
		pos.x += num;
	}
	return -1;
}

int CDecor::IsTeleporte(POINT pos)
{
	if (pos.x % DIMOBJX > 6)
	{
		return -1;
	}
	pos.x += 30;
	pos.y -= 60;
	if (pos.x < 0 || pos.x >= DIMOBJX * MAXCELX || pos.y < 0 || pos.y >= DIMOBJY * MAXCELY)
	{
		return -1;
	}
	if (m_decor[pos.x / DIMOBJX][pos.y / DIMOBJY].icon >= 330 && m_decor[pos.x / DIMOBJX][pos.y / DIMOBJY].icon <= 333)
	{
		return m_decor[pos.x / DIMOBJX][pos.y / DIMOBJY].icon;
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
			if (num == m_decor[i][j].icon)
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

BOOL CDecor::IsSurfWater(POINT pos)
{
	if (pos.y % 64 < 64 - BLUPISURF)
	{
		return FALSE;
	}
	int icon = m_decor[(pos.x + 30) / 64][pos.y / DIMOBJY].icon;
	int icon2 = m_decor[(pos.x + 30) / 64][(pos.y + BLUPISURF) / 64].icon;
	return icon != 92 && icon2 == 92;
}

BOOL CDecor::IsDeepWater(POINT pos)
{
	int num = (pos.x + 30) / 64;
	int num2 = pos.y / DIMOBJY;
	if (num < 0 || num >= 100 || num2 < 0 || num2 >= 100)
	{
		return FALSE;
	}
	int icon = m_decor[num][num2].icon;
	return icon == 91 || icon == 92;
}

BOOL CDecor::IsOutWater(POINT pos)
{
	int icon = m_decor[(pos.x + 30) / 64][(pos.y + 30) / 64].icon;
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
	if (icon == 324 && m_time / 4 % 20 < 18)
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
	int icon = m_decor[pos.x / DIMOBJX][pos.y / DIMOBJY].icon;
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
		if (num != m_decor[pos.x / DIMOBJX][pos.y / DIMOBJY].icon)
		{
			break;
		}
		ModifDecor(pos, -1);
	} while (pos.x >= 0 && pos.x < 6400 && pos.y >= 0 && pos.y < 6400);
	return TRUE;
}

void CDecor::ModifDecor(POINT pos, int icon, BOOL bMulti)
{// TODO: this
	int icon2 = m_decor[pos.x / DIMOBJX][pos.y / DIMOBJY].icon;
	if (icon == -1 && icon >= 126 && icon2 <= 137)
	{

	}
	m_decor[pos.x / DIMOBJX][pos.y / DIMOBJY].icon = icon;
}

BOOL CDecor::IsRightBorder(POINT pos, POINT offset)
{
	return FALSE; // TODO
}


BOOL CDecor::IsFromage(POINT cel)
{
	if (!IsValidCel(cel)) return FALSE;

	int icon = m_decor[cel.x][cel.y].icon;
	return (icon >= 246 && icon <= 249) || icon == 339;
}

BOOL CDecor::IsGrotte(POINT cel)
{
	if (!IsValidCel(cel)) return FALSE;

	int icon = m_decor[cel.x][cel.y].icon;
	return icon = 284 || icon == 301 || icon == 337;
}

void CDecor::AdaptMidBorder(POINT cel)
{
	if (!IsValidCel(cel)) return;

	int num = 15;
	if (!IsRightBorder({ cel.x, cel.y + 1 }, { 0, -1 }))
	{
		num &= -2;
	}
	if (!IsRightBorder({ cel.x, cel.y + 1 }, { 0, 1 }))
	{
		num &= -3;
	}
	if (!IsRightBorder({ cel.x + 1, cel.y }, { -1, 0 }))
	{
		num &= -5;
	}
	if (!IsRightBorder({ cel.x - 1, cel.y }, { 1, 0 }))
	{
		num &= -9;
	}
	int num2 = m_decor[cel.x][cel.y].icon;
	if (num2 == 156)
	{
		num2 = 35;
	}
	if (num2 == 252 || num2 == 253)
	{
		num2 = 251;
	}
	if (num2 == 255)
	{
		num2 = 254;
	}
	if (num2 == 362)
	{
		num2 = 347;
	}
	if (num2 == 363)
	{
		num2 = 348;
	}
	if (num2 >= 341 && num2 <= 346)
	{
		num2 = 341;
	}
	for (int i = 0; i < 144; i++)
	{
		if (num2 == table_adapt_decor[i])
		{
			num2 = table_adapt_decor[i / 16 * 16 + num];
			if (num2 == 35 && rand() % 2 == 0)
			{
				num2 = 156;
			}
			if (num2 == 251)
			{
				num2 = Random(251, 253);
			}
			if (num2 == 254 && rand() % 2 == 0)
			{
				num2 = 255;
			}
			if (num2 == 347 && rand() % 2 == 0)
			{
				num2 = 362;
			}
			if (num2 == 348 && rand() % 2 == 0)
			{
				num2 = 363;
			}
			if (num2 == 341)
			{
				num2 = Random(341, 346);
			}
			m_decor[cel.x][cel.y].icon = num2;
			return;
		}
	}
	num2 = m_decor[cel.x][cel.y].icon;
	if (num2 == -1 || (num2 >= 264 && num2 <= 282))
	{
		num = 15;
		if (!IsFromage(cel + POINT{ 0,1 }))
		{
			num &= -2;
		}
		if (!IsFromage(cel - POINT{ 0,1 }))
		{
			num &= -3;
		}
		if (!IsFromage(cel + POINT{ 1,0 }))
		{
			num &= -5;
		}
		if (!IsFromage(cel - POINT{ 1,0 }))
		{
			num &= -9;
		}
		num2 = table_adapt_fromage[num];
		if (num2 == 268 && rand() % 2 == 0)
		{
			num2 = 279;
		}
		if (num2 == 269 && rand() % 2 == 0)
		{
			num2 = 280;
		}
		if (num2 == 264 && rand() % 2 == 0)
		{
			num2 = 281;
		}
		if (num2 == 265 && rand() % 2 == 0)
		{
			num2 = 282;
		}
		m_decor[cel.x][cel.y].icon = num2;
	}
	num2 = m_decor[cel.x][cel.y].icon;
	if (num2 == -1 || (num2 >= 285 && num2 <= 303 && num2 != 301))
	{
		num = 15;
		if (!IsGrotte(cel+POINT{0,1}))
		{
			num &= -2;
		}
		if (!IsGrotte(cel-POINT{0,1}))
		{
			num &= -3;
		}
		if (!IsGrotte(cel+POINT{1,0}))
		{
			num &= -5;
		}
		if (!IsGrotte(cel-POINT{1,0}))
		{
			num &= -9;
		}
		num2 = table_adapt_fromage[num + 16];
		if (num2 == 289 && rand() % 2 == 0)
		{
			num2 = 300;
		}
		if (num2 == 285 && rand() % 2 == 0)
		{
			num2 = 302;
		}
		if (num2 == 286 && rand() % 2 == 0)
		{
			num2 = 303;
		}
		m_decor[cel.x][cel.y].icon = num2;
	}
}

void CDecor::AdaptBorder(POINT cel)
{
	AdaptMidBorder(cel);
	AdaptMidBorder(cel + POINT{1, 0});
	AdaptMidBorder(cel - POINT{1, 0});
	AdaptMidBorder(cel + POINT{ 0,1 });
	AdaptMidBorder(cel - POINT{ 0,1 });
	int icon = m_decor[cel.x][cel.y].icon;
	if (icon != -1 && !IsPassIcon(icon))
	{
		MoveObjectDelete(cel);
	}
	icon = m_decor[cel.x][cel.y].icon;
	if (icon == 304)
	{
		for (int i = 0; i < 4; i++)
		{
			cel.y++;
			if (cel.y >= 100)
			{
				break;
			}
			icon = m_decor[cel.x][cel.y].icon;
			if (icon != -1)
			{
				break;
			}
			m_decor[cel.x][cel.y].icon = 305;
		}
	}
	if (icon == -1)
	{
		for (int i = 0; i < 4; i++)
		{
			cel.y++;
			if (cel.y >= 100)
			{
				return;
			}
			icon = m_decor[cel.x][cel.y].icon;
			if (icon != 305)
			{
				return;
			}
			m_decor[cel.x][cel.y].icon = -1;
		}
	}
}
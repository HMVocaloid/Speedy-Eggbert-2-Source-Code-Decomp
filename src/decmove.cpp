// DecMove.cpp
//

#include "def.h"
#include "decor.h"
#include "misc.h"
#include "dectables.h"


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


void CDecor::MoveObjectPollution()
{
}

void CDecor::MoveObjectPlouf(POINT pos)
{
	for (int i = 0; i < MAXMOVEOBJECT; i++)
	{
		if (m_moveObject[i].type == 14)
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
		if (m_moveObject[i].type == 35)
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
		int icon = m_decor[(tinyPoint.x + 16) / DIMOBJX][tinyPoint.y / DIMOBJY].icon;
		if (icon != 91 && icon != 92)
		{
			break;
		}
		num++;
		tinyPoint.y -= DIMOBJY;
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
	m_moveObject[num2].type = 15;
	m_moveObject[num2].phase = 0;
	m_moveObject[num2].posCurrent.x = pos.x;
	m_moveObject[num2].posCurrent.y = pos.y;
	m_moveObject[num2].posStart = m_moveObject[num2].posCurrent;
	m_moveObject[num2].posEnd.x = pos.x;
	m_moveObject[num2].posEnd.y = pos.y - num * DIMOBJY;
	m_moveObject[num2].timeStopStart = 0;
	m_moveObject[num2].stepAdvance = num * 10;
	m_moveObject[num2].step = 2;
	m_moveObject[num2].time = 0;
	MoveObjectStepIcon(num2);
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
	pos.x = (pos.x + DIMOBJX / 2) / DIMOBJX;
	pos.y = (pos.y + DIMOBJY / 2) / DIMOBJY;
	if (!IsValidCel(pos)) return FALSE;
	int num = pos.y * 13;
	num += pos.x / 8;
	int num2 = pos.x & 7;
	return (m_balleTraj[num] & 1 << num2) != 0;
}

void CDecor::FlushMoveTraj()
{
	memset(m_moveTraj, 0, sizeof(m_moveTraj));
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
	while (pos.x >= 0 && pos.x < 100 && pos.y >= 0 && pos.y < 100 && !IsBlocIcon(m_decor[pos.x][pos.y].icon))
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

BOOL CDecor::ObjectStart(POINT pos, int type, int speed)
{
	return ObjectStart(pos, type, speed, FALSE);
}

BOOL CDecor::ObjectStart(POINT pos, int type, int speed, BOOL bMulti)
{
	int num = MoveObjectFree();
	if (num == -1)
	{
		return FALSE;
	}
	m_moveObject[num].type = type;
	m_moveObject[num].phase = 0;
	m_moveObject[num].posCurrent = pos;
	m_moveObject[num].posStart = pos;
	m_moveObject[num].posEnd = pos;
	MoveObjectStepIcon(num);
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
			if (type == TYPE_BALLE)
			{
				m_moveObject[num].type = 0;
				return TRUE;
			}
		}
		else
		{
			m_moveObject[num].posEnd = tinyPoint;
			m_moveObject[num].timeStopStart = 0;
			m_moveObject[num].stepAdvance = abs(num2 * num3 / 64);
			m_moveObject[num].step = STEP_ADVANCE;
			m_moveObject[num].time = 0;
		}
	}
	MoveObjectPriority(num);
	if (bMulti)
	{
		NetMessage msg;
		msg.data1 = speed;
		msg.type = MESS_OBJECTSTART;
		msg.x = pos.x;
		msg.y = pos.y;
		msg.channel = type;
		NetMessagePush(&msg);
	}
	return TRUE;
}

BOOL CDecor::ObjectDelete(POINT pos, int type)
{
	int num = MoveObjectSearch(pos, type);
	if (num == -1)
	{
		return FALSE;
	}
	if (m_moveObject[num].type == 4 ||
		m_moveObject[num].type == 12 ||
		m_moveObject[num].type == 16 ||
		m_moveObject[num].type == 17 ||
		m_moveObject[num].type == 20 ||
		m_moveObject[num].type == 40 ||
		m_moveObject[num].type == 96 ||
		m_moveObject[num].type == 97)
	{
		int num2 = 17;
		double animationSpeed = 1.0;
		if (m_moveObject[num].type == 4)
		{
			num2 = 7;
		}
		if (m_moveObject[num].type == 17 || m_moveObject[num].type == 20)
		{
			num2 = 33;
		}
		if (m_moveObject[num].type == 40)
		{
			animationSpeed = 0.5;
		}
		
	}
	m_moveObject[num].type = 0;
	return TRUE;
}

void CDecor::MoveObjectStep()
{
	m_blupiVector = { 0, 0 };
	m_blupiTransport = -1;
	for (int i = 0; i < MAXMOVEOBJECT; i++)
	{
		if (m_moveObject[i].type != 0)
		{
			MoveObjectStepLine(i);
			MoveObjectStepIcon(i);
			if (m_moveObject[i].type == TYPE_BULLDOZER ||
				m_moveObject[i].type == TYPE_BLUPITANK ||
				m_moveObject[i].type == TYPE_BLUPIHELICO)
			{
				int num = MovePersoDetect(m_moveObject[i].posCurrent);
				if (num != -1)
				{
					POINT posCurrent = m_moveObject[i].posCurrent;
					posCurrent.x -= 34;
					posCurrent.y -= 34;
					ObjectStart(posCurrent, TYPE_EXPLO1, 0, TRUE);
					PlaySound(10, m_moveObject[i].posCurrent);
					m_decorAction = 1;
					m_decorPhase = 0;
					posCurrent = m_moveObject[i].posCurrent;
					posCurrent.x += 2;
					posCurrent.y += BLUPIOFFY;
					ObjectDelete(m_moveObject[i].posCurrent, m_moveObject[i].type);
					ObjectStart(posCurrent, 37, 0);
					ObjectDelete(m_moveObject[num].posCurrent, m_moveObject[num].type);
				}
				if (BlupiElectro(m_moveObject[i].posCurrent))
				{
					POINT posCurrent = m_moveObject[i].posCurrent;
					posCurrent.x += 2;
					posCurrent.y += BLUPIOFFY;
					ObjectDelete(m_moveObject[i].posCurrent, m_moveObject[i].type);
					ObjectStart(posCurrent, 38, 55);
					PlaySound(59, posCurrent);
				}
			}
		}
	}
}

void CDecor::MoveObjectStepLine(int i)
{
	MoveObject moveObject;
	POINT tinyPoint;
	BOOL flag = FALSE;
	RECT tinyRect;
	if (m_moveObject[i].type == 1 || m_moveObject[i].type == 47 || m_moveObject[i].type == 48 && !m_blupiSuspend)
	{
		RECT src;
		src.left = m_blupiPos.x + 20;
		src.right = m_blupiPos.x + 60 - 20;
		src.top = m_blupiPos.y + 60 - 2;
		src.bottom = m_blupiPos.y + 60 - 1;
		tinyRect.left = m_moveObject[i].posCurrent.x;
		tinyRect.right = m_moveObject[i].posCurrent.x + 64;
		tinyRect.top = m_moveObject[i].posCurrent.y;
		tinyRect.bottom = m_moveObject[i].posCurrent.y + 16;
		RECT tinyRect2;
		flag = IntersectRect(tinyRect2, tinyRect, src);
		tinyPoint = m_moveObject[i].posCurrent;
	}
	POINT posCurrent;
	if (m_blupiFocus && !m_blupiHide && m_moveObject[i].type == 97)
	{
		posCurrent = m_moveObject[i].posCurrent;
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
		if (TestPath(tinyRect, m_moveObject[i].posCurrent, posCurrent))
		{
			m_moveObject[i].posCurrent = posCurrent;
			m_moveObject[i].posStart = posCurrent;
			m_moveObject[i].posEnd = posCurrent;
		}
		else
		{
			ObjectDelete(m_moveObject[i].posCurrent, m_moveObject[i].type);
			posCurrent.x -= 34;
			posCurrent.y -= 34;
			ObjectStart(posCurrent, 9, 0);
			PlaySound(10, posCurrent);
			m_decorAction = 1;
			m_decorPhase = 0;
		}
	}
	if (m_moveObject[i].posStart.x != m_moveObject[i].posEnd.x || m_moveObject[i].posStart.y != m_moveObject[i].posEnd.y)
	{
		if (m_moveObject[i].step == 1)
		{
			if (m_moveObject[i].time < m_moveObject[i].timeStopStart)
			{
				m_moveObject[i].time = m_moveObject[i].time + 1;
			}
			else
			{
				m_moveObject[i].step = 2;
				m_moveObject[i].time = 0;
			}
		}
		else if (m_moveObject[i].step == 2)
		{
			if (m_moveObject[i].posCurrent.x != m_moveObject[i].posEnd.x || m_moveObject[i].posCurrent.x != m_moveObject[i].posEnd.y)
			{
				m_moveObject[i].time ++;
				if (m_moveObject[i].stepAdvance != 0)
				{
					m_moveObject[i].posCurrent.x = (m_moveObject[i].posEnd.x - m_moveObject[i].posStart.x) * m_moveObject[i].time / m_moveObject[i].stepAdvance + m_moveObject[i].posStart.x;
					m_moveObject[i].posCurrent.y = (m_moveObject[i].posEnd.y - m_moveObject[i].posStart.y) * m_moveObject[i].time / m_moveObject[i].stepAdvance + m_moveObject[i].posStart.y;
				}

			}
			else if (m_moveObject[i].type == 15 || m_moveObject[i].type == 23)
			{
				m_moveObject[i].type = 0;
			}
			else if (m_moveObject[i].type == 34)
			{
				m_moveObject[i].posStart = m_moveObject[i].posCurrent;
				m_moveObject[i].posEnd = m_moveObject[i].posCurrent;
				m_moveObject[i].step = 3;
				m_moveObject[i].time = 0;
			}
			else
			{
				m_moveObject[i].step = 3;
				m_moveObject[i].time = 0;
			}
		}
		else if (m_moveObject[i].step == 3)
		{
			if (m_moveObject[i].time < m_moveObject[i].timeStopEnd)
			{
				m_moveObject[i].time ++;
			}
			else
			{
				m_moveObject[i].step = 4;
				m_moveObject[i].time = 0;
			}
		}
		else if (m_moveObject[i].step == 4)
		{
			if (m_moveObject[i].posCurrent.x != m_moveObject[i].posStart.x || m_moveObject[i].posCurrent.y != m_moveObject[i].posStart.y)
			{
				m_moveObject[i].time ++;
				if (m_moveObject[i].stepRecede != 0)
				{
					m_moveObject[i].posCurrent.x = (m_moveObject[i].posStart.x - m_moveObject[i].posEnd.x) *
						m_moveObject[i].time / m_moveObject[i].stepRecede + m_moveObject[i].posEnd.x;
					m_moveObject[i].posCurrent.y = (m_moveObject[i].posStart.y - m_moveObject[i].posEnd.y) *
						m_moveObject[i].time / m_moveObject[i].stepRecede + m_moveObject[i].posEnd.y;
				}
			}
			else
			{
				m_moveObject[i].step = 1;
				m_moveObject[i].time = 0;
			}
		}
	}
	if (m_moveObject[i].type == 22 && m_moveObject[i].step == 3)
	{
		m_moveObject[i].type = 0;
	}
	posCurrent = m_moveObject[i].posCurrent;
	if (m_moveObject[i].type == 1 || m_moveObject[i].type == 47 || m_moveObject[i].type == 48)
	{
		posCurrent.y -= 64;
	}
	posCurrent.x = (posCurrent.x + 32) / 64;
	posCurrent.y = (posCurrent.y + 32) / 64;
	SetMoveTraj(posCurrent);
	if (flag)
	{
		m_blupiVector.x = m_moveObject[i].posCurrent.x - tinyPoint.x;
		m_blupiVector.y = m_moveObject[i].posCurrent.y - (m_blupiPos.y + 60 - BLUPIFLOOR);
		if (m_moveObject[i].type == 47)
		{
			m_blupiVector.x = m_blupiVector.x + 2;
		}
		if (m_moveObject[i].type == 48)
		{
			m_blupiVector.x = m_blupiVector.x - 2;
		}
		if (m_blupiTimeNoAsc == 0)
		{
			m_blupiTransport = i;
		}
	}
}

void CDecor::MoveObjectStepIcon(int i)
{
	POINT pos;
	if (m_moveObject[i].type == 47)
	{
		m_moveObject[i].icon = table_chenille[m_moveObject[i].phase / 1 % 6];
	}
	if (m_moveObject[i].type == 48)
	{
		m_moveObject[i].icon = table_chenillei[m_moveObject[i].phase / 1 % 6];
	}
	if (m_moveObject[i].type == 2)
	{
		m_moveObject[i].icon = 12 + m_moveObject[i].phase / 2 % 9;
		m_moveObject[i].channel = 10;
	}
	if (m_moveObject[i].type == 3)
	{
		m_moveObject[i].icon = 48 + m_moveObject[i].phase / 2 % 9;
		m_moveObject[i].channel = 10;
	}
	if (m_moveObject[i].type == 16)
	{
		m_moveObject[i].icon = 69 + m_moveObject[i].phase / 1 % 9;
		m_moveObject[i].channel = 10;
	}
	if (m_moveObject[i].type == 96)
	{
		m_moveObject[i].icon = table_follow1[m_moveObject[i].phase / 1 % 26];
		m_moveObject[i].channel = 10;
	}
	if (m_moveObject[i].type == 97)
	{
		m_moveObject[i].icon = table_follow2[m_moveObject[i].phase / 1 % 5];
		m_moveObject[i].channel = 10;
	}
	if (m_moveObject[i].type == 200)
	{
		m_moveObject[i].icon = 257 + m_moveObject[i].phase / 1 % 6;
		m_moveObject[i].channel = 2;
	}
	if (m_moveObject[i].type == 201)
	{
		m_moveObject[i].icon = 257 + m_moveObject[i].phase / 1 % 6;
		m_moveObject[i].channel = 11;
	}
	if (m_moveObject[i].type == 202)
	{
		m_moveObject[i].icon = 257 + m_moveObject[i].phase / 1 % 6;
		m_moveObject[i].channel = 12;
	}
	if (m_moveObject[i].type == 203)
	{
		m_moveObject[i].icon = 257 + m_moveObject[i].phase / 1 % 6;
		m_moveObject[i].channel = 13;
	}
	if (m_moveObject[i].type == 55)
	{
		m_moveObject[i].icon = 252;
		m_moveObject[i].channel = 10;
	}
	if (m_moveObject[i].type == 56)
	{
		m_moveObject[i].icon = table_dynamitef[m_moveObject[i].phase / 1 % 100];
		m_moveObject[i].channel = 10;
		if (m_moveObject[i].phase == 50)
		{
			DynamiteStart(i, 0, 0);
		}
		if (m_moveObject[i].phase == 53)
		{
			DynamiteStart(i, -100, 8);
		}
		if (m_moveObject[i].phase == 55)
		{
			DynamiteStart(i, 80, 10);
		}
		if (m_moveObject[i].phase == 56)
		{
			DynamiteStart(i, -15, -100);
		}
		if (m_moveObject[i].phase == 59)
		{
			DynamiteStart(i, 20, 70);
		}
		if (m_moveObject[i].phase == 62)
		{
			DynamiteStart(i, 30, -50);
		}
		if (m_moveObject[i].phase == 64)
		{
			DynamiteStart(i, -40, 30);
		}
		if (m_moveObject[i].phase == 67)
		{
			DynamiteStart(i, -180, 10);
		}
		if (m_moveObject[i].phase == 69)
		{
			DynamiteStart(i, 200, -10);
		}
		if (m_moveObject[i].phase >= 70)
		{
			m_moveObject[i].type = 0;
		}
	}
	if (m_moveObject[i].type == 5)
	{
		if (m_moveObject[i].phase / 3 % 22 < 11)
		{
			m_moveObject[i].icon = m_moveObject[i].phase / 3 % 11;
		}
		else
		{
			m_moveObject[i].icon = 11 - m_moveObject[i].phase / 3 % 11;
		}
		m_moveObject[i].channel = 10;
	}
	if (m_moveObject[i].type == 6)
	{
		m_moveObject[i].icon = 21 + m_moveObject[i].phase / 4 % 8;
		m_moveObject[i].channel = 10;
	}
	if (m_moveObject[i].type == 7)
	{
		m_moveObject[i].icon = 29 + m_moveObject[i].phase / 3 % 8;
		m_moveObject[i].channel = 10;
	}
	if (m_moveObject[i].type == 21)
	{
		m_moveObject[i].icon = table_cle[m_moveObject[i].phase / 3 % 12];
		m_moveObject[i].channel = 10;
	}
	if (m_moveObject[i].type == 49)
	{
		m_moveObject[i].icon = table_cle1[m_moveObject[i].phase / 3 % 12];
		m_moveObject[i].channel = 10;
	}
	if (m_moveObject[i].type == 50)
	{
		m_moveObject[i].icon = table_cle2[m_moveObject[i].phase / 3 % 12];
		m_moveObject[i].channel = 10;
	}
	if (m_moveObject[i].type == 51)
	{
		m_moveObject[i].icon = table_cle3[m_moveObject[i].phase / 3 % 12];
		m_moveObject[i].channel = 10;
	}
	if (m_moveObject[i].type == 24)
	{
		m_moveObject[i].icon = table_skate[m_moveObject[i].phase / 1 % 34];
		m_moveObject[i].channel = 10;
	}
	if (m_moveObject[i].type == 25)
	{
		m_moveObject[i].icon = table_shield[m_moveObject[i].phase / 2 % 16];
		m_moveObject[i].channel = 10;
	}
	if (m_moveObject[i].type == 26)
	{
		m_moveObject[i].icon = table_power[m_moveObject[i].phase / 2 % 8];
		m_moveObject[i].channel = 10;
	}
	if (m_moveObject[i].type == 40)
	{
		m_moveObject[i].icon = table_invert[m_moveObject[i].phase / 2 % 20];
		m_moveObject[i].channel = 10;
	}
	if (m_moveObject[i].type == 31)
	{
		m_moveObject[i].icon = table_charge[m_moveObject[i].phase / 2 % 6];
		m_moveObject[i].channel = 1;
	}
	if (m_moveObject[i].type == 27)
	{
		m_moveObject[i].icon = table_magictrack[m_moveObject[i].phase / 1 % 24];
		m_moveObject[i].channel = 10;
		if (m_moveObject[i].phase >= 24)
		{
			m_moveObject[i].type = 0;
		}
	}
	if (m_moveObject[i].type == 57)
	{
		m_moveObject[i].icon = table_shieldtrack[m_moveObject[i].phase / 1 % 20];
		m_moveObject[i].channel = 10;
		if (m_moveObject[i].phase >= 20)
		{
			m_moveObject[i].type = 0;
		}
	}
	if (m_moveObject[i].type == 39)
	{
		m_moveObject[i].icon = table_tresortrack[m_moveObject[i].phase / 1 % 11];
		m_moveObject[i].channel = 10;
		if (m_moveObject[i].phase >= 11)
		{
			m_moveObject[i].type = 0;
		}
	}
	if (m_moveObject[i].type == 58 && m_moveObject[i].phase >= 20)
	{
		m_moveObject[i].type = 0;
	}
	if (m_moveObject[i].type == 8)
	{
		if (m_moveObject[i].phase >= table_explo1[0])
		{
			m_moveObject[i].type = 0;
		}
		else
		{
			m_moveObject[i].icon = table_explo1[m_moveObject[i].phase];
			m_moveObject[i].channel = 9;
		}
	}
	if (m_moveObject[i].type == 9)
	{
		if (m_moveObject[i].phase >= 20)
		{
			m_moveObject[i].type = 0;
		}
		else
		{
			m_moveObject[i].icon = table_explo2[m_moveObject[i].phase % 20];
			m_moveObject[i].channel = 9;
		}
	}
	if (m_moveObject[i].type == 10)
	{
		if (m_moveObject[i].phase >= 20)
		{
			m_moveObject[i].type = 0;
		}
		else
		{
			m_moveObject[i].icon = table_explo3[m_moveObject[i].phase / 1 % 20];
			m_moveObject[i].channel = 9;
		}
	}
	if (m_moveObject[i].type == 11)
	{
		if (m_moveObject[i].phase >= 9)
		{
			m_moveObject[i].type = 0;
		}
		else
		{
			m_moveObject[i].icon = table_explo4[m_moveObject[i].phase / 1 % 9];
			m_moveObject[i].channel = 9;
		}
	}
	if (m_moveObject[i].type == 90)
	{
		if (m_moveObject[i].phase >= 12)
		{
			m_moveObject[i].type = 0;
		}
		else
		{
			m_moveObject[i].icon = table_explo5[m_moveObject[i].phase / 1 % 12];
			m_moveObject[i].channel = 9;
		}
	}
	if (m_moveObject[i].type == 91)
	{
		if (m_moveObject[i].phase >= 6)
		{
			m_moveObject[i].type = 0;
		}
		else
		{
			m_moveObject[i].icon = table_explo6[m_moveObject[i].phase / 1 % 6];
			m_moveObject[i].channel = 9;
		}
	}
	if (m_moveObject[i].type == 92)
	{
		if (m_moveObject[i].phase >= 128)
		{
			m_moveObject[i].type = 0;
		}
		else
		{
			m_moveObject[i].icon = table_explo7[m_moveObject[i].phase / 1 % 128];
			m_moveObject[i].channel = 9;
		}
	}
	if (m_moveObject[i].type == 93)
	{
		if (m_moveObject[i].phase >= 5)
		{
			m_moveObject[i].type = 0;
		}
		else
		{
			m_moveObject[i].icon = table_explo8[m_moveObject[i].phase / 1 % 5];
			m_moveObject[i].channel = 9;
		}
	}
	if (m_moveObject[i].type == 98)
	{
		if (m_moveObject[i].phase >= 10)
		{
			m_moveObject[i].type = 0;
		}
		else
		{
			m_moveObject[i].icon = table_sploutch1[m_moveObject[i].phase / 1 % 10];
			m_moveObject[i].channel = 9;
		}
	}
	if (m_moveObject[i].type == 99)
	{
		if (m_moveObject[i].phase >= 13)
		{
			m_moveObject[i].type = 0;
		}
		else
		{
			m_moveObject[i].icon = table_sploutch2[m_moveObject[i].phase / 1 % 13];
			m_moveObject[i].channel = 9;
		}
	}
	if (m_moveObject[i].type == 100)
	{
		if (m_moveObject[i].phase >= 18)
		{
			m_moveObject[i].type = 0;
		}
		else
		{
			m_moveObject[i].icon = table_sploutch3[m_moveObject[i].phase / 1 % 18];
			m_moveObject[i].channel = 9;
		}
	}
	if (m_moveObject[i].type == 53)
	{
		if (m_moveObject[i].phase >= 90)
		{
			m_moveObject[i].type = 0;
		}
		else
		{
			m_moveObject[i].icon = table_tentacule[m_moveObject[i].phase / 2 % 45];
			m_moveObject[i].channel = 9;
		}
	}
	if (m_moveObject[i].type == 52)
	{
		if (m_moveObject[i].phase == 0)
		{
			PlaySound(72, m_moveObject[i].posStart);
		}
		if (m_moveObject[i].phase == 137)
		{
			PlaySound(73, m_moveObject[i].posStart);
		}
		if (m_moveObject[i].phase >= 157)
		{
			m_moveObject[i].type = 0;
		}
		else
		{
			m_moveObject[i].icon = table_bridge[m_moveObject[i].phase / 1 % 157];
			m_moveObject[i].channel = 1;
			pos.x = m_moveObject[i].posStart.x / 64;
			pos.y = m_moveObject[i].posStart.y / 64;
			m_decor[pos.x][pos.y].icon = m_moveObject[i].icon;
		}
	}
	if (m_moveObject[i].type == 36)
	{
		if (m_moveObject[i].phase >= 16)
		{
			m_moveObject[i].type = 0;
		}
		else
		{
			m_moveObject[i].icon = table_pollution[m_moveObject[i].phase / 2 % 8];
			m_moveObject[i].channel = 10;
		}
	}
	if (m_moveObject[i].type == 41)
	{
		if (m_moveObject[i].phase >= 16)
		{
			m_moveObject[i].type = 0;
		}
		else
		{
			m_moveObject[i].icon = table_invertstart[m_moveObject[i].phase / 2 % 8];
			m_moveObject[i].channel = 10;
		}
	}
	if (m_moveObject[i].type == 42)
	{
		if (m_moveObject[i].phase >= 16)
		{
			m_moveObject[i].type = 0;
		}
		else
		{
			m_moveObject[i].icon = table_invertstop[m_moveObject[i].phase / 2 % 8];
			m_moveObject[i].channel = 10;
		}
	}
	if (m_moveObject[i].type == 14)
	{
		if (m_moveObject[i].phase >= 14)
		{
			m_moveObject[i].type = 0;
		}
		else
		{
			m_moveObject[i].icon = table_plouf[m_moveObject[i].phase / 2 % 7];
			m_moveObject[i].channel = 1;
		}
	}
	if (m_moveObject[i].type == 35)
	{
		if (m_moveObject[i].phase >= 6)
		{
			m_moveObject[i].type = 0;
		}
		else
		{
			m_moveObject[i].icon = table_tiplouf[m_moveObject[i].phase / 2 % 7];
			m_moveObject[i].channel = 1;
		}
	}
	if (m_moveObject[i].type == 15)
	{
		m_moveObject[i].icon = table_blup[m_moveObject[i].phase / 2 % 20];
		m_moveObject[i].channel = 1;
	}
	if (m_moveObject[i].type == 4)
	{
		if (m_moveObject[i].posStart.x > m_moveObject[i].posEnd.x)
		{
			if (m_moveObject[i].step == 1)
			{
				m_moveObject[i].icon = table_bulldozer_turn2l[m_moveObject[i].time % 22];
			}
			if (m_moveObject[i].step == 3)
			{
				m_moveObject[i].icon = table_bulldozer_turn2r[m_moveObject[i].time % 22];
			}
			if (m_moveObject[i].step == 2)
			{
				m_moveObject[i].icon = table_bulldozer_left[m_moveObject[i].time % 8];
			}
			if (m_moveObject[i].step == 4)
			{
				m_moveObject[i].icon = table_bulldozer_right[m_moveObject[i].time % 8];
			}
		}
		else
		{
			if (m_moveObject[i].step == 1)
			{
				m_moveObject[i].icon = table_bulldozer_turn2r[m_moveObject[i].time % 22];
			}
			if (m_moveObject[i].step == 3)
			{
				m_moveObject[i].icon = table_bulldozer_turn2l[m_moveObject[i].time % 22];
			}
			if (m_moveObject[i].step == 2)
			{
				m_moveObject[i].icon = table_bulldozer_right[m_moveObject[i].time % 8];
			}
			if (m_moveObject[i].step == 4)
			{
				m_moveObject[i].icon = table_bulldozer_left[m_moveObject[i].time % 8];
			}
		}
		m_moveObject[i].channel = 10;
	}
	if (m_moveObject[i].type == 17)
	{
		if (m_moveObject[i].posStart.x > m_moveObject[i].posEnd.x)
		{
			if (m_moveObject[i].step == 1)
			{
				m_moveObject[i].icon = table_poisson_turn2l[m_moveObject[i].time % 48];
			}
			if (m_moveObject[i].step == 3)
			{
				m_moveObject[i].icon = table_poisson_turn2r[m_moveObject[i].time % 48];
			}
			if (m_moveObject[i].step == 2)
			{
				m_moveObject[i].icon = table_poisson_left[m_moveObject[i].time % 8];
			}
			if (m_moveObject[i].step == 4)
			{
				m_moveObject[i].icon = table_poisson_right[m_moveObject[i].time % 8];
			}
		}
		else
		{
			if (m_moveObject[i].step == 1)
			{
				m_moveObject[i].icon = table_poisson_turn2r[m_moveObject[i].time % 48];
			}
			if (m_moveObject[i].step == 3)
			{
				m_moveObject[i].icon = table_poisson_turn2l[m_moveObject[i].time % 48];
			}
			if (m_moveObject[i].step == 2)
			{
				m_moveObject[i].icon = table_poisson_right[m_moveObject[i].time % 8];
			}
			if (m_moveObject[i].step == 4)
			{
				m_moveObject[i].icon = table_poisson_left[m_moveObject[i].time % 8];
			}
		}
		m_moveObject[i].channel = 10;
	}
	if (m_moveObject[i].type == 20)
	{
		if (m_moveObject[i].posStart.x > m_moveObject[i].posEnd.x)
		{
			if (m_moveObject[i].step == 1)
			{
				m_moveObject[i].icon = table_oiseau_turn2l[m_moveObject[i].time % 10];
			}
			if (m_moveObject[i].step == 3)
			{
				m_moveObject[i].icon = table_oiseau_turn2r[m_moveObject[i].time % 10];
			}
			if (m_moveObject[i].step == 2)
			{
				m_moveObject[i].icon = table_oiseau_left[m_moveObject[i].time % 8];
			}
			if (m_moveObject[i].step == 4)
			{
				m_moveObject[i].icon = table_oiseau_right[m_moveObject[i].time % 8];
			}
		}
		else
		{
			if (m_moveObject[i].step == 1)
			{
				m_moveObject[i].icon = table_oiseau_turn2r[m_moveObject[i].time % 10];
			}
			if (m_moveObject[i].step == 3)
			{
				m_moveObject[i].icon = table_oiseau_turn2l[m_moveObject[i].time % 10];
			}
			if (m_moveObject[i].step == 2)
			{
				m_moveObject[i].icon = table_oiseau_right[m_moveObject[i].time % 8];
			}
			if (m_moveObject[i].step == 4)
			{
				m_moveObject[i].icon = table_oiseau_left[m_moveObject[i].time % 8];
			}
		}
		m_moveObject[i].channel = 10;
	}
	if (m_moveObject[i].type == 44)
	{
		if (m_moveObject[i].posStart.x > m_moveObject[i].posEnd.x)
		{
			if (m_moveObject[i].step == 1)
			{
				m_moveObject[i].icon = table_guepe_turn2l[m_moveObject[i].time % 5];
			}
			if (m_moveObject[i].step == 3)
			{
				m_moveObject[i].icon = table_guepe_turn2r[m_moveObject[i].time % 5];
			}
			if (m_moveObject[i].step == 2)
			{
				m_moveObject[i].icon = table_guepe_left[m_moveObject[i].time % 6];
			}
			if (m_moveObject[i].step == 4)
			{
				m_moveObject[i].icon = table_guepe_right[m_moveObject[i].time % 6];
			}
		}
		else
		{
			if (m_moveObject[i].step == 1)
			{
				m_moveObject[i].icon = table_guepe_turn2r[m_moveObject[i].time % 5];
			}
			if (m_moveObject[i].step == 3)
			{
				m_moveObject[i].icon = table_guepe_turn2l[m_moveObject[i].time % 5];
			}
			if (m_moveObject[i].step == 2)
			{
				m_moveObject[i].icon = table_guepe_right[m_moveObject[i].time % 6];
			}
			if (m_moveObject[i].step == 4)
			{
				m_moveObject[i].icon = table_guepe_left[m_moveObject[i].time % 6];
			}
		}
		m_moveObject[i].channel = 10;
	}
	if (m_moveObject[i].type == 54)
	{
		if (m_moveObject[i].posStart.x > m_moveObject[i].posEnd.x)
		{
			if (m_moveObject[i].step == 1)
			{
				m_moveObject[i].icon = table_creature_turn2[m_moveObject[i].time % 152];
			}
			if (m_moveObject[i].step == 3)
			{
				m_moveObject[i].icon = table_creature_turn2[m_moveObject[i].time % 152];
			}
			if (m_moveObject[i].step == 2)
			{
				m_moveObject[i].icon = table_creature_left[m_moveObject[i].time % 8];
			}
			if (m_moveObject[i].step == 4)
			{
				m_moveObject[i].icon = table_creature_right[m_moveObject[i].time % 8];
			}
		}
		else
		{
			if (m_moveObject[i].step == 1)
			{
				m_moveObject[i].icon = table_creature_turn2[m_moveObject[i].time % 152];
			}
			if (m_moveObject[i].step == 3)
			{
				m_moveObject[i].icon = table_creature_turn2[m_moveObject[i].time % 152];
			}
			if (m_moveObject[i].step == 2)
			{
				m_moveObject[i].icon = table_creature_right[m_moveObject[i].time % 8];
			}
			if (m_moveObject[i].step == 4)
			{
				m_moveObject[i].icon = table_creature_left[m_moveObject[i].time % 8];
			}
		}
		m_moveObject[i].channel = 10;
	}
	if (m_moveObject[i].type == 32)
	{
		if (m_moveObject[i].posStart.x > m_moveObject[i].posEnd.x)
		{
			if (m_moveObject[i].step == 1)
			{
				m_moveObject[i].icon = table_blupih_turn2l[m_moveObject[i].time % 26];
			}
			if (m_moveObject[i].step == 3)
			{
				m_moveObject[i].icon = table_blupih_turn2r[m_moveObject[i].time % 26];
			}
			if (m_moveObject[i].step == 2)
			{
				m_moveObject[i].icon = table_blupih_left[m_moveObject[i].time % 8];
			}
			if (m_moveObject[i].step == 4)
			{
				m_moveObject[i].icon = table_blupih_right[m_moveObject[i].time % 8];
			}
		}
		else
		{
			if (m_moveObject[i].step == 1)
			{
				m_moveObject[i].icon = table_blupih_turn2r[m_moveObject[i].time % 26];
			}
			if (m_moveObject[i].step == 3)
			{
				m_moveObject[i].icon = table_blupih_turn2l[m_moveObject[i].time % 26];
			}
			if (m_moveObject[i].step == 2)
			{
				m_moveObject[i].icon = table_blupih_right[m_moveObject[i].time % 8];
			}
			if (m_moveObject[i].step == 4)
			{
				m_moveObject[i].icon = table_blupih_left[m_moveObject[i].time % 8];
			}
		}
		if ((m_moveObject[i].step == 1 || m_moveObject[i].step == 3) && m_moveObject[i].time == 21)
		{
			pos.x = m_moveObject[i].posCurrent.x;
			pos.y = m_moveObject[i].posCurrent.y + 40;
			if (ObjectStart(pos, 23, 55) != -1)
			{
				PlaySound(52, pos);
			}
		}
	}
	if (m_moveObject[i].type == 33)
	{
		if (m_moveObject[i].posStart.x > m_moveObject[i].posEnd.x)
		{
			if (m_moveObject[i].step == 1)
			{
				m_moveObject[i].icon = table_blupit_turn2l[m_moveObject[i].time % 24];
			}
			if (m_moveObject[i].step == 3)
			{
				m_moveObject[i].icon = table_blupit_turn2r[m_moveObject[i].time % 24];
			}
			if (m_moveObject[i].step == 2)
			{
				m_moveObject[i].icon = table_blupit_left[m_moveObject[i].time % 8];
			}
			if (m_moveObject[i].step == 4)
			{
				m_moveObject[i].icon = table_blupit_right[m_moveObject[i].time % 8];
			}
		}
		else
		{
			if (m_moveObject[i].step == 1)
			{
				m_moveObject[i].icon = table_blupit_turn2r[m_moveObject[i].time % 24];
			}
			if (m_moveObject[i].step == 3)
			{
				m_moveObject[i].icon = table_blupit_turn2l[m_moveObject[i].time % 24];
			}
			if (m_moveObject[i].step == 2)
			{
				m_moveObject[i].icon = table_blupit_right[m_moveObject[i].time % 8];
			}
			if (m_moveObject[i].step == 4)
			{
				m_moveObject[i].icon = table_blupit_left[m_moveObject[i].time % 8];
			}
		}
		if ((m_moveObject[i].step == 1 || m_moveObject[i].step == 3) && m_moveObject[i].time == 3)
		{
			int speed;
			if ((m_moveObject[i].posStart.x < m_moveObject[i].posEnd.x && m_moveObject[i].step == 1) || (m_moveObject[i].posStart.x > m_moveObject[i].posEnd.x && m_moveObject[i].step == 3))
			{
				pos.x = m_moveObject[i].posCurrent.x - 30;
				pos.y = m_moveObject[i].posCurrent.x + BLUPIOFFY;
				speed = -5;
			}
			else
			{
				pos.x = m_moveObject[i].posCurrent.x + 30;
				pos.y = m_moveObject[i].posCurrent.y + BLUPIOFFY;
				speed = 5;
			}
			if (ObjectStart(pos, 23, speed) != -1)
			{
				PlaySound(52, pos);
			}
		}
		if ((m_moveObject[i].step == 1 || m_moveObject[i].step == 3) && m_moveObject[i].time == 21)
		{
			int speed;
			if ((m_moveObject[i].posStart.x < m_moveObject[i].posEnd.x && m_moveObject[i].step == 1) || (m_moveObject[i].posStart.x > m_moveObject[i].posEnd.x && m_moveObject[i].step == 3))
			{
				pos.x = m_moveObject[i].posCurrent.x + 30;
				pos.y = m_moveObject[i].posCurrent.y + BLUPIOFFY;
				speed = 5;
			}
			else
			{
				pos.x = m_moveObject[i].posCurrent.x - 30;
				pos.y = m_moveObject[i].posCurrent.y + BLUPIOFFY;
				speed = -5;
			}
			if (ObjectStart(pos, 23, speed) != -1)
			{
				PlaySound(52, pos);
			}
		}
	}
	if (m_moveObject[i].type == 34)
	{
		m_moveObject[i].icon = table_glu[m_moveObject[i].phase / 1 % 25];
		m_moveObject[i].channel = 10;
	}
	if (m_moveObject[i].type == 37)
	{
		if (m_moveObject[i].phase >= 70)
		{
			m_moveObject[i].type = 0;
		}
		else
		{
			m_moveObject[i].icon = table_clear[m_moveObject[i].phase / 1 % 70];
			m_moveObject[i].channel = 10;
		}
	}
	if (m_moveObject[i].type == 38)
	{
		if (m_moveObject[i].phase >= 90)
		{
			m_moveObject[i].type = 0;
		}
		else
		{
			m_moveObject[i].icon = table_electro[m_moveObject[i].phase / 1 % 90];
			if (m_moveObject[i].phase < 30)
			{
				m_moveObject[i].channel = 12;
			}
			else
			{
				m_moveObject[i].channel = 10;
			}
		}
	}
	if (m_moveObject[i].type == 13)
	{
		m_moveObject[i].icon = 68;
		m_moveObject[i].channel = 10;
	}
	if (m_moveObject[i].type == 46)
	{
		m_moveObject[i].icon = 208;
		m_moveObject[i].channel = 10;
	}
	if (m_moveObject[i].type == 19)
	{
		m_moveObject[i].icon = 89;
		m_moveObject[i].channel = 10;
	}
	if (m_moveObject[i].type == 28)
	{
		m_moveObject[i].icon = 167;
		m_moveObject[i].channel = 10;
	}
	if (m_moveObject[i].type == 23)
	{
		m_moveObject[i].icon = 176;
		m_moveObject[i].channel = 10;
	}
	if (m_moveObject[i].type == 29)
	{
		m_moveObject[i].icon = 177;
		m_moveObject[i].channel = 10;
	}
	if (m_moveObject[i].type == 30)
	{
		m_moveObject[i].icon = 178;
		m_moveObject[i].channel = 10;
	}
	m_moveObject[i].phase ++;
	if (m_moveObject[i].phase > 32700)
	{
		m_moveObject[i].phase = 0;
	}
}

void CDecor::DynamiteStart(int i, int dx, int dy)
{
	POINT posStart = m_moveObject[i].posStart;
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
			if (tinyPoint.x >= 0 && tinyPoint.x < 100 && tinyPoint.y >= 0 && tinyPoint.y < 100)
			{
				int icon = m_decor[tinyPoint.x][tinyPoint.y].icon;
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
		if (m_moveObject[i].type == 2 || m_moveObject[i].type == 3 || m_moveObject[i].type == 96 || m_moveObject[i].type == 97 || m_moveObject[i].type == 4 ||
			m_moveObject[i].type == 6 || m_moveObject[i].type == 12 || m_moveObject[i].type == 13 || m_moveObject[i].type == 16 || m_moveObject[i].type == 17 ||
			m_moveObject[i].type == 19 || m_moveObject[i].type == 20 || m_moveObject[i].type == 24 || m_moveObject[i].type == 25 || m_moveObject[i].type == 26 || m_moveObject[i].type == 28 ||
			m_moveObject[i].type == 30 || m_moveObject[i].type == 32 || m_moveObject[i].type == 33 || m_moveObject[i].type == 34 || m_moveObject[i].type == 40 || m_moveObject[i].type == 44 ||
			m_moveObject[i].type == 46 || m_moveObject[i].type == 52 || m_moveObject[i].type == 54 || m_moveObject[i].type == 200 || m_moveObject[i].type == 201 || m_moveObject[i].type == 202 ||
			m_moveObject[i].type == 203)
		{
			RECT src2;
			src2.left = m_moveObject[i].posCurrent.x;
			src2.right = m_moveObject[i].posCurrent.x + 60;
			src2.top = m_moveObject[i].posCurrent.y;
			src2.bottom = m_moveObject[i].posCurrent.y + 20;
			RECT tinyRect;
			if (IntersectRect(tinyRect, src2, src))
			{
				if (m_moveObject[i].type == 12)
				{
					SearchLinkCaisse(i, TRUE);
					for (int l = 0; l < m_nbLinkCaisse; l++)
					{
						int channel = m_moveObject[m_linkCaisse[l]].channel;
						int icon2 = m_moveObject[m_linkCaisse[l]].icon;
						POINT posCurrent = m_moveObject[m_linkCaisse[l]].posCurrent;
						double num = (double)Random(7, 23);
						if (rand() % 2 == 0)
						{
							num = -num;
						}
						m_moveObject[m_linkCaisse[l]].type = 0;
					}
					ObjectDelete(m_moveObject[i].posCurrent, m_moveObject[i].type);
					UpdateCaisse();
				}
				else
				{
					ObjectDelete(m_moveObject[i].posCurrent, m_moveObject[i].type);
				}
			}
		}
	}
	if (m_blupiFocus && !m_blupiShield && !m_blupiHide && !m_bSuperBlupi && m_blupiPos.x > posStart.x - 30 && m_blupiPos.x < posStart.x + 30 + 64 && m_blupiPos.y > posStart.y - 30 && m_blupiPos.y < posStart.y + 30 + 64)
	{
		BlupiDead(11, -1);
		m_blupiAir = TRUE;
	}

}

int CDecor::AscenseurDetect(RECT rect, POINT oldpos, POINT newpos)
{
	if (m_blupiTimeNoAsc != 0)
	{
		return -1;
	}
	int num = newpos.y - oldpos.y;
	int num2;
	if (num < 0)
	{
		num2 = -30;
	}
	else
	{
		num2 = 30;
	}
	num = abs(num);
	for (int i = 0; i < MAXMOVEOBJECT; i++)
	{
		if (m_moveObject[i].type == 1 || m_moveObject[i].type == 47 || m_moveObject[i].type == 48)
		{
			RECT src;
			src.left = m_moveObject[i].posCurrent.x;
			src.right = m_moveObject[i].posCurrent.x + 64;
			src.top = m_moveObject[i].posCurrent.y;
			src.bottom = m_moveObject[i].posCurrent.y + 16;
			if (num < 30)
			{
				RECT tinyRect;
				if (IntersectRect(tinyRect, src, rect))
				{
					return i;
				}
			}
			else
			{
				RECT src2 = rect;
				src2.top -= num / 30 * num2;
				src2.bottom -= num / 30 * num2;
				for (int j = 0; j <= num / 30; j++)
				{
					RECT tinyRect;
					if (IntersectRect(tinyRect, src, src2))
					{
						return i;
					}
					src2.top += num2;
					src2.bottom += num;
				}
			}

		}
	}
	return -1;
}

void CDecor::AscenseurVertigo(int i, BOOL* pbVertigoLeft, BOOL* pbVertigoRight)
{
	*pbVertigoLeft = FALSE;
	
	*pbVertigoRight = FALSE;
	if (m_blupiPos.x + 20 + 4 < m_moveObject[i].posCurrent.x)
	{
		*pbVertigoLeft = TRUE;
	}
	if (m_blupiPos.x + 60 - 20 - 4 > m_moveObject[i].posCurrent.x + 64)
	{
		*pbVertigoRight = TRUE;
	}
	if (AscenseurShift(i))
	{
		if (*pbVertigoLeft)
		{
			*pbVertigoLeft = FALSE;
			*pbVertigoRight = TRUE;
			m_blupiTimeNoAsc = 10;
			return;
		}
		if (*pbVertigoRight)
		{
			*pbVertigoRight = FALSE;
			*pbVertigoLeft = TRUE;
			m_blupiTimeNoAsc = 10;
		}
	}
}

BOOL CDecor::AscenseurShift(int i)
{
	return i != -1 && m_moveObject[i].icon >= 311 && m_moveObject[i].icon <= 316;
}

void CDecor::AscenseurSynchro(int i)
{
	for (i = 0; i < MAXMOVEOBJECT; i++)
	{
		m_moveObject[i].posCurrent = m_moveObject[i].posStart;
		m_moveObject[i].step = 1;
		m_moveObject[i].time = 0;
		m_moveObject[i].phase = 0;
	}
}

void CDecor::UpdateCaisse()
{
	m_nbRankCaisse = 0;
	for (int i = 0; i < MAXMOVEOBJECT; i++)
	{
		if (m_moveObject[i].type == TYPE_CAISSE)
		{
			m_rankCaisse[m_nbRankCaisse++] = i;
		}
	}
}

BOOL CDecor::TestPushCaisse(int i, POINT pos, BOOL bPop)
{
	POINT move;

	move.x = pos.x - m_moveObject[i].posCurrent.x;
	move.y = 0;
	SearchLinkCaisse(i, bPop);
	int y = m_moveObject[i].posCurrent.y;
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
		i = m_linkCaisse[j];
		int num = i;
		m_moveObject[num].posCurrent.x = m_moveObject[num].posCurrent.x + move.x;
		m_moveObject[num].posStart.x = m_moveObject[num].posStart.x + move.x;
		int num2 = i;
		m_moveObject[num].posEnd.x = m_moveObject[num].posEnd.x + move.x;
	}
	return TRUE;
}

BOOL CDecor::TestPushOneCaisse(int i, POINT move, int b)
{
	// TODO
	return FALSE;
}

void CDecor::SearchLinkCaisse(int rank, BOOL bPop)
{
	m_nbLinkCaisse = 0;
	AddLinkCaisse(rank);
	POINT posCurrent = m_moveObject[rank].posCurrent;

	BOOL flag;
	do
	{
		flag = FALSE;
		for (int i = 0; i < m_nbLinkCaisse; i++)
		{
			int num = m_linkCaisse[i];
			if (m_moveObject[num].posCurrent.y <=
				posCurrent.y && (!bPop || (m_moveObject
					[num].posCurrent.x >= posCurrent.x - DIMOBJX / 2 &&
					m_moveObject[num].posCurrent.x <=
					posCurrent.x + DIMOBJX / 2)))
			{
				RECT src;
				src.left = m_moveObject[num].posCurrent.x - 1;
				src.top = m_moveObject[num].posCurrent.y - 1;
				src.right = src.left + DIMOBJX + 1;
				src.bottom = src.top + DIMOBJY + 1;
				for (int j = 0; j < m_nbRankCaisse; j++)
				{
					int num2 = m_rankCaisse[j];
					if (num2 != num && m_moveObject[num2].posCurrent.y <= posCurrent.y && (!bPop || (m_moveObject[num2].posCurrent.x >= posCurrent.x - 32 && m_moveObject[num2].posCurrent.x <= posCurrent.x + 32)))
					{
						RECT src2;
						src2.left = m_moveObject[num2].posCurrent.x - 1;
						src2.top = m_moveObject[num2].posCurrent.y - 1;
						src2.right = src2.left + 64 + 1;
						src2.bottom = src2.top + 64 + 1;
						RECT tinyRect;
						if (IntersectRect(tinyRect, src2, src) && AddLinkCaisse(num2))
						{
							flag = TRUE;
						}
					}
				}
			}
		}
	} while (flag);
}

BOOL CDecor::AddLinkCaisse(int rank)
{
	for (int i = 0; i < m_nbLinkCaisse; i++)
	{
		if (m_linkCaisse[i] == rank)
		{
			return FALSE;
		}
	}
	m_linkCaisse[m_nbLinkCaisse] = rank;
	m_nbLinkCaisse++;
	return TRUE;
}

int CDecor::CaisseInFront()
{
	POINT tinyPoint;
	if (m_blupiDir == 1)
	{
		tinyPoint.x = m_blupiPos.x + 16 - 32;
		tinyPoint.y = m_blupiPos.y;
	}
	else
	{
		tinyPoint.x = m_blupiPos.x + 60 - 16 + 32;
		tinyPoint.y = m_blupiPos.y;
	}
	for (int i = 0; i < m_nbRankCaisse; i++)
	{
		int num = m_rankCaisse[i];
		if (tinyPoint.x > m_moveObject[num].posCurrent.x &&
			tinyPoint.x < m_moveObject[num].posCurrent.x + 64 &&
			tinyPoint.y > m_moveObject[num].posCurrent.y &&
			tinyPoint.y < m_moveObject[num].posCurrent.y + 64)
		{
			return num;
		}
	}
	return -1;
}

int CDecor::CaisseGetMove(int max)
{
	max -= (m_nbLinkCaisse - 1) / 2;
	if (max < 1)
	{
		max = 1;
	}
	if (m_blupiPower)
	{
		max *= 2;
	}
	if (m_blupiPhase < 20)
	{
		max = max * m_blupiPhase / 20;
		if (max == 0)
		{
			max++;
		}
	}
	return max;
}

int CDecor::MockeryDetect(POINT pos)
{
	if (m_blupiTimeMockery > 0)
	{
		return 0;
	}
	if (m_blupiAir)
	{
		POINT tinyPoint;
		tinyPoint.x = pos.x + 30;
		tinyPoint.y = pos.y + 30 + 64;
		if (tinyPoint.x >= 0 && tinyPoint.x < DIMOBJX*MAXCELX && tinyPoint.y >= 0 && tinyPoint.y < DIMOBJY*MAXCELY)
		{
			int icon = m_decor[tinyPoint.x / DIMOBJX][tinyPoint.y / DIMOBJY].icon;
			if (icon == 68 || icon == 317)
			{
				return 64;
			}
		}
	}
	RECT src;
	src.left = pos.x;
	src.right = pos.x + 60;
	src.top = pos.y + 11;
	src.bottom = pos.y + 60;
	if (m_blupiAir)
	{
		src.bottom += 90;
	}
	for (int i = 0; i < MAXMOVEOBJECT; i++)
	{
		if (m_moveObject[i].type == 2 ||
			m_moveObject[i].type == 16 ||
			m_moveObject[i].type == 96 ||
			m_moveObject[i].type == 97 ||
			m_moveObject[i].type == 4 ||
			m_moveObject[i].type == 20 ||
			m_moveObject[i].type == 44 ||
			m_moveObject[i].type == 54 ||
			m_moveObject[i].type == 23 ||
			m_moveObject[i].type == 32 ||
			m_moveObject[i].type == 33)
		{
			RECT src2;
			src2.left = m_moveObject[i].posCurrent.x;
			src2.right = m_moveObject[i].posCurrent.x + 60;
			src2.top = m_moveObject[i].posCurrent.y + 36;
			src2.bottom = m_moveObject[i].posCurrent.y + 60;
			RECT tinyRect;
			if (IntersectRect(tinyRect, src2, src))
			{
				if (m_moveObject[i].type == 54)
				{
					return 83;
				}
				if (m_blupiDir == 2)
				{
					if (pos.x >= src2.left)
					{
						return 64;
					}
					if (m_moveObject[i].type == 2)
					{
						return 0;
					}
					return 63;
				}
				else
				{
					if (pos.x < src2.left)
					{
						return 64;
					}
					if (m_moveObject[i].type == 2)
					{
						return 0;
					}
					return 63;
				}
			}
		}
	}
	return 0;
}

BOOL CDecor::BlupiElectro(POINT pos)
{
	if (m_blupiCloud)
	{
		return FALSE;
	}
	RECT src;
	src.left = pos.x + 16;
	src.right = pos.x + 60 - 16;
	src.top = pos.y + 11;
	src.bottom = pos.y + 60 - 2;
	RECT src2;
	src2.left = m_blupiPos.x - 16 - 40;
	src2.right = m_blupiPos.x + 60 + 16 + 40;
	src2.top = m_blupiPos.y + 11 - 40;
	src2.bottom = m_blupiPos.y + 60 - 2 + 40;
	RECT tinyRect;
	return IntersectRect(tinyRect, src, src2);
}

void CDecor::MoveObjectFollow(POINT pos)
{
	if (m_blupiHide)
	{
		return;
	}
	RECT src = BlupiRect(pos);
	src.left = pos.x + 16;
	src.right = pos.x + 60 - 16;
	for (int i = 0; i < MAXMOVEOBJECT; i++)
	{
		if (m_moveObject[i].type == 96)
		{
			RECT src2;
			src2.left = m_moveObject[i].posCurrent.x - 100;
			src2.right = m_moveObject[i].posCurrent.x + 60 + 100;
			src2.top = m_moveObject[i].posCurrent.y - 100;
			src2.bottom = m_moveObject[i].posCurrent.y + 60 + 100;
			RECT tinyRect;
			if (IntersectRect(tinyRect, src2, src))
			{
				m_moveObject[i].type = 97;
				PlaySound(92, m_moveObject[i].posCurrent);
			}
		}
	}
}

int CDecor::MoveObjectDetect(POINT pos, BOOL* pbNear)
{
	RECT src = BlupiRect(pos);
	src.left = pos.x + 16;
	src.right = pos.x + 60 - 16;
	RECT src2;
	src2.left = src.left - 20;
	src2.right = src.right + 20;
	src2.top = src.top - 40;
	src2.bottom = src.bottom + 30;

	for (int i = 0; i < MAXMOVEOBJECT; i++)
	{
		if (m_moveObject[i].type != 0 &&
			m_moveObject[i].type != 27 &&
			m_moveObject[i].type != 57 &&
			m_moveObject[i].type != 39 &&
			m_moveObject[i].type != 58 &&
			m_moveObject[i].type != 34 &&
			m_moveObject[i].type != 37 &&
			m_moveObject[i].type != 38 &&
			(m_blupiAction != 14 && m_blupiAction != 29) ||
			m_moveObject[i].type != 12)
		{
			RECT src3;
			// TODO
		}
	}
	return -1;
}

int CDecor::MoveAscenseurDetect(POINT pos, int height)
{
	if (m_blupiTimeNoAsc != 0)
	{
		return -1;
	}
	RECT src;
	src.left = pos.x + 12;
	src.right = pos.x + 60 - 12;
	src.top = pos.y + 60 - 2;
	src.bottom = pos.y + 60 + height - 1;
	for (int i = 0; i < MAXMOVEOBJECT; i++)
	{
		if (m_moveObject[i].type == 1 || m_moveObject[i].type == 47 || m_moveObject[i].type == 48)
		{
			RECT src2;
			src2.left = m_moveObject[i].posCurrent.x;
			src2.right = m_moveObject[i].posCurrent.x + 64;
			src2.top = m_moveObject[i].posCurrent.y;
			src2.bottom = m_moveObject[i].posCurrent.y + 16;
			RECT tinyRect;
			if (IntersectRect(tinyRect, src2, src))
			{
				return i;
			}
		}
	}
	return -1;
}

int CDecor::MoveChargeDetect(POINT pos)
{
	RECT src;
	src.left = pos.x + 16;
	src.right = pos.x + 60 - 16;
	src.top = pos.y + 11;
	src.bottom = pos.y + 60 - 2;
	for (int i = 0; i < MAXMOVEOBJECT; i++)
	{
		if (m_moveObject[i].type == 31)
		{
			RECT src2;
			src2.left = m_moveObject[i].posCurrent.x - 10;
			src2.right = m_moveObject[i].posCurrent.x + 60 + 10;
			src2.top = m_moveObject[i].posCurrent.y + 36;
			src2.bottom = m_moveObject[i].posCurrent.y + 60;
			RECT tinyRect;
			if (IntersectRect(tinyRect, src2, src))
			{
				return i;
			}
		}
	}
	return -1;
}

int CDecor::MovePersoDetect(POINT pos)
{
	RECT src;
	src.left = pos.x + 16;
	src.right = pos.x + 60 - 16;
	src.top = pos.y + 11;
	src.bottom = pos.y + 60 - 2;
	for (int i = 0; i < MAXMOVEOBJECT; i++)
	{
		if (m_moveObject[i].type >= 200 && m_moveObject[i].type <= 203)
		{
			RECT src2;
			src2.left = m_moveObject[i].posCurrent.x - 16;
			src2.right = m_moveObject[i].posCurrent.x + 60 + 16;
			src2.top = m_moveObject[i].posCurrent.y + 36;
			src2.bottom = m_moveObject[i].posCurrent.y + 60;
			RECT tinyRect;
			if (IntersectRect(tinyRect, src2, src))
			{
				return i;
			}
		}
	}
	return -1;
}

int CDecor::MoveBalleDetect(POINT pos)
{
	// TODO
	return -1;
}

int CDecor::MoveObjectDelete(POINT cel)
{
	int result = -1;
	for (int i = 0; i < MAXMOVEOBJECT; i++)
	{
		if (m_moveObject[i].type != 0)
		{
			if (cel.x == m_moveObject[i].posStart.x / 64 && cel.y == m_moveObject[i].posStart.y / 64)
			{
				result = m_moveObject[i].type;
				m_moveObject[i].type = 0;
			}
			else if (cel.x == m_moveObject[i].posEnd.x / 64 && cel.y == m_moveObject[i].posEnd.y / 64)
			{
				result = m_moveObject[i].type;
				m_moveObject[i].type = 0;
			}
		}
	}
	return result;
}

int CDecor::MoveObjectFree()
{
	for (int i = 0; i < MAXMOVEOBJECT; i++)
	{
		if (m_moveObject[i].type == 0)
		{
			m_moveObject[i].type = 0;
			return i;
		}
	}
	return -1;
}

int CDecor::SortGetType(int type)
{
	if (type == 2 || type == 3 || type == 96 || type == 97)
	{
		return 1;
	}
	if (type == 12)
	{
		return 2;
	}
	return 3;
}

void CDecor::MoveObjectSort()
{
	MoveObject src;
	int num = 0;
	for (int i = 0; i < MAXMOVEOBJECT; i++)
	{
		if (m_moveObject[i].type != 0)
		{
			MoveObjectCopy(m_moveObject[num++], m_moveObject[i]);
		}
	}
	for (int i = num; i < MAXMOVEOBJECT; i++)
	{
		m_moveObject[i].type = 0;
	}
	if (num <= 1)
	{
		return;
	}
	BOOL flag;
	do
	{
		flag = FALSE;
		for (int i = 0; i < num - 1; i++)
		{
			if (SortGetType(m_moveObject[i].type) > SortGetType(m_moveObject[i + 1].type))
			{
				MoveObjectCopy(src, m_moveObject[i]);
				MoveObjectCopy(m_moveObject[i], m_moveObject[i + 1]);
				MoveObjectCopy(m_moveObject[i + 1], src);
				flag = TRUE;
			}
		}
	} while (flag);
	UpdateCaisse();
	m_nbLinkCaisse = 0;
}

void CDecor::MoveObjectPriority(int i)
{

}

int CDecor::MoveObjectSearch(POINT pos, int type)
{
	for (int i = 0; i < MAXMOVEOBJECT; i++)
	{
		if (m_moveObject[i].type != 0 && (type == -1 ||
			m_moveObject[i].type == type))
		{
			if (m_moveObject[i].type == 23 &&
				m_moveObject[i].posStart.x != m_moveObject[i].posEnd.x)
			{
				if (m_moveObject[i].posCurrent.x >= pos.x - 100 &&
					m_moveObject[i].posCurrent.x <= pos.x + 100 &&
					m_moveObject[i].posCurrent.y == pos.y)
				{
					return i;
				}
			}
			else if (m_moveObject[i].type == 23 &&
				m_moveObject[i].posStart.y != m_moveObject[i].posEnd.y)
			{
				if (m_moveObject[i].posCurrent.y >= pos.y - 100 &&
					m_moveObject[i].posCurrent.y <= pos.y + 100 &&
					m_moveObject[i].posCurrent.x == pos.x)
				{
					return i;
				}
			}
			else if (m_moveObject[i].posCurrent.x == pos.x &&
				m_moveObject[i].posCurrent.y == pos.y)
			{
				return i;
			}
		}
	}
	return -1;
}

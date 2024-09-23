// DecBlupi.cpp
//

#include "DEF.H"
#include "DECOR.H"
#include "MISC.H"
#include "RESOURCE.H"
#include "dectables.h"

int CDecor::GetBlupiChannelStandard()
{
	if (m_bMulti && m_blupiChannel == CHBLUPI && m_team > 0) {
		return m_team + CHBLUPI1 - 1;
	}
	else {
		return m_blupiChannel;
	}
}

int CDecor::GetBlupiChannelActual()
{
	if (m_bMulti && m_team > 0) {
		return m_team + CHBLUPI1 - 1;
	}
	return CHBLUPI;
}

void CDecor::GetBlupiInfo(BOOL* bHelico, BOOL* bJeep, BOOL* bSkate, BOOL* bNage)
{
	*bHelico = m_blupiHelico;
	*bJeep = m_blupiJeep | m_blupiTank;
	*bSkate = m_blupiSkate;
	*bNage = m_blupiNage | m_blupiSurf;
}

void CDecor::BlupiSearchIcon()
{
	int num = 0;
	int num2 = 2;
	int num3 = m_blupiAction;
	if (m_blupiVent && m_blupiHelico && m_blupiOver)
	{
		if (num3 == 1)
		{
			num3 = 8;
		}
		if (num3 == 2)
		{
			num3 = 14;
		}
	}
	if (m_blupiHelico)
	{
		if (num3 == 1)
		{
			num3 = 15;
		}
		if (num3 == 2)
		{
			num3 = 16;
		}
		if (num3 == 3)
		{
			num3 = 17;
		}
		if (num3 == 10)
		{
			num3 = 15;
		}
		if (num3 == 9)
		{
			num3 = 15;
		}
	}
	if (m_blupiOver)
	{
		if (num3 == 1)
		{
			num3 = 67;
		}
		if (num3 == 2)
		{
			num3 = 68;
		}
		if (num3 == 3)
		{
			num3 = 69;
		}
		if (num3 == 10)
		{
			num3 = 67;
		}
		if (num3 == 9)
		{
			num3 = 67;
		}
	}
	if (m_blupiJeep)
	{
		if (num3 == 1)
		{
			num3 = 25;
		}
		if (num3 == 2)
		{
			num3 = 26;
		}
		if (num3 == 10)
		{
			num3 = 26;
		}
		if (num3 == 3)
		{
			num3 = 27;
		}
	}
	if (m_blupiTank)
	{
		if (num3 == 1)
		{
			num3 = 50;
		}
		if (num3 == 2)
		{
			num3 = 51;
		}
		if (num3 == 10)
		{
			num3 = 51;
		}
		if (num3 == 3)
		{
			num3 = 52;
		}
	}

}

BOOL CDecor::BlupiIsGround()
{
	if (m_blupiTransport == -1)
	{
		RECT rect = BlupiRect(m_blupiPos);
		rect.top = m_blupiPos.y + DIMBLUPIY - 2;
		rect.bottom = m_blupiPos.y + DIMBLUPIY - 1;
		return DecorDetect(rect, TRUE);
	}
	else {
		return FALSE;
	}
}

RECT CDecor::BlupiRect(POINT pos)
{
	RECT result;
	if (m_blupiNage || m_blupiSurf)
	{
		result.left = pos.x + 12;
		result.right = pos.x + DIMBLUPIX - 12;
		if (m_blupiAction == ACTION_STOP)
		{
			result.top = pos.y + 5;
			result.bottom = pos.y + DIMBLUPIY - 10;
		}
		else
		{
			result.top = pos.y + 15;
			result.bottom = pos.y + DIMBLUPIY - 10;
		}
	}
	else if (m_blupiJeep)
	{
		result.left = pos.x + 2;
		result.right = pos.x + DIMBLUPIX - 2;
		result.top = pos.y + 10;
		result.bottom = pos.y + DIMBLUPIY - 2;
	}
	else if (m_blupiTank)
	{
		result.left = pos.x + 2;
		result.right = pos.x + DIMBLUPIX - 2;
		result.top = pos.y + 10;
		result.bottom = pos.y + DIMBLUPIY - 2;
	}
	else if (m_blupiOver)
	{
		result.left = pos.x + 2;
		result.right = pos.x + DIMBLUPIX - 2;
		result.top = pos.y + 2;
		result.bottom = pos.y + DIMBLUPIY - 2;
	}
	else if (m_blupiBalloon)
	{
		result.left = pos.x + 10;
		result.right = pos.x + DIMBLUPIX - 10;
		result.top = pos.y + 5;
		result.bottom = pos.y + DIMBLUPIY - 2;
	}
	else if (m_blupiEcrase)
	{
		result.left = pos.x + 5;
		result.right = pos.x + DIMBLUPIX - 5;
		result.top = pos.y + 39;
		result.bottom = pos.y + DIMBLUPIY - 2;
	}
	else
	{
		result.left = pos.x + 12;
		result.right = pos.x + DIMBLUPIX - 12;
		result.top = pos.y + 11;
		result.bottom = pos.y + DIMBLUPIY - 2;
	}
	return result;
}

void CDecor::BlupiAdjust()
{
	RECT tinyRect = BlupiRect(m_blupiPos);

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

void CDecor::BlupiStep()
{
	int m_blupiSpeedX = 0; //
	int m_blupiSpeedY = 0; // lol. lmao even
	POINT tinyPoint;
	POINT tinyPoint2;
	BlupiAdjust();
	//m_blupiLastPos = m_blupiPos;
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
		m_blupiPos.y = m_blupiPos.y / DIMOBJY * 64 + BLUPIOFFY;
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
		num = m_decor[(tinyPoint3.x + 30) / 64][(tinyPoint3.y + 30) / 64].icon;
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
	BOOL flag4 = TRUE;
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
		m_blupiVitesse.y = 1;
		m_blupiAir = TRUE;
		flag = TRUE;
	}
	if (!m_blupiNage && !m_blupiSurf && !m_blupiSuspend && !m_blupiAir && IsRessort(tinyPoint3))
	{
		if ((m_blupiHelico || m_blupiOver) && !m_blupiShield && !m_blupiHide && !m_bSuperBlupi)
		{
			m_blupiHelico = FALSE;
			m_blupiOver = FALSE;
			tinyPoint.x = tinyPoint3.x - 34;
			tinyPoint.y = tinyPoint3.y - 34;
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
			m_blupiJeep = FALSE;
			tinyPoint.x = tinyPoint3.x - 34;
			tinyPoint.y = tinyPoint3.y - 34;
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
			m_blupiTank = FALSE;
			tinyPoint.x = tinyPoint3.x - 34;
			tinyPoint.y = tinyPoint3.y - 34;
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
			m_blupiSkate = FALSE;
			tinyPoint.x = tinyPoint3.x - 34;
			tinyPoint.y = tinyPoint3.y - 34;
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
			m_blupiVitesse.y = (m_blupiPower ? -25 : -19);
		}
		else
		{
			m_blupiVitesse.y = (m_blupiPower ? -16 : -10);
		}
		m_blupiAir = TRUE;
		flag = TRUE;
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
				m_blupiVitesse.y = (m_blupiPower ? -17 : -13);
			}
			else
			{
				PlaySound(1, tinyPoint3);
				if (/*IsNormalJump(tinyPoint3)*/FALSE)
				{
					m_blupiVitesse.y = (m_blupiPower ? -26 : -16);
				}
				else
				{
					m_blupiVitesse.y = (m_blupiPower ? -16 : -12);
				}
			}
			m_blupiAir = TRUE;
			flag = TRUE;
		}
	}
	if (m_blupiAir)
	{
		if (flag5 && m_blupiVitesse.y < 0)
		{
			if (m_blupiVitesse.y < -14 && m_blupiAction != 11 && m_blupiAction != 75 && m_blupiAction != 76 && m_blupiAction != 77 && m_blupiAction != 78 && m_blupiAction != 79 && m_blupiAction != 80 && m_blupiAction != 81 && !m_blupiSkate)
			{
				m_blupiJumpAie = TRUE;
				PlaySound(40, tinyPoint3);
			}
			else
			{
				PlaySound(SoundEnviron(4, detectIcon), tinyPoint3);
			}
			m_blupiVitesse.y = 1;
		}
		tinyPoint3.y += (int)(m_blupiVitesse.y * 2);
		if (m_blupiVitesse.y < 20)
		{
			m_blupiVitesse.y += 2;
		}
		rect = BlupiRect(tinyPoint3);
		rect.top = tinyPoint3.y + 60 - 30;
		rect.bottom = tinyPoint3.y + 60 - 1;
		if (m_blupiVitesse.y >= 0 && DecorDetect(rect))
		{
			tinyPoint3.y = tinyPoint3.y / 32 * 32 + BLUPIOFFY;
			if (!IsRessort(tinyPoint3))
			{
				PlaySound(SoundEnviron(3, m_detectIcon), tinyPoint3);
			}
			if (m_blupiFocus)
			{
				if (m_blupiVitesse.y > 20)
				{
					m_blupiAction = 61;
				}
				else
				{
					m_blupiAction = 61;
				}
				m_blupiPhase = 0;
			}
			m_blupiAir = FALSE;
			if (m_blupiJumpAie)
			{
				m_blupiJumpAie = FALSE;
				m_blupiAction = 36;
				m_blupiPhase = 0;
			}
		}
		rect.left = tinyPoint3.x + 20;
		rect.right = tinyPoint3.x + 60 - 20;
		rect.top = tinyPoint3.y + 60 - 33;
		rect.bottom = tinyPoint3.y + 60 - 1;
		num = AscenseurDetect(rect, m_blupiPos, tinyPoint3);
		if (m_blupiVitesse.y >= 0 && num != -1)
		{
			m_blupiTransport = num;
			flag4 = FALSE;
			PlaySound(3, tinyPoint3);
			tinyPoint3.y = m_moveObject[num].posCurrent.y - 64 + BLUPIOFFY;
			if (m_blupiFocus)
			{
				if (m_blupiVitesse.y > 20)
				{
					m_blupiAction = 61;
				}
				else
				{
					m_blupiAction = 61;
				}
				m_blupiPhase = 0;
			}
			m_blupiAir = FALSE;
			if (m_blupiJumpAie)
			{
				m_blupiJumpAie = FALSE;
				m_blupiAction = 36;
				m_blupiPhase = 0;
			}
		}
	}
	if (m_blupiAction == 36 && m_blupiPhase == 30)
	{
		m_blupiAction = 1;
		m_blupiPhase = 0;
		m_blupiFocus = TRUE;
	}
	if (m_blupiAction == 56 && m_blupiPhase == 64)
	{
		m_blupiAction = 1;
		m_blupiPhase = 0;
		m_blupiFocus = TRUE;
		m_blupiCloud = TRUE;
		m_blupiTimeShield = 100;
		m_jauges[1].SetHide(FALSE);
		PlaySound(55, tinyPoint3);
	}
	if (m_blupiAction == 58)
	{
		if (m_blupiPhase == 8)
		{
			tinyPoint.x = m_blupiPos.x;
			tinyPoint.y = m_blupiPos.y + 40;
			if (m_blupiVitesse.y > 0)
			{
				tinyPoint.y += (int)(m_blupiVitesse.y * 4);
			}
			m_blupiVitesse.y -= 10;
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
			m_blupiFocus = TRUE;
		}
	}
	if ((m_blupiAction == 44 || m_blupiAction == 45) && m_blupiPhase == 29)
	{
		m_blupiAction = 1;
		m_blupiPhase = 0;
		m_blupiFocus = TRUE;
	}
	if (m_blupiAction == 46 && m_blupiPhase == 32)
	{
		m_blupiAction = 1;
		m_blupiPhase = 0;
		m_blupiFocus = TRUE;
	}
	if (m_blupiAction == 47 && m_blupiPhase == 34)
	{
		m_blupiAction = 1;
		m_blupiPhase = 0;
		m_blupiFocus = TRUE;
	}
	BOOL flag6;
	if (m_blupiAction == 48 && m_blupiPhase == 40)
	{
		m_blupiAction = 1;
		m_blupiPhase = 0;
		m_blupiFocus = TRUE;
		num = MoveObjectDetect(tinyPoint3, &flag6);
		if (num != -1 && !flag6 && tinyPoint3.y - BLUPIFLOOR == m_moveObject[num].posCurrent.y)
		{
			if (m_blupiDir == 2 && tinyPoint3.x < m_moveObject[num].posCurrent.x)
			{
				tinyPoint.x = tinyPoint3.x - 16;
				tinyPoint.y = tinyPoint3.y;
				int num2 = MoveObjectDetect(tinyPoint, &flag6);
				if (num2 == -1)
				{
					m_blupiAction = 9;
					m_blupiPhase = 0;
				}
			}
			if (m_blupiDir == 1 && tinyPoint3.x > m_moveObject[num].posCurrent.x)
			{
				tinyPoint.x = tinyPoint3.x + 16;
				tinyPoint.y = tinyPoint3.y;
				int num2 = MoveObjectDetect(tinyPoint, &flag6);
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
			m_blupiFocus = TRUE;
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
			m_blupiFocus = TRUE;
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
			m_blupiFocus = TRUE;
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
			m_blupiFocus = TRUE;
		}
	}
	if (m_blupiAction == 84 && m_blupiPhase == 18)
	{
		m_blupiAction = 1;
		m_blupiPhase = 0;
		m_blupiFocus = TRUE;
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
		m_blupiVitesse.y = -12;
		m_blupiAir = TRUE;
		flag = TRUE;
	}
	if (m_blupiAction == 49 && m_blupiPhase == 32)
	{
		//ObjectStart(m_sucettePos, m_sucetteType, 0); // respawn item (winphone behavior)
		m_blupiAction = 1;
		m_blupiPhase = 0;
		m_blupiFocus = TRUE;
		m_blupiPower = TRUE;
		m_blupiTimeShield = 100;
		m_blupiPosMagic = m_blupiPos;
		m_jauges[1].SetHide(FALSE);
		PlaySound(44, tinyPoint3);
	}
	if (m_blupiAction == 55 && m_blupiPhase == 36)
	{
		//ObjectStart(m_sucettePos, m_sucetteType, 0); // respawn item (winphone behavior)
		m_blupiAction = 1;
		m_blupiPhase = 0;
		m_blupiFocus = TRUE;
		m_blupiHide = TRUE;
		m_blupiTimeShield = 100;
		m_blupiPosMagic = m_blupiPos;
		m_jauges[1].SetHide(FALSE);
		PlaySound(62, tinyPoint3);
	}
	if ( m_blupiAction != 3 && m_blupiAction != 4 && m_blupiAction != 5 && m_blupiAction != 8 && m_blupiAction != 10 && m_blupiAction != 9 && !m_blupiAir && !m_blupiHelico && !m_blupiOver && !m_blupiBalloon && !m_blupiEcrase && !m_blupiJeep && !m_blupiTank && !m_blupiSkate && !m_blupiNage && !m_blupiSurf && !m_blupiSuspend && m_blupiFocus)
	{
		m_blupiAction = 7;
		m_blupiPhase = 0;
	}
	if (m_blupiAction != 3 && m_blupiAction != 4 && m_blupiAction != 5 && m_blupiAction != 8 && m_blupiAction != 10 && m_blupiAction != 9 && !m_blupiAir && !m_blupiHelico && !m_blupiOver && !m_blupiBalloon && !m_blupiEcrase && !m_blupiJeep && !m_blupiTank && !m_blupiSkate && !m_blupiNage && !m_blupiSurf && !m_blupiSuspend && m_blupiFocus)
	{
		m_blupiAction = 1;
		m_blupiPhase = 0;
	}
	if ( m_blupiAction != 3 && m_blupiAction != 4 && m_blupiAction != 5 && m_blupiAction != 6 && m_blupiAction != 28 && m_blupiAction != 8 && m_blupiAction != 10 && m_blupiAction != 9 && !m_blupiAir && !m_blupiHelico && !m_blupiOver && !m_blupiBalloon && !m_blupiEcrase && !m_blupiJeep && !m_blupiTank && !m_blupiSkate && !m_blupiNage && !m_blupiSurf && !m_blupiSuspend && m_blupiFocus)
	{
		m_blupiAction = 6;
		m_blupiPhase = 0;
	}
	if ( (m_keyPress & 1) == 0 && m_blupiAction != 3 && m_blupiAction != 4 && m_blupiAction != 5 && m_blupiAction != 6 && m_blupiAction != 28 && m_blupiAction != 8 && m_blupiAction != 10 && m_blupiAction != 9 && !m_blupiAir && !m_blupiHelico && !m_blupiOver && !m_blupiBalloon && !m_blupiEcrase && !m_blupiJeep && !m_blupiTank && !m_blupiSkate && !m_blupiNage && !m_blupiSurf && !m_blupiSuspend && m_blupiFocus)
	{
		m_blupiAction = 6;
		m_blupiPhase = 0;
	}
	if (m_blupiAction != 3 && m_blupiAction != 4 && m_blupiAction != 5 && m_blupiAction != 8 && m_blupiAction != 10 && m_blupiAction != 9 && !m_blupiAir && !m_blupiHelico && !m_blupiOver && !m_blupiBalloon && !m_blupiEcrase && !m_blupiJeep && !m_blupiTank && !m_blupiSkate && !m_blupiNage && !m_blupiSurf && !m_blupiSuspend && m_blupiFocus)
	{
		m_blupiAction = 1;
		m_blupiPhase = 0;
	}
	if (m_blupiAction == 7 && m_blupiPhase == 4)
	{
		m_scrollAdd.y = -150;
		PlaySound(21, tinyPoint3);
	}
	if (m_blupiAction == 6 && m_blupiPhase == 4)
	{
		m_scrollAdd.y = 150;
		PlaySound(7, tinyPoint3);
	}
	if (!m_blupiHelico && !m_blupiOver && !m_blupiBalloon && !m_blupiEcrase && !m_blupiJeep && !m_blupiTank && !m_blupiSkate && !m_blupiNage && !m_blupiSurf && !m_blupiSuspend && m_blupiFocus)
	{
		if ( (m_keyPress & 1) == 0 && m_blupiAction != 28 && m_blupiDir == 1 && (num = CaisseInFront()) != -1)
		{
			tinyPoint3.x = m_moveObject[num].posCurrent.x + 64 - 5;
			m_blupiAction = 28;
			m_blupiPhase = 0;
			m_scrollAdd.y = 0;
			PlaySound(39, tinyPoint3);
		}
		if ( (m_keyPress & 1) == 0 && m_blupiAction != 29 && m_blupiDir == 1 && CaisseInFront() != -1)
		{
			m_blupiAction = 29;
			m_blupiPhase = 0;
			m_scrollAdd.y = 0;
			PlaySound(39, tinyPoint3);
		}
		if ( (m_keyPress & 1) == 0 && m_blupiAction != 28 && m_blupiDir == 2 && (num = CaisseInFront()) != -1)
		{
			tinyPoint3.x = m_moveObject[num].posCurrent.x - 60 + 5;
			m_blupiAction = 28;
			m_blupiPhase = 0;
			m_scrollAdd.y = 0;
			PlaySound(39, tinyPoint3);
		}
		if ((m_keyPress & 1) == 0 && m_blupiAction != 29 && m_blupiDir == 2 && CaisseInFront() != -1)
		{
			m_blupiAction = 29;
			m_blupiPhase = 0;
			m_scrollAdd.y = 0;
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
		m_blupiAction = 1;
		m_blupiPhase = 0;
	}
	int num3;
	int num4;
	if (m_blupiFocus)
	{
		if (m_blupiDir == 2 && m_blupiAction != 3 && m_blupiAction != 59 && m_blupiAction != 7 && m_blupiAction != 6 && m_blupiAction != 29 && ((!m_blupiJeep && !m_blupiTank && !m_blupiSkate) || abs(m_blupiVitesse.x) <= 8))
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
				tinyPoint3.x -= CaisseGetMove(5);
			}
			else
			{
				num3 = m_blupiPhase;
				if (num3 > 3 || m_blupiAir)
				{
					num3 = 3;
				}
				num4 = table_vitesse_march[num3];
				if (m_blupiPower)
				{
					num4 *= 3;
					num4 /= 2;
				}
				//tinyPoint3.x += Misc.Speed(m_blupiSpeedX, num4);
			}
		}
		if (m_blupiDir == 2 && m_blupiAction == 29)
		{
			tinyPoint3.x -= CaisseGetMove(3);
		}
	}
	if (m_blupiFocus)
	{
		if (m_blupiDir == 1 && m_blupiAction != 3 && m_blupiAction != 59 && m_blupiAction != 7 && m_blupiAction != 6 && m_blupiAction != 29 && ((!m_blupiJeep && !m_blupiTank && !m_blupiSkate) || abs(m_blupiVitesse.x) <= 8))
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
				tinyPoint3.x += CaisseGetMove(5);
			}
			else
			{
				num3 = m_blupiPhase;
				if (num3 > 3 || m_blupiAir)
				{
					num3 = 3;
				}
				num4 = table_vitesse_march[num3];
				if (m_blupiPower)
				{
					num4 *= 3;
					num4 /= 2;
				}
			}
		}
		if (m_blupiDir == 1 && m_blupiAction == 29)
		{
			tinyPoint3.x += CaisseGetMove(3);
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
	if (m_blupiSpeedX == 0 && m_blupiSpeedY == 0 && !m_blupiHelico && !m_blupiOver && !m_blupiBalloon && !m_blupiEcrase && !m_blupiJeep && !m_blupiTank && !m_blupiSkate && !m_blupiNage && !m_blupiSurf && m_blupiFocus)
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
		m_scrollAdd.y = 0;
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
			tinyPoint3.x += 4;
		}
		if (m_blupiAction == 9 && m_blupiDir == 2)
		{
			tinyPoint3.x -= 4;
		}
		if (m_blupiAction == 10 && m_blupiDir == 1)
		{
			tinyPoint3.x -= 4;
		}
		if (m_blupiAction == 10 && m_blupiDir == 2)
		{
			tinyPoint3.x += 4;
		}
	}
	if ((m_keyPress & -3) == 0 && m_blupiSpeedX == 0 && m_blupiSpeedY == 0 && (m_blupiJeep || m_blupiTank || m_blupiSkate) && m_blupiFocus)
	{
		if (m_blupiAction == 10 && m_blupiDir == 1)
		{
			tinyPoint3.x -= 5;
		}
		if (m_blupiAction == 10 && m_blupiDir == 2)
		{
			tinyPoint3.x += 5;
		}
	}
	if ((m_keyPress & -3) == 0 && m_blupiNage && m_blupiFocus && m_blupiAction == 2)
	{
		m_blupiAction = 1;
		m_blupiPhase = 0;
	}
	if ((m_keyPress & -3) == 0 && m_blupiSurf && m_blupiFocus && m_blupiAction == 2)
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
				m_blupiFocus = FALSE;
			}
		}
		////m_blupiMotorHigh = flag4;
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
				m_blupiVitesse.y = 0;
			}
		}
		
		{
			if (m_blupiSpeedY <= -1 || (m_keyPress & 1) != 0)
			{
				if (m_blupiVitesse.y > -10)
				{
					m_blupiVitesse.y -= 0.5;
				}
			}
			else if (m_blupiSpeedY >= 1)
			{
				if (m_blupiVitesse.y < 12)
				{
					m_blupiVitesse.y += 0.5;
				}
			}
			else
			{
				if (m_blupiVitesse.y > 1)
				{
					m_blupiVitesse.y -= 1;
				}
				if (m_blupiVitesse.y < 1)
				{
					m_blupiVitesse.y += 1;
				}
			}
			tinyPoint3.y += (int)m_blupiVitesse.y;
		}
		if (FALSE)
		{
			if (m_blupiSpeedX <= -1)
			{
				int num5 = (int)(m_blupiSpeedX * 12);
				if (m_blupiVitesse.x > num5)
				{
					m_blupiVitesse.x -= 0.5;
				}
				tinyPoint.x = tinyPoint3.x + (int)m_blupiVitesse.x;
				tinyPoint.y = tinyPoint3.y;
				if (BlupiBloque(tinyPoint, -1))
				{
					m_blupiVitesse.x = 0;
				}
			}
			else if (m_blupiSpeedX >= 1)
			{
				int num6 = (int)(m_blupiSpeedX * 12);
				if (m_blupiVitesse.x < num6)
				{
					m_blupiVitesse.x += 0.5;
				}
				tinyPoint.x = tinyPoint3.x + (int)m_blupiVitesse.x;
				tinyPoint.y = tinyPoint3.y;
				if (BlupiBloque(tinyPoint, 1))
				{
					m_blupiVitesse.x = 0;
				}
			}
			else
			{
				if (m_blupiVitesse.x > 0)
				{
					m_blupiVitesse.x -= 2;
					if (m_blupiVitesse.x < 0)
					{
						m_blupiVitesse.x = 0;
					}
				}
				if (m_blupiVitesse.x < 0)
				{
					m_blupiVitesse.x += 2;
					if (m_blupiVitesse.x > 0)
					{
						m_blupiVitesse.x = 0;
					}
				}
			}
			tinyPoint3.x += (int)m_blupiVitesse.x;
		}
		else
		{
			if (m_blupiSpeedX <= -1)
			{
				int num7 = (int)(m_blupiSpeedX * 16);
				if (m_blupiVitesse.x > num7)
				{
					m_blupiVitesse.x -= 1;
				}
				tinyPoint.x = tinyPoint3.x + (int)m_blupiVitesse.x;
				tinyPoint.y = tinyPoint3.y;
				if (BlupiBloque(tinyPoint, -1))
				{
					m_blupiVitesse.x = 0;
				}
			}
			else if (m_blupiSpeedX >= 1)
			{
				int num8 = (int)(m_blupiSpeedX * 16);
				if (m_blupiVitesse.x < num8)
				{
					m_blupiVitesse.x += 1;
				}
				tinyPoint.x = tinyPoint3.x + (int)m_blupiVitesse.x;
				tinyPoint.y = tinyPoint3.y;
				if (BlupiBloque(tinyPoint, 1))
				{
					m_blupiVitesse.x = 0;
				}
			}
			else
			{
				if (m_blupiVitesse.x > 0)
				{
					m_blupiVitesse.x -= 2;
					if (m_blupiVitesse.x < 0)
					{
						m_blupiVitesse.x = 0;
					}
				}
				if (m_blupiVitesse.x < 0)
				{
					m_blupiVitesse.x += 2;
					if (m_blupiVitesse.x > 0)
					{
						m_blupiVitesse.x = 0;
					}
				}
			}
			tinyPoint3.x += (int)m_blupiVitesse.x;
		}
		MoveObjectPollution();
		if ( !flag4 && m_blupiTransport == -1)
		{
			
			rect.left = m_blupiPos.x + 20;
			rect.right = m_blupiPos.x + 22;
			rect.top = m_blupiPos.y + 60 - 2;
			rect.bottom = m_blupiPos.y + 60;
			flag2 = !DecorDetect(rect);
			rect.left = m_blupiPos.x + 60 - 22;
			rect.right = m_blupiPos.x + 60 - 20;
			rect.top = m_blupiPos.y + 60 - 2;
			rect.bottom = m_blupiPos.y + 60;
			flag3 = !DecorDetect(rect);
			if (!flag2 && !flag3)
			{
				tinyPoint.x = m_blupiPos.x;
				tinyPoint.y = m_blupiPos.y - BLUPIFLOOR;
				ObjectStart(tinyPoint, 13, 0);
				m_blupiHelico = FALSE;
				m_blupiAction = 1;
				m_blupiPhase = 0;
				m_blupiPosHelico = m_blupiPos;
				m_blupiFocus = TRUE;
				StopSound(16);
				StopSound(18);
				PlaySound(17, m_blupiPos);
			}
		}
	}
	if (m_blupiOver && (m_blupiFocus || m_blupiAction == 58))
	{
		////m_blupiMotorHigh = flag4;
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
				m_blupiVitesse.y = 0;
			}
		}
		rect = BlupiRect(tinyPoint3);
		rect.top = tinyPoint3.y + 60 - 2;
		rect.bottom = tinyPoint3.y + 60 + OVERHEIGHT - 1;
		bool flag7 = !DecorDetect(rect);
		num = MoveAscenseurDetect(m_blupiPos, OVERHEIGHT);
		if (num != -1)
		{
			flag7 = FALSE;
		}
		if (((m_keyPress & 1) != 0) && !flag7)
		{
			if (m_blupiVitesse.y == 0 && num != -1)
			{
				m_blupiVitesse.y = -5;
			}
			else if (m_blupiVitesse.y > -5)
			{
				m_blupiVitesse.y -= 1;
			}
		}
		else if (m_blupiSpeedY > 0)
		{
			if (m_blupiVitesse.y < 12)
			{
				m_blupiVitesse.y += 5;
			}
		}
		else if (m_blupiVitesse.y < 12 && m_time % 2 == 0)
		{
			m_blupiVitesse.y += 1;
		}
		tinyPoint3.y += (int)m_blupiVitesse.y;
		if (m_blupiSpeedX < 0 && flag4)
		{
			int num9 = (int)(m_blupiSpeedX * 12);
			if (m_blupiVitesse.x > num9)
			{
				m_blupiVitesse.x -= 1;
			}
			tinyPoint.x = tinyPoint3.x + (int)m_blupiVitesse.x;
			tinyPoint.y = tinyPoint3.y;
			if (BlupiBloque(tinyPoint, -1))
			{
				m_blupiVitesse.x = 0;
			}
		}
		else if (m_blupiSpeedX > 0 && flag4)
		{
			int num10 = (int)(m_blupiSpeedX * 12);
			if (m_blupiVitesse.x < num10)
			{
				m_blupiVitesse.x += 1;
			}
			tinyPoint.x = tinyPoint3.x + (int)m_blupiVitesse.x;
			tinyPoint.y = tinyPoint3.y;
			if (BlupiBloque(tinyPoint, 1))
			{
				m_blupiVitesse.x = 0;
			}
		}
		else
		{
			if (m_blupiVitesse.x > 0)
			{
				m_blupiVitesse.x -= 1;
			}
			if (m_blupiVitesse.x < 0)
			{
				m_blupiVitesse.x += 1;
			}
		}
		tinyPoint3.x += (int)m_blupiVitesse.x;
		MoveObjectPollution();
		if ( !flag4 && m_blupiTransport == -1)
		{
			
			rect.left = m_blupiPos.x + 20;
			rect.right = m_blupiPos.x + 22;
			rect.top = m_blupiPos.y + 60 - 2;
			rect.bottom = m_blupiPos.y + 60;
			flag2 = !DecorDetect(rect);
			rect.left = m_blupiPos.x + 60 - 22;
			rect.right = m_blupiPos.x + 60 - 20;
			rect.top = m_blupiPos.y + 60 - 2;
			rect.bottom = m_blupiPos.y + 60;
			flag3 = !DecorDetect(rect);
			if (!flag2 && !flag3)
			{
				tinyPoint.x = m_blupiPos.x;
				tinyPoint.y = m_blupiPos.y - BLUPIFLOOR;
				ObjectStart(tinyPoint, 46, 0);
				m_blupiOver = FALSE;
				m_blupiAction = 1;
				m_blupiPhase = 0;
				m_blupiPosHelico = m_blupiPos;
				m_blupiFocus = TRUE;
				StopSound(16);
				StopSound(18);
				PlaySound(17, m_blupiPos);
			}
		}
	}
	if (m_blupiBalloon && m_blupiFocus)
	{
		if ((m_keyPress & 1) != 0)
		{
			if (m_blupiVitesse.y > -5 && m_time % 6 == 0)
			{
				m_blupiVitesse.y -= 1;
			}
		}
		else if (m_blupiSpeedY > 0)
		{
			if (m_blupiVitesse.y < 0 && m_time % 6 == 0)
			{
				m_blupiVitesse.y += 1;
			}
		}
		else if (m_blupiVitesse.y > -3 && m_time % 6 == 0)
		{
			m_blupiVitesse.y -= 1;
		}
		tinyPoint3.y += (int)m_blupiVitesse.y;
		if (m_blupiSpeedX < 0)
		{
			int num11 = (int)(m_blupiSpeedX * 10);
			if (m_blupiVitesse.x > num11)
			{
				m_blupiVitesse.x -= 1;
			}
			tinyPoint.x = tinyPoint3.x + (int)m_blupiVitesse.x;
			tinyPoint.y = tinyPoint3.y;
			if (BlupiBloque(tinyPoint, -1))
			{
				m_blupiVitesse.x = 0;
			}
		}
		else if (m_blupiSpeedX > 0)
		{
			int num12 = (int)(m_blupiSpeedX * 10);
			if (m_blupiVitesse.x < num12)
			{
				m_blupiVitesse.x += 1;
			}
			tinyPoint.x = tinyPoint3.x + (int)m_blupiVitesse.x;
			tinyPoint.y = tinyPoint3.y;
			if (BlupiBloque(tinyPoint, 1))
			{
				m_blupiVitesse.x = 0;
			}
		}
		else
		{
			if (m_blupiVitesse.x > 0)
			{
				m_blupiVitesse.x -= 2;
				if (m_blupiVitesse.x < 0)
				{
					m_blupiVitesse.x = 0;
				}
			}
			if (m_blupiVitesse.x < 0)
			{
				m_blupiVitesse.x += 2;
				if (m_blupiVitesse.x > 0)
				{
					m_blupiVitesse.x = 0;
				}
			}
		}
		tinyPoint3.x += (int)m_blupiVitesse.x;
	}
	if (m_blupiEcrase && m_blupiFocus)
	{
		if (flag4)
		{
			if (m_blupiVitesse.y < 2)
			{
				m_blupiVitesse.y += 1;
			}
		}
		else
		{
			m_blupiVitesse.y = 0;
		}
		tinyPoint3.y += (int)m_blupiVitesse.y;
		if (flag4)
		{
			num3 = 7;
		}
		else
		{
			num3 = 4;
		}
		num3 = (int)(num3 * m_blupiSpeedX);
		if (m_blupiSpeedX < 0)
		{
			if (m_blupiVitesse.x > num3)
			{
				m_blupiVitesse.x -= 1;
			}
			tinyPoint.x = tinyPoint3.x + (int)m_blupiVitesse.x;
			tinyPoint.y = tinyPoint3.y;
			if (BlupiBloque(tinyPoint, -1))
			{
				m_blupiVitesse.x = 0;
			}
		}
		else if (m_blupiSpeedX > 0)
		{
			if (m_blupiVitesse.x < num3)
			{
				m_blupiVitesse.x += 1;
			}
			tinyPoint.x = tinyPoint3.x + (int)m_blupiVitesse.x;
			tinyPoint.y = tinyPoint3.y;
			if (BlupiBloque(tinyPoint, 1))
			{
				m_blupiVitesse.x = 0;
			}
		}
		else
		{
			if (m_blupiVitesse.x > 0)
			{
				m_blupiVitesse.x -= 2;
				if (m_blupiVitesse.x < 0)
				{
					m_blupiVitesse.x = 0;
				}
			}
			if (m_blupiVitesse.x < 0)
			{
				m_blupiVitesse.x += 2;
				if (m_blupiVitesse.x > 0)
				{
					m_blupiVitesse.x = 0;
				}
			}
		}
		if (m_blupiVitesse.x == 0 && !flag4)
		{
			m_blupiAction = 1;
			m_blupiPhase = 0;
		}
		tinyPoint3.x += (int)m_blupiVitesse.x;
	}
	if (m_blupiJeep && m_blupiFocus)
	{
		if (m_blupiVitesse.x == 0 && m_blupiAction == 2)
		{
			m_blupiAction = 1;
			m_blupiPhase = 0;
		}
		//m_blupiMotorHigh = (m_blupiAction != 1);
		rect = BlupiRect(tinyPoint3);
		rect.right -= 40;
		rect.top = tinyPoint3.y + 60 - 2;
		rect.bottom = tinyPoint3.y + 60 - 1;
		bool flag8 = !DecorDetect(rect);
		rect.left += 40;
		rect.right += 40;
		bool flag9 = !DecorDetect(rect);
		if (flag4)
		{
			if (m_blupiVitesse.y < 50)
			{
				m_blupiVitesse.y += 5;
			}
		}
		else
		{
			if (m_blupiVitesse.y != 0)
			{
				PlaySound(3, m_blupiPos);
			}
			m_blupiVitesse.y = 0;
		}
		tinyPoint3.y += (int)m_blupiVitesse.y;
		if (m_blupiTransport == -1)
		{
			rect.left = tinyPoint3.x + 20;
			rect.right = tinyPoint3.x + 60 - 20;
			rect.top = tinyPoint3.y + 60 - 35;
			rect.bottom = tinyPoint3.y + 60 - 1;
			num = AscenseurDetect(rect, m_blupiPos, tinyPoint3);
			if (m_blupiVitesse.y >= 0 && num != -1)
			{
				m_blupiTransport = num;
				flag4 = FALSE;
				PlaySound(3, tinyPoint3);
				tinyPoint3.y = m_moveObject[num].posCurrent.y - 64 + BLUPIOFFY;
			}
		}
		if (flag8 && !flag9)
		{
			int num13 = -20;
			if (m_blupiVitesse.x > num13)
			{
				m_blupiVitesse.x -= 1;
			}
		}
		else if (!flag8 && flag9)
		{
			int num14 = 20;
			if (m_blupiVitesse.x < num14)
			{
				m_blupiVitesse.x += 1;
			}
		}
		else if (m_blupiSpeedX < 0)
		{
			int num15 = (int)(m_blupiSpeedX * 20);
			if (m_blupiVitesse.x > num15)
			{
				m_blupiVitesse.x -= 1;
			}
		}
		else if (m_blupiSpeedX > 0)
		{
			int num16 = (int)(m_blupiSpeedX * 20);
			if (m_blupiVitesse.x < num16)
			{
				m_blupiVitesse.x += 1;
			}
		}
		else
		{
			if (m_blupiVitesse.x > 0)
			{
				m_blupiVitesse.x -= 2;
				if (m_blupiVitesse.x < 0)
				{
					m_blupiVitesse.x = 0;
				}
			}
			if (m_blupiVitesse.x < 0)
			{
				m_blupiVitesse.x += 2;
				if (m_blupiVitesse.x > 0)
				{
					m_blupiVitesse.x = 0;
				}
			}
		}
		if (m_blupiAction == 3)
		{
			m_blupiVitesse.x = 0;
		}
		tinyPoint3.x += (int)m_blupiVitesse.x;
		MoveObjectPollution();
		if ( !flag4 && m_blupiTransport == -1)
		{
			tinyPoint.x = m_blupiPos.x;
			tinyPoint.y = m_blupiPos.y - BLUPIFLOOR;
			ObjectStart(tinyPoint, 19, 0);
			m_blupiJeep = FALSE;
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
					tinyPoint.x = m_blupiPos.x - 35;
					tinyPoint.y = m_blupiPos.y;
					num4 = -5;
					m_blupiVitesse.x += 12;
				}
				else
				{
					tinyPoint.x = m_blupiPos.x + 35;
					tinyPoint.y = m_blupiPos.y;
					num4 = 5;
					m_blupiVitesse.x -= 12;
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
		if (m_blupiVitesse.x == 0 && m_blupiAction == 2)
		{
			m_blupiAction = 1;
			m_blupiPhase = 0;
		}
		//m_blupiMotorHigh = (m_blupiAction != 1);
		if (flag4)
		{
			if (m_blupiVitesse.y < 50)
			{
				m_blupiVitesse.y += 5;
			}
		}
		else
		{
			if (m_blupiVitesse.y != 0)
			{
				PlaySound(3, m_blupiPos);
			}
			m_blupiVitesse.y = 0;
		}
		tinyPoint3.y += (int)m_blupiVitesse.y;
		if (m_blupiTransport == -1)
		{
			rect.left = tinyPoint3.x + 20;
			rect.right = tinyPoint3.x + 60 - 20;
			rect.top = tinyPoint3.y + 60 - 35;
			rect.bottom = tinyPoint3.y + 60 - 1;
			num = AscenseurDetect(rect, m_blupiPos, tinyPoint3);
			if (m_blupiVitesse.y >= 0 && num != -1)
			{
				m_blupiTransport = num;
				flag4 = FALSE;
				PlaySound(3, tinyPoint3);
				tinyPoint3.y = m_moveObject[num].posCurrent.y - 64 + BLUPIOFFY;
			}
		}
		if (m_blupiSpeedX < 0)
		{
			int num17 = (int)(m_blupiSpeedX * 12);
			if (m_blupiVitesse.x > num17)
			{
				m_blupiVitesse.x -= 1;
			}
		}
		else if (m_blupiSpeedX > 0)
		{
			int num18 = (int)(m_blupiSpeedX * 12);
			if (m_blupiVitesse.x < num18)
			{
				m_blupiVitesse.x += 1;
			}
		}
		else
		{
			if (m_blupiVitesse.x > 0)
			{
				m_blupiVitesse.x -= 3;
				if (m_blupiVitesse.x < 0)
				{
					m_blupiVitesse.x = 0;
				}
			}
			if (m_blupiVitesse.x < 0)
			{
				m_blupiVitesse.x += 3;
				if (m_blupiVitesse.x > 0)
				{
					m_blupiVitesse.x = 0;
				}
			}
		}
		if (m_blupiAction == 3)
		{
			m_blupiVitesse.x = 0;
		}
		tinyPoint3.x += (int)m_blupiVitesse.x;
		MoveObjectPollution();
		if ( !flag4 && m_blupiTransport == -1)
		{
			
			tinyPoint.x = m_blupiPos.x;
			tinyPoint.y = m_blupiPos.y;
			ObjectStart(tinyPoint, 28, 0);
			m_blupiTank = FALSE;
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
		if (m_blupiVitesse.x == 0 && m_blupiAction == 2)
		{
			m_blupiAction = 1;
			m_blupiPhase = 0;
		}
		if (m_blupiSpeedX < 0)
		{
			int num19 = (int)(m_blupiSpeedX * 15);
			if (m_blupiVitesse.x > num19)
			{
				m_blupiVitesse.x -= 1;
			}
		}
		else if (m_blupiSpeedX > 0)
		{
			int num20 = (int)(m_blupiSpeedX * 15);
			if (m_blupiVitesse.x < num20)
			{
				m_blupiVitesse.x += 1;
			}
		}
		else
		{
			if (m_blupiVitesse.x > 0)
			{
				m_blupiVitesse.x -= 1;
				if (m_blupiVitesse.x < 0)
				{
					m_blupiVitesse.x = 0;
				}
			}
			if (m_blupiVitesse.x < 0)
			{
				m_blupiVitesse.x += 1;
				if (m_blupiVitesse.x > 0)
				{
					m_blupiVitesse.x = 0;
				}
			}
		}
		if (m_blupiAction == 3)
		{
			m_blupiVitesse.x = 0;
		}
		tinyPoint3.x += (int)m_blupiVitesse.x;
		if ( !flag4 && !m_blupiAir && m_blupiTransport == -1 && m_blupiVitesse.x < 8)
		{
			
			m_blupiSkate = FALSE;
			m_blupiAction = 43;
			m_blupiPhase = 0;
			m_blupiFocus = FALSE;
			m_blupiPosHelico = m_blupiPos;
		}
	}
	if (m_blupiAction == 42)
	{
		if (m_blupiPhase == 8)
		{
			num = MoveObjectDetect(m_blupiPos, &flag6);
			if (num != -1)
			{
				ObjectDelete(m_moveObject[num].posCurrent, m_moveObject[num].type);
			}
		}
		if (m_blupiPhase == 20)
		{
			m_blupiAction = 1;
			m_blupiPhase = 0;
			m_blupiFocus = TRUE;
		}
	}
	if (m_blupiAction == 43)
	{
		if (m_blupiPhase == 12)
		{
			tinyPoint.x = m_blupiPos.x;
			tinyPoint.y = m_blupiPos.y - BLUPIFLOOR + 1;
			ObjectStart(tinyPoint, 24, 0);
		}
		if (m_blupiPhase == 20)
		{
			m_blupiAction = 1;
			m_blupiPhase = 0;
			m_blupiFocus = TRUE;
		}
	}
	if (m_blupiNage && m_blupiFocus)
	{
		if (m_blupiTransport == -1)
		{
			if ((m_keyPress & 1) != 0)
			{
				if (m_blupiVitesse.y > -5)
				{
					m_blupiVitesse.y -= 1;
				}
			}
			else if (m_blupiVitesse.y < 5)
			{
				m_blupiVitesse.y += 1;
				
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
				if (m_blupiVitesse.y > num3)
				{
					m_blupiVitesse.y -= 1;
				}
				if (m_blupiVitesse.y < num3)
				{
					m_blupiVitesse.y += 1;
				}
			}
			tinyPoint3.y += (int)m_blupiVitesse.y;
		}
		if (m_blupiSpeedX < 0)
		{
			int num21 = (int)(m_blupiSpeedX * 8);
			if (m_blupiVitesse.x > num21)
			{
				m_blupiVitesse.x -= 1;
			}
		}
		else if (m_blupiSpeedX > 0)
		{
			int num22 = (int)(m_blupiSpeedX * 8);
			if (m_blupiVitesse.x < num22)
			{
				m_blupiVitesse.x += 1;
			}
		}
		else
		{
			if (m_blupiVitesse.x > 0)
			{
				m_blupiVitesse.x -= 2;
				if (m_blupiVitesse.x < 0)
				{
					m_blupiVitesse.x = 0;
				}
			}
			if (m_blupiVitesse.x < 0)
			{
				m_blupiVitesse.x += 2;
				if (m_blupiVitesse.x > 0)
				{
					m_blupiVitesse.x = 0;
				}
			}
		}
		num = table_vitesse_nage[m_blupiPhase % 14 / 2];
		tinyPoint3.x += (int)(m_blupiVitesse.x * num / 7);
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
				//m_jauges[0].SetMode(1);
			}
			m_jauges[0].SetLevel(m_blupiLevel);
			if (m_blupiLevel == 0)
			{
				m_blupiAction = 24;
				m_blupiPhase = 0;
				m_blupiFocus = FALSE;
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
				m_blupiAir = FALSE;
				m_blupiRestart = TRUE;
				m_blupiActionOuf = 0;
				m_jauges[0].SetHide(TRUE);
				m_jauges[1].SetHide(TRUE);
				PlaySound(26, tinyPoint3);
			}
		}
	}
	if (m_blupiSurf && m_blupiFocus)
	{
		if (m_blupiTransport == -1)
		{
			if ((m_keyPress & 1) != 0)
			{
				if (m_blupiVitesse.y > -5)
				{
					m_blupiVitesse.y -= 1;
				}
			}
			else if (m_blupiSpeedY > 0)
			{
				if (m_blupiVitesse.y < 5)
				{
					m_blupiVitesse.y += 1;
				}
			}
			else
			{
				if (m_blupiVitesse.y > -2)
				{
					m_blupiVitesse.y -= 1;
				}
				if (m_blupiVitesse.y < -2)
				{
					m_blupiVitesse.y += 1;
				}
			}
			tinyPoint3.y += (int)m_blupiVitesse.y;
			tinyPoint3.y += BLUPISURF;
			if (tinyPoint3.y % 64 > 30)
			{
				tinyPoint3.y += 64 - tinyPoint3.y % 64;
			}
			tinyPoint3.y -= BLUPISURF;
		}
		if (m_blupiSpeedX < 0)
		{
			int num23 = (int)(m_blupiSpeedX * 8);
			if (m_blupiVitesse.x > num23)
			{
				m_blupiVitesse.x -= 1;
			}
		}
		else if (m_blupiSpeedX > 0)
		{
			int num24 = (int)(m_blupiSpeedX * 8);
			if (m_blupiVitesse.x < num24)
			{
				m_blupiVitesse.x += 1;
			}
		}
		else
		{
			if (m_blupiVitesse.x > 0)
			{
				m_blupiVitesse.x -= 2;
				if (m_blupiVitesse.x < 0)
				{
					m_blupiVitesse.x = 0;
				}
			}
			if (m_blupiVitesse.x < 0)
			{
				m_blupiVitesse.x += 2;
				if (m_blupiVitesse.x > 0)
				{
					m_blupiVitesse.x = 0;
				}
			}
		}
		num = table_vitesse_surf[m_blupiPhase % 12 / 2];
		tinyPoint3.x += (int)(m_blupiVitesse.x * num / 10);
	}
	POINT tinyPoint4;
	if (m_blupiSuspend && m_blupiFocus)
	{
		if (m_blupiSpeedX < 0 && m_blupiAction == 2)
		{
			int num25 = (int)(m_blupiSpeedX * 5);
			tinyPoint3.x += num25;
		}
		if (m_blupiSpeedX > 0 && m_blupiAction == 2)
		{
			int num26 = (int)(m_blupiSpeedX * 5);
			tinyPoint3.x += num26;
		}
		num = GetTypeBarre(tinyPoint3);
		if (num == 2)
		{
			tinyPoint4.x = tinyPoint3.x;
			tinyPoint4.y = tinyPoint3.y / 64 * 64 + BLUPIOFFY;
			rect = BlupiRect(tinyPoint4);
			if (!DecorDetect(rect, TRUE))
			{
				m_blupiSuspend = FALSE;
				m_blupiAction = 1;
				m_blupiPhase = 0;
				tinyPoint3 = tinyPoint4;
				m_blupiPos = tinyPoint3;
			}
		}
		if ((m_blupiSpeedY > 0 && m_blupiPhase > 5) || num == 0)
		{
			m_blupiSuspend = FALSE;
			m_blupiAir = TRUE;
			m_blupiAction = 5;
			tinyPoint3.y = tinyPoint3.y;
			m_blupiVitesse.y = 0;
			m_blupiNoBarre = 5;
			m_blupiActionOuf = 65;
			m_blupiTimeOuf = 0;
		}
		if (((m_keyPress & 1) != 0 || m_blupiSpeedY < 0) && m_blupiAction != 4 && m_blupiAction != 3)
		{
			m_blupiAction = 4;
			m_blupiPhase = 0;
		}
		if ((m_keyPress & 1) == 0 && m_blupiSpeedY == 0 && m_blupiAction == 4)
		{
			m_blupiAction = 1;
			m_blupiPhase = 0;
		}
		if (m_blupiAction == 4 && m_blupiPhase == 10)
		{
			m_blupiSuspend = FALSE;
			m_blupiAir = TRUE;
			m_blupiAction = 5;
			m_blupiPhase = 0;
			tinyPoint3.y -= 2;
			m_blupiVitesse.y = -11;
			m_blupiNoBarre = 5;
			PlaySound(35, tinyPoint3);
		}
	}
	if ( !m_blupiHelico && !m_blupiOver && !m_blupiBalloon && !m_blupiEcrase && !m_blupiTank && !m_blupiJeep && !m_blupiSkate && !flag4 && m_blupiTransport == -1 && m_blupiFocus)
	{
		if (m_blupiDynamite > 0)
		{
			
			rect.left = tinyPoint3.x + 18;
			rect.right = tinyPoint3.x + 20;
			rect.top = tinyPoint3.y + 60 - 2;
			rect.bottom = tinyPoint3.y + 60;
			flag2 = !DecorDetect(rect);
			rect.left = tinyPoint3.x + 60 - 20;
			rect.right = tinyPoint3.x + 60 - 18;
			rect.top = tinyPoint3.y + 60 - 2;
			rect.bottom = tinyPoint3.y + 60;
			flag3 = !DecorDetect(rect);
			if (!flag2 && !flag3 && ObjectStart(tinyPoint3, 56, 0) != -1)
			{
				m_blupiAction = 87;
				m_blupiPhase = 0;
				m_blupiFocus = FALSE;
				PlaySound(61, tinyPoint3);
				m_blupiDynamite--;
			}
		}
		else if (m_blupiPerso > 0)
		{
			num = MoveObjectDetect(tinyPoint3, &flag6);
			if (num == -1 || m_moveObject[num].type != 200)
			{
				rect.left = tinyPoint3.x + 18;
				rect.right = tinyPoint3.x + 20;
				rect.top = tinyPoint3.y + 60 - 2;
				rect.bottom = tinyPoint3.y + 60;
				flag2 = !DecorDetect(rect);
				rect.left = tinyPoint3.x + 60 - 20;
				rect.right = tinyPoint3.x + 60 - 18;
				rect.top = tinyPoint3.y + 60 - 2;
				rect.bottom = tinyPoint3.y + 60;
				flag3 = !DecorDetect(rect);
				num = MoveChargeDetect(tinyPoint3);
				if (num == -1 && !flag2 && !flag3 && ObjectStart(tinyPoint3, 200, 0) != -1)
				{
					m_blupiAction = 46;
					m_blupiPhase = 0;
					m_blupiFocus = FALSE;
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
	TestPath(rect, m_blupiPos,tinyPoint3);
	if (flag && m_blupiPos.x == tinyPoint3.x && m_blupiPos.x != tinyPoint4.x)
	{
		tinyPoint3.y = tinyPoint4.y;
		TestPath(rect, m_blupiPos, tinyPoint3);
	}
	if (m_blupiVent && m_blupiPos.y == tinyPoint3.y && m_blupiPos.y != tinyPoint4.y)
	{
		tinyPoint3.x = tinyPoint4.x;
		TestPath(rect, m_blupiPos, tinyPoint3);
	}
	if (m_blupiTransport != -1 && m_blupiPos.x == tinyPoint3.x && m_blupiPos.x != tinyPoint4.x)
	{
		tinyPoint3.y = tinyPoint4.y;
		TestPath(rect, m_blupiPos, tinyPoint3);
	}
	if (m_blupiHelico || m_blupiOver || m_blupiBalloon || m_blupiEcrase || m_blupiJeep || m_blupiTank || m_blupiSkate || m_blupiNage)
	{
		if (m_blupiPos.x == tinyPoint3.x && m_blupiPos.x != tinyPoint4.x)
		{
			tinyPoint3.y = tinyPoint4.y;
			TestPath(rect, m_blupiPos, tinyPoint3);
		}
		else if (m_blupiPos.y == tinyPoint3.y && m_blupiPos.y != tinyPoint4.y)
		{
			tinyPoint3.x = tinyPoint4.x;
			TestPath(rect, m_blupiPos, tinyPoint3);
		}
	}
	POINT blupiPos = m_blupiPos;
	m_blupiPos = tinyPoint3;
	if ((m_blupiAction == 1 || m_blupiAction == 60 || m_blupiAction == 7 || m_blupiAction == 6) && !m_blupiAir && !m_blupiBalloon && !m_blupiEcrase && !m_blupiJeep && !m_blupiTank && !m_blupiSkate && !m_blupiNage && !m_blupiSurf && !m_blupiSuspend && m_blupiFocus)
	{
		if (m_blupiTransport != -1)
		{
			AscenseurVertigo(m_blupiTransport, &flag2, &flag3);
		}
		else
		{
			rect.left = tinyPoint3.x + 24;
			rect.right = tinyPoint3.x + 26;
			rect.top = tinyPoint3.y + 60 - 2;
			rect.bottom = tinyPoint3.y + 60;
			flag2 = !DecorDetect(rect);
			rect.left = tinyPoint3.x + 60 - 26;
			rect.right = tinyPoint3.x + 60 - 24;
			rect.top = tinyPoint3.y + 60 - 2;
			rect.bottom = tinyPoint3.y + 60;
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
			AscenseurVertigo(m_blupiTransport, &flag2, &flag3);
		}
		else
		{
			rect.left = tinyPoint3.x + 2;
			rect.right = tinyPoint3.x + 18;
			rect.top = tinyPoint3.y + 60 - 2;
			rect.bottom = tinyPoint3.y + 60;
			flag2 = !DecorDetect(rect);
			rect.left = tinyPoint3.x + 60 - 18;
			rect.right = tinyPoint3.x + 60 - 2;
			rect.top = tinyPoint3.y + 60 - 2;
			rect.bottom = tinyPoint3.y + 60;
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
			AscenseurVertigo(m_blupiTransport, &flag2, &flag3);
		}
		else
		{
			rect.left = tinyPoint3.x + 2;
			rect.right = tinyPoint3.x + 18;
			rect.top = tinyPoint3.y + 60 - 2;
			rect.bottom = tinyPoint3.y + 60;
			flag2 = !DecorDetect(rect);
			rect.left = tinyPoint3.x + 60 - 18;
			rect.right = tinyPoint3.x + 60 - 2;
			rect.top = tinyPoint3.y + 60 - 2;
			rect.bottom = tinyPoint3.y + 60;
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
			AscenseurVertigo(m_blupiTransport, &flag2, &flag3);
		}
		else
		{
			rect.left = tinyPoint3.x + 12;
			rect.right = tinyPoint3.x + 19;
			rect.top = tinyPoint3.y + 60 - 2;
			rect.bottom = tinyPoint3.y + 60;
			flag2 = !DecorDetect(rect);
			rect.left = tinyPoint3.x + 60 - 19;
			rect.right = tinyPoint3.x + 60 - 12;
			rect.top = tinyPoint3.y + 60 - 2;
			rect.bottom = tinyPoint3.y + 60;
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
			m_blupiShield = FALSE;
			m_jauges[1].SetHide(TRUE);
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
			m_blupiPower = FALSE;
			m_jauges[1].SetHide(TRUE);
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
			m_blupiCloud = FALSE;
			m_jauges[1].SetHide(TRUE);
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
			m_blupiHide = FALSE;
			m_jauges[1].SetHide(TRUE);
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
			m_blupiInvert = FALSE;
			m_jauges[1].SetHide(TRUE);
			tinyPoint.x = m_blupiPos.x;
			tinyPoint.y = m_blupiPos.y + 100;
			ObjectStart(tinyPoint, 42, -60);
			tinyPoint.x = m_blupiPos.x;
			tinyPoint.y = m_blupiPos.y - 100;
			ObjectStart(tinyPoint, 42, 60);
			tinyPoint.x = m_blupiPos.x - 100;
			tinyPoint.y = m_blupiPos.y;
			ObjectStart(tinyPoint, 42, 10);
			tinyPoint.x = m_blupiPos.x + 100;
			tinyPoint.y = m_blupiPos.y;
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
			m_blupiBalloon = FALSE;
			m_jauges[1].SetHide(TRUE);
			tinyPoint.x = m_blupiPos.x - 34;
			tinyPoint.y = m_blupiPos.y - 34;
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
			m_blupiEcrase = FALSE;
			m_blupiAir = TRUE;
			m_jauges[1].SetHide(TRUE);
			ObjectStart(m_blupiPos, 41, -60);
			ObjectStart(m_blupiPos, 41, 60);
			ObjectStart(m_blupiPos, 41, 10);
			ObjectStart(m_blupiPos, 41, -10);
			tinyPoint.x = m_blupiPos.x - 34;
			tinyPoint.y = m_blupiPos.y - 34;
			ObjectStart(tinyPoint, 90, 0);
			PlaySound(41, m_blupiPos);
		}
		else if (m_time % 2 == 0)
		{
			m_blupiTimeShield--;
			m_jauges[1].SetLevel(m_blupiTimeShield);
		}
	}
	if (m_blupiPower && abs(m_blupiPos.x - m_blupiPosMagic.x) + abs(m_blupiPos.y - m_blupiPosMagic.y) >= 40)
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
	if (m_blupiShield && abs(m_blupiPos.x - m_blupiPosMagic.x) + abs(m_blupiPos.y - m_blupiPosMagic.y) >= 40)
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
	if (m_blupiHide && abs(m_blupiPos.x - m_blupiPosMagic.x) + abs(m_blupiPos.y - m_blupiPosMagic.y) >= 10)
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
	if (m_blupiHelico && m_blupiPos.y > 2 && m_blupiFocus && !m_blupiShield && !m_blupiHide && !m_bSuperBlupi)
	{
		rect = BlupiRect(tinyPoint3);
		rect.top = tinyPoint3.y + 4;
		rect.bottom = tinyPoint3.y + 20;
		if (DecorDetect(rect))
		{
			m_blupiAction = 1;
			m_blupiPhase = 0;
			m_blupiHelico = FALSE;
			tinyPoint.x = m_blupiPos.x - 34;
			tinyPoint.y = m_blupiPos.y - 34;
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
			m_scrollAdd.x = 0;
			m_scrollAdd.y = 0;
			m_blupiAir = FALSE;
			m_blupiNage = FALSE;
			m_blupiSurf = TRUE;
			m_blupiAction = 1;
			m_blupiPhase = 0;
			m_blupiVitesse.x = 0;
			m_blupiVitesse.y = 0;
			MoveObjectPlouf(m_blupiPos);
			if (m_blupiTransport != -1)
			{
				m_blupiPos.y = m_blupiPos.y - 10;
				m_blupiTransport = -1;
			}
			if (m_blupiCloud)
			{
				m_blupiCloud = FALSE;
				m_jauges[1].SetHide(TRUE);
			}
		}
		if (!m_blupiNage && !IsSurfWater(m_blupiPos) && IsDeepWater(m_blupiPos))
		{
			if (!m_blupiSurf)
			{
				m_blupiAction = 1;
				m_blupiPhase = 0;
				m_blupiVitesse.x = 0;
				m_blupiVitesse.y = 0;
				MoveObjectPlouf(m_blupiPos);
			}
			m_blupiAir = FALSE;
			m_blupiSurf = FALSE;
			m_blupiNage = TRUE;
			m_blupiLevel = 100;
			m_jauges[0].SetLevel(m_blupiLevel);
			//m_jauges[0].SetMode(2);
			m_jauges[0].SetHide(FALSE);
		}
		if (m_blupiNage && IsSurfWater(m_blupiPos))
		{
			m_blupiAir = FALSE;
			m_blupiNage = FALSE;
			m_blupiSurf = TRUE;
			PlaySound(25, m_blupiPos);
			m_jauges[0].SetHide(TRUE);
		}
		tinyPoint4.x = m_blupiPos.x;
		tinyPoint4.y = m_blupiPos.y - 60;
		if ((m_blupiSurf || m_blupiNage) && (m_blupiPos.y % 64 == 64 - BLUPISURF || m_blupiPos.y % 64 == 32) && IsOutWater(tinyPoint4) && (m_keyPress & 1) != 0)
		{
			m_blupiNage = FALSE;
			m_blupiSurf = FALSE;
			m_blupiAir = TRUE;
			m_blupiAction = 5;
			m_blupiPhase = 0;
			m_blupiVitesse.x = 0;
			if (m_blupiPower)
			{
				m_blupiVitesse.y = -16;
			}
			else
			{
				m_blupiVitesse.y = -12;
			}
			MoveObjectTiplouf(m_blupiPos);
			PlaySound(22, m_blupiPos);
			m_jauges[0].SetHide(TRUE);
		}
		if ((m_blupiSurf || m_blupiNage) && IsOutWater(m_blupiPos))
		{
			if (m_blupiVitesse.y < 0)
			{
				if (m_blupiTransport == -1)
				{
					m_blupiPos = blupiPos;
				}
				else
				{
					m_blupiTransport = -1;
					m_blupiNage = FALSE;
					m_blupiSurf = FALSE;
					m_blupiAir = TRUE;
					m_blupiAction = 5;
					m_blupiPhase = 0;
					m_blupiPos.y = m_blupiPos.y - 10;
					m_blupiVitesse.x = 0;
					m_blupiVitesse.y = -10;
					PlaySound(22, m_blupiPos);
					m_jauges[0].SetHide(TRUE);
				}
			}
			else if (m_blupiVitesse.y > 0)
			{
				m_blupiNage = FALSE;
				m_blupiSurf = FALSE;
				m_blupiAir = FALSE;
				m_blupiAction = 5;
				m_blupiPhase = 0;
				m_blupiPos.y = m_blupiPos.y + 30;
				m_blupiVitesse.x = 0;
				m_blupiVitesse.y = 0;
				PlaySound(22, m_blupiPos);
				m_jauges[0].SetHide(TRUE);
			}
			else
			{
				m_blupiNage = FALSE;
				m_blupiSurf = FALSE;
				m_blupiAir = FALSE;
				m_blupiAction = 1;
				m_blupiPhase = 0;
				m_blupiPos.y = m_blupiPos.y - 10;
				m_blupiVitesse.x = 0;
				m_blupiVitesse.y = 0;
				PlaySound(22, m_blupiPos);
				m_jauges[0].SetHide(TRUE);
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
		
		m_blupiAction = 1;
		m_blupiPhase = 0;
		m_blupiHelico = FALSE;
		m_blupiOver = FALSE;
		m_blupiJeep = FALSE;
		m_blupiTank = FALSE;
		m_blupiSkate = FALSE;
		tinyPoint.x = m_blupiPos.x - 34;
		tinyPoint.y = m_blupiPos.y - 34;
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
		tinyPoint4.x = m_blupiPos.x;
		tinyPoint4.y = (m_blupiPos.y + 22) / 64 * 64 + BLUPISUSPEND;
		rect = BlupiRect(tinyPoint4);
		if (!DecorDetect(rect, TRUE))
		{
			m_blupiPos = tinyPoint4;
			m_blupiSuspend = TRUE;
			m_blupiAir = FALSE;
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
		tinyPoint.x = m_blupiPos.x - 34;
		tinyPoint.y = m_blupiPos.y - 34;
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
			m_blupiFocus = FALSE;
			m_blupiFront = TRUE;
		}
	}
	int num27 = MoveObjectDetect(m_blupiPos, &flag6);
	POINT tinyPoint5;
	if (m_blupiAction != 11 && m_blupiAction != 75 && m_blupiAction != 76 && m_blupiAction != 77 && m_blupiAction != 78 && m_blupiAction != 79 && m_blupiAction != 80 && m_blupiAction != 81)
	{
		if (IsLave(m_blupiPos) && !m_blupiShield && !m_blupiHide && !m_bSuperBlupi)
		{
			BlupiDead(76, -1);
			m_blupiRestart = TRUE;
			m_blupiPos.y = m_blupiPos.y / DIMOBJY * 64 + BLUPIOFFY;
			PlaySound(8, m_blupiPos);
		}
		if (IsPiege(m_blupiPos) && !m_blupiOver && !m_blupiJeep && !m_blupiTank && !m_blupiShield && !m_blupiHide && !m_bSuperBlupi && m_blupiFocus)
		{
			BlupiDead(54, -1);
			m_blupiRestart = TRUE;
			m_blupiAir = TRUE;
			ObjectStart(m_blupiPos, 53, 0);
			PlaySound(51, m_blupiPos);
		}
		if (IsGoutte(m_blupiPos, FALSE) && !m_blupiOver && !m_blupiJeep && !m_blupiTank && !m_blupiShield && !m_blupiHide && !m_bSuperBlupi && m_blupiFocus)
		{
			BlupiDead(54, -1);
			m_blupiRestart = TRUE;
			m_blupiAir = TRUE;
			PlaySound(51, m_blupiPos);
		}
		if (IsScie(m_blupiPos) && !m_blupiOver && !m_blupiJeep && !m_blupiTank && !m_blupiShield && !m_blupiHide && !m_bSuperBlupi && m_blupiFocus)
		{
			BlupiDead(77, -1);
			m_blupiFront = TRUE;
			m_blupiRestart = TRUE;
			m_blupiAir = TRUE;
		}
		if ( (num27 == -1 || !flag6) && IsSwitch(m_blupiPos, tinyPoint) && !m_blupiOver && !m_blupiBalloon && !m_blupiJeep && !m_blupiTank && !m_blupiSkate && !m_blupiShield && !m_blupiHide && !m_bSuperBlupi && m_blupiFocus)
		{
			
			ActiveSwitch(m_decor[tinyPoint.x][tinyPoint.y].icon == 385, tinyPoint);
			m_blupiAction = 82;
			m_blupiPhase = 0;
			m_blupiFocus = FALSE;
			m_blupiVitesse.x = 0;
			m_blupiVitesse.y = 0;
		}
		if (IsBlitz(m_blupiPos, FALSE) && !m_blupiShield && !m_blupiHide && !m_bSuperBlupi)
		{
			BlupiDead(11, -1);
			m_blupiRestart = TRUE;
			m_blupiAir = TRUE;
			m_blupiPos.y = m_blupiPos.y / DIMOBJY * 64 + BLUPIOFFY;
			PlaySound(8, m_blupiPos);
		}
		if (IsEcraseur(m_blupiPos) && !m_blupiEcrase && !m_blupiShield && !m_blupiHide && !m_bSuperBlupi && m_blupiFocus)
		{
			m_blupiAction = 1;
			m_blupiPhase = 0;
			m_blupiVitesse.x = 0;
			m_blupiVitesse.y = 0;
			m_blupiEcrase = TRUE;
			m_blupiBalloon = FALSE;
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
			m_blupiTimeShield = 100;
			m_blupiPosMagic = m_blupiPos;
			m_jauges[1].SetHide(FALSE);
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
			tinyPoint.x = m_blupiPos.x - 34;
			tinyPoint.y = m_blupiPos.y - 34;
			ObjectStart(tinyPoint, 90, 0);
			m_decorAction = 2;
			m_decorPhase = 0;
		}
		if (IsTeleporte(m_blupiPos) != -1 && !m_blupiHelico && !m_blupiOver && !m_blupiBalloon && !m_blupiEcrase && !m_blupiJeep && !m_blupiTank && !m_blupiSkate && !m_blupiAir && m_blupiFocus && m_blupiPosHelico.x == -1)
		{
			m_blupiAction = 74;
			m_blupiPhase = 0;
			m_blupiVitesse.x = 0;
			m_blupiVitesse.y = 0;
			m_blupiFocus = FALSE;
			m_blupiPos.x = m_blupiPos.x / DIMOBJX * 64;
			PlaySound(71, m_blupiPos);
			tinyPoint.x = m_blupiPos.x;
			tinyPoint.y = m_blupiPos.y - 5;
			ObjectStart(tinyPoint, 92, 0);
		}
		tinyPoint2.x = 0;
		tinyPoint2.y = 0;
		if (IsBridge(m_blupiPos, tinyPoint2) && m_blupiFocus)
		{
			tinyPoint2.x *= 64;
			tinyPoint2.y *= 64;
			ObjectStart(tinyPoint2, 52, 0);
		}
		int num2 = IsDoor(m_blupiPos, tinyPoint2);
		if (num2 != -1 && (m_blupiCle & 1 << num2 - 334) != 0)
		{
			OpenDoor(tinyPoint2);
			m_blupiCle &= ~(1 << num2 - 334);
			tinyPoint.x = 520;
			tinyPoint.y = 418;
			tinyPoint5.x = tinyPoint2.x * 64 - m_posDecor.x;
			tinyPoint5.y = tinyPoint2.y * 64 - m_posDecor.y;
			////VoyageInit(tinyPoint, m_pPixmap->HotSpotToHud(tinyPoint5), 214 + (num2 - 334) * 7, 10);
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
		if (m_moveObject[num].type == 13 && !m_blupiHelico && !m_blupiOver && !m_blupiBalloon && !m_blupiEcrase && !m_blupiJeep && !m_blupiTank && !m_blupiSkate && !m_blupiNage && !m_blupiSurf && !m_blupiSuspend && m_blupiFocus)
		{
			ObjectDelete(m_moveObject[num].posCurrent, m_moveObject[num].type);
			m_scrollAdd.x = 0;
			m_scrollAdd.y = 0;
			m_blupiAir = FALSE;
			m_blupiHelico = TRUE;
			m_blupiVitesse.x = 0;
			if (m_blupiCloud || m_blupiHide)
			{
				m_blupiCloud = FALSE;
				m_blupiHide = FALSE;
				m_jauges[1].SetHide(TRUE);
			}
		}
		if (m_moveObject[num].type == 46 && !m_blupiHelico && !m_blupiOver && !m_blupiBalloon && !m_blupiEcrase && !m_blupiJeep && !m_blupiTank && !m_blupiSkate && !m_blupiNage && !m_blupiSurf && !m_blupiSuspend && m_blupiFocus)
		{
			ObjectDelete(m_moveObject[num].posCurrent, m_moveObject[num].type);
			m_scrollAdd.x = 0;
			m_scrollAdd.y = 0;
			m_blupiAir = FALSE;
			m_blupiOver = TRUE;
			m_blupiVitesse.x = 0;
			if (m_blupiCloud || m_blupiHide)
			{
				m_blupiCloud = FALSE;
				m_blupiHide = FALSE;
				m_jauges[1].SetHide(TRUE);
			}
		}
		if (m_moveObject[num].type == 19 && !m_blupiHelico && !m_blupiOver && !m_blupiBalloon && !m_blupiEcrase && !m_blupiJeep && !m_blupiTank && !m_blupiSkate && !m_blupiNage && !m_blupiSurf && !m_blupiSuspend && m_blupiFocus)
		{
			ObjectDelete(m_moveObject[num].posCurrent, m_moveObject[num].type);
			m_scrollAdd.x = 0;
			m_scrollAdd.y = 0;
			m_blupiAction = 1;
			m_blupiPhase = 0;
			m_blupiAir = FALSE;
			m_blupiJeep = TRUE;
			m_blupiVitesse.x = 0;
			if (m_blupiCloud || m_blupiHide)
			{
				m_blupiCloud = FALSE;
				m_blupiHide = FALSE;
				m_jauges[1].SetHide(TRUE);
			}
		}
		if ( m_moveObject[num].type == 28 && !m_blupiHelico && !m_blupiOver && !m_blupiBalloon && !m_blupiEcrase && !m_blupiJeep && !m_blupiTank && !m_blupiSkate && !m_blupiNage && !m_blupiSurf && !m_blupiSuspend && m_blupiFocus)
		{
			
			ObjectDelete(m_moveObject[num].posCurrent, m_moveObject[num].type);
			m_scrollAdd.x = 0;
			m_scrollAdd.y = 0;
			m_blupiAction = 1;
			m_blupiPhase = 0;
			m_blupiAir = FALSE;
			m_blupiTank = TRUE;
			m_blupiVitesse.x = 0;
			if (m_blupiCloud || m_blupiHide)
			{
				m_blupiCloud = FALSE;
				m_blupiHide = FALSE;
				m_jauges[1].SetHide(TRUE);
			}
		}
		if (m_moveObject[num].type == 29 && m_blupiFocus && m_blupiBullet < 10)
		{
			ObjectDelete(m_moveObject[num].posCurrent, m_moveObject[num].type);
			tinyPoint.x = m_moveObject[num].posCurrent.x - m_posDecor.x;
			tinyPoint.y = m_moveObject[num].posCurrent.y - m_posDecor.y;
			tinyPoint5.x = 570;
			tinyPoint5.y = 430;
			////VoyageInit(m_pPixmap->HotSpotToHud(tinyPoint), tinyPoint5, 177, 10);
			m_blupiBullet += 10;
			if (m_blupiBullet > 10)
			{
				m_blupiBullet = 10;
			}
		}
		if ( m_moveObject[num].type == 24 && !m_blupiHelico && !m_blupiOver && !m_blupiBalloon && !m_blupiEcrase && !m_blupiJeep && !m_blupiTank && !m_blupiSkate && !m_blupiNage && !m_blupiSurf && !m_blupiSuspend && m_blupiFocus)
		{
			
			m_scrollAdd.x = 0;
			m_scrollAdd.y = 0;
			m_blupiAction = 42;
			m_blupiPhase = 0;
			m_blupiPos.y = m_moveObject[num].posCurrent.y / 64 * 64 + BLUPIOFFY;
			m_blupiFocus = FALSE;
			m_blupiAir = FALSE;
			m_blupiSkate = TRUE;
			m_blupiVitesse.x = 0;
			if (m_blupiCloud || m_blupiHide)
			{
				m_blupiCloud = FALSE;
				m_blupiHide = FALSE;
				m_jauges[1].SetHide(TRUE);
			}
		}
		if ((m_moveObject[num].type == 3 || m_moveObject[num].type == 16 || m_moveObject[num].type == 96 || m_moveObject[num].type == 97) && m_blupiBalloon && m_blupiPosHelico.x == -1)
		{
			m_blupiBalloon = FALSE;
			m_blupiAir = TRUE;
			m_blupiTimeShield = 0;
			m_jauges[1].SetHide(TRUE);
			m_decorAction = 0;
			tinyPoint.x = m_blupiPos.x - 34;
			tinyPoint.y = m_blupiPos.y - 34;
			ObjectStart(tinyPoint, 91, 0);
			PlaySound(41, m_blupiPos);
			m_blupiPos.y = m_blupiPos.y + 4;
			m_blupiVitesse.y = 0;
			m_blupiPosHelico = m_blupiPos;
		}
		else if ((m_moveObject[num].type == 2 || m_moveObject[num].type == 3 || m_moveObject[num].type == 96 || m_moveObject[num].type == 97 || m_moveObject[num].type == 16 || m_moveObject[num].type == 4 || m_moveObject[num].type == 17 || m_moveObject[num].type == 20) && !m_blupiShield && !m_blupiHide && !m_bSuperBlupi && m_blupiPosHelico.x == -1)
		{
			if (!m_blupiJeep && !m_blupiTank && !m_blupiSkate && (m_blupiFocus || m_blupiAction == 5 || m_blupiAction == 36))
			{
				if (m_blupiHelico || m_blupiOver || m_blupiBalloon || m_blupiEcrase)
				{
					m_blupiAir = TRUE;
				}
				BlupiDead(11, 75);
			}
			if (m_moveObject[num].type == 17 || m_moveObject[num].type == 20)
			{
				tinyPoint = m_moveObject[num].posCurrent;
				ObjectDelete(tinyPoint, m_moveObject[num].type);
				tinyPoint.x -= 34;
				tinyPoint.y -= 34;
				ObjectStart(tinyPoint, 10, 0);
				m_decorAction = 2;
				m_decorPhase = 0;
			}
			else
			{
				tinyPoint = m_moveObject[num].posCurrent;
				ObjectDelete(tinyPoint, m_moveObject[num].type);
				tinyPoint.x -= 34;
				tinyPoint.y -= 34;
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
			
			m_blupiAction = 1;
			m_blupiPhase = 0;
			m_blupiVitesse.x = 0;
			m_blupiVitesse.y = 0;
			m_blupiBalloon = TRUE;
			m_blupiEcrase = FALSE;
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
			m_blupiTimeShield = 100;
			m_blupiPosMagic = m_blupiPos;
			m_jauges[1].SetHide(FALSE);
			if (!m_blupiJeep && !m_blupiTank)
			{
				StopSound(16);
				StopSound(18);
				StopSound(29);
				StopSound(31);
			}
			PlaySound(40, m_moveObject[num].posCurrent);
			tinyPoint.x = m_blupiPos.x - 34;
			tinyPoint.y = m_blupiPos.y - 34;
			ObjectStart(tinyPoint, 90, 0);
			m_decorAction = 5;
			m_decorPhase = 0;
		}
		if (m_moveObject[num].type == 54 && m_moveObject[num].step != 2 && m_moveObject[num].step != 4 && m_blupiFocus && !m_blupiBalloon && !m_blupiShield && !m_blupiHide && !m_bSuperBlupi)
		{
			
			tinyPoint.x = m_blupiPos.x;
			tinyPoint.y = (m_blupiPos.y + 64 - 10) / 64 * 64 + 4;
			ObjectStart(tinyPoint, 53, 0);
			m_blupiAction = 54;
			m_blupiPhase = 0;
			m_blupiSuspend = FALSE;
			m_blupiJumpAie = FALSE;
			m_blupiFocus = FALSE;
			m_blupiRestart = TRUE;
			if (flag4)
			{
				m_blupiAir = TRUE;
			}
			if (m_blupiHelico || m_blupiOver || m_blupiBalloon || m_blupiEcrase || m_blupiJeep || m_blupiTank || m_blupiSkate)
			{
				m_blupiHelico = FALSE;
				m_blupiOver = FALSE;
				m_blupiBalloon = FALSE;
				m_blupiEcrase = FALSE;
				m_blupiJeep = FALSE;
				m_blupiTank = FALSE;
				m_blupiSkate = FALSE;
				tinyPoint = m_moveObject[num].posCurrent;
				tinyPoint.x -= 34;
				tinyPoint.y -= 34;
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
			m_blupiCloud = FALSE;
			m_blupiHide = FALSE;
			m_jauges[1].SetHide(TRUE);
		}
		if (m_moveObject[num].type == 23 && !m_blupiShield && !m_blupiHide && !m_bSuperBlupi && m_blupiAction != 13 && m_blupiAction != 30 && m_blupiAction != 11 && m_blupiAction != 75 && m_blupiAction != 76 && m_blupiAction != 77 && m_blupiAction != 78 && m_blupiAction != 79 && m_blupiAction != 80 && m_blupiAction != 81 && m_blupiAction != 54 && m_blupiAction != 57 && m_blupiAction != 35)
		{
			
			tinyPoint = m_moveObject[num].posCurrent;
			ObjectDelete(tinyPoint, m_moveObject[num].type);
			m_blupiAction = 54;
			m_blupiPhase = 0;
			m_blupiSuspend = FALSE;
			m_blupiJumpAie = FALSE;
			m_blupiFocus = FALSE;
			m_blupiRestart = TRUE;
			if (flag4)
			{
				m_blupiAir = TRUE;
			}
			if (m_blupiHelico || m_blupiOver || m_blupiBalloon || m_blupiEcrase || m_blupiJeep || m_blupiTank || m_blupiSkate)
			{
				m_blupiHelico = FALSE;
				m_blupiOver = FALSE;
				m_blupiBalloon = FALSE;
				m_blupiEcrase = FALSE;
				m_blupiJeep = FALSE;
				m_blupiTank = FALSE;
				m_blupiSkate = FALSE;
			}
			StartSploutchGlu(m_moveObject[num].posCurrent);
			m_blupiCloud = FALSE;
			m_blupiHide = FALSE;
			m_jauges[1].SetHide(TRUE);
		}
		if (m_moveObject[num].type == 5)
		{
			ObjectDelete(m_moveObject[num].posCurrent, m_moveObject[num].type);
			tinyPoint.x = m_moveObject[num].posCurrent.x - m_posDecor.x;
			tinyPoint.y = m_moveObject[num].posCurrent.y - m_posDecor.y;
			POINT end;
			end.x = 430;
			end.y = 430;
			//VoyageInit(m_pPixmap->HotSpotToHud(tinyPoint), end, 6, 10);
			ObjectStart(m_moveObject[num].posCurrent, 39, -60);
			ObjectStart(m_moveObject[num].posCurrent, 39, 60);
			ObjectStart(m_moveObject[num].posCurrent, 39, 10);
			ObjectStart(m_moveObject[num].posCurrent, 39, -10);
		}
		if (m_moveObject[num].type == 49 && (m_voyageIcon != 215 || m_voyageChannel != 10) && (m_blupiCle & 1) == 0)
		{
			ObjectDelete(m_moveObject[num].posCurrent, m_moveObject[num].type);
			tinyPoint.x = m_moveObject[num].posCurrent.x - m_posDecor.x;
			tinyPoint.y = m_moveObject[num].posCurrent.y - m_posDecor.y;
			POINT end2;
			end2.x = 520;
			end2.y = 418;
			//VoyageInit(m_pPixmap->HotSpotToHud(tinyPoint), end2, 215, 10);
			ObjectStart(m_moveObject[num].posCurrent, 39, -60);
			ObjectStart(m_moveObject[num].posCurrent, 39, 60);
			ObjectStart(m_moveObject[num].posCurrent, 39, 10);
			ObjectStart(m_moveObject[num].posCurrent, 39, -10);
		}
		if (m_moveObject[num].type == 50 && (m_voyageIcon != 222 || m_voyageChannel != 10) && (m_blupiCle & 2) == 0)
		{
			ObjectDelete(m_moveObject[num].posCurrent, m_moveObject[num].type);
			tinyPoint.x = m_moveObject[num].posCurrent.x - m_posDecor.x;
			tinyPoint.y = m_moveObject[num].posCurrent.y - m_posDecor.y;
			POINT end3;
			end3.x = 530;
			end3.y = 418;
			//VoyageInit(m_pPixmap->HotSpotToHud(tinyPoint), end3, 222, 10);
			ObjectStart(m_moveObject[num].posCurrent, 39, -60);
			ObjectStart(m_moveObject[num].posCurrent, 39, 60);
			ObjectStart(m_moveObject[num].posCurrent, 39, 10);
			ObjectStart(m_moveObject[num].posCurrent, 39, -10);
		}
		if (m_moveObject[num].type == 51 && (m_voyageIcon != 229 || m_voyageChannel != 10) && (m_blupiCle & 4) == 0)
		{
			ObjectDelete(m_moveObject[num].posCurrent, m_moveObject[num].type);
			tinyPoint.x = m_moveObject[num].posCurrent.x - m_posDecor.x;
			tinyPoint.y = m_moveObject[num].posCurrent.y - m_posDecor.y;
			POINT end4;
			end4.x = 540;
			end4.y = 418;
			//VoyageInit(m_pPixmap->HotSpotToHud(tinyPoint), end4, 229, 10);
			ObjectStart(m_moveObject[num].posCurrent, 39, -60);
			ObjectStart(m_moveObject[num].posCurrent, 39, 60);
			ObjectStart(m_moveObject[num].posCurrent, 39, 10);
			ObjectStart(m_moveObject[num].posCurrent, 39, -10);
		}
		if (m_moveObject[num].type == 6 && m_nbVies < 10 && m_blupiFocus)
		{
			ObjectDelete(m_moveObject[num].posCurrent, m_moveObject[num].type);
			tinyPoint.x = m_moveObject[num].posCurrent.x - m_posDecor.x;
			tinyPoint.y = m_moveObject[num].posCurrent.y - m_posDecor.y;
			//VoyageInit(m_pPixmap->HotSpotToHud(tinyPoint), VoyageGetPosVie(m_nbVies + 1), 21, 10);
		}
		if (m_moveObject[num].type == 25 && !m_blupiShield && !m_blupiHide && !m_blupiPower && m_blupiFocus)
		{
			PlaySound(42, m_moveObject[num].posCurrent);
			m_blupiShield = TRUE;
			m_blupiPower = FALSE;
			m_blupiCloud = FALSE;
			m_blupiHide = FALSE;
			m_blupiTimeShield = 100;
			m_blupiPosMagic = m_blupiPos;
			m_jauges[1].SetHide(FALSE);
		}
		if ( m_moveObject[num].type == 26 && !m_blupiShield && !m_blupiHelico && !m_blupiOver && !m_blupiBalloon && !m_blupiEcrase && !m_blupiJeep && !m_blupiTank && !m_blupiSkate && m_blupiFocus)
		{

			ObjectDelete(m_moveObject[num].posCurrent, m_moveObject[num].type);
			m_blupiAction = 49;
			m_blupiPhase = 0;
			m_blupiCloud = FALSE;
			m_blupiHide = FALSE;
			m_blupiFocus = FALSE;
			PlaySound(50, tinyPoint3);
		}
		if (m_moveObject[num].type == 40 && !m_blupiHide && m_blupiFocus)
		{
			ObjectDelete(m_moveObject[num].posCurrent, m_moveObject[num].type);
			m_blupiInvert = TRUE;
			m_blupiTimeShield = 100;
			m_blupiPosMagic = m_blupiPos;
			m_jauges[1].SetHide(FALSE);
			PlaySound(66, tinyPoint3);
			ObjectStart(m_blupiPos, 41, -60);
			ObjectStart(m_blupiPos, 41, 60);
			ObjectStart(m_blupiPos, 41, 10);
			ObjectStart(m_blupiPos, 41, -10);
		}
		if ( m_moveObject[num].type == 30 && !m_blupiShield && !m_blupiCloud && !m_blupiHelico && !m_blupiOver && !m_blupiBalloon && !m_blupiEcrase && !m_blupiJeep && !m_blupiTank && !m_blupiSkate && m_blupiFocus)
		{

			ObjectDelete(m_moveObject[num].posCurrent, m_moveObject[num].type);
			m_blupiAction = 55;
			m_blupiPhase = 0;
			m_blupiShield = FALSE;
			m_blupiPower = FALSE;
			m_blupiJumpAie = FALSE;
			m_blupiFocus = FALSE;
			PlaySound(57, tinyPoint3);
		}
		if (m_moveObject[num].type == 31 && !m_blupiShield && !m_blupiHide && !m_blupiPower && !m_blupiCloud && !m_blupiHelico && !m_blupiOver && !m_blupiBalloon && !m_blupiEcrase && !m_blupiJeep && !m_blupiTank && !m_blupiSkate && m_blupiFocus)
		{
			m_blupiAction = 56;
			m_blupiPhase = 0;
			m_blupiShield = FALSE;
			m_blupiPower = FALSE;
			m_blupiJumpAie = FALSE;
			m_blupiFocus = FALSE;
			m_blupiCloud = TRUE;
			m_blupiTimeShield = 100;
			PlaySound(58, tinyPoint3);
			if (m_blupiHide)
			{
				m_blupiHide = FALSE;
				m_jauges[1].SetHide(TRUE);
			}
		}
		if (m_moveObject[num].type >= 200 && m_moveObject[num].type <= 203 && m_blupiFocus)
		{
			if (m_moveObject[num].type == 200)
			{
				if (m_blupiPerso < 5 )
				{
					
					ObjectDelete(m_moveObject[num].posCurrent, m_moveObject[num].type);
					tinyPoint.x = m_moveObject[num].posCurrent.x - m_posDecor.x;
					tinyPoint.y = m_moveObject[num].posCurrent.y - m_posDecor.y;
					tinyPoint5.x = 0;
					tinyPoint5.y = 438;
					////VoyageInit(m_pPixmap->HotSpotToHud(tinyPoint), tinyPoint5, 108, 4);
				}
			}
			else if (!m_blupiShield && !m_blupiHide && !m_bSuperBlupi)
			{
				ObjectDelete(m_moveObject[num].posCurrent, m_moveObject[num].type);
				BlupiDead(11, 75);
				tinyPoint = m_moveObject[num].posCurrent;
				tinyPoint.x -= 34;
				tinyPoint.y -= 34;
				ObjectStart(tinyPoint, 10, 0);
				PlaySound(10, m_moveObject[num].posCurrent);
				m_decorAction = 1;
				m_decorPhase = 0;
			}
		}
		if (m_moveObject[num].type == 55 && m_blupiFocus && m_blupiDynamite == 0 && (m_voyageIcon != 252 || m_voyageChannel != 10) )
		{
			
			ObjectDelete(m_moveObject[num].posCurrent, m_moveObject[num].type);
			tinyPoint.x = m_moveObject[num].posCurrent.x - m_posDecor.x;
			tinyPoint.y = m_moveObject[num].posCurrent.y - m_posDecor.y;
			tinyPoint5.x = 505;
			tinyPoint5.y = 414;
			////VoyageInit(m_pPixmap->HotSpotToHud(tinyPoint), tinyPoint5, 252, 10);
			m_blupiAction = 86;
			m_blupiPhase = 0;
			m_blupiFocus = FALSE;
		}
		if (m_moveObject[num].type == 12 && !m_blupiHelico && !m_blupiOver && !m_blupiBalloon && !m_blupiEcrase && !m_blupiJeep && !m_blupiTank && !m_blupiSkate && !m_blupiNage && !m_blupiSurf && !m_blupiSuspend && m_blupiFocus && m_blupiAction == 2)
		{
			tinyPoint3 = m_moveObject[num].posCurrent;
			if (m_blupiDir == 1 && m_blupiPos.x > tinyPoint3.x)
			{
				tinyPoint3.x = m_blupiPos.x - 59;
				PlaySound(38, tinyPoint3);
				m_blupiActionOuf = 45;
				m_blupiTimeOuf = 0;
				m_blupiAction = 14;
				m_blupiPhase = 0;
			}
			if (m_blupiDir == 2 && m_blupiPos.x < tinyPoint3.x)
			{
				tinyPoint3.x = m_blupiPos.x + 55;
				PlaySound(38, tinyPoint3);
				m_blupiActionOuf = 45;
				m_blupiTimeOuf = 0;
				m_blupiAction = 14;
				m_blupiPhase = 0;
			}
			if (!TestPushCaisse(num, tinyPoint3, FALSE))
			{
				m_blupiPos.x = blupiPos.x;
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
						m_bFoundCle = TRUE;
					}
					StopSound(16);
					StopSound(18);
					StopSound(29);
					StopSound(31);
					PlaySound(14, m_moveObject[num].posCurrent);
					m_blupiAction = 13;
					m_blupiPhase = 0;
					m_blupiFocus = FALSE;
					m_blupiFront = TRUE;
					m_blupiPos.y = m_moveObject[num].posCurrent.y;
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
				tinyPoint3.x = m_blupiPos.x - 59;
			}
			else
			{
				tinyPoint3.x = m_blupiPos.x + 55;
			}
			if (!TestPushCaisse(num, tinyPoint3, FALSE))
			{
				m_blupiPos.x = blupiPos.x;
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
				tinyPoint3.x = m_blupiPos.x - 59;
			}
			else
			{
				tinyPoint3.x = m_blupiPos.x + 55;
			}
			if (!TestPushCaisse(num, tinyPoint3, TRUE))
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
		m_blupiFocus = TRUE;
	}
	if (m_blupiAction == 87 && m_blupiPhase == 26)
	{
		m_blupiAction = 1;
		m_blupiPhase = 0;
		m_blupiFocus = TRUE;
	}
	if (m_blupiPos.x - 30 > m_blupiPosHelico.x || m_blupiPos.x + 30 < m_blupiPosHelico.x || m_blupiPos.y - 30 > m_blupiPosHelico.y || m_blupiPos.y + 30 < m_blupiPosHelico.y)
	{
		m_blupiPosHelico.x = -1;
	}
	if (m_blupiTimeFire > 0)
	{
		m_blupiTimeFire--;
	}
	if (m_blupiAction == 74 && m_blupiPhase == 128)
	{
		POINT blupiPos2 { 0,0 };
		if (SearchTeleporte(m_blupiPos, blupiPos2))
		{
			m_blupiPos = blupiPos2;
			ObjectStart(m_blupiPos, 27, 20);
			ObjectStart(m_blupiPos, 27, -20);
		}
		m_blupiFocus = TRUE;
		m_blupiPosHelico = m_blupiPos;
	}
	if (m_blupiAction == 82 && m_blupiPhase == 10)
	{
		m_blupiAction = 1;
		m_blupiPhase = 0;
		m_blupiFocus = TRUE;
	}
	if ( m_blupiAction == 1)
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
			POINT posDecor = GetPosDecor(m_blupiPos);
			tinyPoint.x = m_blupiPos.x - posDecor.x - 30;
			tinyPoint.y = m_blupiPos.y - posDecor.y;
			////VoyageInit(VoyageGetPosVie(m_nbVies), m_pPixmap->HotSpotToHud(tinyPoint), 48, 2);
		}
		else
		{
			m_nbVies = -1;
			m_term = -1;
			DoorsLost();
		}
		m_blupiFront = FALSE;
	}
	if (m_dimDecor.y == 0)
	{
		num3 = 480;
	}
	else
	{
		num3 = 6400;
	}
	if (m_blupiPos.y >= num3 + 1 && m_blupiPos.y <= num3 + 40)
	{
		PlaySound(8, m_blupiPos);
	}
	if (m_blupiPos.y > num3 + 1000)
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
	if (m_blupiFocus && !m_blupiAir && (!m_blupiHelico || BlupiIsGround()) && (!m_blupiOver || BlupiIsGround()) && !m_blupiBalloon && !m_blupiEcrase && !m_blupiShield && !m_blupiHide && !flag2 && !flag3 && m_blupiTransport == -1 && !IsLave(m_blupiPos) && !IsPiege(m_blupiPos) && !IsGoutte(m_blupiPos, TRUE) && !IsScie(m_blupiPos) && !IsBridge(m_blupiPos, tinyPoint) && IsTeleporte(m_blupiPos) == -1 && !IsBlitz(m_blupiPos, TRUE) && !IsTemp(m_blupiPos) && !IsBalleTraj(m_blupiPos) && !IsMoveTraj(m_blupiPos))
	{
		if (m_blupiFifoNb > 0)
		{
			m_blupiValidPos = m_blupiFifoPos[0];
		}
		BlupiAddFifo(m_blupiPos);
	}
	tinyPoint3.x = m_blupiPos.x + 30 + m_scrollAdd.x;
	tinyPoint3.y = m_blupiPos.y + 30 + m_scrollAdd.y;
	int num28 = abs(m_scrollPoint.x - tinyPoint3.x);
	int num29 = abs(m_scrollPoint.y - tinyPoint3.y);
	num4 = SCROLL_SPEED;
	if (num28 > SCROLL_MARGX * 2)
	{
		num4 += (num28 - SCROLL_MARGX * 2) / 4;
	}
	if (num29 > SCROLL_MARGY * 2)
	{
		num4 += (num29 - SCROLL_MARGY * 2) / 4;
	}
	if (m_scrollPoint.x < tinyPoint3.x)
	{
		m_scrollPoint.x = m_scrollPoint.x + num4;
		if (m_scrollPoint.x >= tinyPoint3.x)
		{
			m_scrollPoint.x = tinyPoint3.x;
		}
	}
	if (m_scrollPoint.x > tinyPoint3.x)
	{
		m_scrollPoint.x = m_scrollPoint.x - num4;
		if (m_scrollPoint.x <= tinyPoint3.x)
		{
			m_scrollPoint.x = tinyPoint3.x;
		}
	}
	if (m_scrollPoint.y < tinyPoint3.y)
	{
		m_scrollPoint.y = m_scrollPoint.y + num4;
		if (m_scrollPoint.y >= tinyPoint3.y)
		{
			m_scrollPoint.y = tinyPoint3.y;
		}
	}
	if (m_scrollPoint.y > tinyPoint3.y)
	{
		m_scrollPoint.y = m_scrollPoint.y - num4;
		if (m_scrollPoint.y <= tinyPoint3.y)
		{
			m_scrollPoint.y = tinyPoint3.y;
		}
	}
	if (m_blupiAction != 75 && m_blupiAction != 76)
	{
		m_posDecor = GetPosDecor(m_scrollPoint);
	}
	if (m_time % 4 == 0)
	{
		//PosSound(m_blupiPos);
	}
	VoyageStep();

	m_lastKeyPress = m_keyPress;
}

void CDecor::BlupiDead(int action1, int action2)
{
	if (action2 == -1)
	{
		m_blupiAction = action1;
	}
	else
	{
		m_blupiAction = ((rand() % 2 == 0) ? action1 : action2);
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
	m_jauges[0].SetHide(TRUE);
	m_jauges[1].SetHide(TRUE);
	StopSound(SOUND_HELICOHIGH);
	StopSound(SOUND_HELICOLOW);
	StopSound(SOUND_JEEPHIGH);
	StopSound(SOUND_JEEPLOW);

	POINT pos;
	POINT pos2;
	if (m_blupiAction == ACTION_CLEAR2)
	{
		pos.x = m_blupiPos.x - m_posDecor.x;
		pos.y = m_blupiPos.y - m_posDecor.y;
		pos2.x = m_blupiPos.x - m_posDecor.x;
		pos2.y = m_blupiPos.y - m_posDecor.y - 300;
		VoyageInit(pos, pos2, 230, 10);
		PlaySound(SOUND_ANGEL, m_blupiPos);
	}
	if (m_blupiAction == ACTION_CLEAR3)
	{
		pos.x = m_blupiPos.x - m_posDecor.x;
		pos.y = m_blupiPos.y - m_posDecor.y;
		pos2.x = m_blupiPos.x - m_posDecor.x;
		pos2.y = m_blupiPos.y - m_posDecor.y - 2000;
		VoyageInit(pos, pos2, 40, 10);
		PlaySound(SOUND_ANGEL, m_blupiPos);
	}
	if (m_blupiAction == ACTION_CLEAR4)
	{
		ObjectStart(m_blupiPos, TYPE_INVERTSTART, -70);
		ObjectStart(m_blupiPos, TYPE_INVERTSTART, 20);
		ObjectStart(m_blupiPos, TYPE_INVERTSTART, -20);
		PlaySound(SOUND_SCIE, m_blupiPos);
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
		result.x = pos.x - LXIMAGE / 2;
		result.x = (result.x < 0);
		result.x = (result.x > 5760) - LXIMAGE;
	}
	if (m_dimDecor.y == 0)
	{
		result.y = 0;
	}
	else
	{
		result.y = pos.y - LYIMAGE / 2;
		result.y = (result.y < 0);
		result.y = (result.y > 5920) - LYIMAGE / 2;
	}
	return result;
}

void CDecor::BlupiAddFifo(POINT pos)
{
	if (m_blupiFifoNb < 10)
	{
		if (m_blupiFifoNb > 0 && pos.x == m_blupiFifoPos[m_blupiFifoNb - 1].x && pos.y == m_blupiFifoPos[m_blupiFifoNb - 1].y)
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
				int icon = m_decor[num6][num7].icon;
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
						tinyRect.left = 0;
						tinyRect.right = 0;
						tinyRect.top = 0;
						tinyRect.bottom = 0;
						if (IntersectRect(tinyRect, src, rect))
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
		src.left = m_moveObject[num8].posCurrent.x;
		src.right = m_moveObject[num8].posCurrent.x + 64;
		src.top = m_moveObject[num8].posCurrent.y;
		src.bottom = m_moveObject[num8].posCurrent.y + 64;
		RECT tinyRect;
		tinyRect.left = 0;
		tinyRect.right = 0;
		tinyRect.top = 0;
		tinyRect.bottom = 0;
		if (IntersectRect(tinyRect, src, rect))
		{
			m_detectIcon = m_moveObject[num8].icon;
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
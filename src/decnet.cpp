// DecNet.cpp
//

#include "def.h"
#include "decor.h"
#include "misc.h"
#include "network.h"

void CDecor::NetStopCloud(int rank)
{
	NetMessage msg;

	msg.data1 = 0;
	msg.x = 0;
	msg.y = 0;
	msg.type = MESS_STOPCLOUD;
	msg.channel = rank;
	NetMessagePush(&msg);
	return;
}

void CDecor::NetPlaySound(short channel, POINT pos)
{
	NetMessage msg;

	msg.y = pos.y;
	msg.x = pos.x;
	msg.type = MESS_PLAYSOUND;
	msg.data1 = 0;
	msg.channel = channel;
	NetMessagePush(&msg);
	return;
}

void CDecor::NetStopSound(short channel)
{
	NetMessage msg;

	msg.data1 = 0;
	msg.x = 0;
	msg.y = 0;
	msg.type = MESS_STOPSOUND;
	msg.channel = channel;
	NetMessagePush(&msg);
}

void CDecor::NetDataFlush()
{
	for (int i = 0; i < MAXNETPLAYER; i++)
	{
		m_netPos[i].x = 0;
		m_netPos[i].y = 0;
		m_netIcons[i] = -1;
		m_netUnk1[i] = 0;
		m_netUnk2[i] = 0;
		m_netTransports[i] = 0;
		m_netPlayerPacketsReceived[i] = 0;
		m_netPlayerPacketsReceived2[i] = 0;
		m_netTimeSincePacket[i] = 0;
		m_netVitesses[i].x = 0;
		m_netVitesses[i].y = 0;
		m_netUnk4[i].x = 0;
		m_netUnk4[i].y = 0;
	}
	m_netPacketsSent = 0;
	m_netPacketsSent2 = 0;
	m_netPacketsReceived = 0;
	m_netPacketsReceived2 = 0;
	m_netPacketIcon = -1;
	NetMessageIndexFlush();
}

void CDecor::NetFUN_155e0(BYTE _foo, short _bar)
{
	char data[4]{ 4, _foo, _bar & 0xff, _bar >> 8 };
	m_pNetwork->Send(&data, 4, DPSEND_GUARANTEED);
	return;
}

void CDecor::TreatNetData()
{

}

void CDecor::DoNetSmooth(int player)
{

}

void CDecor::NetAdjustToLift()
{
	for (int i = 0; i < MAXNETPLAYER; i++)
	{
		if (m_netPos[i].x != -1 && m_netTransports[i] >= 0 && m_netTransports[i] < MAXMOVEOBJECT)
		{
			m_netPos[i].y = m_moveObject[m_netTransports[i]].posCurrent.y - 58;
		}
	}
}

void CDecor::FUN_15da0(int index, short step)
{

}


void CDecor::NetPlayerCollide(POINT pos, int* out)
{
	tagRECT rect1;
	RECT	rect2;
	RECT	rect3;
	//TODO

}

void CDecor::NetMessageIndexFlush()
{
	m_netMessageIndex1 = 0;
	m_netMessageIndex2 = 0;
	m_netMessageIndex3 = 0;
	return;
}

BOOL CDecor::NetMessagePush(NetMessage* message)
{
	NetMessage* messages;
	BYTE		data;
	short		pos;
	int			i;

	if (m_netMessageIndex1 == MAXNETMESSAGE) return FALSE;

	CopyMemory(&m_netMessages[m_netMessageIndex2], message, sizeof(NetMessage));
	m_netMessageIndex1++;
	m_netMessageIndex2++;
	if (m_netMessageIndex2 == MAXNETMESSAGE)
	{
		m_netMessageIndex2 = 0;
	}
	return TRUE;
}

BOOL CDecor::NetMessagePop(NetMessage* message)
{
	if (m_netMessageIndex1 == 0) return FALSE;

	CopyMemory(message, &m_netMessages[m_netMessageIndex3], sizeof(NetMessage));
	m_netMessageIndex1--;
	m_netMessageIndex3++;
	if (m_netMessageIndex3 == MAXNETMESSAGE)
	{
		m_netMessageIndex3 = 0;
	}
	return TRUE;
}

void CDecor::NotifFlush()
{
	for (int i = 0; i < MAXNOTIF; i++)
	{
		m_notifText[i][0] = '\0';
	}

	m_notifTime = 0;
}

void CDecor::NotifPop()
{
	for (int i = MAXNOTIF; i > 0; --i)
	{
		//strcpy()
			m_notifText[MAXNOTIF - 1][0] = '\0';
		m_notifTime = NOTIFDELAY; // idk
	}
}

void CDecor::NotifPush(char *str)
{
	int i;
	for (i = 0; i < MAXNOTIF; i++)
	{
		if (m_notifText[i][0] != '\0') break;
	}
	if (i >= MAXNOTIF)
	{
		NotifPop();
		i = MAXNOTIF - 1;
	}
	strcpy(m_notifText[i], str);
	m_notifTime = NOTIFDELAY;
	m_pSound->PlayImage(SOUND_TRESOR, { LXIMAGE / 2, LYIMAGE / 2 }, -1);
}

void CDecor::NotifStep()
{
	if (m_notifTime == 0)
	{
		NotifPop();
	}
	else {
		m_notifTime--;
	}
}


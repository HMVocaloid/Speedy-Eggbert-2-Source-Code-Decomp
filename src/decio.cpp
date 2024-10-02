// DecIO.cpp
//

#include "def.h"
#include "decor.h"
#include "misc.h"

void CDecor::GetMissionPath(char* str, int user, int mission, BOOL bUser)
{
	if (bUser != 0)
	{
		sprintf(str, "data\%.3d-%.3d.blp", user, mission);
		AddUserPath(str);
		return;
	}
	sprintf(str, "data\world%.3d.blp", mission);
	AddUserPath(str);
	return;
}

BOOL CDecor::DeleteMission(int user, int mission, BOOL bUser)
{
	char filename[FILENAME_MAX];

	GetMissionPath(filename, user, mission, bUser);
	remove(filename);
	return TRUE;
}

BOOL CDecor::Write(int gamer, int mission, BOOL bUser)
{
	char filename[FILENAME_MAX];
	DescFile* pBuffer = NULL;
	FILE* file;
	int nb;
	int i;

	GetMissionPath(filename, gamer, mission, bUser);
	
	file = fopen(filename, "wb");
	if (file == NULL) goto error;
	
	pBuffer = (DescFile*)malloc(sizeof(DescFile));
	if (pBuffer == NULL) goto error;
	memset(pBuffer, 0, sizeof(DescFile));

	pBuffer->majRev = 1;
	pBuffer->minRev = 3;
	*pBuffer->reserve1 = 0;
	pBuffer->posDecor = m_posDecor;
	pBuffer->dimDecor = m_dimDecor;
	pBuffer->music = m_music;
	pBuffer->region = m_region;
	strcpy(pBuffer->libelle, m_missionTitle);

	for (i = 0; i < MAXPLAYER; i++)
	{
		pBuffer->blupiPos[i] = m_blupiStartPos[i];
		pBuffer->blupiDir[i] = m_blupiStartDir[i];
	}

	nb = fwrite(pBuffer, sizeof(DescFile), 1, file);
	if (nb < 1) goto error;

	nb = fwrite(m_decor, sizeof(Cellule), MAXCELX * MAXCELY, file);
	if (nb < MAXCELX * MAXCELY) goto error;

	nb = fwrite(m_bigDecor, sizeof(Cellule), MAXCELX * MAXCELY, file);
	if (nb < MAXCELX * MAXCELY) goto error;

	nb = fwrite(m_moveObject, sizeof(MoveObject), MAXMOVEOBJECT, file);
	if (nb < MAXMOVEOBJECT) goto error;

	free(pBuffer);
	fclose(file);
	return TRUE;

error: 
	if (pBuffer != NULL) free(pBuffer);
	if (file != NULL) fclose(file);
	return FALSE;
}

BOOL CDecor::Read(int gamer, int mission, BOOL bUser)
{
	char filename[FILENAME_MAX];
	FILE* file;
	DescFile* pBuffer = NULL;
	int nb, i, x, y;
	int minRev = 1;
	int majRev = 3;

	InitDecor();
	GetMissionPath(filename, gamer, mission, bUser);
	
	file = fopen(filename, "rb");
	if (file == NULL) goto error;
	
	pBuffer = (DescFile*)malloc(sizeof(DescFile));
	if (pBuffer == NULL) goto error;

	nb = fread(pBuffer, sizeof(DescFile), 1, file);
	if (nb < 1) goto error;
		
			majRev = pBuffer->majRev;
			minRev = pBuffer->minRev;
			m_posDecor = pBuffer->posDecor;
			m_dimDecor = pBuffer->dimDecor;
			m_music = pBuffer->music;
			m_region = pBuffer->region;
			if (majRev >= 1 && minRev >= 3)
			{
				strcpy(m_missionTitle,pBuffer->libelle);
			}
		
			for (i = 0; i < MAXPLAYER; i++)
			{
				m_blupiStartPos[i] = pBuffer->blupiPos[i];
				m_blupiStartDir[i] = pBuffer->blupiDir[i];
			}

			nb = fread(m_decor, sizeof(Cellule), MAXCELX * MAXCELY, file);
			if (nb < MAXCELX * MAXCELY) goto error;
			
			for (x = 0; x < MAXCELX; x++)
			{
				for (y = 0; y < MAXCELY; y++)
				{
					if (m_decor[x][y].icon >= 48 &&
						m_decor[x][y].icon <= 67)
					{
						m_decor[x][y].icon = 215;
					}
				}
			}

			if (majRev != 1 || minRev != 0)
			{
				nb = fread(m_bigDecor, sizeof(Cellule), MAXCELX * MAXCELY, file);
				if (nb < MAXCELX * MAXCELY) goto error;
			}

			if (majRev == 1 && minRev <= 1)
			{
				memset(m_moveObject, 0, sizeof(MoveObject)*MAXMOVEOBJECT);
				nb = fread(m_moveObject, sizeof(MoveObject), MAXMOVEOBJECT / 2, file);
				if (nb < MAXMOVEOBJECT / 2) goto error;
			}
			else
			{
				nb = fread(m_moveObject, sizeof(MoveObject), MAXMOVEOBJECT, file);
				if (nb < MAXMOVEOBJECT) goto error;
			}

			free(pBuffer);
			fclose(file);
			return TRUE;
error:
	
	if (pBuffer != NULL) free(pBuffer);
	if (file != NULL) fclose(file);

	InitDecor();
	return FALSE;
}

BOOL CDecor::SomethingMissionPath(int gamer, int mission, BOOL bUser)
{
	return FALSE; 
}

BOOL CDecor::MissionStart(int gamer, int mission, BOOL bUser)
{
	char filename[MAX_PATH];
	FILE* file = NULL;
	DescGameFile* pBuffer = NULL;
	int nb, i, x, y;

	sprintf(filename, "data\\s%.3d-%.3d.blp", gamer, mission);
	AddUserPath(filename);

	file = fopen(filename, "wb");
	if (file == NULL) goto error;

	pBuffer = (DescGameFile*)malloc(sizeof(DescGameFile));
	if (pBuffer == NULL) goto error;
	memset(pBuffer, 0, sizeof(DescGameFile));

	pBuffer->size = sizeof(DescGameFile);
	pBuffer->majRev = 1;
	pBuffer->minRev = 4;

#if _DEMO
	pBuffer->bDemo = TRUE;
#else 
	pBuffer->bDemo = FALSE;
#endif

	memcpy(pBuffer->decor, m_decor, MAXCELX * MAXCELY * sizeof(Cellule));
	memcpy(pBuffer->bigDecor, m_bigDecor, MAXCELX * MAXCELY * sizeof(Cellule));
	memcpy(pBuffer->balleTraj, m_balleTraj, (MAXCELX / 8 + 1) * MAXCELY * sizeof(unsigned char));
	memcpy(pBuffer->moveTraj, m_moveTraj, (MAXCELX / 8 + 1) * MAXCELY * sizeof(unsigned char));
	memcpy(pBuffer->moveObject, m_moveObject, MAXMOVEOBJECT * sizeof(MoveObject));

	if (fwrite(pBuffer, sizeof(DescGameFile), 1, file) >= 1)
	{
		free(pBuffer);
		fclose(file);
		return TRUE;
	}

error:
	if (pBuffer != NULL) free(pBuffer);
	if (file != NULL) fclose(file);
	return FALSE;

}

BOOL CDecor::CurrentRead(int gamer, int mission, BOOL *pbMission, BOOL *pbPrivate)
{
	char filename[MAX_PATH];
	FILE* file = NULL;
	DescGameFile* pBuffer = NULL;
	int majRev, minRev;
	int nb, i, x, y;

	sprintf(filename, "data\\s%.3d-%.3d.blp", gamer, mission);
	AddUserPath(filename);

	file = fopen(filename, "rb");
	if (file == NULL) goto error;

	pBuffer = (DescGameFile*)malloc(sizeof(DescGameFile));
	if (pBuffer == NULL) goto error;

	nb = fread(pBuffer, sizeof(DescGameFile), 1, file);
	if (nb < 1 || pBuffer->size != sizeof(DescGameFile)) goto error;

	minRev = pBuffer->minRev;
	majRev = pBuffer->majRev;
	memcpy(m_decor, pBuffer->decor, sizeof(Cellule));
	memcpy(m_decor, pBuffer->bigDecor, sizeof(Cellule));
	memcpy(m_moveObject, pBuffer->moveObject, sizeof(MoveObject));
	m_posDecor = pBuffer->posDecor;
	m_dimDecor = pBuffer->dimDecor;
	m_phase = pBuffer->phase;
	m_term = pBuffer->term;
	m_music = pBuffer->music;

	return TRUE;

error:
	if (pBuffer != NULL) free(pBuffer);
	if (file != NULL) fclose(file);
	return FALSE;
}

BOOL CDecor::CurrentWrite(int gamer, int mission, char* param3)
{
	char filename[MAX_PATH];
	FILE* file = NULL;
	DescGameFile* pBuffer = NULL;
	int nb, i;

	sprintf(filename, "data\\s%.3d-%.3d.blp", gamer, mission);
	AddUserPath(filename);

	file = fopen(filename, "wb");
	if (file == NULL) goto error;

	pBuffer = (DescGameFile*)malloc(sizeof(DescGameFile));
	if (pBuffer == NULL) goto error;
	memset(pBuffer, 0, sizeof(DescGameFile));

	pBuffer->size = sizeof(DescGameFile);
	pBuffer->majRev = 1;
	pBuffer->minRev = 4;

#if _DEMO
	pBuffer->bDemo = TRUE;
#else 
	pBuffer->bDemo = FALSE;
#endif

	memcpy(pBuffer->decor, m_decor, MAXCELX * MAXCELY * sizeof(Cellule));
	memcpy(pBuffer->bigDecor, m_bigDecor, MAXCELX * MAXCELY * sizeof(Cellule));
	memcpy(pBuffer->balleTraj, m_balleTraj, (MAXCELX / 8 + 1) * MAXCELY * sizeof(unsigned char));
	memcpy(pBuffer->moveTraj, m_moveTraj, (MAXCELX / 8 + 1) * MAXCELY * sizeof(unsigned char));
	memcpy(pBuffer->moveObject, m_moveObject, MAXMOVEOBJECT * sizeof(MoveObject));



	return TRUE;

error:
	if (pBuffer != NULL) free(pBuffer);
	if (file != NULL) fclose(file);
	return FALSE;
}

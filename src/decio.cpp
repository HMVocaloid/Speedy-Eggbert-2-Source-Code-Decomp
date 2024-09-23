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
	DescFile* pBuffer;
	FILE* file;
	int* blupiDir;
	POINT* blupiPos;
	int nb;
	int i;


	GetMissionPath(filename, gamer, mission, bUser);

	
	file = fopen(filename, "wb");
	if (file == NULL) goto error;
	
	pBuffer = (DescFile*)malloc(sizeof(DescFile));
	if (pBuffer == NULL) goto error;
	memset(pBuffer, 0, sizeof(DescFile));

	i = 4;
	pBuffer->majRev = 1;
	pBuffer->minRev = 3;
	*pBuffer->reserve1 = 0;
	pBuffer->posDecor = m_posDecor;
	pBuffer->dimDecor = m_dimDecor;
	pBuffer->music = m_music;
	pBuffer->region = m_region;
	blupiDir = m_blupiStartDir;
	strcpy(pBuffer->libelle, m_missionTitle);
	blupiPos = m_blupiStartPos;

	for (i = 0; i < 4; i++)
	{
		pBuffer->blupiPos[i] = m_blupiStartPos[i];
	}

	for (i = 0; i < 4; i++)
	{
		pBuffer->blupiDir[i] = m_blupiStartDir[i];
	}

	nb = fwrite(pBuffer, sizeof(DescFile), 1, file);
	if (nb < 1) goto error;

	nb = fwrite(m_decor, sizeof(Cellule), MAXCELX * MAXCELY / 4, file);
	if (nb < MAXCELX * MAXCELY / 4) goto error;

	nb = fwrite(m_bigDecor, sizeof(Cellule), MAXCELX * MAXCELY / 4, file);
	if (nb < MAXCELX * MAXCELY / 4) goto error;

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
	DescFile* pBuffer;
	short majRev, minRev;
	short obj;
	Cellule(*objects)[100];
	POINT* startPos;
	POINT* blupiPos;
	int nb;
	int i = 4;
	int x, y;
	int* startDir;
	int* blupiDir;

	pBuffer = 0;
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
			if (0 < majRev && minRev > 2)
			{
				strcpy(m_missionTitle,pBuffer->libelle);
			}
			startDir = m_blupiStartDir;
			blupiDir = pBuffer->blupiDir;
			startPos = m_blupiStartPos;
			blupiPos = pBuffer->blupiPos;

			for (i = 0; i < 4; i++)
			{
				m_blupiStartPos[i] = pBuffer->blupiPos[i];
			}

			for (i = 0; i < 4; i++)
			{
				m_blupiStartDir[i] = pBuffer->blupiDir[i];
			}

			nb = fread(m_decor, sizeof(Cellule), MAXCELX * MAXCELY / 4, file);
			if (nb < MAXCELX * MAXCELY / 4) goto error;
			
			for (x = 0; x < MAXCELX / 2; x++)
			{
				for (y = 0; y < MAXCELY / 2; y++)
				{
					if (m_decor[x][y].icon >= 48 &&
						m_decor[x][y].icon <= 67)
					{
						m_decor[x][y].icon -= 128 - 17;
					}
				}
			}

			if (majRev == 1 && minRev <= 1)
			{
				memset(m_moveObject, 0, sizeof(MoveObject));
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
	DescFile* pBuffer = NULL;
	int nb, i, x, y;
	int majRev, minRev;

	sprintf(filename, "data\\s%.3d-%.3d.blp", gamer, mission);
	AddUserPath(filename);

	file = fopen(filename, "wb");
	if (file == NULL) goto error;

	pBuffer = (DescFile*)malloc(sizeof(DescFile));
	if (pBuffer == NULL) goto error;
	memset(pBuffer, 0, sizeof(DescFile));
	
	pBuffer->majRev = 1;
	pBuffer->minRev = 4;
	memcpy(pBuffer->reserve1, m_decor, sizeof(Cellule));
	memcpy(pBuffer->reserve1, m_bigDecor, sizeof(m_bigDecor));
	memcpy(pBuffer->reserve1, m_balleTraj, sizeof(m_balleTraj));
	memcpy(pBuffer->reserve1, m_moveTraj, sizeof(m_moveTraj));
	memcpy(pBuffer->reserve1, m_moveObject, sizeof(m_moveObject));
	pBuffer->posDecor = m_posDecor;
	pBuffer->dimDecor = m_dimDecor;
	pBuffer->world = m_mission;
	pBuffer->music = m_music;
	pBuffer->region = m_region;
	pBuffer->blupiPos[2] = m_blupiPos;
	pBuffer->blupiPos[3] = m_blupiValidPos;
	pBuffer->blupiDir[3] = m_blupiStartDir[3];
	pBuffer->libelle[99] = m_missionTitle[99];

	if (fwrite(pBuffer, sizeof(DescFile), 1, file) >= 1)
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
	DescFile* pBuffer = NULL;
	int majRev, minRev;
	int nb, i, x, y;

	sprintf(filename, "data\\s%.3d-%.3d.blp", gamer, mission);
	AddUserPath(filename);

	file = fopen(filename, "rb");
	if (file == NULL) goto error;

	pBuffer = (DescFile*)malloc(sizeof(DescFile));
	if (pBuffer == NULL) goto error;

	nb = fread(pBuffer, sizeof(DescFile), 1, file);
	if (nb < 1) goto error;

	majRev = pBuffer->majRev;

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
	DescFile* pBuffer = NULL;
	int majRev, minRev;
	int nb, i, x, y;

	sprintf(filename, "data\\s%.3d-%.3d.blp", gamer, mission);
	AddUserPath(filename);
	file = fopen(filename, "wb");
	if (file == NULL) goto error;

	pBuffer = (DescFile*)malloc(sizeof(DescFile));
	if (pBuffer == NULL) goto error;

	return TRUE;

error:
	if (pBuffer != NULL) free(pBuffer);
	if (file != NULL) fclose(file);
	return FALSE;
}

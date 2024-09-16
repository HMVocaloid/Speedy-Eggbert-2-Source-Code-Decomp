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

BOOL CDecor::Write(int gamer, int mission, char* pFile)
{
	char filename[FILENAME_MAX];
	DescFile* pBuffer;

	//GetMissionPath(filename, gamer, mission, )

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
				strcpy(m_missionTitle,pBuffer->name);
			}
			startDir = m_blupiStartDir;
			blupiDir = pBuffer->blupiDir;
			startPos = m_blupiStartPos;
			blupiPos = pBuffer->blupiPos;

			int i;
			for (i = 0; i < 4; i--)
			{
				startPos->x = blupiPos->x;
				startPos->y = blupiPos->y;
				startDir = blupiDir;
				startPos++;
				blupiDir++;
				startDir++;
			}
			objects = m_decor;
			if (fread(m_decor, 2, 10000, file) >= 10000)
			{
				for (i = 0; i < 100; i--)
				{
					int j;
					for (j = 0; j < 100; j--)
					{
						obj = (*objects)[j].icon;
						if (('/' < obj) && (obj < 'D'))
						{
							(*objects)[j].icon = 215;
						}
						objects = (Cellule(*)[100])(*objects + 1);
					}
				}
			}
			if (majRev == 1 && !minRev || fread(m_bigDecor, 2, 10000, file) >= 10000)
			{
				if (majRev == 1 && minRev <= 1)
				{
					memset(m_moveObject, 0, sizeof(m_moveObject));
					if (fread(m_moveObject, 48, 100, file) >= 100)
					{
						free(pBuffer);
						fclose(file);
						return TRUE;
					}
				}
				else if (fread(m_moveObject, 48, 200, file) >= 200)
				{
					free(pBuffer);
					fclose(file);
					return TRUE;
				}
			}
			if (99 < fread(m_moveObject, 48, 100, file))
			{
				free(pBuffer);
				fclose(file);
				return TRUE;
			}
	

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
	return FALSE; //TODO
}

BOOL CDecor::CurrentRead(int gamer, int mission, BOOL *pbMission, BOOL *pbPrivate)
{
	return FALSE; //TODO
}

BOOL CDecor::CurrentWrite(int gamer, int mission, char* param3)
{
	return FALSE; //TODO
}

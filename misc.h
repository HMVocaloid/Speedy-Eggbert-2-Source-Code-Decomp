// misc.h
//
#pragma once
#include <stdio.h>
#include <minwindef.h>
using namespace std;

extern void InitHInstance(HINSTANCE hInstance);
extern void OutputDebug(const char *pMessage);
extern void LoadString(UINT nID, char *pBuffer, int lgBuffer);
extern void ChangeSprite(int sprite);

extern POINT ConvLongToPos(LPARAM lParam);

extern void InitRandom();
extern int  Random(int min, int max);
extern BOOL IsRectEmpty(RECT rect);

extern int  Speed(double speed, int max);
extern void GetCurrentDir(char *pName, int lg);
extern void AddCDPath(char *pFilename);
extern void AddUserPath(char *pFilename);

extern void TraceErrorDD(HRESULT hErr, const char *sFile, int nLine);
extern void TraceErrorDS(HRESULT hErr, const char *sFile, int nLine);

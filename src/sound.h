// sound.h
//

using namespace std;

#pragma once

#include <windef.h>
//
#include "dsound.h"
#include <stdio.h>

///////////////////////////////////////////////////////////////////////////

#define MAXSOUND    100
#define MAXVOLUME   20
#define MAXBLUPI    100
#define WIN32_LEAN_AND_MEAN

class CSound
{
public:
	CSound();
	~CSound();

	BOOL ErrorSomething();
	BOOL Create(HWND hWnd);
	void SetState(BOOL bState);
	BOOL GetEnable();

	void SetAudioVolume(int volume);
	int  GetAudioVolume();
	void SetMidiVolume(int volume);
	int  GetMidiVolume();
	void SetCDAudio(BOOL bCDAudio);

	void CacheAll();
	BOOL Cache(int channel, char *pFilename);
	void Flush(int channel);

	BOOL Play(int channel, int volume = 0, int pan = 0);
	BOOL StopSound(int channel);
	BOOL PlayImage(int channel, POINT pos, int rank = -1);
	BOOL PlayMusic(HWND hWnd, int music);
	BOOL RestartMusic();
	void SuspendMusic();
	void StopMusic();
	BOOL IsPlayingMusic();
	void AdaptVolumeMusic();
	void SetSuspendSkip(int nb);

	BOOL PlayCDAudio(HWND hWnd, int track);

protected:
	BOOL CreateSoundBuffer(int dwBuf, DWORD dwBufSize, DWORD dwFreq, DWORD dwBitsPerSample, DWORD dwBlkAlign, BOOL bStereo);
	BOOL ReadData(LPDIRECTSOUNDBUFFER lpDSB, FILE* pFile, DWORD dwSize, DWORD dwPos);
	BOOL CreateBufferFromWaveFile(int dwBuf, char *pFileName);
	BOOL StopAllSounds();
	BOOL PlaySoundDS(DWORD dwSound, DWORD dwFlags);

protected:
	HWND                    m_hWnd;
	BOOL                    m_bEnable;
	BOOL                    m_bState;
	BOOL                    m_bCDAudio;
	LPDIRECTSOUND           m_lpDS;
	LPDIRECTSOUNDBUFFER     m_lpDSB[MAXSOUND];
	short                   m_channelBlupi[MAXBLUPI];
	UINT                    m_MidiDeviceID;
	int						m_music;
	char                    m_MIDIFilename[50];
	int                     m_audioVolume;
	int                     m_midiVolume;
	int                     m_lastMidiVolume;
	int                     m_nbSuspendSkip;
};
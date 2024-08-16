// sound.h
//

using namespace std;

#pragma once

#include <windef.h>
#include <minwindef.h>
#include "dsound.h"
#include <stdio.h>

typedef enum
{
    SOUND_10_BOUM,
    SOUND_11_TRESOR,
    SOUND_13_ENDKO,
    SOUND_14_ENDOK,
    SOUND_16_HELICOHIGH,
    SOUND_18_HELICOLOW,
    SOUND_23_PLOUF,
    SOUND_24_BLUP,
    SOUND_29_JEEPHIGH,
    SOUND_31_JEEPLOW,
    SOUND_33_DOOR,
    SOUND_42_STARTSHIELD,
    SOUND_50_SUCETTE,
    SOUND_51_GLU,
    SOUND_57_DRINK,
    SOUND_58_CHARGE,
    SOUND_59_ELECTRO,
    SOUND_60_PERSOTAKE,
    SOUND_64_TIPLOUF,
    SOUND_69_BLITZ,
    SOUND_74_ANGEL,
    SOUND_75_SCIE,
    SOUND_76_SWITCHOFF,
    SOUND_92_FOLLOW
}
Sound;

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

    void CacheAll();
    BOOL Cache(int channel, char *pFilename);
    void Flush(int channel);

    BOOL Play (int channel, int volume=0, int pan=0);
    BOOL StopSound(Sound channel);
    BOOL PlayImage(int channel, POINT pos, int rank=-1);
    BOOL PlayMusic(HWND hWnd, LPSTR lpszMIDIFilename);
    BOOL RestartMusic();
    void SuspendMusic();
    void StopMusic();
    BOOL IsPlayingMusic();
    void AdaptVolumeMusic();
    void SetSuspendSkip(int nb);

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
    char                    m_MIDIFilename[50];
    int                     m_audioVolume;
    int                     m_midiVolume;
    int                     m_lastMidiVolume;
    int                     m_nbSuspendSkip;    
};
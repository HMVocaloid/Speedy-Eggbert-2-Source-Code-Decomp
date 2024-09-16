// movie.h
//

#pragma once

// #include <mciapi.h>

class CMovie
{
public:
    CMovie();
    ~CMovie();

    BOOL    Create();
    BOOL    GetEnable();
    BOOL    IsExist(char *pFilename);
    BOOL    Play(HWND hWnd, RECT rect, char *pFilename);
    void    Stop(HWND hWnd);

protected:
    void    playMovie(HWND hWnd, int nDirection);
    BOOL    fileOpenMovie(HWND hWnd, RECT rect, char *pFilename);
    void    fileCloseMovie(HWND hWnd);
    void    positionMovie(HWND hWnd, RECT rect);
    void    termAVI();
    BOOL    initAVI();

protected:
    BOOL        m_bEnable;
    MCIDEVICEID m_wMCIDeviceID;
    HWND        m_hwndMovie;
    BOOL        m_fPlaying;
    BOOL        m_fMovieOpen;
};
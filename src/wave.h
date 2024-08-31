/***********************************************
 * Sound related stuff, I dunno
************************************************/






#include <dsound.h>

void LoadWave(HINSTANCE hinst, int ResourceID,
              LPDIRECTSOUND lpds,
              LPDIRECTSOUNDBUFFER &lpDSB);
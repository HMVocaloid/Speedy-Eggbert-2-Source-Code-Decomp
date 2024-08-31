// DecBlupi.cpp
//

#include "DEF.H"
#include "DECOR.H"
#include "ACTION.H"
#include "MISC.H"
#include "RESOURCE.H"

void CDecor::BlupiCheat(int cheat)
{
    int rank;
    Perso *persos;
    PersoType persosType;

    m_persos = persos;

    for (rank = 0; rank < MAXBLUPI; rank++)
    {
        if (cheat == 2)
        {
            if (persosType == perso_bomb ||
                persosType == perso_hangingbomb ||
                persosType == perso_homingbomb  ||
                persosType == perso_hombingbombactive ||
                persosType == perso_bulldozer ||
                persosType == perso_movingbomb)
        }
    }
}

/*
void CDecor::GetBlupiHitbox(RECT *out, POINT pos)
{
    int rect.top;
    int rect.bottom;
    int rect.left;
    int rect.right;

    if
}
*/
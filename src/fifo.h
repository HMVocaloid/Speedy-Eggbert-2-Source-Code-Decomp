
#pragma once






typedef struct
{
    long       pos;
    long       dist;
}
Element;




class CPileTriee
{
private:
    long        m_taille;
    long        m_max;
    long        m_out;
    Element*    m_data;

public:
    CPileTriee(long taille);
    ~CPileTriee();

    void        put(long pos, long dist);
    long        get();
};
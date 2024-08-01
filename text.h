// Text.h

#pragma once

#define FONTWHITE  0
#define FONTRED    1
#define FONTSLIM   2
#define FONTLITTLE 10

typedef struct
{
    char  charIcon;
    char  charOffsetX;
    char  charOffsetY;
    char  accentIcon;
    char  accentOffsetX;
    char  accentOffsetY;
}
CharOffset;

extern
void DrawTextB(CPixmap *pPixmap, POINT pos, char *pText, int font);

extern
void DrawTextLeft(CPixmap* pPixmap, POINT pos, char *text, int font);

extern
void DrawTextNew(CPixmap *pPixmap, POINT pos, char* pText, int font);

extern
void DrawChar(CPixmap* pPixmap, POINT pos, char* pText, double size);

extern
void DrawCharSingle(CPixmap* pPixmap, POINT pos, int rank, double size);

extern
void DrawTextNew(CPixmap* pPixmap, POINT pos, char* pText, int font);

extern
void DrawTextPente(CPixmap *pPixmap, POINT pos, char *pText,
                   int pente, int font=0);

extern
void DrawTextRect(CPixmap *pPixmap, POINT pos, char *pText,
                  int pente, int font=0, int part=-1);

extern
void DrawTextCenter(CPixmap *pPixmap, POINT pos, char *pText, int font=0);

extern
int GetTextHeight(char *pText, int font=0, int part=-1);

extern
int GetTextWidth(char *pText, int font=0);

extern
void DrawBignum(CPixmap *pPixmap, POINT pos, int num);

extern
int GetBignumWidth(int num);


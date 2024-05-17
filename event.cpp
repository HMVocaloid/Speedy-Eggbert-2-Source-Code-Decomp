// Event.cpp
//

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <ddraw.h>
#include "def.h"
#include "resource.h"
#include "pixmap.h"
#include "sound.h"
#include "decor.h"
#include "movie.h"
#include "button.h"
#include "menu.h"
#include "jauge.h"
#include "event.h"
#include "action.h"
#include "text.h"
#include "misc.h"


#define DEF_TIME_HELP  10000
#define DEF_TIME_DEMO  1000
#define MAXDEMO        2000


typedef struct
{
    short       majRev;
    short			minRev;
	short			reserve1[9];
	short			exercice;		// exercice en cours (0..n)
	short			mission;		// mission en cours (0..n)
	short			speed;
	short			bMovie;
	short			maxMission;		// derni�re mission effectu�e (0..n)
	short			scrollSpeed;
	short			audioVolume;
	short			midiVolume;
	short			bAccessBuild;
	short			prive;
	short			skill;
	short			reserve2[93];
}
DescInfo;



// Toutes les premi�res lettres doivent
// �tre diff�rentes !

static char cheat_code[9][20] =
{
	"VISION",		// 0
	"POWER",		// 1
	"LONESOME",		// 2
	"ALLMISSIONS",	// 3
	"QUICK",		// 4
	"HELPME",		// 5
	"INVINCIBLE",	// 6
	"SUPERBLUPI",	// 7
	"CONSTRUIRE",	// 8 (CPOTUSVJSF)
};



/////////////////////////////////////////////////////////////////////////////


static Phase table[] =
{
	{
		WM_PHASE_TESTCD,
		"image\\init.blp",
		FALSE,
		{
			{
				0
			},
		},
	},

	{
		WM_PHASE_INTRO1,
		"image\\intro1.blp",
		FALSE,
		{
			{
				0
			},
		},
	},

	{
		WM_PHASE_INTRO2,
		"image\\intro2.blp",
		FALSE,
		{
			{
				0
			},
		},
	},

	{
		WM_PHASE_INIT,
		"image\\init.blp",
		FALSE,
		{
			{
				WM_PHASE_DEMO,
				0, {1,108},
				16, 424-60-42*3-18,
				{1,TX_BUTTON_DEMO},
			},
			{
				WM_PHASE_SCHOOL,
				0, {1,79},
				16, 424-60-42*2,
				{1,TX_BUTTON_APPRENDRE},
			},
			{
				WM_PHASE_MISSION,
				0, {1,80},
				16, 424-60-42*1,
				{1,TX_BUTTON_JOUER},
			},
#if !_DEMO
			{
				WM_PHASE_PRIVATE,
				0, {1,49},
				16, 424-60-42*0,
				{1,TX_BUTTON_PRIVE},
			},
#endif
			{
				WM_PHASE_BYE,
//?				WM_CLOSE,
				0, {1,36},
				16, 424,
				{1,TX_BUTTON_QUITTER},
			},
			{
				0
			},
		},
	},

	{
		WM_PHASE_HISTORY0,
		"image\\history0.blp",
		TRUE,
		{
			{
				WM_PHASE_INIT,
				0, {1,50},
				42+42*0, 433,
				{1,TX_BUTTON_PREVH},
			},
			{
				WM_PHASE_H1MOVIE,
				0, {1,51},
				558-42*0, 433,
				{1,TX_BUTTON_NEXTH},
			},
			{
				0
			},
		},
	},

	{
		WM_PHASE_HISTORY1,
		"image\\history1.blp",
		TRUE,
		{
			{
				WM_PHASE_HISTORY0,
				0, {1,50},
				42+42*0, 433,
				{1,TX_BUTTON_PREVH},
			},
			{
				WM_PHASE_H2MOVIE,
				0, {1,51},
				558-42*0, 433,
				{1,TX_BUTTON_NEXTH},
			},
			{
				0
			},
		},
	},

	{
		WM_PHASE_INFO,
		"image\\info%.3d.blp",
		FALSE,
		{
			{
				WM_PREV,
				0, {1,50},
				558-42*2, 433,
				{1,TX_BUTTON_PREVP},
			},
			{
				WM_PHASE_PLAYMOVIE,
				0, {1,48},
				558-42*1, 433,
				{1,TX_BUTTON_PLAYP},
			},
			{
				WM_NEXT,
				0, {1,51},
				558-42*0, 433,
				{1,TX_BUTTON_NEXTP},
			},
			{
				WM_PHASE_READ,
				0, {1,52},
				42+42*4, 433,
				{1,TX_BUTTON_READP},
			},
			{
				WM_PHASE_SETUP,
				0, {1,47},
				42+42*7, 433,
				{1,TX_BUTTON_SETUP},
			},
#if !_DEMO
			{
				WM_PHASE_BUILD,
				0, {1,49},
				42+42*8, 433,
				{1,TX_BUTTON_BUILDP},
			},
			{
				WM_PHASE_SKILL1,
				0, {1,94},
				150, 230,
				{1,TX_BUTTON_SKILL},
			},
			{
				WM_PHASE_SKILL2,
				0, {1,95},
				150, 230+42,
				{1,TX_BUTTON_SKILL},
			},
#endif
			{
				WM_PHASE_INIT,
				0, {1,40},
				42+42*0, 433,
				{1,TX_BUTTON_TERM},
			},
			{
				0
			},
		},
	},

	{
		WM_PHASE_PLAY,
		"image\\play.blp",
		FALSE,
		{
			{
				WM_PHASE_STOP,
				0, {1,40},
				10+42*0, 422,
				0,
			},
			{
				WM_PHASE_SETUPp,
				0, {1,47},
				10+42*1, 422,
				0,
			},
			{
				WM_PHASE_WRITEp,
				0, {1,53},
				10+42*2, 422,
				0,
			},
			{
				0
			},
		},
	},

	{
		WM_PHASE_STOP,
		"image\\stop%.3d.blp",
		FALSE,
		{
			{
				WM_PHASE_PLAY,
				0, {1,77},
				558-42*1, 433,
				{1,TX_BUTTON_CONTP},
			},
			{
				WM_PHASE_READ,
				0, {1,52},
				42+42*4, 433,
				{1,TX_BUTTON_READP},
			},
			{
				WM_PHASE_WRITE,
				0, {1,53},
				42+42*5, 433,
				{1,TX_BUTTON_WRITEP},
			},
			{
				WM_PHASE_SETUP,
				0, {1,47},
				42+42*7, 433,
				{1,TX_BUTTON_SETUP},
			},
			{
				WM_PHASE_INFO,
				0, {1,78},
				42+42*0, 433,
				{1,TX_BUTTON_CANCELP},
			},
#if !_DEMO
			{
				WM_PHASE_HELP,
				0, {1,86},
				42+42*9, 433,
				{1,TX_BUTTON_HELP},
			},
#endif
			{
				0
			},
		},
	},

	{
		WM_PHASE_HELP,
		"image\\help.blp",
		TRUE,
		{
			{
				WM_PHASE_PLAY,
				0, {1,77},
				558-42*1, 433,
				{1,TX_BUTTON_CONTP},
			},
			{
				WM_PHASE_READ,
				0, {1,52},
				42+42*4, 433,
				{1,TX_BUTTON_READP},
			},
			{
				WM_PHASE_WRITE,
				0, {1,53},
				42+42*5, 433,
				{1,TX_BUTTON_WRITEP},
			},
			{
				WM_PHASE_SETUP,
				0, {1,47},
				42+42*7, 433,
				{1,TX_BUTTON_SETUP},
			},
			{
				WM_PHASE_STOP,
				0, {1,50},
				42+42*0, 433,
				{1,TX_BUTTON_PREVH},
			},
			{
				0
			},
		},
	},

	{
		WM_PHASE_SETUP,
		"image\\setup.blp",
		FALSE,
		{
			{
				WM_BUTTON1,
				0, {1,50},
				54, 330,
				{1,TX_BUTTON_SETUP1},
			},
			{
				WM_BUTTON2,
				0, {1,51},
				54+40, 330,
				{1,TX_BUTTON_SETUP2},
			},
			{
				WM_BUTTON3,
				0, {1,50},
				284, 330,
				{1,TX_BUTTON_SETUP3},
			},
			{
				WM_BUTTON4,
				0, {1,51},
				284+40, 330,
				{1,TX_BUTTON_SETUP4},
			},
			{
				WM_BUTTON5,
				0, {1,50},
				399, 330,
				{1,TX_BUTTON_SETUP5},
			},
			{
				WM_BUTTON6,
				0, {1,51},
				399+40, 330,
				{1,TX_BUTTON_SETUP6},
			},
#if !_EGAMES
			{
				WM_BUTTON7,
				0, {1,50},
				514, 330,
				{1,TX_BUTTON_SETUP7},
			},
			{
				WM_BUTTON8,
				0, {1,51},
				514+40, 330,
				{1,TX_BUTTON_SETUP8},
			},
#endif
			{
				WM_BUTTON9,
				0, {1,50},
				169, 330,
				{1,TX_BUTTON_SETUP9},
			},
			{
				WM_BUTTON10,
				0, {1,51},
				169+40, 330,
				{1,TX_BUTTON_SETUP10},
			},
			{
				WM_PHASE_STOP,
				0, {1,40},
				11, 424,
				{1,TX_BUTTON_TERM},
			},
			{
				0
			},
		},
	},

	{
		WM_PHASE_SETUPp,
		"image\\setup.blp",
		FALSE,
		{
			{
				WM_BUTTON1,
				0, {1,50},
				54, 330,
				{1,TX_BUTTON_SETUP1},
			},
			{
				WM_BUTTON2,
				0, {1,51},
				54+40, 330,
				{1,TX_BUTTON_SETUP2},
			},
			{
				WM_BUTTON3,
				0, {1,50},
				284, 330,
				{1,TX_BUTTON_SETUP3},
			},
			{
				WM_BUTTON4,
				0, {1,51},
				284+40, 330,
				{1,TX_BUTTON_SETUP4},
			},
			{
				WM_BUTTON5,
				0, {1,50},
				399, 330,
				{1,TX_BUTTON_SETUP5},
			},
			{
				WM_BUTTON6,
				0, {1,51},
				399+40, 330,
				{1,TX_BUTTON_SETUP6},
			},
#if !_EGAMES
			{
				WM_BUTTON7,
				0, {1,50},
				514, 330,
				{1,TX_BUTTON_SETUP7},
			},
			{
				WM_BUTTON8,
				0, {1,51},
				514+40, 330,
				{1,TX_BUTTON_SETUP8},
			},
#endif
			{
				WM_BUTTON9,
				0, {1,50},
				169, 330,
				{1,TX_BUTTON_SETUP9},
			},
			{
				WM_BUTTON10,
				0, {1,51},
				169+40, 330,
				{1,TX_BUTTON_SETUP10},
			},
			{
				WM_PHASE_PLAY,
				0, {1,77},
				11, 424,
				{1,TX_BUTTON_CONTP},
			},
			{
				0
			},
		},
	},

	{
		WM_PHASE_READ,
		"image\\read.blp",
		FALSE,
		{
			{
				WM_READ0,
				0, {0},
				420, 30+42*0,
				0,
			},
			{
				WM_READ1,
				0, {0},
				420, 30+42*1,
				0,
			},
			{
				WM_READ2,
				0, {0},
				420, 30+42*2,
				0,
			},
			{
				WM_READ3,
				0, {0},
				420, 30+42*3,
				0,
			},
			{
				WM_READ4,
				0, {0},
				420, 30+42*4,
				0,
			},
			{
				WM_READ5,
				0, {0},
				420, 30+42*5,
				0,
			},
			{
				WM_READ6,
				0, {0},
				420, 30+42*6,
				0,
			},
			{
				WM_READ7,
				0, {0},
				420, 30+42*7,
				0,
			},
			{
				WM_READ8,
				0, {0},
				420, 30+42*8,
				0,
			},
			{
				WM_READ9,
				0, {0},
				420, 30+42*9,
				0,
			},
			{
				WM_PHASE_STOP,
				0, {1,40},
				16, 424,
				{1,TX_BUTTON_TERM},
			},
			{
				0
			},
		},
	},

	{
		WM_PHASE_WRITE,
		"image\\write.blp",
		FALSE,
		{
			{
				WM_WRITE0,
				0, {0},
				420, 30+42*0,
				0,
			},
			{
				WM_WRITE1,
				0, {0},
				420, 30+42*1,
				0,
			},
			{
				WM_WRITE2,
				0, {0},
				420, 30+42*2,
				0,
			},
			{
				WM_WRITE3,
				0, {0},
				420, 30+42*3,
				0,
			},
			{
				WM_WRITE4,
				0, {0},
				420, 30+42*4,
				0,
			},
			{
				WM_WRITE5,
				0, {0},
				420, 30+42*5,
				0,
			},
			{
				WM_WRITE6,
				0, {0},
				420, 30+42*6,
				0,
			},
			{
				WM_WRITE7,
				0, {0},
				420, 30+42*7,
				0,
			},
			{
				WM_WRITE8,
				0, {0},
				420, 30+42*8,
				0,
			},
			{
				WM_WRITE9,
				0, {0},
				420, 30+42*9,
				0,
			},
			{
				WM_PHASE_STOP,
				0, {1,40},
				16, 424,
				{1,TX_BUTTON_TERM},
			},
			{
				0
			},
		},
	},

	{
		WM_PHASE_WRITEp,
		"image\\write.blp",
		FALSE,
		{
			{
				WM_WRITE0,
				0, {0},
				420, 30+42*0,
				0,
			},
			{
				WM_WRITE1,
				0, {0},
				420, 30+42*1,
				0,
			},
			{
				WM_WRITE2,
				0, {0},
				420, 30+42*2,
				0,
			},
			{
				WM_WRITE3,
				0, {0},
				420, 30+42*3,
				0,
			},
			{
				WM_WRITE4,
				0, {0},
				420, 30+42*4,
				0,
			},
			{
				WM_WRITE5,
				0, {0},
				420, 30+42*5,
				0,
			},
			{
				WM_WRITE6,
				0, {0},
				420, 30+42*6,
				0,
			},
			{
				WM_WRITE7,
				0, {0},
				420, 30+42*7,
				0,
			},
			{
				WM_WRITE8,
				0, {0},
				420, 30+42*8,
				0,
			},
			{
				WM_WRITE9,
				0, {0},
				420, 30+42*9,
				0,
			},
			{
				WM_PHASE_PLAY,
				0, {1,77},
				16, 424,
				{1,TX_BUTTON_CONTP},
			},
			{
				0
			},
		},
	},

	{
		WM_PHASE_LOST,
		"image\\lost.blp",
		TRUE,
		{
			{
				WM_PHASE_INFO,
				0, {1,50},
				9, 431,
				{1,TX_BUTTON_REPEAT},
			},
			{
				0
			},
		},
	},

	{
		WM_PHASE_WIN,
		"image\\win.blp",
		TRUE,
		{
			{
				WM_NEXT,
				0, {1,51},
				9, 431,
				{1,TX_BUTTON_NEXTP},
			},
			{
				0
			},
		},
	},

	{
		WM_PHASE_LASTWIN,
		"image\\last%.3d.blp",
		TRUE,
		{
			{
				WM_PHASE_INIT,
				0, {1,51},
				9, 431,
				{1,TX_BUTTON_NEXTP},
			},
			{
				0
			},
		},
	},

	{
		WM_PHASE_BUILD,
		"image\\build.blp",
		TRUE,
		{
			{
				WM_DECOR1,		// pose des sols
				0, {6, 0,1,2,3,4,25},
				11+42*2, 190+42*0,
				{6,TX_OBJ_HERBE,TX_OBJ_MOUSSE,TX_OBJ_TERRE,
				   TX_OBJ_EAU,TX_OBJ_DALLESPEC,TX_OBJ_COUVTELE},
			},
			{
				WM_DECOR2,		// pose des plantes
				0, {4, 6,7,8,11},
				11+42*2, 190+42*1,
				{4,TX_OBJ_DELOBJ,TX_OBJ_PLANTE,
				   TX_OBJ_ARBRE,TX_OBJ_FLEUR1},
			},
			{
				WM_DECOR3,		// pose des batiments
				0, {11, 18,81,33,61,82,93,20,21,22,57,58},
				11+42*2, 190+42*2,
				{11,TX_OBJ_DELOBJ,TX_OBJ_BATIMENT,TX_OBJ_TOUR,
					TX_OBJ_MINEFER,TX_OBJ_BATENNEMIS,TX_OBJ_BARENNEMIS,
					TX_OBJ_MURPAL,TX_OBJ_ROC,TX_OBJ_OBJET,
					TX_OBJ_ARME,TX_OBJ_VEHICULE},
			},
			{
				WM_DECOR4,		// pose des blupi
				0, {10, 12,13,14,85,15,16,17,38,75,56},
				11+42*2, 190+42*3,
				{10,TX_OBJ_DELPERSO,TX_OBJ_BLUPIf,TX_OBJ_BLUPI,
					TX_OBJ_DISCIPLE,TX_OBJ_ARAIGNEE,TX_OBJ_VIRUS,
					TX_OBJ_TRACKS,TX_OBJ_BOMBE,TX_OBJ_ELECTRO,
					TX_OBJ_ROBOT},
			},
			{
				WM_DECOR5,		// pose les catastrophes
				0, {2, 36,37},
				11+42*2, 190+42*4,
				{2,TX_OBJ_DELFEU,TX_OBJ_STARTFEU},
			},
			{
				WM_PHASE_REGION,
				0, {1,5},
				11+42*0, 190+42*1,
				{1,TX_BUTTON_REGION},
			},
			{
				WM_PHASE_MUSIC,
				0, {1,44},
				11+42*0, 190+42*2,
				{1,TX_BUTTON_MUSIC},
			},
			{
				WM_PHASE_BUTTON,
				0, {1,46},
				11+42*0, 190+42*3,
				{1,TX_BUTTON_BUTTON},
			},
			{
				WM_PHASE_TERM,
				0, {1,45},
				11+42*0, 190+42*4,
				{1,TX_BUTTON_CTERM},
			},
			{
				WM_PHASE_INFO,
				0, {1,40},
				11+42*0, 424,
				{1,TX_BUTTON_TERMC},
			},
			{
				WM_PHASE_UNDO,
				0, {1,87},
				11+42*2, 424,
				{1,TX_BUTTON_UNDO},
			},
			{
				0
			},
		},
	},

	{
		WM_PHASE_BUTTON,
		"image\\button.blp",
		TRUE,
		{
			{
				WM_BUTTON1,		// stop
				0, {1,40},
				170+42*0, 30+52*0,
				{1,TX_ACTION_STOP},
			},
			{
				WM_BUTTON0,		// go
				0, {1,24},
				170+42*1, 30+52*0,
				{1,TX_ACTION_GO},
			},
			{
				WM_BUTTON3,		// carry
				0, {1,30},
				170+42*3, 30+52*0,
				{1,TX_ACTION_CARRY},
			},
			{
				WM_BUTTON4,		// depose
				0, {1,31},
				170+42*4, 30+52*0,
				{1,TX_ACTION_DEPOSE},
			},
			{
				WM_BUTTON32,	// r�p�te
				0, {1,100},
				170+42*6, 30+52*0,
				{1,TX_ACTION_REPEAT},
			},

			{
				WM_BUTTON5,		// abat
				0, {1,22},
				170+42*0, 30+52*1,
				{1,TX_ACTION_ABAT},
			},
			{
				WM_BUTTON16,	// abat n
				0, {1,42},
				170+42*1, 30+52*1,
				{1,TX_ACTION_ABATn},
			},
			{
				WM_BUTTON6,		// roc
				0, {1,27},
				170+42*3, 30+52*1,
				{1,TX_ACTION_ROC},
			},
			{
				WM_BUTTON17,	// roc n
				0, {1,43},
				170+42*4, 30+52*1,
				{1,TX_ACTION_ROCn},
			},
			{
				WM_BUTTON22,	// fleurs
				0, {1,54},
				170+42*6, 30+52*1,
				{1,TX_ACTION_FLEUR},
			},
			{
				WM_BUTTON23,	// fleurs n
				0, {1,55},
				170+42*7, 30+52*1,
				{1,TX_ACTION_FLEURn},
			},

			{
				WM_BUTTON9,		// build2 (couveuse)
				0, {1,25},
				170+42*0, 30+52*2,
				{1,TX_ACTION_BUILD2},
			},
			{
				WM_BUTTON15,	// palis
				0, {1,26},
				170+42*1, 30+52*2,
				{1,TX_ACTION_PALIS},
			},
			{
				WM_BUTTON18,	// pont
				0, {1,23},
				170+42*2, 30+52*2,
				{1,TX_ACTION_PONT},
			},
			{
				WM_BUTTON25,	// bateau
				0, {1,58},
				170+42*3, 30+52*2,
				{1,TX_ACTION_BATEAU},
			},
			{
				WM_BUTTON13,	// build6 (t�l�porteur)
				0, {1,101},
				170+42*4, 30+52*2,
				{1,TX_ACTION_BUILD6},
			},
			{
				WM_BUTTON14,	// mur
				0, {1,20},
				170+42*6, 30+52*2,
				{1,TX_ACTION_MUR},
			},
			{
				WM_BUTTON19,	// tour
				0, {1,33},
				170+42*7, 30+52*2,
				{1,TX_ACTION_TOUR},
			},

			{
				WM_BUTTON8,		// build1 (cabane)
				0, {1,19},
				170+42*0, 30+52*3,
				{1,TX_ACTION_BUILD1},
			},
			{
				WM_BUTTON7,		// cultive
				0, {1,28},
				170+42*1, 30+52*3,
				{1,TX_ACTION_CULTIVE},
			},
			{
				WM_BUTTON2,		// mange
				0, {1,32},
				170+42*2, 30+52*3,
				{1,TX_ACTION_MANGE},
			},

			{
				WM_BUTTON10,	// build3 (laboratoire)
				0, {1,35},
				170+42*0, 30+52*4,
				{1,TX_ACTION_BUILD3},
			},
			{
				WM_BUTTON21,	// laboratoire
				0, {1,39},
				170+42*1, 30+52*4,
				{1,TX_ACTION_LABO},
			},
			{
				WM_BUTTON20,	// boit
				0, {1,34},
				170+42*2, 30+52*4,
				{1,TX_ACTION_BOIT},
			},
			{
				WM_BUTTON24,	// dynamite
				0, {1,41},
				170+42*3, 30+52*4,
				{1,TX_ACTION_DYNAMITE},
			},

			{
				WM_BUTTON27,	// drapeau
				0, {1,64},
				170+42*0, 30+52*5,
				{1,TX_ACTION_DRAPEAU},
			},
			{
				WM_BUTTON11,	// build4 (mine)
				0, {1,61},
				170+42*1, 30+52*5,
				{1,TX_ACTION_BUILD4},
			},
			{
				WM_BUTTON28,	// extrait
				0, {1,62},
				170+42*2, 30+52*5,
				{1,TX_ACTION_EXTRAIT},
			},
			{
				WM_BUTTON12,	// build5 (usine)
				0, {1,59},
				170+42*4, 30+52*5,
				{1,TX_ACTION_BUILD5},
			},
			{
				WM_BUTTON29,	// fabrique jeep
				0, {1,65},
				170+42*5, 30+52*5,
				{1,TX_ACTION_FABJEEP},
			},
			{
				WM_BUTTON30,	// fabrique mine
				0, {1,63},
				170+42*6, 30+52*5,
				{1,TX_ACTION_FABMINE},
			},
			{
				WM_BUTTON34,	// fabrique armure
				0, {1,106},
				170+42*7, 30+52*5,
				{1,TX_ACTION_FABARMURE},
			},
			{
				WM_BUTTON31,	// fabrique disciple
				0, {1,83},
				170+42*8, 30+52*5,
				{1,TX_ACTION_FABDISC},
			},

//			{
//				WM_BUTTON13,	// build6
//				0, {0},
//				170+42*2, 30+52*5,
//				{1,TX_ACTION_BUILD6},
//			},
			{
				WM_PHASE_BUILD,
				0, {1,50},
				11, 424,
				{1,TX_BUTTON_TERM},
			},
			{
				0
			},
		},
	},

	{
		WM_PHASE_TERM,
		"image\\term.blp",
		TRUE,
		{
			{
				WM_BUTTON8,		// home blupi
				0, {1,81},
				170+42*0, 30+42*0,
				{1,TX_BUTTON_TERMMBLUPI},
			},
			{
				WM_BUTTON9,		// kill robots
				0, {1,57},
				170+42*1, 30+42*0,
				{1,TX_BUTTON_TERMKILL},
			},
			{
				WM_BUTTON3,		// stop fire
				0, {1,37},
				170+42*2, 30+42*0,
				{1,TX_BUTTON_TERMFIRE},
			},
			{
				WM_BUTTON1,		// hach blupi
				0, {1,14},
				170+42*0, 30+42*2,
				{1,TX_BUTTON_TERMHBLUPI},
			},
			{
				WM_BUTTON2,		// hach planche
				0, {1,22},
				170+42*1, 30+42*2,
				{1,TX_BUTTON_TERMHPLANCHE},
			},
			{
				WM_BUTTON10,	// hach tomate
				0, {1,28},
				170+42*2, 30+42*2,
				{1,TX_BUTTON_TERMHTOMATE},
			},
			{
				WM_BUTTON11,	// hach m�tal
				0, {1,84},
				170+42*3, 30+42*2,
				{1,TX_BUTTON_TERMHMETAL},
			},
			{
				WM_BUTTON12,	// hach robot
				0, {1,94},
				170+42*4, 30+42*2,
				{1,TX_BUTTON_TERMHROBOT},
			},
			{
				WM_BUTTON4,		// - min blupi
				0, {1,50},
				170+42*0, 30+42*4,
				{1,TX_BUTTON_TERMDEC},
			},
			{
				WM_BUTTON5,		// + min blupi
				0, {1,51},
				170+42*1, 30+42*4,
				{1,TX_BUTTON_TERMINC},
			},
			{
				WM_BUTTON6,		// - max blupi
				0, {1,50},
				170+42*0, 30+42*5,
				{1,TX_BUTTON_TERMDEC},
			},
			{
				WM_BUTTON7,		// + max blupi
				0, {1,51},
				170+42*1, 30+42*5,
				{1,TX_BUTTON_TERMINC},
			},
			{
				WM_PHASE_BUILD,
				0, {1,50},
				11, 424,
				{1,TX_BUTTON_TERM},
			},
			{
				0
			},
		},
	},

	{
		WM_PHASE_MUSIC,
		"image\\music.blp",
		TRUE,
		{
			{
				WM_BUTTON1,
				0, {1,40},
				170+42*0, 30+42*0,
				{1,TX_BUTTON_MUSIC1},
			},
			{
				WM_BUTTON2,
				0, {1,44},
				170+42*0, 30+42*1,
				{1,TX_BUTTON_MUSIC2},
			},
			{
				WM_BUTTON3,
				0, {1,44},
				170+42*0, 30+42*2,
				{1,TX_BUTTON_MUSIC3},
			},
			{
				WM_BUTTON4,
				0, {1,44},
				170+42*0, 30+42*3,
				{1,TX_BUTTON_MUSIC4},
			},
			{
				WM_BUTTON5,
				0, {1,44},
				170+42*0, 30+42*4,
				{1,TX_BUTTON_MUSIC5},
			},
			{
				WM_BUTTON6,
				0, {1,44},
				170+42*0, 30+42*5,
				{1,TX_BUTTON_MUSIC6},
			},
			{
				WM_BUTTON7,
				0, {1,44},
				170+42*0, 30+42*6,
				{1,TX_BUTTON_MUSIC7},
			},
			{
				WM_BUTTON8,
				0, {1,44},
				170+42*0, 30+42*7,
				{1,TX_BUTTON_MUSIC8},
			},
			{
				WM_BUTTON9,
				0, {1,44},
				170+42*0, 30+42*8,
				{1,TX_BUTTON_MUSIC9},
			},
			{
				WM_BUTTON10,
				0, {1,44},
				170+42*0, 30+42*9,
				{1,TX_BUTTON_MUSIC10},
			},
			{
				WM_PHASE_BUILD,
				0, {1,50},
				11, 424,
				{1,TX_BUTTON_TERM},
			},
			{
				0
			},
		},
	},

	{
		WM_PHASE_REGION,
		"image\\region.blp",
		TRUE,
		{
			{
				WM_BUTTON1,		// normal
				0, {0},
				220, 60,
				{1,TX_BUTTON_REGION1},
			},
			{
				WM_BUTTON4,		// sapins
				0, {0},
				220, 170,
				{1,TX_BUTTON_REGION4},
			},
			{
				WM_BUTTON2,		// palmiers
				0, {0},
				220, 280,
				{1,TX_BUTTON_REGION2},
			},
			{
				WM_BUTTON3,		// hivers
				0, {0},
				220, 390,
				{1,TX_BUTTON_REGION3},
			},
			{
				WM_PHASE_BUILD,
				0, {1,50},
				11, 424,
				{1,TX_BUTTON_TERM},
			},
			{
				0
			},
		},
	},

	{
		WM_PHASE_PLAYMOVIE,
		"image\\movie.blp",
		FALSE,
		{
			{
				0
			},
		},
	},

	{
		WM_PHASE_WINMOVIE,
		"image\\movie.blp",
		FALSE,
		{
			{
				0
			},
		},
	},

	{
		WM_PHASE_H0MOVIE,
		"image\\movie.blp",
		FALSE,
		{
			{
				0
			},
		},
	},

	{
		WM_PHASE_H1MOVIE,
		"image\\movie.blp",
		FALSE,
		{
			{
				0
			},
		},
	},

	{
		WM_PHASE_H2MOVIE,
		"image\\movie.blp",
		FALSE,
		{
			{
				0
			},
		},
	},

	{
		WM_PHASE_BYE,
		"image\\bye.blp",
		FALSE,
		{
			{
				0
			},
		},
	},

	{
		WM_PHASE_INSERT,
		"image\\insert.blp",
		FALSE,
		{
//?			{
//?				WM_PHASE_INFO,
//?				0, {1,48},
//?				16, 424-42,
//?				{1,TX_BUTTON_PLAYP},
//?			},
			{
				WM_PHASE_INIT,
				0, {1,40},
				16, 424,
				{1,TX_BUTTON_QUITTER},
			},
			{
				0
			},
		},
	},

	{
		0
	}
};

// Constructor

CEvent::CEvent()
{
    int     i;

    m_bFullScreen   = TRUE;
	m_mouseType     = MOUSETYPEGRA;
	m_exercice      = 0;
	m_mission       = 0;
	m_private       = 0;
	m_maxMission    = 0;
	m_phase         = 0;
	m_index         = -1;
	m_bSchool       = FALSE;
	m_bPrivate      = FALSE;
	m_bAccessBuild  = FALSE;
	m_bRunMovie     = FALSE;
	m_bBuildModify  = FALSE;
	m_bMousePress   = FALSE;
	m_bMouseDown    = FALSE;
	m_oldMousePos.x = 0;
	m_oldMousePos.y = 0;
	m_mouseSprite   = 0;
	m_bFillMouse    = FALSE;
	m_bWaitMouse    = FALSE;
	m_bHideMouse    = FALSE;
	m_bShowMouse    = FALSE;
	m_rankCheat     = -1;
	m_posCheat      = 0;
	m_speed         = 1;
	m_bMovie        = TRUE;
	m_bSpeed        = FALSE;
	m_bHelp         = FALSE;
	m_bAllMissions  = FALSE;
	m_bChangeCheat  = FALSE;
	m_scrollSpeed   = 1;
	m_bPause        = FALSE;
	m_bShift        = FALSE;
	m_shiftPhase    = 0;
	m_movieToStart[0] = 0;
	m_bInfoHelp     = FALSE;
	m_bDemoRec      = FALSE;
	m_bDemoPlay     = FALSE;
	m_pDemoBuffer   = NULL;
	m_demoTime      = 0;
	m_bCtrlDown     = FALSE;

    for ( i=0 ; i<MAXBUTTON ; i++ )
    {
        m_lastFloor[i] = 0;
    }

    for ( i=0 ; i<MAXBUTTON; i++ )
    {
        m_lastObject[i] = 0;
    }

    for ( i=0 ; i<MAXBUTTON ; i++ )
    {
        m_lastHome[i] = 0;
    }
}

// Destructor

CEvent::~CEvent()
{
    WriteInfo(); // Read the file "info.blp"
}

// Returns the mouse position

POINT CEvent::GetMousePos()
{
    POINT       pos;

    GetCursorPos(&pos);
    ScreenToClient(m_hWnd, &pos);

    return pos;
}

void CEvent::SetFullScreen(BOOL bFullScreen)
{
    m_bFullScreen = bFullScreen;
}

// Initializes the mouse type.

void CEvent::SetMouseType(int mouseType)
{
    m_mouseType = mouseType;
}

// Creates the event handler.

void CEvent::Create(HWND hWnd, CPixmap *pPixmap, CDecor *pDecor,
                    CSound *pSound, CMovie *pMovie, CNetwork *pNetwork)
{
    POINT   pos;

    m_hWnd    = hWnd;
    m_pPixmap = pPixmapl
    m_pDecor  = pDecor;
    m_pSound  = pSound;
    m_pMovie  = pMovie;

    ReadInfo();
}


// Returns the index of the button.

int CEvent::GetButtonIndex(int button)
{
    int         i=0;

    while ( table[m_index].buttons[i].message != 0 )
    {
        if ( (UINT)button == table[m_index].buttons[i].message )
        {
            return i;
        }
        i ++;
    }

    return -1;
}

int CEvent::GetState(int button)
{
    int     index;

    index = GetButtonIndex(button);
    if ( index < 0 ) return 0;

    return m_buttons[index].GetState();
}

void CEvent::SetState(int button, int state)
{
    ind     index;

    index = GetButtonIndex(button);
    if ( index < 0 ) return;

    m_buttons[index].SetState(state);
}

BOOL CEvent::GetEnable(int button)
{
    int     index;

    index = GetButtonIndex(button);
    if ( index < 0 ) return 0;

    return m_buttons[index].GetEnable();
}

void CEvent::SetEnable(int button, BOOL bEnable)
{
    int      index;

    index = GetButtonIndex(button);
    if ( index < 0 ) return;

    m_buttons[index].SetEnable(bEnable);
}

int CEvent::GetMenu(int button)
{
    int     index;

    index = GetButtonIndex(button);
    if ( index < 0 ) return 0;

    return m_buttons[index].GetMenu();
}

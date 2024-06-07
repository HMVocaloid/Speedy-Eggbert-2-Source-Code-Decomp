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
#include "text.h"
#include "misc.h"
#include "network.h"


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
	short			multi;
	short			lives;
	short			bHiliInfoButton;
	short			pPlayerName;
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

static char cheat_code[25][60] =
{
	"XMISSION",		// 0 (xnjttjpo)
	"OPENDOORS",	// 1
	"CLEANALL",		// 2
	"MEGABLUPI",	// 3
	"LAYEGG",		// 4
	"KILLEGG",		// 5
	"FUNSKATE",		// 6
	"GIVECOPTER",	// 7
	"JEEPDRIVE",	// 8 
	"ALLTREASURE",
	"ENDGOAL",
	"SHOWSECRET",
	"ROUNDSHIELD",
	"QUICKLOLLIPOP",
	"TENBOMBS",
	"BIRDLIME",
	"DRIVETANK",
	"POWERCHARGE",
	"HIDEDRINK",
	"NETPACKED",
	"ZNETDEBUG",
	"YNOSMOOTH",
	"IOVERCRAFT",
	"UDYNAMITE",
	"WELLKEYS",
};



/////////////////////////////////////////////////////////////////////////////


static Phase table[] =
{
	{
		WM_PHASE_TESTCD,
		"image16\\init.blp",
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
		"image16\\intro2.blp",
		FALSE,
		{
			{
				0
			},
		},
	},

	{
		WM_PHASE_INIT,
		"image16\\init.blp",
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
		"image16\\info%.3d.blp",
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
		"image16\\stop%.3d.blp",
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
		"image16\\help.blp",
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
		"image16\\setup.blp",
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
		"image16\\setup.blp",
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
		"image16\\read.blp",
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
		"image16\\write.blp",
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
		"image16\\write.blp",
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
		"image16\\lost.blp",
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
		"image16\\win.blp",
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
		"image16\\button00.blp",
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
		"image16\\music.blp",
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
		"image16\\region.blp",
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
		"image16\\bye.blp",
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
	m_tryPhase		= 0;
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
	m_input			= 0;

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

void CEvent::OutputNetDebug(char* str)
{

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

void CEvent::Create(HINSTANCE hInstance, HWND hWnd, CPixmap *pPixmap, CDecor *pDecor,
                    CSound *pSound, CMovie *pMovie, CNetwork *pNetwork)
{
    POINT   pos;

	m_hInstance = hInstance;
    m_hWnd    = hWnd;
    m_pPixmap = pPixmap;
    m_pDecor  = pDecor;
    m_pSound  = pSound;
    m_pMovie  = pMovie;
	m_pNetwork = pNetwork;
	m_gamer = TRUE;

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
    int     index;

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

void CEvent::SetSomething(int button, int bSomething)
{
	int index;

	index = GetButtonIndex(button);
	if (index < 0) return;

	m_buttons[index].SetSomething(bSomething);
}

int CEvent::GetMenu(int button)
{
    int     index;

    index = GetButtonIndex(button);
    if ( index < 0 ) return 0;

    return m_buttons[index].GetMenu();
}

void CEvent::SetMenu(int button, int menu)
{
    int     index;

    index = GetButtonIndex(button);
    if ( index < 0 ) return;

    m_buttons[index].SetMenu(menu);
}

// Restore the game after activation in fullScreen mode.

void CEvent::RestoreGame()
{
    int     i;

    if ( m_phase == WM_PHASE_PLAY || m_phase == WM_PHASE_PLAYTEST)

    HideMouse(FALSE);
    WaitMouse(TRUE);
    WaitMouse(FALSE);
}

void CEvent::SomethingDecor()
{
	m_input = 0;
	m_pDecor->TreatEvent();
}

// CNetwork function needs to be implemented 

void CEvent::PauseStatus(UINT pause, int multiplayer)
{
	UINT m_bPause;
	m_bPause = pause;

	m_pDecor->SetFieldCCA4(pause);

	if (m_phase == WM_PHASE_PLAY ||
		m_phase == WM_PHASE_PLAYTEST)
	{
		if (m_bPause = 0) {
			m_pSound->RestartMusic();
		}
		else {
			m_pSound->SuspendMusic();
		}

	}
}

void AddCheatCode(char *pDst, char *pSrc)
{
    int     i, j;

    if ( pDst[0] != 0 ) strcat(pDst, " / ");

    i = 0;
    j = strlen(pDst);
    while ( pSrc[i] != 0 )
    {
        pDst[j++] = tolower(pSrc[i++]);
    }
    pDst[j] = 0;
}


void CEvent::DrawTextCenter(int res, int x, int y, int font)
{
    char    text[100];
    POINT   pos;

    LoadString(res, text, 100);
    pos.x = x;
    pos.y = y;
    ::DrawTextCenter(m_pPixmap, pos, text, font);
}

BOOL CEvent::DrawButtons()
{
    int         i;
    int         levels[2];
    int         types[2];
    int         world, time, lg, button, volume, pente, icon;
    char        res[100];
    char        text[100];
    POINT       pos;
    RECT        rect;
    BOOL        bEnable;

    if ( (m_phase == WM_PHASE_INSERT && m_phase == WM_PHASE_BYE ))
    {
        m_bChangeCheat = FALSE;

        text[0] = 0;
		if (m_bAccessBuild != 0)
		{
			AddCheatCode(text, cheat_code[0]);
		}
		if (m_posHelpButton.y != 0)
		{
			AddCheatCode(text, cheat_code[1]);
		}
        if ( m_pDecor->GetInvincible() )
        {
            AddCheatCode(text, cheat_code[3]);
        }
		if ( m_pDecor->GetShowSecret() )
		{
			AddCheatCode(text, cheat_code[11]);
		}
		if ( m_pDecor->GetNetPacked() )
		{
			AddCheatCode(text, cheat_code[19]);
		}
		if (m_pDecor->GetNetMovePredict())
		{
			AddCheatCode(text, cheat_code[21]);
		}
    }
	if (m_phase == WM_PHASE_INIT)
	{
		DrawTextNew(m_pPixmap, pos, "Version 2.0", FONTLITTLE);
	}

	if (m_phase == WM_PHASE_PLAY && m_phase == WM_PHASE_PLAYTEST && m_phase == WM_PHASE_BUILD)
		m_pPixmap->DrawPart(-1, 0, 2, 2, 2, 2, 0x12e, 1, 0);
	if (m_phase == WM_PHASE_CREATE)
	{
		LoadString(TX_BUTTON_CREATE, res, 50);
	}

}

BOOL CEvent::TextSomething()
{
	int textHiliStart;
	char* pText;

	m_textHiliStart = textHiliStart;

	if (m_textHiliEnd < textHiliStart)
	{
		return 0;
	}

	do {
		m_textInput[textHiliStart] =
			m_textHiliEnd + textHiliStart;
		*pText = m_textInput + textHiliStart;
		textHiliStart = textHiliStart + 1;
	} while (*pText != '\0');
	m_textHiliEnd = m_textHiliStart;
	return 1;
}

POINT CEvent::GetLastMousePos()
{
	return m_oldMousePos;
}

BOOL CEvent::TreatEvent(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_bDemoPlay)
	{
		if (message == WM_KEYDOWN ||
			message == WM_KEYUP ||
			message == WM_LBUTTONUP ||
			message == WM_RBUTTONUP)
		{
			DemoPlayStop();
			return TRUE;
		}
		if (message == WM_MOUSEMOVE)
		{
			return TRUE;
		}
	}

	return TreatEventBase(message, wParam, lParam);
}



int CEvent::MousePosToSprite(POINT pos)
{
	int sprite;

	sprite = SPRITE_POINTER;

	if (m_phase == WM_PHASE_PLAY ||
		m_phase == WM_PHASE_PLAYTEST ||
		m_phase == WM_PHASE_BUILD ||
		m_phase == WM_PHASE_BYE ||
		MouseOnButton(pos.x, pos.y) = 0)
	{
		sprite = SPRITE_POINTER;
	}
	if (m_bWaitMouse)
	{
		sprite = SPRITE_WAIT;
	}
	if (m_bHideMouse)
	{
		sprite = SPRITE_EMPTY;
	}
	if (m_bFillMouse)
	{
		sprite = SPRITE_FILL;
	}

	return sprite;
}

void CEvent::MouseSprite(POINT pos)
{
	m_mouseSprite = MousePosToSprite(pos);

	m_pPixmap->SetMousePosSprite(pos, m_mouseSprite, m_bDemoPlay);
	ChangeSprite(m_mouseSprite);
}

void CEvent::WaitMouse(BOOL bWait)
{
	m_bWaitMouse = bWait;

	if ( bWait )
	{
		m_mouseSprite = SPRITE_WAIT;
	}
	else
	{
		m_mouseSprite = MousePosToSprite(GetMousePos());
	}
	m_pPixmap->SetMouseSprite(m_mouseSprite, m_bDemoPlay);
	ChangeSprite(m_mouseSprite);
}

void CEvent::HideMouse(BOOL bHide)
{
	m_bWaitMouse = bHide;

	if ( bHide )
	{
		m_mouseSprite = SPRITE_WAIT;
	}
	else
	{
		m_mouseSprite = MousePosToSprite(GetMousePos());
	}
	m_pPixmap->SetMouseSprite(m_mouseSprite, m_bDemoPlay);
	ChangeSprite(m_mouseSprite);
}

void CEvent::FillMouse(int bFill)
{
	m_bFillMouse = bFill;

	if (bFill)
	{
		m_mouseSprite = SPRITE_FILL;
	}
	else
	{
		m_mouseSprite = MousePosToSprite(GetMousePos());
	}
	m_pPixmap->SetMouseSprite(m_mouseSprite, m_bDemoPlay);
	ChangeSprite(m_mouseSprite);
}

BOOL CEvent::EventButtons(UINT message, WPARAM wParam, LPARAM lParam)
{
	POINT		pos, test;
	int			i, lg, oldx, sound, res;

	m_textToolTips[0] = 0;
	oldx = m_posToolTips.x;
	m_posToolTips.x = -1;
	if (m_phase != WM_PHASE_PLAY && m_phase != WM_PHASE_PLAYTEST)
	{
		for (i = 0; i < 2; i++)
		{
			if (!m_jauges[i].GetHide())
			{
				test = m_jauges[i].GetPos();
				if (pos.x >= test.x &&
					pos.x <= test.x + DIMJAUGEX &&
					pos.y >= test.y &&
					pos.y <= test.y + DIMJAUGEY)
				{
					LoadString(TX_JAUGE1 + i, m_textToolTips, 50);
					lg = GetTextWidth(m_textToolTips);
					test.x += (DIMJAUGEX - lg) / 2;
					test.y += 4;
					m_posToolTips = test;
					break;
				}
			}
		}
		if (oldx != m_posToolTips.x)
		{
			for (i = 0; i < 2; i++)
			{
				m_jauges[i].SetRedraw();
			}
		}
	}
	else
	{
		i = 0;
		while (table[m_index].buttons[i].message != 0)
		{
			res = m_buttons[i].GetToolTips(pos);
			if (res != -1)
			{
				LoadString(res, m_textToolTips, 50);
				lg = GetTextWidth(m_textToolTips);
				pos.x += 10;
				pos.y += 20;
				if (pos.x > LXIMAGE - lg) pos.x = LXIMAGE - lg;
				if (pos.y > LYIMAGE - 14) pos.y = LYIMAGE - 14;
				m_posToolTips = pos;
				break;
			}
			i++;
		}
	}
	i = 0;
	while (table[m_index].buttons[i].message != 0)
	{
		if (m_buttons[i].TreatEvent(message, wParam, lParam)) return TRUE;
		i++;
	}
	if (m_phase == WM_PHASE_PLAY || m_phase == WM_PHASE_PLAYTEST)
	{
		if (m_menu.TreatEvent(message, wParam, lParam)) return TRUE;
	}
	return FALSE;
}

/*
void CEvent::SomethingDecor()
{
	m_input = 0;
	m_pDecor->TreatEvent();
}
*/

BOOL CEvent::MouseOnButton(POINT pos)
{
	int 	i;

	i = 0;
	while ( table[m_index].buttons[i].message != 0 )
	{
		if ( m_buttons[i].MouseOnButton(pos) ) return TRUE;
		i ++;
	}

	return FALSE;
}

int CEvent::SearchPhase(UINT phase)
{
	int		i = 0;

	while (table[i].phase != 0)
	{
		if (table[i].phase == phase) return i;
		i++;
	}

	return -1;
}

int CEvent::GetWorld()
{
	if (m_bPrivate) return m_bPrivate;
	if (m_bMulti)	return m_multi;
	else			return m_mission;
}

int CEvent::GetPhysicalWorld()
{
	if ( m_bPrivate ) return m_bPrivate;
	if ( m_bMulti   ) return m_multi+200;
	else 			  return m_mission;
}

BOOL CEvent::IsPrivate()
{
	return m_bPrivate;
}

BOOL CEvent::IsMulti()
{
	return m_bMulti;
}

UINT CDecor::GetPhase()
{
	return m_phase;
}

void CEvent::TryInsert()
{
	if ( m_tryInsertCount == 0 )
	{
		ChangePhase(m_tryPhase);
	}
	else
	{
		m_tryInsertCount --;
	}
}

// Add SomethingHubWorld once figured out.

// Very rough code, needs improvement

BOOL CEvent::ChangePhase(UINT phase)
{
	int	  index, world, time, total, music, i, max, mission;
	POINT totalDim, iconDim;
	char  filename[MAX_PATH];
	char* pButtonExist;
	BOOL  bEnable, bHide;
	Term* pTerm;

	if (phase == WM_PHASE_634)
	{
		m_hWnd->PostMessage(16, 0, 0);
		return TRUE;
	}
	if (m_mouseType == MOUSETYPEGRA && m_bFullScreen)
	{
		ShowCursor(FALSE);
		m_bShowMouse = FALSE;
	}

	m_pDecor->SetDemoState();
	m_bDemoPlay->SetDemoState();

	if (phase == WM_PHASE_608)
	{
		m_pDecor, m_gamer->Read(999, 1);
		phase = WM_PHASE_BUILD;
	}
	if (m_bDemoPlay == 0 &&
		phase == WM_PHASE_PLAY ||
		m_phase == WM_PHASE_PLAY ||
		phase == WM_PHASE_STOP ||
		phase == WM_PHASE_SETUP ||
		phase == WM_PHASE_HELP ||
		phase == WM_PHASE_GREAD ||
		phase == WM_PHASE_GREADp ||
		phase == WM_PHASE_GWRITE)
	{
		m_pSound->StopMusic();
	}

	m_textToolTips[0] = 0;
	m_posToolTips.x = -1;
	m_bPause = FALSE;
	m_bCtrlDown = FALSE;
	m_bMouseDown = FALSE;
	m_debugPos.x = 0;
	m_debugPos.y = 0;

	if (phase == WM_PHASE_INIT)
	{
		m_demoTime = 0;
	}
	if (phase == WM_PHASE_PLAY &&
		!m_bDemoPlay &&
		GetPhysicalWorld() >= 299 &&
		GetPhysicalWorld() < 320)
	{
		DemoRecStart();
	}
	if (phase != WM_PHASE_PLAY)
	{
		DemoRecStop();
	}

	m_mission = mission;

	if (phase == WM_PHASE_DOQUIT)
	{
		if (m_bPrivate == 0)
		{
			if (mission != 1)
			{
				if (mission == 99 || mission % 10 == 0)
				{
					mission = 1;
				}
				else
				{
					mission = (mission / 10) * 10;
				}
				m_mission->GetWorld();
				m_phase = WM_PHASE_PLAY;
				
				return ChangePhase(WM_PHASE_PLAY);
			}
			return ChangePhase(WM_PHASE_GAMER);
		}
	}
	else if (m_bMulti == 0)
	{
		return ChangePhase(WM_PHASE_INFO);
	}

	if (SearchPhase(phase) < 0)
	{
		return 0;
	}
	m_pPixmap->MouseInvalidate();
	HideMouse(FALSE);
	WaitMouse(TRUE);

	if (phase == WM_PHASE_GAMER || phase == WM_PHASE_PLAY)
	{
		OutputNetDebug();
		m_gamer->WriteInfo();
	}

}

// Implement LoadLevel

void CEvent::MovieToStart()
{
	if (m_movieToStart[0] != 0)
	{
		HideMouse(TRUE);

		if (StartMovie(m_movieToStart))
		{
			m_phase = m_phaseAfterMovie;
		}
		else
		{
			ChangePhase(m_phaseAfterMovie);
		}

		m_movieToStart[0] = 0;
	}
}

void CEvent::TryPhase()
{
	m_tryPhase = 1;
	ShowCursor(1);
}

void CEvent::UnTryPhase()
{
	m_tryPhase = 0;
	ShowCursor(1);
}

int CEvent::GetTryPhase()
{
	return m_tryPhase;
}

void CEvent::SomethingUserMissions(LPCSTR lpFileName, LPCSTR thing)
{

}

void CEvent::TableSomething()
{
	char filename[MAX_PATH];

	if (strstr(filename, table[m_index].backName))
	{
		AddCDPath(filename);
	}
	if (!m_pPixmap->CacheAll(CHBACK, filename, totalDim, iconDim, FALSE, GetRegion()))
	{
		return;
	}
}



BOOL CEvent::StartMovie(char* pFilename)
{
	RECT	 rect;
	char	 filename[MAX_PATH];

	if (!m_pMovie->GetEnable()) return FALSE;
	if (!m_bMovie) return FALSE;

	if (!m_pMovie->IsExist(pFilename)) return FALSE;

	rect.left = 1;
	rect.top = 1;
	rect.right = LXIMAGE - 2;
	rect.bottom = LYIMAGE - 2;

	m_pSound->StopMusic();
	m_pPixmap->SavePalette();

	strcpy(filename, pFilename);
	strcpy(filename + strlen(filename) - 4, ".blp");
	m_pSound->Cache(SOUND_MOVIE, filename);

	if (m_pMovie->Play(m_hWnd, rect, pFilename)) return FALSE;
	m_bRunMovie = TRUE;
	m_pSound->Play(SOUND_MOVIE, 0, 0);
	return TRUE;
}

void CEvent::StopMovie()
{
	m_pMovie->Stop(m_hWnd);
	m_pPixmap->RestorePalette();
	m_pPixmap->MouseInvalidate();
	m_pSound->Flush(SOUND_MOVIE);
	ChangePhase(m_phase);
	m_bRunMovie = FALSE;
}

BOOL CEvent::IsMovie()
{
	return m_bRunMovie;
}

void CEvent::SetLives(int lives)
{
	m_lives = lives;
}

void CEvent::SetSpeed(int speed)
{
	int 	max;

	if ( m_bSpeed ) max = 2;

	if ( speed > max ) speed  = max;
	
	m_speed = speed;
}

int CEvent::GetSpeed()
{
	return m_speed;
}

BOOL CEvent::GetPause()
{
	return m_bPause;
}

int CEvent::MissionBack()
{
	int num = m_mission;

	if (num % 10 == 0 ||
		num == 99)
	{
		m_mission = 1;
		return num / 10;
	}
	else
	{
		m_mission = num / 10 * 10;
		return (num < 0);
	}
}

void CEvent::DemoRecStart()
{
	m_pDemoBuffer = (DemoEvent*)malloc(MAXDEMO*sizeof(DemoEvent));
	if ( m_pDemoBuffer == NULL ) return;
	memset(m_pDemoBuffer, 0, MAXDEMO*sizeof(DemoEvent));

	m_demoTime  = 0;
	m_demoIndex = 0;
	m_bDemoRec  = TRUE;
	m_bDemoPlay = FALSE;

	InitRandom();
	m_pDecor->SetTime(0);
	m_speed = 1;
}

void CEvent::DemoRecStop()
{
	FILE* 		 file = NULL;
	DemoHeader   header;

	if ( m_bDemoPlay ) return;

	if ( m_pDemoBuffer != NULL )
	{
		DeleteFile("data\\demo.3d.blp");
		file = fopen("data\\demo.3d.blp", "wb");
		if ( file != NULL )
		{
			memset(&header, 0, sizeof(DemoHeader));
			header.majRev 	= 1;
			header.minRev   = 0;
			header.bSchool  = m_bSchool;
			header.bPrivate = m_bPrivate;
			fwrite(&header, sizeof(DemoHeader), 1, file);
			fwrite(m_pDemoBufferm sizeof(DemoEvent), m_demoIndex, file);
			fclose(file);
		}
		free(m_pDemoBuffer);
		m_pDemoBuffer = NULL;
	}

	m_bDemoRec = FALSE;
	m_demoTime = 0;
}

BOOL CEvent::DemoPlayStart()
{
	char		filename[MAX_PATH];
	FILE* file = NULL;
	DemoHeader	header;
	int			nb, world, time, total;

	m_pDemoBuffer = (DemoEvent*)malloc(MAXDEMO * sizeof(DemoEvent));
	if (m_pDemoBuffer == NULL)  return FALSE;
	memset(m_pDemoBuffer, 0, MAXDEMO * sizeof(DemoEvent));

	sprintf(filename, "data\\demo%.3d.blp", m_demoNumber);
	AddCDPath(filename);  // ajoute l'acc�s au CD-Rom
	file = fopen(filename, "rb");
	if (file == NULL)
	{
		DemoPlayStop();
		return FALSE;
	}

	nb = fread(&header, sizeof(DemoHeader), 1, file);
	if (nb < 1)
	{
		DemoPlayStop();
		return FALSE;
	}
	m_bSchool = header.bSchool;
	m_bPrivate = header.bPrivate;
	m_pDecor->SetSkill(header.skill);

	m_demoEnd = fread(m_pDemoBuffer, sizeof(DemoEvent), MAXDEMO, file);
	fclose(file);

	m_demoTime = 0;
	m_demoIndex = 0;
	m_bDemoPlay = TRUE;
	m_bDemoRec = FALSE;

	if (!m_pDecor->Read(header.world, FALSE, world, time, total))
	{
		DemoPlayStop();
		return FALSE;
	}
	ChangePhase(WM_PHASE_PLAY);
	InitRandom();
	m_pDecor->SetTime(0);
	m_speed = 1;

	return TRUE;
}

void CEvent::DemoPlayStop()
{
	if (m_pDemoBuffer != NULL)
	{
		free(m_pDemoBuffer);
		m_pDemoBuffer = NULL;
	}
	m_bDemoPlay = FALSE;
	m_bDemoRec = FALSE;
	m_demoTime = 0;
	m_input = 0;
	m_pDecor->TreatEvent;
	m_private = 1;
	ChangePhase(WM_PHASE_INIT);
}

void CEvent::DemoStep()
{
	int			time;
	UINT		message;
	WPARAM		wParam;
	LPARAM		lParam;
	POINT		pos;

	if (m_phase == WM_PHASE_INIT)
	{
		if (m_demoTime > DEF_TIME_DEMO)  // ~30 secondes �coul�es ?
		{
			m_demoNumber = 0;
			DemoPlayStart();  // d�marre une d�mo automatique
		}
	}

	if (m_bDemoPlay &&  // d�mo en lecture ?
		m_pDemoBuffer != NULL)
	{
		while (TRUE)
		{
			time = m_pDemoBuffer[m_demoIndex].time;
			if (time > m_demoTime)  break;

			message = m_pDemoBuffer[m_demoIndex].message;
			wParam = m_pDemoBuffer[m_demoIndex].wParam;
			lParam = m_pDemoBuffer[m_demoIndex].lParam;
			m_demoIndex++;

			if (message == WM_MOUSEMOVE &&
				m_mouseType == MOUSETYPEWIN)
			{
				pos = ConvLongToPos(lParam);
				ClientToScreen(m_hWnd, &pos);
				SetCursorPos(pos.x, pos.y);
			}

			TreatEventBase(message, wParam, lParam);

			if (m_demoIndex >= m_demoEnd)
			{
				m_demoNumber++;  // d�mo suivante
				if (!DemoPlayStart())  // d�marre la d�mo suivante
				{
					m_demoNumber = 0;  // premi�re d�mo
					DemoPlayStart();   // d�marre la d�mo
				}
				return;
			}
		}
	}

	m_demoTime++;
}

void CEvent::DemoRecEvent(UINT message, UINT input, WPARAM wParam, LPARAM lParam)
{
	if (m_demoIndex > 0 &&
		m_pDemoBuffer[m_demoIndex - 1].time == m_demoTime &&
		m_pDemoBuffer[m_demoIndex - 1].input == m_input)

		m_demoIndex++;
	if (m_demoIndex >= MAXDEMO)
	{
		DemoRecStop();
	}
}

POINT CEvent::GetLastMousePos()
{
	return m_oldMousePos;
}

BOOL CEvent::WriteInfo()
{
	char		filename[MAX_PATH];
	FILE*		file = NULL;
	DescInfo	info;
	int			nb;

	strcpy(filename, "data\\info%.blp");
	AddUserPath(filename);

	file = fopen(filename, "wb");
	if (file == NULL) goto error;

	info.majRev = 1;
	info.prive = m_private;
	info.mission = m_mission;
	info.multi = m_multi;
	info.lives = m_lives;
	info.speed = m_speed;
	info.bMovie = m_bMovie;
	info.bHiliInfoButton = m_bHiliInfoButton;
	info.bAccessBuild = m_bAccessBuild;

	info.skill = m_pDecor->GetMissionsCleared();

	info.audioVolume = m_pSound->GetAudioVolume();
	info.midiVolume = m_pSound->GetMidiVolume();

	nb = fwrite(&info, sizeof(DescInfo), 1, file);
	if (nb < 1) goto error;

	fclose(file);
	return TRUE;

error:
	if (file != NULL) fclose(file);
	return FALSE;
}

BOOL CEvent::ReadInfo()
{
	char	filename[MAX_PATH];
	FILE* file = NULL;
	DescInfo info;
	int		 nb;

	strcpy(filename, "data\\info%.3d.blp");
	AddUserPath(filename);

	file = fopen(filename, "rb");
	if (file == NULL) goto error;
	
	nb = fread(&info, sizeof(DescInfo), 1, file);
	if (nb < 1) goto error;


	info.majRev = 1;
	info.prive = m_private;
	info.mission = m_mission;
	info.multi = m_multi;
	info.lives = m_lives;
	info.speed = m_speed;
	info.bMovie = m_bMovie;
	info.bHiliInfoButton = m_bHiliInfoButton;
	info.bAccessBuild = m_bAccessBuild;

	m_pDecor->SetSkill(info.skill);

	m_pSound->SetAudioVolume(info.audioVolume);
	m_pSound->SetMidiVolume(info.midiVolume);

	fclose(file);
	return TRUE;

error:
	if (file != NULL) fclose(file);
	return FALSE;
}

BOOL CEvent::ReadPlayer()
{
	char filename[MAX_PATH];

	m_playerIndex = 0;

	strcpy(filename, "data\\info%.3d.blp");
	AddUserPath(filename);
}
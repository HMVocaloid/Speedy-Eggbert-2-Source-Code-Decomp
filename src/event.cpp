// Event.cpp
//

#pragma once

using namespace std;

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <ddraw.h>
#include <direct.h>
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

#pragma warning (disable : 4996)
#pragma warning (disable : 4700)

#define DEF_TIME_HELP  10000
#define DEF_TIME_DEMO  1000
#define MAXDEMO        2000
#define MAXINDEX	   20


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
		"init.blp",
		FALSE,
		{
			{
				0
			},
		},
	},

	{
		WM_PHASE_INIT,
		"init.blp",
		FALSE,
		{
			{
				WM_PHASE_DEMO,
				0, {1,48},
				86, 410,
				{1,TX_BUTTON_DEMO},
			},
			{
				WM_PHASE_BYE,
//?				WM_CLOSE,
				0, {1,84},
				128, 410,
				{1,TX_BUTTON_QUITTER},
			},
			{
				WM_PHASE_SCHOOL,
				0, {1,6},
				21, 410,
				{1,TX_BUTTON_APPRENDRE},
			},
			{
				0
			},
		},
	},

	{
		WM_PHASE_GAMER,
		"gamer.blp",
		FALSE,
		{
			{
				WM_BUTTON1,
				0, {0,0},
				60, 58,
				{1,TX_CHOOSEPLAYER},
			},
			{
				WM_BUTTON2,
				0, {0,0},
				60, 98,
				{1,TX_CHOOSEPLAYER},
			},
			{
				WM_BUTTON3,
				0, {0,0},
				60, 138,
				{1,TX_CHOOSEPLAYER},
			},
			{
				WM_BUTTON4,
				0, {0,0},
				60, 178,
				{1,TX_CHOOSEPLAYER},
			},
			{
				WM_BUTTON5,
				0, {0,0},
				60, 218,
				{1,TX_CHOOSEPLAYER},
			},
			{
				WM_BUTTON6,
				0, {0,0},
				60, 258,
				{1,TX_CHOOSEPLAYER},
			},
			{
				WM_BUTTON7,
				0, {0,0},
				60, 298,
				{1,TX_CHOOSEPLAYER},
			},
			{
				WM_BUTTON8,
				0, {0,0},
				60, 338,
				{1,TX_CHOOSEPLAYER},
			},
			{
				WM_PHASE_NAMEg,
				0, {1,46},
				546, 178,
				{1,TX_PLAYERSNAME},
			},
			{
				WM_PHASE_CLEARg,
				0, {1,36},
				546, 220,
				{1, TX_CLEARPLAYER},
			},
			{
				WM_PHASE_DOPLAY,
				0, {1, 48},
				65, 414,
				{1,	TX_SINGLEPLAYER},
			},
			{
				WM_PHASE_SERVICE,
				0, {1, 83},
				107, 414,
				{1, TX_MUTLIPLAYER},
			},
			{
				WM_PHASE_PRIVATE,
				0, {1, 49},
				149, 414,
				{1, TX_DESIGN},
			},
			{
				WM_PHASE_GREAD,
				0, {1, 52},
				191, 414,
				{1, TX_OPEN},
			},
			{
				WM_PHASE_SETUP,
				0, {1, 47},
				330, 414,
				{1, TX_SETTINGS},
			},
			{
				WM_PHASE_INIT,
				0, {1, 40},
				540, 414,
				{1, TX_BUTTON_TERM},
			},
			{
				0
			},
		},
	},

	{
		WM_PHASE_NAMEg,
		"name.blp",
		FALSE,
		{
			{
				WM_PHASE_CONFIRM,
				0, {1,18},
				222, 326,
				{1, TX_CONFIRM},
			},
			{
				WM_PHASE_GAMER,
				0, {1,36},
				378, 326,
				{1, TX_CANCEL},
			},
			{
				0
			},
		},
	},

	{
		WM_PHASE_CLEARg,
		"clear.blp",
		FALSE,
		{
			{
				WM_PHASE_YES,
				0, {1,18},
				222, 326,
				{1,TX_YES},
			},
			{
				WM_PHASE_GAMER,
				0, {1,36},
				378, 326,
				{1,TX_NO},
			},
			{
				0
			},
		},
	},
	
	{
		WM_PHASE_SERVICE,
		"service.blp",
		FALSE,
		{
			{
				WM_BUTTON1,
				0, {1,51},
				140, 110,
				0,
			},
			{
				WM_BUTTON2,
				0, {1,51},
				140, 150,
				0,
			},
			{
				WM_BUTTON3,
				0, {1,51},
				140, 190,
				0,
			},
			{
				WM_BUTTON4,
				0, {1,51},
				140, 230,
				0,
			},
			{
				WM_BUTTON5,
				0, {1,51},
				140, 270,
				0,
			},
			{
				WM_BUTTON6,
				0, {1, 51},
				140, 310,
				0,
			},
			{
				WM_BUTTON10,
				0, {1, 72},
				466, 110,
				{1, TX_SHOWCONNECTION},
			},
			{
				WM_BUTTON11,
				0, {1, 73},
				466, 310,
				{1, TX_SHOWNEXT},
			},
			{
				WM_PHASE_DPLAY_DO_SERVICE,
				0, {1, 18},
				222, 389,
				{1, TX_CONFIRM},
			},
			{
				WM_PHASE_DPLAY_CANCEL_SERVICE,
				0, {1, 36},
				380, 389,
				{1, TX_CANCEL},
			},
			{
				0
			},
		},
	},

	{
		WM_PHASE_SESSION,
		"session.blp",
		FALSE,
		{
			{
				WM_BUTTON1,
				0, {1,51},
				120, 100,
				0,
			},
			{
				WM_BUTTON2,
				0, {1,51},
				120, 150,
				0,
			},
			{
				WM_BUTTON3,
				0, {1,51},
				120, 190,
				0,
			},
			{
				WM_BUTTON4,
				0, {1,51},
				120, 230,
				0,
			},
			{
				WM_BUTTON5,
				0, {1,51},
				120, 270,
				0,
			},
			{
				WM_BUTTON6,
				0, {1,51},
				120, 310,
				0,
			},
			{
				WM_BUTTON7,
				0, {1,72},
				490, 330,
				{1,TX_SHOWPREV},
			},
			{
				WM_BUTTON8,
				0, {1,73},
				490, 310,
				{1,TX_SHOWNEXT},
			},
			{
				WM_PHASE_JOINGAME,
				0, {1,45},
				120, 389,
				{1,TX_GAMEJOIN},
			},
			{
				WM_PHASE_DPLAY_CREATE_LOBBY,
				0, {1, 43},
				162, 389,
				{1, TX_CREATE_MULTIGAME},
			},
			{
				WM_PHASE_DPLAY_REFRESH,
				0, {1, 72},
				260, 389,
				{1, TX_UPDATELIST},
			},
			{
				WM_PHASE_DPLAY_CANCEL_SESSION,
				0, {1, 36},
				485, 389,
				{1, TX_CANCEL},
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
				WM_PHASE_INFO,
				0, {1,40},
				11+42*0, 424,
				{1,TX_BUTTON_TERMC},
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
	int* menuIndex;


	CMenu(m_menu);

	m_somethingJoystick = 0;
    m_bFullScreen   = TRUE;
	m_mouseType     = MOUSETYPEGRA;
	m_saveIndex		= -1;
	m_index         = -1;
	m_exercice      = 0;
	m_mission       = 1;
	m_private       = 1;
	m_maxMission    = 0;
	m_phase         = 0;
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
	m_bAllMissions  = FALSE;
	m_bHiliInfoButton = TRUE;
	m_bSpeed        = FALSE;
	m_bHelp         = FALSE;
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

	for (i = 0; i < MAXINDEX; i++)
	{
		m_menuIndex = 0;
	}

	m_menuDecor[10] = 1;

	return;
}

// Destructor

CEvent::~CEvent()
{
	char filename[260];

    WriteInfo(m_gamer, filename); // Read the file "info.blp"
	OutputDebug(filename);

	return;
}

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
	m_gamer = 1;

    ReadInfo(1);
	return;
}

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



// Returns the index of the button.



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

    return FALSE;
}

void CEvent::SetEnable(WMessage button, int bEnable)
{
    int      index;

    index = GetButtonIndex(button);
    if ( index < 0 ) return;

    m_buttons[index].SetEnable(bEnable);
}

/*
BOOL CEvent::GetHide(int button)
{
	int		index;

	index = GetButtonIndex(button);
	if (index < 0)  return 0;

	return m_buttons[index].GetHide();
}
*/

void CEvent::SetHide(int button, BOOL bHide)
{
	int index;

	index = GetButtonIndex(button);
	if (index < 0) return;

	m_buttons[index].SetHide(bHide);
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

	if (m_phase == WM_PHASE_PLAY || m_phase == WM_PHASE_PLAYTEST)
	{
		HideMouse(FALSE);
		WaitMouse(TRUE);
		WaitMouse(FALSE);
		return;
	}
	FillMouse(TRUE);
	return;
    
}

void CEvent::FlushInput()
{
	m_input = 0;
	
	m_pDecor->SetInput(0);
	return;

}

BOOL CEvent::CreateButtons()
{
	int		i = 0, message, num = 0, size;
	int		num3 = 0; 
	int*	iconMenu;
	POINT	pos, toolTips;
	BOOL	bMinimizeRedraw = FALSE;
	CButton* button;

	size = m_phase * sizeof(Phase);
	button = m_buttons;

	
	if (table[m_index].buttons[0].message != 0)
	{

		while (table[m_index].buttons[1].iconMenu + -8 != 0)
		{
			pos.x = table[m_index].buttons[i].x;
			pos.y = table[m_index].buttons[i].y;

			message = table[m_index].buttons[i].message;

			m_buttons[i].Create(m_hWnd, m_pPixmap, m_pSound, pos,
				table[m_index].buttons[i].type,
				table[m_index].buttons[i].iconMenu + size,
				table[m_index].buttons[i].iconMenu[0],
				table[m_index].buttons[i].toolTips + size,
				table[m_index].buttons[i].toolTips[0],
				bMinimizeRedraw, m_pDecor->GetRegion(), message);

			iconMenu = table[m_index].buttons[i].iconMenu + (m_phase * sizeof(Phase));
			if (((m_bAccessBuild == FALSE) && (m_phase == WM_PHASE_BUILD)) && (message == 1054))
			{
				iconMenu++;
			}
			m_buttons->SetSomethingMenu(table[m_index].buttons[i].iconMenu + i + 4, *(int*)iconMenu);
			m_buttons->MenuToolTips(table[m_index].buttons[i].toolTips + i + 4, *(int*)table[m_index].buttons[i].toolTips + i);
		}

	}
	return TRUE;
}

void CEvent::ReadInput()
{
	BOOL something;
	MMRESULT joyPos;
	int  i;
	UINT keyInput;
	JOYINFOEX* joyInfo;
	BOOL bSkateboard;
	BOOL bHelicopter;
	BOOL bCar;
	BOOL bWater;
	JOYINFOEX joy;
	UINT bJoyID;


	if (m_bMulti != FALSE)
	{
		//m_pDecor->TreatNetData();
	}
	
	if ((m_somethingJoystick == NULL) || (m_bDemoPlay != FALSE)) 
	{
		m_pDecor->SetJoystickEnable(FALSE);
	}
	else
	{
		m_pDecor->GetBlupiInfo(bHelicopter, bCar, bSkateboard, bWater);
		something = TRUE;

		if (((bHelicopter != FALSE) || (bCar != FALSE)) || (bSkateboard != FALSE))
		{
			something = FALSE;
		}
		bJoyID = m_joyID;
		joyInfo = &joy;

		for (i != 0; i = 13; i++)
		{
			joyInfo->dwSize = 0;
			joyInfo = (JOYINFOEX*)&joyInfo->dwFlags;
		}
		joy.dwSize = 52;
		joy.dwFlags = 255;

		joyPos = joyGetPosEx(bJoyID, &joy);

		if (joyPos == 0)
		{
			m_input = 0;

			if ((int)joy.dwXpos < 16384)
			{
				m_input = KEY_LEFT;
			}
			if ((m_input == KEY_NONE) && ((int)joy.dwYpos < 16384))
			{
				m_input = KEY_UP;
			}
			if (((m_input == KEY_NONE) || (something)) && (49152 < (int)joy.dwYpos))
			{
				m_input = m_input | KEY_DOWN;
			}
			if (((BYTE)joy.dwButtons & JOY_BUTTON1) != 0)
			{
				m_input = m_input & ~(INPUT_DOWN | INPUT_UP) | KEY_JUMP;
			}
			if (((BYTE)joy.dwButtons & JOY_BUTTON2) != 0)
			{
				if (bSkateboard == FALSE)
				{
					keyInput = m_input & ~INPUT_DOWN | KEY_UP | KEY_JUMP;
				}
				else
				{
					keyInput = m_input & ~(INPUT_DOWN | INPUT_UP) | KEY_JUMP;
				}
				m_input = keyInput;
			}
			if (((BYTE)joy.dwButtons & JOY_BUTTON3) != 0)
			{
				if (bHelicopter == FALSE)
				{
					if (bSkateboard == FALSE)
					{
						keyInput = m_input | KEY_DOWN | KEY_JUMP;
					}
					else
					{
						keyInput = m_input & ~(INPUT_DOWN | INPUT_UP) | KEY_JUMP;
					}
				}
				else
				{
					keyInput = m_input | KEY_DOWN;
				}
				m_input = keyInput;
				m_input = keyInput & ~INPUT_UP;
			}
			if (((BYTE)joy.dwButtons & JOY_BUTTON4) != 0)
			{
				m_input = m_input & ~(INPUT_DOWN | INPUT_UP) | KEY_FIRE;
			}
			m_pDecor->SetInput(m_input);
			m_pDecor->SetJoystickEnable(TRUE);
			return;
		}
	}
	return;
}


// CNetwork function needs to be implemented 

void CEvent::NetSetPause(BOOL bPause, int players)
{
	BOOL bPause_;
	
	bPause_ = bPause;
	m_pDecor->SetPause(bPause);
	if ((m_phase == WM_PHASE_PLAY) || (m_phase == WM_PHASE_PLAYTEST))
	{
		if (bPause_ == FALSE)
		{
			m_pSound->RestartMusic();
		}
		else
		{
			m_pSound->SuspendMusic();
		}
	}
	if ((m_bMulti != FALSE) && (players != 0))
	{
		m_pNetwork->Send(&bPause, 3, DPSEND_GUARANTEED);
	}
	return;
}

void CEvent::NetSendLobby()
{
	NetPlayer* player;
	UCHAR (packet)[132];
	CNetwork* pNetwork;

	*(UCHAR*)packet = m_multi;
	pNetwork = m_pNetwork;
	packet[0] = 132;
	packet[1] = MESS_LOBBY;
	player = pNetwork->m_players;
	memcpy(packet, pNetwork, 128);
	pNetwork->Send(packet, 132, DPSEND_GUARANTEED);
	return;
}

int	CEvent::NetSearchPlayer(DPID dpid)
{
	int i;
	BYTE* pDpid;
	
	i = 0;
	for (pDpid = (BYTE*)m_pNetwork->m_players[0].dpid; !pDpid[-4] == 0 || (dpid != *pDpid); pDpid += 32)
	{
		if (i++ >= 4)
		{
			return -1;
		}
	}
	return i;
}

void CEvent::NetStartPlay()
{
	BOOL host;
	int i;
	int* player;
	char message[2];
	char str[52];
	CNetwork* pNetwork;

	OutputNetDebug("CEvent::NetStartPlay");
	host = m_pNetwork->IsHost();

	if (host != FALSE)
	{
		message[0] = '\x02';
		message[1] = '\a';
		m_pNetwork->Send(message, 2, DPSEND_GUARANTEED);
		OutputNetDebug("Sending_MESS_START");
	}
	m_pDecor->SetTeam(0);
	pNetwork = m_pNetwork;

	i = 0;
	player = (int*) & pNetwork->m_players[0].dpid;
	
	while ((((NetPlayer*)(player + -1))->bIsPresent == FALSE || (pNetwork->m_dpid != (DPID)player)))
	{
		i++;
		player = player + 8;
		if (3 < i)
		{
			m_bMulti = TRUE;
			m_bPrivate = FALSE;
			m_pDecor->SetMulti(TRUE);
			return;
		}
	}
	m_pDecor->SetTeam((int)pNetwork->m_players[i].team);
	sprintf(str, "color=%d", (int)m_pNetwork->m_players[i].team);
	OutputNetDebug(str);
}

void CEvent::NetSend(NetMessageType message, USHORT data)
{
	UCHAR packet[4];

	packet[2] = '\0';
	packet[3] = '\0';
	packet[1] = message;
	packet[0] = 4;
	*(USHORT*)packet = data;
	m_pNetwork->Send(packet, 4, DPSEND_GUARANTEED);
	return;
}

void CEvent::NetDraw()
{
	int player;

	player = NetSearchPlayer(m_pNetwork->m_dpid);
	//m_pDecor->DrawMap(TRUE, player);
	return;
}

void CEvent::ChatSend()
{
	int		netplay;
	UINT	i;
	char*	text;
	char	end[4];
	POINT*  pos;
	DPID	dpid;
	LPVOID	data[25];
	char	textInput[100];

	text = m_textInput;
	if (m_textInput[0] != '\0')
	{
		netplay = NetSearchPlayer(m_pNetwork->m_dpid);
		strcpy(textInput, "<");
	}
	if (netplay != -1)
	{
		strcat(textInput, (const char*)m_pNetwork->m_players[netplay].name);
		strcat(textInput, "> ");
		strcat(textInput, text);
		//ChatMessageSound((char*)textInput);
		end[0] = 108;
		end[1] = 11;
		dpid = m_pNetwork->m_dpid;
		m_pNetwork->Send(&end, 108, 1);
		text = 0;
		pos[132].x = 0;
		pos[132].y = strlen(text);
		pos[133].x = 0;
		m_textHiliEnd = i - 1;
		m_textCursorIndex = 0;
		SetEnable((WMessage)WM_BUTTON20, 0);
	}
	return;
}

/*
void CEvent::ChatMessageSound(char* data)
{
	int num;
	char (*chatZone);
	char(*chat)[5];
	POINT pos;

	num = 3;
	chatZone = m_chatZone[0];
	do
	{
		if (chatZone = '\0')
		{
			chat = m_chatZone + num * 20;
			goto error;
		}
		num++;
		chatZone = chatZone + 100;
	} while (num < 6);
	HandleChatBuffer();
	chat = (char(*) [5])m_text;
	return;

error:
	strcpy((char*)chat, data);
	pos.x = 320;
	pos.y = 240;
	m_pSound->PlayImage(11, pos, -1);
}
*/

void CEvent::HandleChatBuffer()
{
	char (*chatZone)[5];
	int num;
	int result;
	char* text;

	num = 5;
	chatZone = m_chatZone;
	do
	{
		result = strlen((const char*)chatZone + 100) + 1;
		text = (char*)chatZone;
		chatZone += 100;
		memcpy(text, chatZone, result);
		--num;
	} while (num);
	*((BYTE*)m_text) = 0;
	return;
}

void CEvent::OutputNetDebug(const char* str)
{
	char* stream;
	FILE* streamf;
	UINT  element;

	streamf = (FILE*)m_pDecor->GetNetDebug();

	if (m_pDecor->GetNetDebug() != FALSE)
	{
		if (fopen("debug.txt", "ab") != (FILE*)0)
		{
			fwrite(str, 1, strlen(str), streamf);
			streamf = (FILE*)fclose(streamf);
		}
	}
	return;
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
    int         world, time, lg, button, volume, pente, icon, sound;
	int			nice;
	BOOL		soundEnabled;
    char        res[100];
	char		textLeft[24];
    char        text[100];
	char		pText[100];
    POINT       pos;
    RECT        rect;
    BOOL        bEnable;
	int     	phase;

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
	m_pDecor->OutputNetDebug(text);

	phase = m_phase;

	if (((phase != WM_PHASE_PLAY) && (phase != WM_PHASE_PLAYTEST)) && (phase != WM_PHASE_BUILD))
	{
		rect.right = 302;
		rect.left = 2;
		rect.top = 2;
		rect.bottom = 14;
		pos.x = 2;
		pos.y = 2;
		m_pPixmap->DrawPart(-1, 0, pos, rect, 1, FALSE);
	}
	DrawTextLeft(m_pPixmap, pos, textLeft, 10);

	if (m_phase == WM_PHASE_INIT)
	{
		DrawTextB(m_pPixmap, pos, (char*)"Version 2.0", FONTLITTLE);
	}

	if (m_phase == WM_PHASE_GAMER)
	{
		LoadString(TX_CHOOSEGAMER, res, 100);
		lg = GetTextWidth(res, 0);
		pos.y = 26;
		pos.x = LXIMAGE / 2 - lg / 2;
		DrawTextLeft(m_pPixmap, pos, res, 1);
		*(char*)pText = m_gamerNameList[10][100];
		lg = 8;
		nice = 69;
		do
		{
			pos.y = 69;
			pos.x = 110;
			DrawTextB(m_pPixmap, pos, pText, 0);
			nice = 69 + 40;
			*(char*)pText += 100;
			lg++;
		} while (lg != 0);
		SetEnable((WMessage)WM_PHASE_CLEARg, (int)(m_filenameBuffer + -1) + m_gamer * 4 + 212);
	}

	if (m_phase == WM_PHASE_PLAY && m_phase == WM_PHASE_PLAYTEST && m_phase == WM_PHASE_BUILD)
		m_pPixmap->DrawPart(-1, 0, pos, rect, 1, 0);
	if (m_phase == WM_PHASE_CREATE)
	{
		LoadString(TX_MULTI_CREATE, res, 50);
		lg=GetTextWidth(res);
		pos.x = (320 - lg) / 2;
		pos.y = 103;
		DrawTextLeft(m_pPixmap, pos, res, FONTSLIM);
		LoadString(TX_MULTI_GNAME, res, 100);
		pos.x = (320 - lg) / 2;
		pos.y = 190;
		DrawTextLeft(m_pPixmap, pos, res, FONTSLIM);
	}
	if (m_phase == WM_PHASE_SETUP || m_phase == WM_PHASE_SETUPp)
	{
		sound = m_pSound->GetAudioVolume();
		soundEnabled = TRUE;
		if ((sound == 0) || (m_pSound->GetEnable()) == FALSE)
		{
			soundEnabled = FALSE;
		}
	}
	if (m_phase == WM_PHASE_PLAY || m_phase == WM_PHASE_PLAYTEST)
	{
		if (m_pDecor->GetPause() == 0)
		{
			if (m_bDemoRec != 0)
			{
				LoadString(TX_DEMOREC, res, 100);
				DrawTextLeft(m_pPixmap, pos, res, FONTRED);
			}
			if (m_bDemoPlay != 0)
			{
				LoadString(TX_DEMOPLAY, res, 100);
				DrawTextLeft(m_pPixmap, pos, res, FONTRED);
			}
		}
		else
		{
			if (m_pDecor->GetTime() % 20 < 15)
			{
				DrawTextCenter(TX_PAUSE, 320, 240, 0);
			}
		}
		if (m_speed > 1)
		{
			sprintf(res, "x%d", m_speed);
			DrawTextLeft(m_pPixmap, pos, res, FONTWHITE);
		}
	}
	if (m_phase == WM_PHASE_STOP)
	{
		LoadString(TX_GAMEPAUSE, res, 100);
		lg = GetTextWidth(res);
		pos.x = (319 - lg) / 2;
		pos.y = 103;
		DrawTextLeft(m_pPixmap, pos, res, FONTRED);
	}
	if (m_phase == WM_PHASE_MUSIC)
	{
		LoadString(TX_MUSIC, res, 100);
		lg=GetTextWidth(res);
		pos.x = (320 - lg) / 2;
		pos.y = 84;
		DrawTextLeft(m_pPixmap, pos, res, FONTRED);
	}
	if (m_phase == WM_PHASE_REGION)
	{
		LoadString(TX_REGION, res, 100);
		lg = GetTextWidth(res);
		pos.x = (320 - lg) / 2;
		pos.y = 26;
		DrawTextLeft(m_pPixmap, pos, res, FONTRED);
	}
	if (m_phase == WM_PHASE_LOST || m_phase == WM_PHASE_LOSTd || m_phase == WM_PHASE_WINm)
	{
		LoadString(TX_LOST1 + GetWorld() % 5, res, 50);
		DrawTextLeft(m_pPixmap, pos, res, FONTWHITE);
	}
	if (m_phase == WM_PHASE_WIN || m_phase == WM_PHASE_WINd || m_phase == WM_PHASE_LOSTm)
	{
		LoadString(TX_WIN1 + GetWorld() % 5, res, 50);
		DrawTextLeft(m_pPixmap, pos, res, FONTWHITE);
	}
	if (m_phase == WM_PHASE_READd)
	{

	}
	if (m_phase == WM_PHASE_GREAD || m_phase == WM_PHASE_GREADp || m_phase == WM_PHASE_GWRITE)
	{
		if (m_phase == WM_PHASE_GREAD)
		{
			LoadString(TX_SAVE_CGAME, res, 50);
		}
		else
		{
			LoadString(TX_LOAD_CGAME, res, 50);
		}
	}
	if (m_phase == WM_PHASE_BYE)
	{
		LoadString(TX_FULL_END1, res, 100);
		lg = GetTextWidth(res);
		pos.x = (320 - lg) / 2;
		pos.y = 20;
		DrawTextLeft(m_pPixmap, pos, res, FONTRED);
		LoadString(TX_FULL_END2, res, 100);
		lg = GetTextWidth(res);
		pos.x = (320 - lg) / 2;
		pos.y = 40;
		DrawTextLeft(m_pPixmap, pos, res, FONTRED);
		LoadString(TX_FULL_END3, res, 100);
		lg = GetTextWidth(res);
		pos.x = (320 - lg) / 2;
		pos.y = 430;
		DrawTextLeft(m_pPixmap, pos, res, FONTRED);
		LoadString(TX_FULL_END4, res, 100);
		lg = GetTextWidth(res);
		pos.x = (320 - lg) / 2;
		pos.y = 450;
		DrawTextLeft(m_pPixmap, pos, res, FONTRED);
	}
	if (m_phase == WM_PHASE_INSERT)
	{
		DrawTextCenter(TX_INSERT, LXIMAGE / 2, 20);
	}
	if (m_textToolTips[0] != '\0')
	{
		DrawTextLeft(m_pPixmap, m_posToolTips, m_textToolTips, FONTWHITE);
	}
	if (m_phase == WM_PHASE_CLEARg)
	{
		LoadString(TX_CHOOSEGAMER, res, 100);
		lg = GetTextWidth((char*)res, 0);
		pos.y = 102;
		pos.x = 320 - lg / 2;
		DrawTextLeft(m_pPixmap, pos, (char*)res, 1);
		LoadString(TX_DISCARDGAME, res, 100);
		lg = GetTextWidth(res, 0);
		strcpy(text, (const char*)m_gamerName);
		strcat(text, "?");
		lg = GetTextWidth(text, 0);
		DrawTextLeft(m_pPixmap, pos, res, 0);
	}
	if (m_phase == WM_PHASE_CLEARd)
	{
		LoadString(TX_DESIGNMISSION, res, 100);
		lg = GetTextWidth(res, 0);
		pos.y = 104;
		pos.x = 320 - lg / 2;
		DrawTextLeft(m_pPixmap, pos, res, 1);
		LoadString(TX_DELETEMISSION, res, 100);
		GetWorld();
		sprintf(text, res);
		lg = GetTextWidth(text, 0);
		pos.y = 210;
		pos.x = 320 - lg / 2;
		DrawTextLeft(m_pPixmap, pos, text, 0);
		strcpy(text, (char*)m_pDecor->GetMissionTitle());
		
		if (text[0] == '\0')
		{
			LoadString(TX_NONAME, res, 100);
		}
		strcat(text, "?");
		lg = GetTextWidth(text, 0);
		pos.y = 230;
		pos.x = 320 - lg / 2;
		DrawTextLeft(m_pPixmap, pos, res, 0);
	}
	if (m_phase == WM_PHASE_INFO)
	{
		LoadString(TX_DESIGNMISSION, res, 100);
		lg = GetTextWidth(res, 0);
		pos.y = 37;
		pos.x = 320 - lg / 2;
		DrawTextLeft(m_pPixmap, pos, res, 0);
		// Unknown Field
		// DrawIcon
		// End of if function
		LoadString(TX_MISSIONNUM, res, 100);
		sprintf(text, res);
		lg = GetTextWidth(text, 0);
		pos.y = 106;
		pos.x = 250 - lg / 2;
		DrawTextLeft(m_pPixmap, pos, text, 1);
		strcpy(text, (char*)m_pDecor->GetMissionTitle());
		if (res[0] == '\0')
		{
			LoadString(TX_NONAME, res, 100);
		}
		lg = GetTextWidth(res, 0);
		pos.y = 269;
		pos.x = 250 - lg / 2;
		DrawTextLeft(m_pPixmap, pos, res, 0);
	}
	
	return TRUE;
}

void CEvent::PutTextInputBox(POINT pos)
{
	char textInput[100];
	char* textConst;
	int	 text;
	CPixmap* pPixmap;
	int  num;
	UINT textHili;
	LONG posD;

	text = GetTextWidth(m_textInput, 0);
	posD = pos.x - text / 2;
	textHili = m_textHiliStart;

	if (0 < (int)textHili)
	{
		memcpy(textInput, textConst, textHili);
		pPixmap = m_pPixmap;
		textInput[textHili] = 0;
		DrawTextLeft(pPixmap, pos, textInput, 0);
		text += GetTextWidth(textInput, 0);
	}
	if (m_textHiliStart < m_textHiliEnd)
	{
		textHili = m_textHiliEnd - m_textHiliStart;
		memcpy(textInput, m_textInput + m_textHiliStart, text);
		pPixmap = m_pPixmap;
		textInput[textHili] = 0;
		DrawTextLeft(pPixmap, pos, textInput, 2);
		text += GetTextWidth(textInput, 0);
	}
	if (m_textCursorIndex % 16 < 8)
	{
		pPixmap = m_pPixmap;
		DrawTextLeft(pPixmap, pos, (char*)"|", 0);
	}
	num = m_textCursorIndex;

	if (num < (int)strlen((const char*)m_textInput))
	{
		pPixmap = m_pPixmap;
		strcpy(textInput, num + m_textInput);
		DrawTextLeft(pPixmap, pos, textInput, 0);
	}
	m_textCursorIndex = m_textCursorIndex + 1;
	return;
}

/*
BOOL CEvent::TextSomething()
{
	int textHiliStart;
	char pText;

	m_textHiliStart = textHiliStart;

	if (m_textHiliEnd < textHiliStart)
	{
		return 0;
	}

	do {
		m_textInput[textHiliStart] =
			m_textHiliEnd + textHiliStart;
		pText = m_textInput + textHiliStart;
		textHiliStart = textHiliStart + 1;
	} while (pText != '\0');
	m_textHiliEnd = m_textHiliStart;
	return 1;
}
*/

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

BOOL CEvent::TreatEventBase(UINT message, WPARAM wParam, LPARAM lParam)
{
	POINT	pos;
	int		fwKeys;
	int		i, sound;
	char	c;
	BOOL	bEnable;

	pos = ConvLongToPos(lParam);
	fwKeys = wParam;

	switch (message)
	{
	case WM_KEYDOWN:
		if (wParam >= 'A' && wParam <= 'Z')
		{
			if (m_posCheat == 0)
			{
				m_rankCheat = -1;
				
				for (i = 0; i < 9; i++)
				{
					if ((char)wParam == cheat_code[i][0])
					{
						m_rankCheat = i;
						break;
					}
				}
			}
			if (m_rankCheat != -1)
			{
				c = cheat_code[m_rankCheat][m_posCheat];
				if (m_posCheat != 0 && m_rankCheat == 0) c++;
				if ((char)wParam == c)
				{
					m_posCheat++;

				}
			}

			if (m_phase != WM_PHASE_PLAY)
			{
				ChangePhase(m_phase);
			}
			if (bEnable)
			{
				pos.x = 320;
				pos.y = LYIMAGE / 2;
				m_pSound->PlayImage(SOUND_3_JUMPEND, pos, -1);
			}
			else
			{
				pos.x = 320;
				pos.y = LYIMAGE / 2;
				m_pSound->PlayImage(SOUND_41_RESSORT, pos, -1);
			}
			m_rankCheat = -1;
			m_posCheat = 1;
		}
		return TRUE;

		if (m_phase == WM_PHASE_INIT)
		{
			ChangePhase(WM_PHASE_INIT);
			return TRUE;
		}

		if (m_phase == WM_PHASE_BYE)
		{
			PostMessageA(m_hWnd, WM_CLOSE, 0, 0);
		}

		switch (wParam)
		{
			case VK_END:
				DemoRecStop();
				return TRUE;
			case VK_ESCAPE:
				if (m_bRunMovie)
				{
					StopMovie();
					m_pSound->SetSuspendSkip(1);
					return TRUE;
				}
				if (m_phase != WM_PHASE_PLAYTEST)
				{
					if (m_phase != WM_PHASE_SETUP)
					{
						if (m_phase != WM_PHASE_NAMEg)
						{
							if (m_phase == WM_PHASE_NAMEd)
							{
								m_pDecor->SetGamerName(m_textInput);
								ChangePhase(WM_PHASE_INFO);
								return TRUE;
							}
							if ((m_phase == WM_PHASE_INIT) || (m_phase == WM_PHASE_WINm)) ChangePhase(WM_PHASE_GAMER); return TRUE;
							if ((m_phase == WM_PHASE_BUILD) || ((m_phase == WM_PHASE_LOSTd || m_phase == WM_PHASE_LOST))) ChangePhase(WM_PHASE_INFO); return TRUE;
							if (((m_phase != WM_PHASE_INFO) && (m_phase != WM_PHASE_STOP)) && (m_phase != WM_PHASE_HELP))
							{
								if (m_phase == WM_PHASE_SERVICE)
								{
									ChangePhase(WM_PHASE_DPLAY_DO_SERVICE);
									return TRUE;
								}
								if (m_phase == WM_PHASE_CREATE)
								{
									ChangePhase(WM_PHASE_DPLAY_CREATE);
									return TRUE;
								}
								if (m_phase == WM_PHASE_MULTI)
								{
									ChatSend();
									return TRUE;
								}
								if (((m_phase != WM_PHASE_GREAD) && (m_phase != WM_PHASE_GREADp)) || ((m_fileIndex < 0 || LoadState(m_fileIndex) == FALSE)))
								{
									if (m_phase != WM_PHASE_GWRITE) return TRUE;
						
									if (m_fileIndex < 0) return TRUE;
			
									if (SaveState(m_fileIndex) == FALSE) return TRUE;
								}
							}
						}
					}
					strcpy(m_gamerName, m_textInput);
				}
		}

	}

	if (m_phase != WM_PHASE_PLAY && m_phase != WM_PHASE_PLAYTEST)
	{
		return 0;
	}
	// Unknown Function

	switch (wParam)
	{
	case WM_RBUTTONDOWN:
		m_bMouseDown = TRUE;
		MouseSprite(pos);
		if (EventButtons(message, wParam, lParam)) return TRUE;
		if (m_phase == WM_PHASE_BUILD)
		{
			if (BuildDown(pos, fwKeys)) return TRUE;
		}
		if (m_phase == WM_PHASE_PLAY)
		{
		//	if (PlayDown(pos, fwKeys)) return TRUE;
		}
		break;
	}

	return FALSE;
}

BOOL CEvent::LoadState(BOOL save)
{
	BOOL saveNum;
	CEvent* pEvent;

	saveNum = save;

	if (m_pDecor->Read(m_gamer, save, (BOOL*)&pEvent, &save) == FALSE)
	{
		return FALSE;
	}
	m_bPrivate = save;
	SetMission((int)pEvent);
	m_saveIndex = saveNum;
	return TRUE;
}

int CEvent::MousePosToSprite(POINT pos)
{
	int sprite;

	sprite = SPRITE_POINTER;

	if (m_phase == WM_PHASE_PLAY ||
		m_phase == WM_PHASE_PLAYTEST ||
		m_phase == WM_PHASE_BUILD ||
		m_phase == WM_PHASE_BYE ||
		!MouseOnButton(pos))
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
		m_mouseSprite = SPRITE_EMPTY;
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
	UINT uid;

	m_textToolTips[0] = 0;
	oldx = m_posToolTips.x;
	m_posToolTips.x = -1;
	if (m_phase != WM_PHASE_PLAY && m_phase != WM_PHASE_PLAYTEST)
	{
		for (i = 0; i < 2; i++)
		{
			if (!m_jauges[i].GetHide())
			{

				uid = 0xFFFFFFF;

				if (uid < 0)
				{
					LoadString(TX_NOTINDEMO + i, m_textToolTips, 50);
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
				m_jauges[i].Redraw();
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
	//m_mission = mission;
	if (m_bPrivate) return m_bPrivate;
	if (m_bMulti)	return m_multi+200;
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

int CEvent::GetWorldGroup()
{
	int mission;
	m_mission = mission;
	
	if (m_mission % 10 != 0 && m_mission != 99)
	{
		m_mission = (mission / 10) * 10;
		return -(m_mission >> 31);
	}
	m_mission = 1;
	return m_mission / 10;
}

void CEvent::SetMission(int index)
{
	if (m_bPrivate != 0)
	{
		m_private = index;
		return;
	}
	if (m_bMulti != 0)
	{
		m_multi = index;
		return;
	}
	m_mission = index;
	return;
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

void CEvent::ReadAll()
{
	BOOL mission;
	BOOL read;
	BOOL bUser;
	BOOL bPrivate;
	BOOL bMission;

	if ((-1 < m_fileIndex) && (*(int*)((int)(m_filenameBuffer + -1) + m_fileIndex * 4 + 216) != 0))
	{
		//mission = m_pDecor->MissionStart(m_gamer, 999, bUser);
		
		if (mission != FALSE)
		{
			read = m_pDecor->Read(m_gamer, m_fileIndex, &bMission, &bPrivate);
			
			if (read != FALSE)
			{
				//m_pDecor->DrawMap(FALSE, -1);
			}
			m_pDecor->Read(m_gamer, 999, &bMission, &bPrivate);
		}
	}
	return;
}

BOOL CEvent::SaveState(int rank)
{
	BOOL bMission;
	BOOL bUser;
	char str[100];

	//bMission = m_pDecor->MissionStart(m_gamer, rank, bUser);

	if (bMission == FALSE)
	{
		return FALSE;
	}
	LoadString(TX_GAMESAVED, str, 100);
	m_pDecor->NotifPush(str);
	// m_field959_0x6d10 = rank;
	return TRUE;
}

void CEvent::SomethingUserMissions(char* lpFilename, LPCSTR fileSomething)
{
	UINT buffer;
	char* folderName;

	mkdir("\\User");
	strcpy(lpFilename, "\\User\\");
	strcat(lpFilename, fileSomething);

	if ((folderName = strstr(folderName, ".xch")) || ((buffer = 0, folderName - lpFilename != strlen(lpFilename) - 4)))
	{
		buffer = 0;
		strcat(lpFilename, ".xch");
	}
	return;
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
	char* playerName;

	sprintf(filename, "CEvent::ChangePhase [Begin] --- % ", phase);
	OutputNetDebug(filename);
	if (phase == WM_PHASE_634)
	{
	    PostMessageA(m_hWnd, 16, 0, 0);
		return TRUE;
	}
	m_pDecor->SetSpeedY(m_bDemoPlay);
	if (m_mouseType == MOUSETYPEGRA && m_bFullScreen != 0)
	{
		ShowCursor(FALSE);
		m_bShowMouse = FALSE;
	}
	if (phase == WM_PHASE_608)
	{
		//m_pDecor->CurrentRead(999, 1, m_gamer);
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
	m_bInfoHelp = FALSE;


	if (phase == WM_PHASE_INIT)
	{
		m_demoTime = 0;
	}
	if (phase == WM_PHASE_PLAY)
	{
		if (((m_bDemoPlay == FALSE) && (mission = GetWorld(), 299 < mission)) && (mission = GetWorld(), mission < LXIMAGE / 2))
		{
		DemoRecStart();
		}
	}
	else
	{
		DemoRecStop();
	}

	if (phase == WM_PHASE_DOQUIT)
	{
		if (m_bPrivate == FALSE)
		{
			mission = m_mission;
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
				SetMission(m_mission);
				m_phase = (WMessage)WM_PHASE_PLAY;
				
				return ChangePhase(WM_PHASE_PLAY);
			}
			return ChangePhase(WM_PHASE_GAMER);
		}
	}
	else if (m_bMulti == 0)
	{
		return ChangePhase(WM_PHASE_INFO);
	}

	CreateButtons();

	if (SearchPhase(phase) < 0)
	{
		return 0;
	}
	m_pPixmap->MouseInvalidate();
	HideMouse(FALSE);
	WaitMouse(TRUE);

	if (phase == WM_PHASE_GAMER || phase == WM_PHASE_PLAY)
	{
		OutputNetDebug("CEvent::ChangePhase_[WriteInfo]\r\n");
		WriteInfo(m_gamer, playerName);
	}

}

UINT CEvent::GetPhase()
{
	return m_phase;
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

BOOL CEvent::BuildDown(POINT pos, int fwKeys, BOOL bMix)
{
	POINT cel;
	int	  menu, channel, icon;
	
	if (pos.x < POSDRAWX || pos.x > POSDRAWX + DIMDRAWX ||
		pos.y < POSDRAWY || pos.y > POSDRAWY + DIMDRAWY) return FALSE;

	if (GetState(WM_DECOR1) == 1)
	{
		//cel = m_pDecor->ConvPosToCel2(pos);
		//m_pDecor->BlupiDelete(pos);
	}
	if (GetState(WM_DECOR2) == 2)
	{
		//cel = m_pDecor->ConvPosToCel2(pos);
		menu = GetMenu(WM_DECOR2);
	}
}

BOOL CEvent::BuildMove(POINT pos, int fwKeys)
{
	if (fwKeys & MK_LBUTTON)
	{
		BuildDown(pos, fwKeys, FALSE);
	}
	//m_pDecor->ConvPosToCel2(pos);
	return TRUE;
}

void CEvent::MouseRelease()
{
	m_bMouseRelease = TRUE;
	ShowCursor(TRUE);
	return;
}

void CEvent::MouseCapture()
{
	m_bMouseRelease = FALSE;
	ShowCursor(FALSE);
	return;
}

BOOL CEvent::NetCreate(int session)
{
	BOOL created;

	MouseRelease();
	created = m_pNetwork->CreateProvider(session);
	MouseCapture();
	return created;
}

BOOL CEvent::NetEnumSessions()
{
	BOOL enumSess;

	MouseRelease();
	enumSess = m_pNetwork->EnumProviders();
	MouseCapture();
	return enumSess;
}

BOOL CEvent::BuildUp(POINT pos, int fwKeys)
{
	return TRUE;
}

/*
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

void CEvent::GetDoors(int doors)
{
	for (int i = 0; i < 200; i++)
	{
		doors[i] = (int)data[Gamer];
	}
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
*/



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

BOOL CEvent::ReadLibelle(int world, BOOL bSchool, BOOL bHelp)
{
	FILE* file = NULL;
	char* pBuffer = NULL;
	char* pText;
	char* pDest;
	char  indic;
	int	  nb, h1, h2;

	pBuffer = (char*)malloc(sizeof(char) * 2560);
	if (pBuffer == NULL) goto error;
	memset(pBuffer, 0, sizeof(char) * 2560);

	//file = fopen


error:
	if (pBuffer != NULL) free(pBuffer);
	if (file	!= NULL) fclose(file);
	return FALSE;
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
		DeleteFileA("data\\demo.3d.blp");
		file = fopen("data\\demo.3d.blp", "wb");
		if ( file != NULL )
		{
			memset(&header, 0, sizeof(DemoHeader));
			header.majRev 	= 1;
			header.minRev   = 0;
			header.bSchool  = m_bSchool;
			header.bPrivate = m_bPrivate;
			fwrite(&header, sizeof(DemoHeader), 1, file);
			fwrite(m_pDemoBuffer, sizeof(DemoEvent), m_demoIndex, file);
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
	int			nb, world, time, total, mission;

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
	//m_pDecor->SetSkill(header.skill);

	m_demoEnd = fread(m_pDemoBuffer, sizeof(DemoEvent), MAXDEMO, file);
	fclose(file);

	m_demoTime = 0;
	m_demoIndex = 0;
	m_bDemoPlay = TRUE;
	m_bDemoRec = FALSE;

	/*
	if (!m_pDecor->CurrentRead(m_gamer, mission, FALSE))
	{
		DemoPlayStop();
		return FALSE;
	}
	ChangePhase(WM_PHASE_PLAY);
	InitRandom();
	m_pDecor->SetTime(0);
	m_speed = 1;
	*/
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
	m_pDecor->SetInput(0);
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

BOOL CEvent::WriteInfo(int gamer, char* playername)
{
	char		filename[MAX_PATH];
	FILE*		file = NULL;
	DescInfo	info;
	int			nb;
	int			doors;
	BYTE		door[200];
	char		text[100];

	sprintf(filename, "data\\info%.3d.blp", gamer);
	AddUserPath(filename);
	file = fopen(filename, "wb");
	if (file == NULL) goto error;

	strcpy(text, (const char*)m_gamerName);

	info.majRev = 1;
	info.prive = m_private;
	info.mission = m_mission;
	info.multi = m_multi;
	info.lives = m_lives;
	info.speed = m_speed;
	info.bMovie = m_bMovie;
	info.bHiliInfoButton = m_bHiliInfoButton;
	info.bAccessBuild = m_bAccessBuild;

	m_pDecor->InitalizeDoors(door);

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

BOOL CEvent::ReadInfo(int gamer)
{
	char	 filename[MAX_PATH];
	FILE*	 file = NULL;
	DescInfo info;
	int		 nb;
	BYTE	 doors[200];
	char	 buffer[100];


	m_pDecor->InitGamer();
	m_lives = 3;
	m_mission = 1;
	m_private = 1;
	m_multi = 1;

	LoadString(TX_READINFO, buffer, 100);
	sprintf(m_gamerName, buffer, gamer);
	sprintf(filename, "data\\info%.3d.blp", gamer);
	AddUserPath(filename);


	file = fopen(filename, "rb");
	if (file == NULL) goto error;
	
	nb = fread(&info, sizeof(DescInfo), 1, file);
	if (nb < 1) goto error;

	if ((BYTE*)m_gamerName)
	{
		strcpy((char*)m_gamerName, buffer);
	}

	info.majRev = 1;
	info.prive = m_private;
	info.mission = m_mission;
	info.multi = m_multi;
	info.lives = m_lives;
	info.speed = m_speed;
	info.bMovie = m_bMovie;
	info.bHiliInfoButton = m_bHiliInfoButton;
	info.bAccessBuild = m_bAccessBuild;

	m_pDecor->SetAccessBuild(info.skill);

	m_pSound->SetAudioVolume(info.audioVolume);
	m_pSound->SetMidiVolume(info.midiVolume);
	m_pDecor->MemorizeDoors(doors);

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
	remove(filename);
	return TRUE;
}


// Def.h
//

#pragma once

#include <Windows.h>

#define _DEMO			FALSE	// TRUE=demo, FALSE=complet
#define _INTRO			FALSE	// TRUE si images d'introduction
#define _EGAMES			FALSE	// TRUE version pour eGames
#define _SE				FALSE	// TRUE eGames Special Edition


#define LXIMAGE			640		// dimensions de la fen�tre de jeu
#define LYIMAGE			480

#define POSDRAWX		144		// surface de dessin
#define POSDRAWY		15
#define DIMDRAWX		480
#define DIMDRAWY		450

#define POSMAPX			8		// surface pour la carte
#define POSMAPY			15
#define DIMMAPX			128
#define DIMMAPY			128

#define MAXCELX			200		// nb max de cellules d'un monde
#define MAXCELY			200

#define DIMCELX			60		// dimensions d'une cellule (d�cor)
#define DIMCELY			30

#define DIMOBJX			120		// dimensions d'un objet
#define DIMOBJY			120

#define DIMBLUPIX		60		// dimensions de blupi
#define DIMBLUPIY		60
#define SHIFTBLUPIY		5		// petit d�calage vers le haut

#define DIMEXPLOX		128
#define DIMEXPLOY		128

#define DIMBUTTONX		40		// dimensions d'un button
#define DIMBUTTONY		40

#define DIMJAUGEX		124		// dimensions de la jauge
#define DIMJAUGEY		22

#define POSSTATX		12		// statistiques
#define POSSTATY		220
#define DIMSTATX		60
#define DIMSTATY		30

#define DIMTEXTX		16		// dimensions max d'un caract�re
#define DIMTEXTY		16

#define DIMLITTLEX		16		// dimensions max d'un petit caract�re
#define DIMLITTLEY		12

#define CHBACK			0
#define CHFLOOR			1
#define CHOBJECT		1
#define CHBLUPI			2
#define CHDECOR			3
#define CHBUTTON		4
#define CHJAUGE			5
#define CHTEXT			6
#define CHEXPLO			9
#define CHELEMENT		10
#define CHBLUPI1		11
#define CHBLUPI2		12
#define CHBLUPI3		13
#define CHPAD			14
#define CHSPEEDYBLUPI   15
#define CHBLUPIYOUPIE   16
#define CHGEAR			17
#define CHLITTLE		18
#define CHBIGNUM		19

#define MAXMOVEOBJECT	200


// Directions :

#define DIRECT_E		(0*16)		// est
#define DIRECT_SE		(1*16)		// sud-est
#define DIRECT_S		(2*16)		// sud
#define DIRECT_SO		(3*16)		// sud-ouest
#define DIRECT_O		(4*16)		// ouest
#define DIRECT_NO		(5*16)		// nord-ouest
#define DIRECT_N		(6*16)		// nord
#define DIRECT_NE		(7*16)		// nord-est

//                  NO
//            O     |     N
//             \    |    / 
//               \  |  / 
//                 \|/
//        SO -------o------- NE
//                 /|\
//               /  |  \
//             /    |    \
//            S     |     E
//          (y)     SE    (x)


// Actions :

#define ACTION_STOP			1		// arr�t
#define ACTION_MARCH		2
#define ACTION_TURN			3
#define ACTION_JUMP			4
#define	ACTION_AIR			5
#define	ACTION_DOWN			6

// Sons :

#define SOUND_CLICK			0
#define SOUND_JUMP1			1
#define SOUND_JUMP2			2
#define	SOUND_JUMPEND		3
#define SOUND_JUMPTOC		4
#define SOUND_TURN			5
#define SOUND_VERTIGO		6
#define SOUND_DOWN			7
#define SOUND_FALL			8
#define SOUND_NEW			9
#define SOUND_BOUM			10
#define SOUND_TRESOR		11
#define SOUND_EGG			12
#define SOUND_ENDKO			13
#define SOUND_ENDOK			14
#define SOUND_HELICOSTART   15
#define SOUND_HELICOHIGH	16
#define SOUND_HELICOSTOP	17
#define SOUND_HELICOLOW		18
#define SOUND_LASTTRESOR    19
#define SOUND_UP			20
#define SOUND_LOOKUP		21
#define SOUND_JUMP0			22
#define SOUND_PLOUF			23
#define SOUND_BLUP			24
#define SOUND_SURF			25
#define SOUND_DROWN			26
#define SOUND_ERROR			27
#define SOUND_JEEPSTART		28
#define SOUND_JEEPHIGH		29
#define SOUND_JEEPSTOP		30
#define SOUND_JEEPLOW		31
#define SOUND_BYE			32
#define SOUND_DOOR			33
#define SOUND_SUSPENDTOC    34
#define SOUND_SUSPENDJUMP	35
#define SOUND_SINGE			36
#define SOUND_PATIENT		37



// Boutons (play) :

#define MAXBUTTON			40

#define BUTTON_GO			0
#define BUTTON_STOP			1
#define BUTTON_MANGE		2
#define BUTTON_CARRY		3
#define BUTTON_DEPOSE		4
#define BUTTON_ABAT			5
#define BUTTON_ROC			6
#define BUTTON_CULTIVE		7
#define BUTTON_BUILD1		8
#define BUTTON_BUILD2		9
#define BUTTON_BUILD3		10
#define BUTTON_BUILD4		11
#define BUTTON_BUILD5		12
#define BUTTON_BUILD6		13
#define BUTTON_MUR			14
#define BUTTON_PALIS		15
#define BUTTON_ABATn		16
#define BUTTON_ROCn			17
#define BUTTON_PONT			18
#define BUTTON_TOUR			19
#define BUTTON_BOIT			20
#define BUTTON_LABO			21
#define BUTTON_FLEUR		22
#define BUTTON_FLEURn		23
#define BUTTON_DYNAMITE		24
#define BUTTON_BATEAU		25
#define BUTTON_DJEEP		26
#define BUTTON_DRAPEAU		27
#define BUTTON_EXTRAIT		28
#define BUTTON_FABJEEP		29
#define BUTTON_FABMINE		30
#define BUTTON_FABDISC		31
#define BUTTON_REPEAT		32
#define BUTTON_DARMURE		33
#define BUTTON_FABARMURE	34


// Erreurs :

#define ERROR_MISC			1
#define ERROR_GROUND		2
#define ERROR_FREE			3
#define ERROR_PONTOP		4
#define ERROR_PONTTERM		5
#define ERROR_TOURISOL		6
#define ERROR_TOUREAU		7
#define ERROR_TELE2			8


// Lutins pour la souris

#define SPRITE_ARROW		1
#define SPRITE_POINTER		2
#define SPRITE_MAP			3
#define SPRITE_ARROWU		4
#define SPRITE_ARROWD		5
#define SPRITE_ARROWL		6
#define SPRITE_ARROWR		7
#define SPRITE_ARROWUL		8
#define SPRITE_ARROWUR		9
#define SPRITE_ARROWDL		10
#define SPRITE_ARROWDR		11
#define SPRITE_WAIT			12
#define SPRITE_EMPTY		13
#define SPRITE_FILL			14


#define TYPE_BALLE			23
#define	TYPE_CAISSE			12
#define TYPE_GOAL			7
#define TYPE_CLE			21
#define TYPE_BLUPIHELICO	32
#define TYPE_BLUPITANK		33
#define TYPE_empty		   0
#define MAXMOVEOBJECT = 200;
#define INPUT_LEFT	1
#define INPUT_RIGHT 2


// User define message

#define WM_UPDATE				(WM_USER+1)

#define WM_DECOR1				(WM_USER+20)
#define WM_DECOR2				(WM_USER+21)
#define WM_DECOR3				(WM_USER+22)
#define WM_DECOR4				(WM_USER+23)
#define WM_DECOR5				(WM_USER+24)

#define WM_ACTION_GO			(WM_USER+30)
#define WM_ACTION_ABAT1			(WM_USER+31)
#define WM_ACTION_ABAT2			(WM_USER+32)
#define WM_ACTION_ABAT3			(WM_USER+33)
#define WM_ACTION_ABAT4			(WM_USER+34)
#define WM_ACTION_ABAT5			(WM_USER+35)
#define WM_ACTION_ABAT6			(WM_USER+36)
#define WM_ACTION_BUILD1		(WM_USER+37)
#define WM_ACTION_BUILD2		(WM_USER+38)
#define WM_ACTION_BUILD3		(WM_USER+39)
#define WM_ACTION_BUILD4		(WM_USER+40)
#define WM_ACTION_BUILD5		(WM_USER+41)
#define WM_ACTION_BUILD6		(WM_USER+42)
#define WM_ACTION_STOP			(WM_USER+43)
#define WM_ACTION_CARRY			(WM_USER+44)
#define WM_ACTION_DEPOSE		(WM_USER+45)
#define WM_ACTION_ROC1			(WM_USER+46)
#define WM_ACTION_ROC2			(WM_USER+47)
#define WM_ACTION_ROC3			(WM_USER+48)
#define WM_ACTION_ROC4			(WM_USER+49)
#define WM_ACTION_ROC5			(WM_USER+50)
#define WM_ACTION_ROC6			(WM_USER+51)
#define WM_ACTION_ROC7			(WM_USER+52)
#define WM_ACTION_MUR			(WM_USER+53)
#define WM_ACTION_CULTIVE		(WM_USER+54)
#define WM_ACTION_CULTIVE2		(WM_USER+55)
#define WM_ACTION_MANGE			(WM_USER+56)
#define WM_ACTION_MAKE			(WM_USER+57)
#define WM_ACTION_BUILD			(WM_USER+58)
#define WM_ACTION_PALIS			(WM_USER+59)
#define WM_ACTION_NEWBLUPI		(WM_USER+60)
#define WM_ACTION_PONTE			(WM_USER+61)
#define WM_ACTION_PONTS			(WM_USER+62)
#define WM_ACTION_PONTO			(WM_USER+63)
#define WM_ACTION_PONTN			(WM_USER+64)
#define WM_ACTION_PONTEL		(WM_USER+65)
#define WM_ACTION_PONTSL		(WM_USER+66)
#define WM_ACTION_PONTOL		(WM_USER+67)
#define WM_ACTION_PONTNL		(WM_USER+68)
#define WM_ACTION_TOUR			(WM_USER+69)
#define WM_ACTION_CARRY2		(WM_USER+70)
#define WM_ACTION_DEPOSE2		(WM_USER+71)
#define WM_ACTION_MANGE2		(WM_USER+72)
#define WM_ACTION_BOIT			(WM_USER+73)
#define WM_ACTION_BOIT2			(WM_USER+74)
#define WM_ACTION_LABO			(WM_USER+75)
#define WM_ACTION_FLEUR1		(WM_USER+76)
#define WM_ACTION_FLEUR2		(WM_USER+77)
#define WM_ACTION_DYNAMITE		(WM_USER+78)
#define WM_ACTION_DYNAMITE2		(WM_USER+79)
#define WM_ACTION_T_DYNAMITE	(WM_USER+80)
#define WM_ACTION_FLEUR3		(WM_USER+81)
#define WM_ACTION_R_BUILD1		(WM_USER+82)
#define WM_ACTION_R_BUILD2		(WM_USER+83)
#define WM_ACTION_R_BUILD3		(WM_USER+84)
#define WM_ACTION_R_BUILD4		(WM_USER+85)
#define WM_ACTION_R_MAKE1		(WM_USER+86)
#define WM_ACTION_R_MAKE2		(WM_USER+87)
#define WM_ACTION_R_MAKE3		(WM_USER+88)
#define WM_ACTION_R_MAKE4		(WM_USER+89)
#define WM_ACTION_R_BUILD5		(WM_USER+90)
#define WM_ACTION_R_MAKE5		(WM_USER+91)
#define WM_ACTION_BATEAUE		(WM_USER+92)
#define WM_ACTION_BATEAUS		(WM_USER+93)
#define WM_ACTION_BATEAUO		(WM_USER+94)
#define WM_ACTION_BATEAUN		(WM_USER+95)
#define WM_ACTION_BATEAUDE		(WM_USER+96)
#define WM_ACTION_BATEAUDS		(WM_USER+97)
#define WM_ACTION_BATEAUDO		(WM_USER+98)
#define WM_ACTION_BATEAUDN		(WM_USER+99)
#define WM_ACTION_BATEAUAE		(WM_USER+100)
#define WM_ACTION_BATEAUAS		(WM_USER+101)
#define WM_ACTION_BATEAUAO		(WM_USER+102)
#define WM_ACTION_BATEAUAN		(WM_USER+103)
#define WM_ACTION_MJEEP			(WM_USER+104)
#define WM_ACTION_DJEEP			(WM_USER+105)
#define WM_ACTION_DRAPEAU		(WM_USER+106)
#define WM_ACTION_DRAPEAU2		(WM_USER+107)
#define WM_ACTION_DRAPEAU3		(WM_USER+108)
#define WM_ACTION_EXTRAIT		(WM_USER+109)
#define WM_ACTION_FABJEEP		(WM_USER+110)
#define WM_ACTION_FABMINE		(WM_USER+111)
#define WM_ACTION_MINE			(WM_USER+112)
#define WM_ACTION_MINE2			(WM_USER+113)
#define WM_ACTION_R_BUILD6		(WM_USER+114)
#define WM_ACTION_R_MAKE6		(WM_USER+115)
#define WM_ACTION_E_RAYON		(WM_USER+116)
#define WM_ACTION_ELECTRO		(WM_USER+117)
#define WM_ACTION_ELECTROm		(WM_USER+118)
#define WM_ACTION_GRILLE		(WM_USER+119)
#define WM_ACTION_MAISON		(WM_USER+120)
#define WM_ACTION_FABDISC		(WM_USER+121)
#define WM_ACTION_A_MORT		(WM_USER+122)
#define WM_ACTION_REPEAT		(WM_USER+123)
#define WM_ACTION_TELEPORTE00	(WM_USER+124)
#define WM_ACTION_TELEPORTE10	(WM_USER+125)
#define WM_ACTION_TELEPORTE01	(WM_USER+126)
#define WM_ACTION_TELEPORTE11	(WM_USER+127)
#define WM_ACTION_FABARMURE		(WM_USER+128)
#define WM_ACTION_MARMURE		(WM_USER+129)
#define WM_ACTION_DARMURE		(WM_USER+130)

#define WM_BUTTON0				(WM_USER+200)
#define WM_BUTTON1				(WM_USER+201)
#define WM_BUTTON2				(WM_USER+202)
#define WM_BUTTON3				(WM_USER+203)
#define WM_BUTTON4				(WM_USER+204)
#define WM_BUTTON5				(WM_USER+205)
#define WM_BUTTON6				(WM_USER+206)
#define WM_BUTTON7				(WM_USER+207)
#define WM_BUTTON8				(WM_USER+208)
#define WM_BUTTON9				(WM_USER+209)
#define WM_BUTTON10				(WM_USER+210)
#define WM_BUTTON11				(WM_USER+211)
#define WM_BUTTON12				(WM_USER+212)
#define WM_BUTTON13				(WM_USER+213)
#define WM_BUTTON14				(WM_USER+214)
#define WM_BUTTON15				(WM_USER+215)
#define WM_BUTTON16				(WM_USER+216)
#define WM_BUTTON17				(WM_USER+217)
#define WM_BUTTON18				(WM_USER+218)
#define WM_BUTTON19				(WM_USER+219)
#define WM_BUTTON20				(WM_USER+220)
#define WM_BUTTON21				(WM_USER+221)
#define WM_BUTTON22				(WM_USER+222)
#define WM_BUTTON23				(WM_USER+223)
#define WM_BUTTON24				(WM_USER+224)
#define WM_BUTTON25				(WM_USER+225)
#define WM_BUTTON26				(WM_USER+226)
#define WM_BUTTON27				(WM_USER+227)
#define WM_BUTTON28				(WM_USER+228)
#define WM_BUTTON29				(WM_USER+229)
#define WM_BUTTON30				(WM_USER+230)
#define WM_BUTTON31				(WM_USER+231)
#define WM_BUTTON32				(WM_USER+232)
#define WM_BUTTON33				(WM_USER+233)
#define WM_BUTTON34				(WM_USER+234)
#define WM_BUTTON35				(WM_USER+235)
#define WM_BUTTON36				(WM_USER+236)
#define WM_BUTTON37				(WM_USER+237)
#define WM_BUTTON38				(WM_USER+238)
#define WM_BUTTON39				(WM_USER+239)

#define WM_READ0				(WM_USER+300)
#define WM_READ1				(WM_USER+301)
#define WM_READ2				(WM_USER+302)
#define WM_READ3				(WM_USER+303)
#define WM_READ4				(WM_USER+304)
#define WM_READ5				(WM_USER+305)
#define WM_READ6				(WM_USER+306)
#define WM_READ7				(WM_USER+307)
#define WM_READ8				(WM_USER+308)
#define WM_READ9				(WM_USER+309)

#define WM_WRITE0				(WM_USER+310)
#define WM_WRITE1				(WM_USER+311)
#define WM_WRITE2				(WM_USER+312)
#define WM_WRITE3				(WM_USER+313)
#define WM_WRITE4				(WM_USER+314)
#define WM_WRITE5				(WM_USER+315)
#define WM_WRITE6				(WM_USER+316)
#define WM_WRITE7				(WM_USER+317)
#define WM_WRITE8				(WM_USER+318)
#define WM_WRITE9				(WM_USER+319)

#define WM_PHASE_INIT			(WM_USER+500)
#define WM_PHASE_PLAY			(WM_USER+501)
#define WM_PHASE_BUILD			(WM_USER+502)
#define WM_PHASE_READ			(WM_USER+503)
#define WM_PHASE_WRITE			(WM_USER+504)
#define WM_PHASE_INFO			(WM_USER+505)
#define WM_PHASE_BUTTON			(WM_USER+506)
#define WM_PHASE_TERM			(WM_USER+507)
#define WM_PHASE_WIN			(WM_USER+508)
#define WM_PHASE_LOST			(WM_USER+509)
#define WM_PHASE_STOP			(WM_USER+510)
#define WM_PHASE_SETUP			(WM_USER+511)
#define WM_PHASE_MUSIC			(WM_USER+512)
#define WM_PHASE_PLAYMOVIE		(WM_USER+513)
#define WM_PHASE_WINMOVIE		(WM_USER+514)
#define WM_PHASE_SCHOOL			(WM_USER+515)
#define WM_PHASE_MISSION		(WM_USER+516)
#define WM_PHASE_LASTWIN		(WM_USER+517)
#define WM_PHASE_WRITEp			(WM_USER+518)
#define WM_PHASE_SETUPp			(WM_USER+519)
#define WM_PHASE_REGION			(WM_USER+520)
#define WM_PHASE_INSERT			(WM_USER+521)
#define WM_PHASE_HISTORY0		(WM_USER+522)
#define WM_PHASE_HISTORY1		(WM_USER+523)
#define WM_PHASE_HELP			(WM_USER+524)
#define WM_PHASE_H0MOVIE		(WM_USER+525)
#define WM_PHASE_H1MOVIE		(WM_USER+526)
#define WM_PHASE_H2MOVIE		(WM_USER+527)
#define WM_PHASE_TESTCD			(WM_USER+528)
#define WM_PHASE_MANUEL			(WM_USER+529)
#define WM_PHASE_PRIVATE		(WM_USER+530)
#define WM_PHASE_UNDO			(WM_USER+531)
#define WM_PHASE_BYE			(WM_USER+532)
#define WM_PHASE_SKILL1			(WM_USER+533)
#define WM_PHASE_SKILL2			(WM_USER+534)
#define WM_PHASE_DEMO			(WM_USER+535)
#define WM_PHASE_INTRO1			(WM_USER+536)
#define WM_PHASE_INTRO2			(WM_USER+537)
#define WM_PHASE_PLAYTEST       (WM_USER+538)
#define WM_PHASE_WINMOVIEDESIGN (WM_USER+539)
#define WM_PHASE_WINMOVIEMULTI  (WM_USER+540)

#define WM_PREV					(WM_USER+600)
#define WM_NEXT					(WM_USER+601)
#define WM_MOVIE				(WM_USER+602)
#define WM_PHASE_CREATE 1579
#define WM_PHASE_608	1544

#define WM_PHASE_WINd   1546
#define	WM_PHASE_LOSTd  1547
#define WM_PHASE_WINm   1549
#define WM_PHASE_LOSTm	1550
#define WM_PHASE_READd  1560
#define WM_PHASE_634	1588
#define WM_PHASE_GREAD  1586
#define WM_PHASE_GREADp 1585
#define WM_PHASE_GWRITE 1584
#define WM_PHASE_DOQUIT 1587
#define WM_PHASE_GAMER  1545



// Types de gestion de la souris.

#define MOUSETYPEGRA			1
#define MOUSETYPEWIN			2
#define MOUSETYPEWINPOS			3



// Conditions pour gagner.

typedef struct
{
	short	bHachBlupi;		// blupi sur dalle hachur�e
	short	bHachPlanche;	// planches sur dalle hachur�e
	short	bStopFire;		// feu �teint
	short	nbMinBlupi;		// nb de blupi n�cessaires
	short	nbMaxBlupi;		// nb de blupi n�cessaires
	short	bHomeBlupi;		// blupi � la maison
	short	bKillRobots;	// plus d'ennemis
	short	bHachTomate;	// tomates sur dalle hachur�e
	short	bHachMetal;		// m�tal sur dalle hachur�e
	short	bHachRobot;		// robot sur dalle hachur�e
	short	reserve[14];
}
Term;


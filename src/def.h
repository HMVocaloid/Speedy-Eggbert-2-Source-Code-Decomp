// Def.h
//

#pragma once

#include <Windows.h>

// prevent WinAPI from overriding our functions
#undef PlaySound
#undef DrawText
#undef GetCharWidth

#define _DEMO			FALSE	// TRUE=demo, FALSE=complet
#define _EGAMES			FALSE	// TRUE version pour eGames
#define _SE				FALSE	// TRUE eGames Special Edition
#define _INTRO			FALSE	// TRUE si images d'introduction

// additional flags
#define _CD				FALSE	// whether to require the game CD
#define _BYE			!_EGAMES // whether to show exit image (like _INTRO)

#define MAXGAMER		8

#define LXIMAGE			640		// dimensions de la fenêtre de jeu
#define LYIMAGE			480

#define POSDRAWX		0
#define POSDRAWY		0

#define MAXCELX			100		// nb max de cellules d'un monde
#define MAXCELY			100

#define DIMOBJX			64		// dimensions d'un objet
#define DIMOBJY			64

#define DIMEXPLOX		128
#define DIMEXPLOY		128

#define DIMBLUPIX		60		// dimensions de blupi
#define DIMBLUPIY		60

#define DIMEXPLOX		128
#define DIMEXPLOY		128

#define DIMBUTTONX		40		// dimensions d'un button
#define DIMBUTTONY		40

#define DIMJAUGEX		124		// dimensions de la jauge
#define DIMJAUGEY		22

#define DIMTEXTX		16		// dimensions max d'un caractère
#define DIMTEXTY		16

#define DIMLITTLEX		16		// dimensions max d'un petit caractère
#define DIMLITTLEY		12

enum {
	CHBACK = 0,
	CHOBJECT,
	CHBLUPI,
	CHDECOR,
	CHBUTTON,
	CHJAUGE,
	CHTEXT,
	CHLITTLE,
	CHMAP,
	CHEXPLO,
	CHELEMENT,
	CHBLUPI1,
	CHBLUPI2,
	CHBLUPI3,
	CHTEMP
};

enum {
	MESS_RESUME = 0,
	MESS_PAUSE,
	MESS_2,
	MESS_3,
	MESS_LOBBY,
	MESS_5,
	MESS_6,
	MESS_7,
	MESS_LEAVE,
	MESS_LOST,
	MESS_START,
	MESS_11,
	MESS_PAUSE2,

	MESS_OBJECTSTART = 20,
	MESS_OBJECTDELETE,

	MESS_MODIFDECOR = 30,

	MESS_PLAYSOUND = 40,
	MESS_STOPSOUND,

	MESS_ASCENSEURSTART = 50,
	MESS_ASCENSEUREND,

	MESS_STOPCLOUD = 60
};

#define MAXNETMESSAGE		20

// Directions :

enum {
	DIR_LEFT = 1,
	DIR_RIGHT
};

// Actions :

#define ACTION_STOP 1
#define ACTION_MARCH 2
#define ACTION_TURN 3
#define ACTION_JUMP 4
#define ACTION_AIR 5
#define ACTION_DOWN 6
#define ACTION_UP 7
#define ACTION_VERTIGO 8
#define ACTION_RECEDE 9
#define ACTION_ADVANCE 10
#define ACTION_CLEAR1 11
#define ACTION_SET 12
#define ACTION_WIN 13
#define ACTION_PUSH 14
#define ACTION_STOPHELICO 15
#define ACTION_MARCHHELICO 16
#define ACTION_TURNHELICO 17
#define ACTION_STOPNAGE 18
#define ACTION_MARCHNAGE 19
#define ACTION_TURNNAGE 20
#define ACTION_STOPSURF 21
#define ACTION_MARCHSURF 22
#define ACTION_TURNSURF 23
#define ACTION_DROWN 24
#define ACTION_STOPJEEP 25
#define ACTION_MARCHJEEP 26
#define ACTION_TURNJEEP 27
#define ACTION_STOPPOP 28
#define ACTION_POP 29
#define ACTION_BYE 30
#define ACTION_STOPSUSPEND 31
#define ACTION_MARCHSUSPEND 32
#define ACTION_TURNSUSPEND 33
#define ACTION_JUMPSUSPEND 34
#define ACTION_HIDE 35
#define ACTION_JUMPAIE 36
#define ACTION_STOPSKATE 37
#define ACTION_MARCHSKATE 38
#define ACTION_TURNSKATE 39
#define ACTION_JUMPSKATE 40
#define ACTION_AIRSKATE 41
#define ACTION_TAKESKATE 42
#define ACTION_DEPOSESKATE 43
#define ACTION_OUF1a 44
#define ACTION_OUF1b 45
#define ACTION_OUF2 46
#define ACTION_OUF3 47
#define ACTION_OUF4 48
#define ACTION_SUCETTE 49
#define ACTION_STOPTANK 50
#define ACTION_MARCHTANK 51
#define ACTION_TURNTANK 52
#define ACTION_FIRETANK 53
#define ACTION_GLU 54
#define ACTION_DRINK 55
#define ACTION_CHARGE 56
#define ACTION_ELECTRO 57
#define ACTION_HELICOGLU 58
#define ACTION_TURNAIR 59
#define ACTION_STOPMARCH 60
#define ACTION_STOPJUMP 61
#define ACTION_STOPJUMPh 62
#define ACTION_MOCKERY 63
#define ACTION_MOCKERYi 64
#define ACTION_OUF5 65
#define ACTION_BALLOON 66
#define ACTION_STOPOVER 67
#define ACTION_MARCHOVER 68
#define ACTION_TURNOVER 69
#define ACTION_RECEDEq 70
#define ACTION_ADVANCEq 71
#define ACTION_STOPECRASE 72
#define ACTION_MARCHECRASE 73
#define ACTION_TELEPORTE 74
#define ACTION_CLEAR2 75
#define ACTION_CLEAR3 76
#define ACTION_CLEAR4 77
#define ACTION_CLEAR5 78
#define ACTION_CLEAR6 79
#define ACTION_CLEAR7 80
#define ACTION_CLEAR8 81
#define ACTION_SWITCH 82
#define ACTION_MOCKERYp 83
#define ACTION_NON 84
#define ACTION_SLOWDOWNSKATE 85
#define ACTION_TAKEDYNAMITE 86
#define ACTION_PUTDYNAMITE 87

// Sécurités :

enum {
	SEC_SHIELD = 1,
	SEC_POWER,
	SEC_CLOUD,
	SEC_HIDE
};

// Types :

#define TYPE_ASCENSEUR 1
#define TYPE_BOMBEDOWN 2
#define TYPE_BOMBEUP 3
#define TYPE_BULLDOZER 4
#define TYPE_TRESOR 5
#define TYPE_EGG 6
#define TYPE_GOAL 7
#define TYPE_EXPLO1 8
#define TYPE_EXPLO2 9
#define TYPE_EXPLO3 10
#define TYPE_EXPLO4 11
#define TYPE_CAISSE 12
#define TYPE_HELICO 13
#define TYPE_PLOUF 14
#define TYPE_BLUP 15
#define TYPE_BOMBEMOVE 16
#define TYPE_POISSON 17
#define TYPE_TOMATES 18 // unused
#define TYPE_JEEP 19
#define TYPE_OISEAU 20
#define TYPE_CLE 21
#define TYPE_DOOR 22
#define TYPE_BALLE 23
#define TYPE_SKATE 24
#define TYPE_SHIELD 25
#define TYPE_POWER 26
#define TYPE_MAGICTRACK 27
#define TYPE_TANK 28
#define TYPE_BULLET 29
#define TYPE_DRINK 30
#define TYPE_CHARGE 31
#define TYPE_BLUPIHELICO 32
#define TYPE_BLUPITANK 33
#define TYPE_GLU 34
#define TYPE_TIPLOUF 35
#define TYPE_POLLUTION 36
#define TYPE_CLEAR 37
#define TYPE_ELECTRO 38
#define TYPE_TRESORTRACK 39
#define TYPE_INVERT 40
#define TYPE_INVERTSTART 41
#define TYPE_INVERTSTOP 42
#define TYPE_GUEPE 44
#define TYPE_OVER 46
#define TYPE_ASCENSEURs 47
#define TYPE_ASCENSEURsi 48
#define TYPE_CLE1 49
#define TYPE_CLE2 50
#define TYPE_CLE3 51
#define TYPE_BRIDGE 52
#define TYPE_TENTACULE 53
#define TYPE_CREATURE 54
#define TYPE_DYNAMITE 55
#define TYPE_DYNAMITEf 56
#define TYPE_SHIELDTRACK 57
#define TYPE_HIDETRACK 58
#define TYPE_EXPLO5 90
#define TYPE_EXPLO6 91
#define TYPE_EXPLO7 92
#define TYPE_EXPLO8 93
#define TYPE_EXPLO9 94
#define TYPE_EXPLO10 95
#define TYPE_BOMBEFOLLOW1 96
#define TYPE_BOMBEFOLLOW2 97
#define TYPE_SPLOUTCH1 98
#define TYPE_SPLOUTCH2 99
#define TYPE_SPLOUTCH3 100
#define TYPE_BOMBEPERSO1 200
#define TYPE_BOMBEPERSO2 201
#define TYPE_BOMBEPERSO3 202
#define TYPE_BOMBEPERSO4 203

// Steps :

enum {
	STEP_STOPSTART = 1,
	STEP_ADVANCE,
	STEP_STOPEND,
	STEP_RECEDE
};

// Sons :

#define SOUND_CLICK 0
#define SOUND_JUMP1 1
#define SOUND_JUMP2 2
#define SOUND_JUMPEND 3
#define SOUND_JUMPTOC 4
#define SOUND_TURN 5
#define SOUND_VERTIGO 6
#define SOUND_DOWN 7
#define SOUND_FALL 8
#define SOUND_NEW 9
#define SOUND_BOUM 10
#define SOUND_TRESOR 11
#define SOUND_EGG 12
#define SOUND_ENDKO 13
#define SOUND_ENDOK 14
#define SOUND_HELICOSTART 15
#define SOUND_HELICOHIGH 16
#define SOUND_HELICOSTOP 17
#define SOUND_HELICOLOW 18
#define SOUND_LASTTRESOR 19
#define SOUND_UP 20
#define SOUND_LOOKUP 21
#define SOUND_JUMP0 22
#define SOUND_PLOUF 23
#define SOUND_BLUP 24
#define SOUND_SURF 25
#define SOUND_DROWN 26
#define SOUND_ERROR 27
#define SOUND_JEEPSTART 28
#define SOUND_JEEPHIGH 29
#define SOUND_JEEPSTOP 30
#define SOUND_JEEPLOW 31
#define SOUND_BYE 32
#define SOUND_DOOR 33
#define SOUND_SUSPENDTOC 34
#define SOUND_SUSPENDJUMP 35
#define SOUND_SINGE 36
#define SOUND_PATIENT 37
#define SOUND_PUSH 38
#define SOUND_POP 39
#define SOUND_JUMPAIE 40
#define SOUND_RESSORT 41
#define SOUND_STARTSHIELD 42
#define SOUND_STOPSHIELD 43
#define SOUND_STARTPOWER 44
#define SOUND_STOPPOWER 45
#define SOUND_OUF1 46
#define SOUND_OUF2 47
#define SOUND_OUF3 48
#define SOUND_OUF4 49
#define SOUND_SUCETTE 50
#define SOUND_GLU 51
#define SOUND_FIREOK 52
#define SOUND_FIREKO 53
#define SOUND_TAKEGLU 54
#define SOUND_STARTCLOUD 55
#define SOUND_STOPCLOUD 56
#define SOUND_DRINK 57
#define SOUND_CHARGE 58
#define SOUND_ELECTRO 59
#define SOUND_PERSOTAKE 60
#define SOUND_PERSOPOSE 61
#define SOUND_STARTHIDE 62
#define SOUND_STOPHIDE 63
#define SOUND_TIPLOUF 64
#define SOUND_MOCKERY 65
#define SOUND_INVERTSTART 66
#define SOUND_INVERTSTOP 67
#define SOUND_OVERSTOP 68
#define SOUND_BLITZ 69
#define SOUND_ECRASE 70
#define SOUND_TELEPORTE 71
#define SOUND_BRIDGE1 72
#define SOUND_BRIDGE2 73
#define SOUND_ANGEL 74
#define SOUND_SCIE 75
#define SOUND_SWITCHOFF 76
#define SOUND_SWITCHON 77
#define SOUND_JUMPENDb 78
#define SOUND_JUMPTOCb 79
#define SOUND_JUMPENDm 80
#define SOUND_JUMPTOCm 81
#define SOUND_JUMPENDg 82
#define SOUND_JUMPTOCg 83
#define SOUND_JUMPENDo 84
#define SOUND_JUMPTOCo 85
#define SOUND_JUMPENDk 86
#define SOUND_JUMPTOCk 87
#define SOUND_JUMPENDf 88
#define SOUND_JUMPTOCf 89
#define SOUND_JUMPENDh 90
#define SOUND_JUMPTOCh 91
#define SOUND_FOLLOW 92
#define SOUND_MOVIE 99

// 

enum {
	KEY_NONE = 0,
	KEY_LEFT = 1,
	KEY_RIGHT = 2,
	KEY_UP = 4,
	KEY_DOWN = 8,
	KEY_JUMP = 16,
	KEY_FIRE = 32
};

// Boutons (play) :

#define MAXBUTTON			40

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


// User define message

enum {
	WM_UPDATE = WM_USER + 1,

	WM_DECOR1 = WM_USER + 20,
	WM_DECOR2,
	WM_DECOR3,
	WM_DECOR4,
	WM_DECOR5,
	WM_DECOR6,
	WM_DECOR7,
	WM_DECOR8,
	WM_DECOR9,
	WM_DECOR10,
	WM_DECOR11,

	WM_BUTTON0 = WM_USER + 200,
	WM_BUTTON1,
	WM_BUTTON2,
	WM_BUTTON3,
	WM_BUTTON4,
	WM_BUTTON5,
	WM_BUTTON6,
	WM_BUTTON7,
	WM_BUTTON8,
	WM_BUTTON9,
	WM_BUTTON10,
	WM_BUTTON11,
	WM_BUTTON12,
	WM_BUTTON13,
	WM_BUTTON14,
	WM_BUTTON15,
	WM_BUTTON16,
	WM_BUTTON17,
	WM_BUTTON18,
	WM_BUTTON19,
	WM_BUTTON20,
	WM_BUTTON21,
	WM_BUTTON22,
	WM_BUTTON23,
	WM_BUTTON24,
	WM_BUTTON25,
	WM_BUTTON26,
	WM_BUTTON27,
	WM_BUTTON28,
	WM_BUTTON29,
	WM_BUTTON30,
	WM_BUTTON31,
	WM_BUTTON32,
	WM_BUTTON33,
	WM_BUTTON34,
	WM_BUTTON35,
	WM_BUTTON36,
	WM_BUTTON37,
	WM_BUTTON38,
	WM_BUTTON39,

	WM_DIMS1,
	WM_DIMS2,
	WM_DIMS3,
	WM_DIMS4,

	WM_READ0 = WM_USER + 300,
	WM_READ1,
	WM_READ2,
	WM_READ3,
	WM_READ4,
	WM_READ5,
	WM_READ6,
	WM_READ7,
	WM_READ8,
	WM_READ9,
	WM_WRITE0,
	WM_WRITE1,
	WM_WRITE2,
	WM_WRITE3,
	WM_WRITE4,
	WM_WRITE5,
	WM_WRITE6,
	WM_WRITE7,
	WM_WRITE8,
	WM_WRITE9,

	WM_PHASE_INIT = WM_USER + 500,
	WM_PHASE_PLAY,
	WM_PHASE_BUILD,
	WM_PHASE_NAMEGAMER,
	WM_PHASE_CLEARGAMER,
	WM_PHASE_INFO,
	WM_PHASE_PLAYTEST,
	WM_PHASE_1531,
	WM_PHASE_WIN,
	WM_PHASE_LOST,
	WM_PHASE_SETUP,
	WM_PHASE_MUSIC,
	WM_PHASE_PLAYMOVIE,
	WM_PHASE_WINMOVIE,
	WM_PHASE_1539,
	WM_PHASE_DOPLAY,
	WM_PHASE_LASTWIN, // PB vestige
	WM_PHASE_SETUPp,
	WM_PHASE_REGION,
	WM_PHASE_INSERT,
	WM_PHASE_1544,
	WM_PHASE_GAMER,
	WM_PHASE_WINDESIGN,
	WM_PHASE_LOSTDESIGN,
	WM_PHASE_WINMOVIEDESIGN,
	WM_PHASE_WINMULTI,
	WM_PHASE_LOSTMULTI,
	WM_PHASE_WINMOVIEMULTI,
	WM_PHASE_TESTCD,
	WM_PHASE_MANUEL,
	WM_PHASE_PRIVATE,
	WM_PHASE_UNDO,
	WM_PHASE_BYE,
	WM_PHASE_DEMO,
	WM_PHASE_NAMEDESIGN,
	WM_PHASE_WRITEDESIGN,
	WM_PHASE_READDESIGN,
	WM_PHASE_CLEARDESIGN,
	WM_PHASE_DONAMEGAMER,
	WM_PHASE_DOCLEARGAMER,
	WM_PHASE_DONAMEDESIGN,
	WM_PHASE_1565,
	WM_PHASE_DOREADDESIGN,
	WM_PHASE_DOCLEARDESIGN,
	WM_PHASE_SERVICE,
	WM_PHASE_DPLAY_DO_SERVICE,
	WM_PHASE_DPLAY_CANCEL_SERVICE,
	WM_PHASE_SESSION,
	WM_PHASE_1572,
	WM_PHASE_DPLAY_CREATE_LOBBY,
	WM_PHASE_DPLAY_REFRESH,
	WM_PHASE_DPLAY_CANCEL_SESSION,
	WM_PHASE_MULTI,
	WM_PHASE_DPLAY_START_GAME_2,
	WM_PHASE_DPLAY_CANCEL_MULTI,
	WM_PHASE_CREATE,
	WM_PHASE_DPLAY_CREATE,
	WM_PHASE_DPLAY_CANCEL_CREATE,
	WM_PHASE_STOP,
	WM_PHASE_HELP,
	WM_PHASE_GWRITE,
	WM_PHASE_GREADp,
	WM_PHASE_GREAD,
	WM_PHASE_DOQUIT,
	WM_PHASE_1588,
	WM_PHASE_INTRO1, // PB vestige
	WM_PHASE_INTRO2, // PB vestige

	WM_PREV = WM_USER + 600,
	WM_NEXT,
	WM_MOVIE
};

// Types de gestion de la souris.

#define MOUSETYPEGRA			1
#define MOUSETYPEWIN			2
#define MOUSETYPEWINPOS			3

// Button icons

enum {
	IC_BT_TECH = 0, // Item: Square tech-block
	IC_BT_SPECIALTECH, // Item: Special tech-block
	IC_BT_TRIANGULARTECH, // Item: Triangular tech-block
	IC_BT_9, // Item: Special tech-block (T shape)
	IC_BT_10, // Scrolling: Horizontal and vertical (duplicate?)
	IC_BT_BLUPI, // Item: Yellow Blupi
	IC_BT_CANCEL, // UI: Black X (cancel)
	IC_BT_TREASURE, // Item: Treasure chest
	IC_BT_BOMB, // Item: Bomb
	IC_BT_BOMBUP, // Item: Hanging bomb
	IC_BT_EGG, // Item: Egg
	IC_BT_GOAL, // Item: Goal
	IC_BT_CANCEL2, // UI: Yellow X
	IC_BT_HORIZONTAL, // Scrolling: Horizontal only
	IC_BT_VERTICAL, // Scrolling: Vertical only
	IC_BT_HORIZONTALVERTICAL, // Scrolling: Horizontal and vertical
	IC_BT_BULLDOZER, // Item: Bulldozer
	IC_BT_CASE, // Item: Wooden case
	IC_BT_ACCEPT, // UI: Black checkmark
	IC_BT_LIFTFAST, // Item: Fast lift
	IC_BT_LIFTNORMAL, // Item: Normal lift
	IC_BT_LIFTSLOW, // Item: Slow lift
	IC_BT_ROCK, // Item: Square rock
	IC_BT_WOODENWALL, // Item: Wooden wall
	IC_BT_HELICOPTER, // Item: Helicopter
	IC_BT_DREAM, // Item: Dream
	IC_BT_LAVA, // Item: Lava
	IC_BT_SECRETTECH, // Item: Secret tech-block
	IC_BT_LIFTFASTSLOW, // Item: Fast/slow lift
	IC_BT_PALMTREE, // Item: Palmtree
	IC_BT_SUPPORT, // Item: Support
	IC_BT_TREE, // Item: Tree
	IC_BT_VEGETATION, // Item: Vegetation
	IC_BT_HOUSE, // Item: House
	IC_BT_MECH, // Item: Square mechanical
	IC_BT_SPECIALMECH, // Item: Special mechanical
	IC_BT_DELETE, // UI: Red X (delete)
	IC_BT_BIGMECH, // Item: Mechanical background element
	IC_BT_WATER, // Item: Water
	IC_BT_GRASS, // Item: Grass
	IC_BT_STOP, // UI: STOP sign
	IC_BT_WIND, // Item: Wind
	IC_BT_FAN, // Item: Fan
	IC_BT_CREATE, // UI: Create multiplayer lobby
	IC_BT_MUSIC, // UI: Music
	IC_BT_JOIN, // UI: Join multiplayer lobby
	IC_BT_NAME, // UI: Edit name
	IC_BT_SETUP, // UI: Setup (analog gauge)
	IC_BT_PLAY, // UI: Play (dice)
	IC_BT_DESIGN, // UI: Design (wrench and screwdriver)
	IC_BT_ARROWLEFT, // UI: Arrow pointing left
	IC_BT_ARROWRIGHT, // UI: Arrow pointing right
	IC_BT_READ, // UI: Load game
	IC_BT_WRITE, // UI: Save game
	IC_BT_MOVINGBOMB, // Item: Moving bomb
	IC_BT_FISH, // Item: Fish
	IC_BT_BAR, // Item: Bar to hang from
	IC_BT_JEEP, // Item: Jeep
	IC_BT_FURNITURE, // Item: Furniture
	IC_BT_TRIANGULARROCK, // Item: Triangular rock
	IC_BT_BIRD, // Item: Bird
	IC_BT_TINY, // Scrolling: Tiny (No scrolling)
	IC_BT_LEVELSTART, // Item: Level start
	IC_BT_DOOR, // Item: Door (hub)
	IC_BT_KEY, // Item: Key (goal)
	IC_BT_FACADE, // Item: Building facade
	IC_BT_ROOF, // Item: Roof
	IC_BT_SECRETMECH, // Item: Secret mechanical
	IC_BT_SECRETROCK, // Item: Secret rock
	IC_BT_MARINE, // Item: Marine plant
	IC_BT_SPRING, // Item: Spring
	IC_BT_SKATEBOARD, // Item: Skateboard
	IC_BT_ARROWUP, // UI: Arrow pointing up
	IC_BT_ARROWDOWN, // UI: Arrow pointing down
	IC_BT_SHIELD, // Item: Shield
	IC_BT_LOLLIPOP, // Item: Lollipop
	IC_BT_SECRETCASE, // Item: Secret wooden case
	IC_BT_CONTINUE, // UI: Continue game
	IC_BT_HALT, // UI: Halt (hand)
	IC_BT_INVISIBLEBLOCK, // Item: Invisible block
	IC_BT_KIDSSTUFF, // Item: Kid's stuff block
	IC_BT_SPECIALKIDSSTUFF, // Item: Special kid's stuff
	IC_BT_BIGKIDSSTUFF, // Item: Kid's stuff background element
	IC_BT_MULTI, // UI: Multiplayer
	IC_BT_DEMO, // UI: Demo
	IC_BT_TANK, // Item: Tank
	IC_BT_HELP, // UI: Help
	IC_BT_DYNAMITE, // Item: Dynamite
	IC_BT_GLUE, // Item: Glue supply
	IC_BT_DRINK, // Item: Invisibility potion
	IC_BT_NOTREADY, // UI: Not ready (multiplayer lobby)
	IC_BT_READY, // UI: Ready (multiplayer lobby)
	IC_BT_PERSO, // Item: Personal bomb
	IC_BT_CHARGER, // Item: Recharging device
	IC_BT_SEND, // UI: Send message
	IC_BT_HELICOENEMY, // Item: Heliported enemy
	IC_BT_BLUPI1, // Item: Orange Blupi
	IC_BT_BLUPI2, // Item: Blue Blupi
	IC_BT_BLUPI3, // Item: Green Blupi
	IC_BT_TANKENEMY, // Item: Motorized enemy
	IC_BT_CHEESE, // Item: Cheese
	IC_BT_INVERTER, // Item: Inverter
	IC_BT_PERSO0, // Item: Yellow personal bomb
	IC_BT_PERSO1, // Item: Orange personal bomb
	IC_BT_PERSO2, // Item: Blue personal bomb
	IC_BT_PERSO3, // Item: Green personal bomb
	IC_BT_PIPES, // Item: Pipes
	IC_BT_HOMINGBOMB, // Item: Homing bomb
	IC_BT_TEAM1, // UI: Select team 1
	IC_BT_TEAM2, // UI: Select team 2
	IC_BT_TEAM3, // UI: Select team 3
	IC_BT_TEAM4, // UI: Select team 4
	IC_BT_BRICKS, // Item: Bricks
	IC_BT_WASP, // Item: Wasp
	IC_BT_TEAMLITTLE1, // Gameplay: Team 1 player indicator
	IC_BT_TEAMLITTLE2, // Gameplay: Team 2 player indicator
	IC_BT_TEAMLITTLE3, // Gameplay: Team 3 player indicator
	IC_BT_TEAMLITTLE4, // Gameplay: Team 4 player indicator
	IC_BT_CAVE, // Item: Cave
	IC_BT_HOVERCRAFT, // Item: Hovercraft
	IC_BT_LIGHTNING, // Item: Lightning
	IC_BT_CONVEYOR, // Item: Lift with conveyor
	IC_BT_CRUSHER, // Item: Crusher
	IC_BT_VANISH, // Item: Vanishing bloc
	IC_BT_TELEPORTER, // Item: Teleporter
	IC_BT_KEYCOLOR, // Item: Key (color)
	IC_BT_DOORCOLOR, // Item: Door (color)
	IC_BT_SECRETCAVE, // Item: Secret cave
	IC_BT_SECRETCHEESE, // Item: Secret cheese
	IC_BT_SLIME, // Item: Slime block
	IC_BT_BIGSLIME, // Item: Slime background element
	IC_BT_SLIMEFLOOR, // Item: Floor slime trap
	IC_BT_SAW, // Item: Saw
	IC_BT_LOWCOLORBACK, // UI: 256-color background
	IC_BT_TRUECOLORBACK, // UI: 65536-color background
	IC_BT_LOWCOLORDECOR, // UI: 256-color foreground
	IC_BT_TRUECOLORDECOR, // UI: 65536-color foreground
	IC_BT_PALACE, // Item: Palace
	IC_BT_PALACEELEMENT, // Item: Element for palace
	IC_BT_BIGPALACE, // Item: Palace background element
	IC_BT_SLIMECREATURE, // Item: Slime creature
	IC_BT_BRIDGE, // Item: Fragile bridge
	IC_BT_SPIDERWEB, // Item: Spider's web
	IC_BT_SLIMECEILING, // Item: Ceiling slime trap
	IC_BT_TREASUREDOOR // Item: Numbered treasure door
};


namespace Object {
	enum Object {
		Empty = -1,
		Hili,
		TechSquare_1,
		TechSquare_2,
		TechSquare_3,
		TechSquare_4,
		TechSquare_5,
		TechSquare_6,
		TechSquare_7,
		TechSquare_8,
		TechSquare_9,
		TechSquare_10,
		TechSquare_11,
		TechSquare_12,
		TechSquare_13,
		TechSquare_14,
		TechTriRight_1,
		TechTriRight_2, // 16
		TechTriLeft_1,
		TechTriLeft_2,
		TechSpecial_1,
		TechSpecial_2,
		TechSpecial_3,
		TechSecret_1,
		TechSpecial_4,
		TechSpecial_5,
		TechSpecial_6,
		TechSpecial_7,
		TechSpecial_8,
		TechSpecial_9,
		TechSpecial_10,
		LiftPoint_1,
		LiftPoint_2,
		Caisse_1, // 32
		Caisse_2,
		Caisse_3,
		RockSquare_1,
		RockSquare_2,
		RockSquare_3,
		RockSquare_4,
		RockSquare_5,
		RockSquare_6,
		WoodWall_1,
		WoodWall_2,
		WoodWall_3,
		WoodWall_4,
		WoodWall_5,
		WoodWall_6,
		WoodWall_7,
		Dream_1, // 48
		Dream_2,
		Dream_3,
		Dream_4,
		Dream_5,
		Dream_6,
		Dream_7,
		Dream_8,
		Dream_9,
		Dream_10,
		Dream_11,
		Dream_12,
		Dream_13,
		Dream_14,
		Dream_15,
		Dream_16,
		Dream_17,  // 64
		Dream_18,
		Dream_19,
		Dream_20,
		Lava_1,
		Lava_2,
		Lava_3,
		Lava_4,
		Lava_5,
		TechSecret_2,
		RockTriLeft_1,
		RockTriRight_1,
		Support_1,
		Support_2,
		MechSquare_1,
		MechSquare_2,
		MechSquare_3, // 80
		MechSquare_4,
		MechSquare_5,
		MechSquare_6,
		MechSquare_7,
		MechSecret_1,
		MechSecret_2,
		MechSpecial_1,
		MechSpecial_2,
		MechSpecial_3,
		MechSpecial_4,
		WaterSquare_1,
		WaterSurf_1,
		WaterSurf_2,
		WaterSurf_3,
		WaterSurf_4,
		WaterSquare_2, // 96
		WaterSquare_3,
		WaterSquare_4,
		Splash_1,
		Splash_2,
		Splash_3,
		Splash_4,
		Bubble_1,
		Bubble_2,
		Bubble_3,
		Bubble_4,
		GrassSquare_1,
		GrassLeft,
		GrassRight,
		WindLeft_1,
		WindLeft_2, // 112
		WindLeft_3,
		WindLeft_4,
		WindRight_1,
		WindRight_2,
		WindRight_3,
		WindRight_4,
		WindUp_1,
		WindUp_2,
		WindUp_3,
		WindUp_4,
		WindDown_1,
		WindDown_2,
		WindDown_3,
		WindDown_4,
		FanLeft_1,
		FanLeft_2, // 128
		FanLeft_3,
		FanRight_1,
		FanRight_2,
		FanRight_3,
		FanUp_1,
		FanUp_2,
		FanUp_3,
		FanDown_1,
		FanDown_2,
		FanDown_3,
		Bar_1,
		Bookshelf_1,
		Bookshelf_2,
		Bookshelf_3,
		Bookshelf_4,
		Bookshelf_5,
		RockSquare_7, // 144
		RockSquare_8,
		RockSquare_9,
		RockSquare_10,
		RockSquare_11,
		RockSquare_12,
		RockSquare_13,
		RockSquare_14,
		RockSquare_15,
		RockSquare_16,
		RockTriLeft_2,
		RockTriRight_2,
		RockSquare_17,
		GrassSquare_2,
		Course_1,
		Course_2,
		Course_3, // 160
		Course_4,
		Course_5,
		Course_6,
		Course_7,
		Course_8,
		CourseDone_1,
		CourseDone_2,
		CourseDone_3,
		CourseDone_4,
		CourseDone_5,
		CourseDone_6,
		CourseDone_7,
		CourseDone_8,
		Level_1,
		Level_2,
		Level_3, // 176
		Level_4,
		Level_5,
		Level_6,
		Level_7,
		Level_8,
		DoorLevel,
		DoorCourse,
		CourseBack,
		RockSecret,
		Facade_1,
		Facade_2,
		Facade_3,
		Facade_4,
		Facade_5,
		Facade_6,
		Facade_7, // 192
		Roof_1,
		Roof_2,
		Roof_3,
		Roof_4,
		Roof_5,
		Support_3,
		Support_4,
		Support_5,
		Support_6,
		Bar_2,
		Marine_1,
		Marine_2,
		Marine_3,
		Marine_4,
		Marine_5,
		Marine_6, // 208
		Spring_1,
		Spring_2,
		Spring_3,
		Spring_4,
		Spring_5,
		Invisible,
		KidsSquare_1,
		KidsSquare_2,
		KidsSquare_3,
		KidsSquare_4,
		KidsSquare_5,
		KidsSquare_6,
		KidsSquare_7,
		KidsSquare_8,
		KidsSpecial_1,
		KidsSpecial_2, // 224
		KidsSpecial_3,
		KidsSpecial_4,
		KidsSpecial_5,
		KidsSpecial_6,
		KidsSpecial_7,
		KidsSquare_9,
		KidsSquare_10,
		KidsSpecial_8,
		KidsSquare_11,
		KidsSquare_12,
		Support_7,
		Support_8,
		DitherMask,
		Charger_1,
		Charger_2,
		Charger_3, // 240
		Charger_4,
		Charger_5,
		Charger_6,
		Splash_5,
		Unk_F5,
		CheeseSquare_1,
		CheeseSquare_2,
		CheeseSquare_3,
		CheeseSquare_4,
		Pipes_1,
		Pipes_2,
		Pipes_3,
		Pipes_4,
		Pipes_5,
		Pipes_6,
		Pipes_7, // 256
		Pipes_8,
		Pipes_9,
		Pipes_10,
		Pipes_11,
		Bricks_1,
		Bricks_2,
		Bricks_3,
		CheeseSupport_1,
		CheeseSupport_2,
		CheeseSupport_3,
		CheeseSupport_4,
		CheeseSupport_5,
		CheeseSupport_6,
		CheeseSupport_7,
		CheeseSupport_8,
		CheeseSupport_9, // 272
		CheeseSupport_10,
		CheeseSupport_11,
		CheeseSupport_12,
		CheeseSupport_13,
		CheeseSupport_14,
		CheeseSupport_15,
		CheeseSupport_16,
		CheeseSupport_17,
		CheeseSupport_18,
		CheeseSupport_19,
		Bricks_4,
		Cave_1,
		CaveSupport_1,
		CaveSupport_2,
		CaveSupport_3,
		CaveSupport_4, // 288
		CaveSupport_5,
		CaveSupport_6,
		CaveSupport_7,
		CaveSupport_8,
		CaveSupport_9,
		CaveSupport_10,
		CaveSupport_11,
		CaveSupport_12,
		CaveSupport_13,
		CaveSupport_14,
		CaveSupport_15,
		CaveSupport_16,
		Cave_2,
		CaveSupport_17,
		CaveSupport_18,
		LightningMachine, // 304
		Lightning_1,
		Lightning_2,
		Lightning_3,
		Lightning_4,
		Course_9,
		CourseDone_9,
		Conveyor_1,
		Conveyor_2,
		Conveyor_3,
		Conveyor_4,
		Conveyor_5,
		Conveyor_6,
		Crusher_1,
		Crusher_2,
		Crusher_3,
		Crusher_4, // 320
		Crusher_5,
		Crusher_6,
		Crusher_7,
		Vanish_1,
		Vanish_2,
		Vanish_3,
		Vanish_4,
		Vanish_5,
		Vanish_6,
		Teleporter_1,
		Teleporter_2,
		Teleporter_3,
		Teleporter_4,
		DoorRed,
		DoorGreen,
		DoorBlue, // 336
		CaveSecret,
		Cave_3,
		CheeseSecret,
		CheeseSquare_5,
		Slime_1,
		Slime_2,
		Slime_3,
		Slime_4,
		Slime_5,
		Slime_6,
		Slime_7,
		Slime_8,
		Slime_9,
		Slime_10,
		Slime_11,
		Slime_12, // 352
		Slime_13,
		Slime_14,
		Slime_15,
		Slime_16,
		Slime_17,
		Slime_18,
		Slime_19,
		Slime_20,
		Slime_21,
		Slime_22,
		Slime_23,
		FragileBridge_1,
		FragileBridge_2,
		FragileBridge_3,
		FragileBridge_4,
		FragileBridge_5, // 368
		FragileBridge_6,
		FragileBridge_7,
		FragileBridge_8,
		FragileBridge_9,
		SlimeTrapFloor_1,
		SlimeTrapFloor_2,
		Support_9,
		Support_10,
		Support_11,
		Saw_1,
		Saw_2,
		Saw_3,
		Saw_4,
		Saw_5,
		Saw_6,
		SawSwitchOn, // 382
		SawSwitchOff,
		Palace_1,
		Palace_2,
		Palace_3,
		Palace_4,
		Palace_5,
		Palace_6,
		Palace_7,
		Palace_8,
		Palace_9,
		Palace_10,
		Palace_11,
		Palace_12,
		PalaceElement_1,
		PalaceElement_2,
		PalaceElement_3, // 398
		SpiderWeb_1,
		SpiderWeb_2,
		SpiderWeb_3,
		SlimeTrapCeiling_1,
		SlimeTrapCeiling_2,
		SlimeTrapCeiling_3,
		SlimeTrapCeiling_4,
		SlimeTrapCeiling_5,
		SlimeTrapCeiling_6,
		SlimeTrapCeiling_7,
		Course_10,
		Course_11,
		Course_12,
		Course_13,
		Course_14,
		CourseDone_10, // 414
		CourseDone_11,
		CourseDone_12,
		CourseDone_13,
		CourseDone_14,
		DoorTreasure_1,
		DoorTreasure_2,
		DoorTreasure_3,
		DoorTreasure_4,
		DoorTreasure_5,
		DoorTreasure_6,
		DoorTreasure_7,
		DoorTreasure_8,
		DoorTreasure_9,
		DoorTreasure_10,
		DoorTreasure_11,
		DoorTreasure_12,	// 430
		DoorTreasure_13,
		DoorTreasure_14,
		DoorTreasure_15,
		DoorTreasure_16,
		DoorTreasure_17,
		DoorTreasure_18,
		DoorTreasure_19,
		DoorTreasure_20
	};
}

#define CLE_RED (1 << 0)
#define CLE_GREEN (1 << 1)
#define CLE_BLUE (1 << 2)

// helpers for POINT

POINT operator+(POINT p, const POINT& a)
{
	return { a.x + p.x, a.y + p.y };
}

POINT operator-(POINT p, const POINT& a)
{
	return { a.x - p.x, a.y - p.y };
}

POINT operator*(POINT p, const POINT& a)
{
	return { a.x * p.x, a.y * p.y };
}

POINT operator/(POINT p, const POINT& a)
{
	return { p.x / a.x, p.y / a.y };
}

POINT operator*(POINT p, const int& a)
{
	return { p.x * a, p.y * a };
}

POINT operator/(POINT p, const int& a)
{
	return { p.x / a, p.y / a };
}

POINT operator+=(POINT p, const POINT& a)
{
	return { p.x += a.x, p.y += a.y };
}

POINT operator-=(POINT p, const POINT& a)
{
	return { p.x -= a.x, p.y -= a.y };
}

POINT operator*=(POINT p, const POINT& a)
{
	return { p.x *= a.x, p.y *= a.y };
}

POINT operator/=(POINT p, const POINT& a)
{
	return { p.x /= a.x, p.y /= a.y };
}

POINT operator*=(POINT p, const int& a)
{
	return { p.x *= a, p.y *= a };
}

POINT operator/=(POINT p, const int& a)
{
	return { p.x /= a, p.y /= a };
}
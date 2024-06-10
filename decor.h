// Decor.h

#pragma once

#include <Windows.h>

#include "DEF.H"
#include "SOUND.H"
#include "PIXMAP.H"
#include "network.h"

/////////////////////////////////////////////////////////////////////////////


#define MAXENERGY		4000
#define MAXFIRE			400

#define ICON_HILI_STAT	112
#define ICON_HILI_SEL	113
#define ICON_HILI_ANY	114
#define ICON_HILI_OP	115
#define ICON_HILI_GO	117
#define ICON_HILI_BUILD	118
#define ICON_HILI_ERR	119
#define ICON_BUTTON_PERSONALBOMBICON

// Descripteur d'une cellule du d�cor.
typedef struct
{
	short	floorChannel;
	short	floorIcon;
	short	objectChannel;
	short	objectIcon;
	short	fog;			// brouillard
	short	rankMove;		// rang dans m_move
	short	workBlupi;		// rang du blupi travaillant ici
	short	fire;
	int		icon;
}
Cellule;
// Cette structure doit �tre la plus petite possible, car
// il en existe un tableau de 100x100 = 10'000 cellules !

// Descripteur d'un blupi anim�.
#define MAXBLUPI	100
#define MAXUSED		50
#define MAXLIST		10

typedef struct
{
	BOOL	bExist;			// TRUE -> utilis�
	BOOL	bHili;			// TRUE -> s�lectionn�

	short	perso;
	short	goalAction;		// action (long terme)
	short	goalPhase;		// phase (long terme)
	POINT	goalCel;		// cellule vis�e (long terme)
	POINT	passCel;		// cellule tranversante

	short	energy;			// �nergie restante

	POINT	cel;			// cellule actuelle
	POINT	destCel;		// cellule destination
	short	action;			// action en cours
	short	aDirect;		// direction actuelle
	short	sDirect;		// direction souhait�e

	POINT	pos;			// position relative � partir de la cellule
	short	posZ;			// d�placement z
	short	channel;
	short	lastIcon;
	short	icon;
	short	phase;			// phase dans l'action
	short	step;			// pas global
	short	interrupt;		// 0=prioritaire, 1=normal, 2=misc
	short	clipLeft;

	int		nbUsed;			// nb de points d�j� visit�s
	char	nextRankUsed;
	POINT	posUsed[MAXUSED];
	char	rankUsed[MAXUSED];

	short	takeChannel;	// objet transport�
	short	takeIcon;

	POINT	fix;			// point fixe (cultive, pont)

	short	jaugePhase;
	short	jaugeMax;
	short	stop;			// 1 -> devra stopper
	short	bArrow;			// TRUE -> fl�che en dessus de blupi
	short	bRepeat;		// TRUE -> r�p�te l'action
	short	nLoop;			// nb de boucles pour GOAL_OTHERLOOP
	short	cLoop;			// boucle en cours
	short	vIcon;			// ic�ne variable
	POINT	goalHili;		// but vis�
	short	bMalade;		// TRUE -> blupi malade
	short	bCache;			// TRUE -> cach� (pas dessin�)
	short	vehicule;		// v�hicule utilis� par blupi, voir (**)
	char	busyCount;
	char	busyDelay;
	char	clicCount;
	char	clicDelay;
	char	reserve2[2];
	short	listButton[MAXLIST];
	POINT	listCel[MAXLIST];
	short	listParam[MAXLIST];
	short	repeatLevelHope;
	short	repeatLevel;
	short	reserve3[88];
}
Blupi;

// (*)	Personnages :
//		0 -> blupi
//		1 -> araign�e
//		2 -> virus
//		3 -> tracks
//		4 -> robot
//		5 -> bombe
//		6 -> d�tonnateur de mine (invisible)
//		7 -> �lectro
//		8 -> disciple (robot2)

// (**)	V�hicule :
//		0 -> � pied
//		1 -> en bateau
//		2 -> en jeep
//		3 -> armure

typedef struct
{
	int   type;
	int   stepAdvance;
	int   stepRecede;
	int   timeStopStart;
	int	  timeStopEnd;
	POINT posStart;
	POINT posEnd;
	POINT posCurrent;
	int   step;
	int	  time;
	int	  phase;
	int	  channel;
	int   icon;
}
MoveObject;


typedef struct
{		
	short 	move_frames_forward;
	short 	move_frames_backward;
	short 	delay_frames_start;
	short 	delay_frames_end;
	POINT 	pos_start;
	POINT 	pos_end;
	POINT	pos;
	short 	move_phase;
	short 	move_timer;
	short	life_time;
	short 	channel;
	short 	icon;
}
PersoType;

typedef struct
{
	short 	move_frames_forward;
	short 	move_frames_backward;
	short 	delay_frames_start;
	short 	delay_frames_end;
	POINT 	pos_start;
	POINT 	pos_end;
	POINT	pos;
	short 	move_phase;
	short 	move_timer;
	short	life_time;
	short 	channel;
	short 	icon;
}
Perso;


// Descripteur d'un d�cor anim�.
#define MAXMOVE		100
#define MOVEICONNB	1000

typedef struct
{
	BOOL	bExist;			// TRUE -> utilis�

	POINT	cel;			// cellule du d�cor
	short	rankBlupi;		// blupi travaillant ici

	BOOL	bFloor;			// TRUE -> floor, FALSE -> object
	short	channel;
	short	icon;
	short	maskChannel;
	short	maskIcon;
	short	phase;			// phase pour pMoves ou pIcon
	short	rankMoves;		// *nb,dx,dy,...
	short	rankIcons;		// *nb,i,i,...

	short	total;			// nb total d'�tapes
	short	delai;			// d�lai entre deux pas
	short	stepY;			// pas vertical *100

	short	cTotal;
	short	cDelai;
}
Move;


class ByeByeObject
{
public:
	int channel;
	int icon;
	double posX;
	double posY;
	double rotation;
	double phase;
	double animationSpeed;
	double rotationSpeed;
	double speedX;

protected:
	ByeByeObject m_byeByeObjects;
};


#define MAXLASTDRAPEAU	50

class CDecor
{
public:
	CDecor();
	~CDecor();

	// Arrange.cpp
	void	ArrangeFloor(POINT cel);
	void	ArrangeMur(POINT cel, int &icon, int index);
	void	ArrangeBuild(POINT cel, int &channel, int &icon);
	void	ArrangeObject(POINT cel);

	BOOL	ArrangeFillTestFloor(POINT cel1, POINT cel2);
	BOOL	ArrangeFillTest(POINT pos);
	void	ArrangeFillPut(POINT pos, int channel, int icon);
	void	ArrangeFillSearch(POINT pos);
	void	ArrangeFill(POINT pos, int channel, int icon, BOOL bFloor);

	void	ArrangeBlupi();

	// Obstacle.cpp
	void	SearchFloor(int rank, int icon, POINT cel, int *pBits);
	void	SearchObject(int rank, int icon, POINT cel, int *pBits);
	void	AjustFloor(int rank, int icon, POINT cel, int *pBits);
	void	AjustObject(int rank, int icon, POINT cel, int *pBits);
	BOOL	IsFreeDirect(POINT cel, int direct, int rank);
	BOOL	IsFreeCelObstacle(POINT cel);
	BOOL	IsFreeCelFloor(POINT cel, int rank);
	BOOL	IsFreeCelGo(POINT cel, int rank);
	BOOL	IsFreeCelHili(POINT cel, int rank);
	BOOL	IsFreeCel(POINT cel, int rank);
	BOOL	IsFreeCelDepose(POINT cel, int rank);
	BOOL	IsFreeCelEmbarque(POINT cel, int rank, int &action, POINT &limit);
	BOOL	IsFreeCelDebarque(POINT cel, int rank, int &action, POINT &limit);
	BOOL	IsFreeJump(POINT cel, int direct, int rank, int &action);
	BOOL	IsFreeGlisse(POINT cel, int direct, int rank, int &action);
	int		DirectSearch(POINT cel, POINT goal);
	void	FlushUsed(int rank);
	void	AddUsedPos(int rank, POINT pos);
	BOOL	IsUsedPos(int rank, POINT pos);
	BOOL	SearchBestBase(int rank, int &action, POINT &newCel, int &direct);
	BOOL	SearchBestPass(int rank, int &action);
	BOOL	IsWorkableObject(POINT cel, int rank);
	BOOL	SearchOtherObject(int rank, POINT initCel, int action,
							  int distMax, int channel,
							  int firstIcon1, int lastIcon1,
							  int firstIcon2, int lastIcon2,
							  POINT &foundCel, int &foundIcon);
	BOOL	SearchOtherDrapeau(int rank, POINT initCel, int distMax,
							   POINT &foundCel, int &foundIcon);
	BOOL	SearchOtherBateau(int rank, POINT initCel, int distMax,
							  POINT &foundCel, int &foundIcon);
	BOOL	IsSpiderObject(int icon);
	BOOL	SearchSpiderObject(int rank, POINT initCel, int distMax,
							   POINT &foundCel, int &foundIcon);
	BOOL	IsTracksObject(int icon);
	BOOL	SearchTracksObject(int rank, POINT initCel, int distMax,
							   POINT &foundCel, int &foundIcon);
	BOOL	IsRobotObject(int icon);
	BOOL	SearchRobotObject(int rank, POINT initCel, int distMax,
							  POINT &foundCel, int &foundIcon,
							  int &foundAction);
	BOOL	IsBombeObject(int icon);
	BOOL	SearchBombeObject(int rank, POINT initCel, int distMax,
							  POINT &foundCel, int &foundIcon);
	BOOL	SearchElectroObject(int rank, POINT initCel, int distMax,
								POINT &foundCel, int &foundIcon);
	BOOL	IsUsineBuild(int rank, POINT cel);
	BOOL	IsUsineFree(int rank, POINT cel);
	BOOL	IsFireCel(POINT cel);
	BOOL	IsVirusCel(POINT cel);
	int		IsBuildPont(POINT &cel, int &iconBuild);
	BOOL	IsBuildBateau(POINT cel, int &direct);
	void	InitDrapeau();
	void	AddDrapeau(POINT cel);
	void	SubDrapeau(POINT cel);
	BOOL	TestDrapeau(POINT cel);

	// DecBlupi.cpp
	void	BlupiFlush();
	int		BlupiCreate(POINT cel, int action, int direct,
						int perso, int energy);
	BOOL	BlupiDelete(POINT cel, int perso=-1);
	void	BlupiDelete(int rank);
	void	BlupiKill(int exRank, POINT cel, int type);
	BOOL	BlupiIfExist(int rank);
	void	BlupiCheat(int cheat);
	void	BlupiActualise(int rank);
	void	BlupiAdaptIcon(int rank);
	void	BlupiPushFog(int rank);
	void	BlupiSound(int rank, int sound, POINT pos, BOOL bStop=FALSE);
	void	BlupiInitAction(int rank, int action, int direct=-1);
	void	BlupiChangeAction(int rank, int action, int direct=-1);
	void	ListFlush(int rank);
	int		ListGetParam(int rank, int button, POINT cel);
	BOOL	ListPut(int rank, int button, POINT cel, POINT cMem);
	void	ListRemove(int rank);
	int		ListSearch(int rank, int button, POINT cel, int &textForButton);
	BOOL	RepeatAdjust(int rank, int button, POINT &cel, POINT &cMem,
						 int param, int list);
	void	GoalStart(int rank, int action, POINT cel);
	BOOL	GoalNextPhase(int rank);
	void	SetTotalTime(int total);
	int		GetTotalTime();
	void	GoalInitJauge(int rank);
	void	GoalInitPassCel(int rank);
	void	GoalAdjustCel(int rank, int &x, int &y);
	BOOL	GoalNextOp(int rank, short *pTable);
	void	GoalUnwork(int rank);
	void	GoalStop(int rank, BOOL bError=FALSE, BOOL bSound=TRUE);
	BOOL	BlupiIsGoalUsed(POINT cel);
	void	BlupiStartStopRayon(int rank, POINT startCel, POINT endCel);
	BOOL	BlupiRotate(int rank);
	BOOL	BlupiNextAction(int rank);
	void	BlupiNextGoal(int rank);
	void	BlupiStep(BOOL bFirst);
	void	BlupiGetRect(int rank, RECT &rect);
	int		GetTargetBlupi(POINT pos);
	void	BlupiDeselect();
	void	BlupiDeselect(int rank);
	void	BlupiSetArrow(int rank, BOOL bArrow);
	void	InitOutlineRect();
	void	BlupiHiliDown(POINT pos, BOOL bAdd=FALSE);
	void	BlupiHiliMove(POINT pos, BOOL bAdd=FALSE);
	void	BlupiHiliUp(POINT pos, BOOL bAdd=FALSE);
	void	BlupiDrawHili();
	int		GetDefButton(POINT cel);
	BOOL	BlupiGoal(int rank, int button, POINT cel, POINT cMem);
	void	BlupiGoal(POINT cel, int button);
	void	BlupiDestCel(int rank);
	BOOL	IsTracksHere(POINT cel, BOOL bSkipInMove);
	BOOL	IsBlupiHereEx(POINT cel1, POINT cel2, int exRank, BOOL bSkipInMove);
	BOOL	IsBlupiHereEx(POINT cel, int exRank, BOOL bSkipInMove);
	BOOL	IsBlupiHere(POINT cel, BOOL bSkipInMove);
	BOOL	IsBlupiHere(POINT cel, int direct, BOOL bSkipInMove);
	void	GetLevelJauge(int *pLevels, int *pTypes);
	BOOL	IsWorkBlupi(int rank);
	void	BlupiGetButtons(POINT pos, int &nb, int *pButtons, int *pErrors, int &perso);
	void	TerminatedInit();
	int		IsTerminated();
	Term*	GetTerminated();

	// DecMove.cpp
	void	MoveFlush();
	int		MoveMaxFire();
	void	MoveFixInit();
	BOOL	MoveCreate(POINT cel, int rankBlupi, BOOL bFloor,
					   int channel, int icon,
					   int maskChannel, int maskIcon,
					   int total, int delai, int stepY,
					   BOOL bMisc=FALSE, BOOL bNotIfExist=FALSE);
	BOOL	MoveAddMoves(POINT cel, int rankMoves);
	BOOL	MoveAddIcons(POINT cel, int rankIcons, BOOL bContinue=FALSE);
	BOOL	MoveStartFire(POINT cel);
	void	MoveProxiFire(POINT cel);
	void	MoveFire(int rank);
	void	MoveStep(BOOL bFirst);
	void	MoveFinish(POINT cel);
	void	MoveFinish(int rankBlupi);
	BOOL	MoveIsUsed(POINT cel);
	BOOL	MoveGetObject(POINT cel, int &channel, int &icon);
	BOOL	MovePutObject(POINT cel, int channel, int icon);

	// DecIO.cpp
	BOOL	Write(int rank, BOOL bUser, int world, int time, int total);
	BOOL	Read(int rank, BOOL bUser, int &world, int &time, int &total);
	BOOL	FileExist(int rank, BOOL bUser, int &world, int &time, int &total);
	void	Flush();

	// DecMap.cpp
	void	MapInitColors();
	POINT	ConvCelToMap(POINT cel);
	POINT	ConvMapToCel(POINT pos);
	BOOL	MapMove(POINT pos);
	void	MapPutCel(POINT pos);
	BOOL	GenerateMap();

	// DecStat.cpp
	void	StatisticInit();
	void	StatisticUpdate();
	int		StatisticGetBlupi();
	int		StatisticGetFire();
	void	StatisticDraw();
	void	GenerateStatictic();
	BOOL	StatisticDown(POINT pos, int fwKeys);
	BOOL	StatisticMove(POINT pos, int fwKeys);
	BOOL	StatisticUp(POINT pos, int fwKeys);
	int		StatisticDetect(POINT pos);

	// Chemin.cpp
	void	CheminMemPos(int exRank);
	BOOL	CheminTestPos(POINT pos, int &rank);
	int		CheminARebours(int rank);
	void	CheminFillTerrain(int rank);
	BOOL	CheminTestDirection(int rank, int pos, int dir,
								int &next, int &ampli,
								int &cout, int &action);
	BOOL	CheminCherche(int rank, int &action);
	BOOL	IsCheminFree(int rank, POINT dest, int button);

	// Decor.cpp
	void	SetShiftOffset(POINT offset);
	POINT	ConvCelToPos(POINT cel);
	POINT	ConvPosToCel(POINT pos, BOOL bMap=FALSE);
	POINT	ConvPosToCel2(POINT pos);

	void	Create(HWND hWnd, CSound *pSound, CPixmap *pPixmap, CNetwork *pNetwork);
	BOOL	LoadImages();
	void	InitGamer();
	BOOL	AddLinkCaisse(int rank);
	void	InitDecor(int channel, int icon);
	void	InitAfterBuild();
	void	SetTime(int time);
	int	    GetTime();
	void	PlayPrepare(BOOL bTest);
	void	BuildPrepare();
	void	Build();
	BOOL	BlitzActif(int celx, int cely);
	void	DrawInfo();
	void	UpdateCaisse();
	POINT	DecorNextAction();
	BOOL	TestPushCaisse(int i, POINT pos, BOOL bPop);
	void	SearchLinkCaisse(int rank, BOOL bPop);
	void	ResetHili();
	BOOL	LoadImages();
	BOOL	LoadBackgroundImages();
	BOOL	TestPushOneCaisse(int i, POINT move, int b);
	void	ClearFog();
	void	ClearFire();
	void	SetBuild(BOOL bBuild);
	void	EnableFog(BOOL bEnable);
	BOOL	GetInvincible();
	void	SetInvincible(BOOL bInvincible);
	BOOL	GetSuper();
	void	SetSuper(BOOL bSuper);
	void	FlipOutline();
	BOOL	PutFloor(POINT cel, int channel, int icon);
	BOOL	PutObject(POINT cel, int channel, int icon);
	BOOL	GetFloor(POINT cel, int &channel, int &icon);
	BOOL	GetObject(POINT cel, int &channel, int &icon);
	BOOL	SetFire(POINT cel, BOOL bFire);

	void	SetCoin(POINT coin, BOOL bCenter=FALSE);
	POINT	GetCoin();
	POINT	GetHome();
	void	MemoPos(int rank, BOOL bRecord);

	void	SetTime(int time);
	int		GetTime();

	void	SetMusic(int music);
	int		GetMusic();

	void	SetSkill(int skill);
	int		GetSkill();

	void	SetRegion(int region);
	int		GetRegion();

	void	SetInfoMode(BOOL bInfo);
	BOOL	GetInfoMode();
	void	SetInfoHeight(int height);
	int		GetInfoHeight();

	int 	GetTargetLevel();
	void	GetBlupiInfo(BOOL bHelico, BOOL bJeep, BOOL bSkate, BOOL bNage);

	char*	GetButtonExist();

	void	BuildPutBlupi();
	void	BuildMoveFloor(int x, int y, POINT pos, int rank);
	void	BuildMoveObject(int x, int y, POINT pos, int rank);
	void	BuildGround(RECT clip);
	void	Build(RECT clip, POINT posMouse);
	void	NextPhase(int mode);

	int		CountFloor(int channel, int icon);
	int		CelOkForAction(POINT cel, int action, int rank,
						   int   icons[4][4],
						   POINT &celOutline1,
						   POINT &celOutline2);
	int		CelOkForAction(POINT cel, int action, int rank);
	int		GetHiliRankBlupi(int nb);
	void	CelHili(POINT pos, int action);
	void	CelHiliButton(POINT cel, int button);
	void	CelHiliRepeat(int list);
	int		GetResHili(POINT posMouse);
	void	HideTooltips(BOOL bHide);

	void	UndoOpen();
	void	UndoClose();
	void	UndoCopy();
	void	UndoBack();
	BOOL	IsUndo();
	BOOL	GetShowSecret();
	BOOL	GetNetPacked();
	BOOL	GetNetMovePredict();
	UINT	GetPhase();
	int		GetMissionTitle();
	void	SetRegion(int region);
	int		GetMusic();
	void	SetMusic(int music);
	void	GetDims(POINT* ptr);
	void	SetDims(POINT dims);
	int		GetLives();
	void	SetLives(int lives);
	void	SetAccessBuild(BOOL build);
	void	SetNetPacked(BOOL net);
	void	SetNetMovePredict(BOOL netmove);
	BOOL	GetNetDebug();
	void	SetMulti(int multi);
	void	SetTeam(int team);
	void	MoveObjectSort();
	void	GetMissionsCleared();
	void	SetDemoState(BOOL demoState);
	
protected:
	BOOL	GetSeeBits(POINT cel, char *pBits, int index);
	int		GetSeeIcon(char *pBits, int index);

protected:
	static int  MAXMOVEOBJECT[200];
	static int	MAXQUART[441];
	HWND		m_hWnd;
	CSound*		m_pSound;
	CPixmap*	m_pPixmap;
    CNetwork*   m_pNetwork;
    MoveObject  m_moveObject[100][100];
    Explo       m_explos[100][100];
    Perso       m_persos[200];
    int         m_input;
    int         m_previousInput;
    POINT       m_cameraPos;
    POINT       m_worldDims;
    POINT       m_selectedCelPos;
	Random		m_random;
    WMessage    m_phase;
    int         m_targetMission;
    char        m_missionTitle[100];
    int         m_nbCases;
	int			m_linkCaisse;
    int         m_caseIndexes[200];
    int         m_nbSomethings;
    int         m_somethingIndexes;
    POINT       m_pos;
    POINT       m_safePos;
	POINT		m_posDecor;
	RECT		m_drawBounds;
    Action      m_action;
    int         m_direction;
    int         m_actionFrameCount;
    POINT       m_velocity;
    Icon4       m_blupiIcon;
	POINT		m_blupiStartPos;
	int			m_blupiStartDir;
	int			m_blupiAction;
	int			m_blupiPhase;
    /*
    undefined
    undefined
    undefined
    undefined
    */
	int			m_decor;
	int			m_bigDecor;
	int			m_decorAction;
    IconChannel m_blupiChannel;
    POINT       m_activeConveyorVelocity;
	int			m_nbRankCaisse;
	int			m_rankCaisse;
	int			m_nbLinkCaisse;
    int         m_activeLiftIndex;
    int         m_blupiChannel;
	BOOL		m_blupiFocus;
    BOOL        m_blupiAir;
    BOOL        m_blupiHelico;
    BOOL        m_blupiOver;
    BOOL        m_blupiJeep;
    BOOL        m_blupiTank;
    BOOL        m_blupiSkate;
    BOOL        m_blupiNage;
    BOOL        m_blupiSurf;
    BOOL        m_bInWind;
    BOOL        m_blupiSuspend;
    BOOL        m_blupiJumpAie;
    BOOL        m_blupiShield;
    BOOL        m_blupiPower;
    BOOL        m_blupiCloud;
    BOOL        m_blupiHide;
	BOOL        m_blupiInvert;
    BOOL        m_blupiBalloon;
    BOOL        m_blupiEcrase;
	BOOL		m_blupiMotorHigh;
	int			m_blupiMotorSound;
	POINT		m_blupiPosHelico;
	int			m_blupiActionOuf;
	int			m_blupiTimeNoAsc;
	int			m_blupiTimeMockery;
	double		m_blupiVitesseX;
	double		m_blupiVitesseY;
	POINT		m_blupiValidPos;
	BOOL		m_blupiFront;
	int			m_blupiNoBarre;
	int			m_blupiFifoNb;
	CJauge		m_jauges;
	BOOL		m_bFoundCle;
	BOOL		m_bPause;
	int			m_blupiTimeFire;
	int			m_voyageIcon;
	int			m_blupiBullet;
	int			m_blupiCle;
	int			m_blupiPerso;
	int			m_blupiDynamite;
	int			m_nbTresor;
	int			m_totalTresor;
	int			m_goalPhase;
	POINT		m_scrollPoint;
	POINT		m_scrollAdd;
	int			m_nbVies;
    BOOL        m_bUseSafePosition;
    BOOL        m_bIsTerminating;
	POINT		m_blupiPos;
	int			m_blupiDir;
	int			m_lastDecorIcon;
    int         m_glue;
    int         m_keys;
    int         m_personalBombs;
    int         m_dynamite;
    int         m_powerEnergy;
    int         m_queuedActionFrames;
    Action      m_queuedAction;
    int         m_nbSafePositions;
    POINT       m_safePositions[13];
    int         m_bMulti;
    int         m_team;
    int         m_netPacketsSent;
    int         m_netPacketsSent2;
    int         m_netPacketsRecieved;
    int         m_netPacketsRecieved2;
    SoundEvent  m_soundEvents[20];
    int         m_soundEventIndex1;
    char        m_messages[4][100];
    int         m_air;
    int         m_energyUnused;
    BOOL        m_bHelicopterFlying;
    BOOL        m_bHelicopterStationary;
    BOOL        m_bCarMoving;
    BOOL        m_bCarStationary;
    BOOL        m_bWorldComplete;
    BOOL        m_bPrivate;
    BOOL        m_bAllMissions;		// opendoors
    BOOL        m_bInvincible;		// megablupi
    BOOL        m_bShowSecret;  	// showsecret
    BOOL        m_bAccessBuild; 	// xmission/xnjttjpo
    BOOL        m_bNetPacked;		// netpacked
    BOOL        m_bNetMovePredict;  // ynosmooth
    BOOL        m_bNetDebug;		// znetdebug
	BOOL		m_demoState;
    int         m_mission;
    BYTE        m_missionsCleared[180];
    BYTE        m_worldsCleared[20];
    int         m_lives;
    int         m_chestsCollected;
    int         m_chestsTotal;
    POINT       m_cameraTargetPos;
    POINT       m_cameraTargetOffset;
    int         m_flyupIcon;
    int         m_flyupChannel;
    int         m_flyupFrameCount;
    int         m_flyupFrameTotal;
    POINT       m_flyupStartPos;
    POINT       m_flyupEndPos;
	BOOL 		m_bScreenShake;
	int 		m_screenShakeIndex;
	int 		m_menuSelections[112];
	BYTE 		m_overloadProtection[100000];
	Cellule*	m_pUndoDecor;
	Cellule		m_decor[MAXCELX/2][MAXCELY/2];
	short		m_rankBlupi[MAXCELX][MAXCELY];
	Blupi		m_blupi[MAXBLUPI];
	Move		m_move[MAXMOVE];
	POINT		m_celCoin;			// cellule sup/gauche
	POINT		m_celHome;			// pour touche Home
	POINT		m_celHili;
	POINT		m_celOutline1;
	POINT		m_celOutline2;
	POINT		m_shiftOffset;
	int			m_iconHili[4][4];
	int			m_rankHili;			// rang du blupi vis�
	BOOL		m_bHiliRect;
	POINT		m_p1Hili;			// coins rectangle de s�lection
	POINT		m_p2Hili;
	int			m_shiftHili;
	int			m_nbBlupiHili;		// nb de blupi s�lectionn�s
	int			m_rankBlupiHili;	// rang blupi s�lectionn�
	BOOL		m_bFog;				// TRUE -> brouillard (jeu)
	BOOL		m_bBuild;			// TRUE -> construction
	BOOL		m_bInvincible;		// TRUE -> cheat code
	BOOL		m_bSuper;			// TRUE -> cheat code
	short		m_colors[100];
	int			m_time;				// temps relatif global
	int			m_timeConst;		// temps relatif global constant
	int			m_timeFlipOutline;	// temps quand basculer mode outline
	int			m_totalTime;		// temps total pass� sur une partie
	int			m_phase;			// phase pour la carte
	POINT		m_celArrow;			// cellule avec fl�che
	BOOL		m_bOutline;
	BOOL		m_bGroundRedraw;
	char		m_buttonExist[MAXBUTTON];
	int			m_statNb;			// nb de statistiques
	int			m_statFirst;		// premi�re statistique visible
	int			m_bStatUp;			// fl�che up statistique
	int			m_bStatDown;		// fl�che down statistique
	int			m_statHili;			// statistique survol�e
	BOOL		m_bStatRecalc;		// TRUE -> recalcule les statistiques
	BOOL		m_bStatRedraw;		// TRUE -> redessine les statistiques
	int			m_nbStatHach;		// nb de hachures
	int			m_nbStatHachBlupi;	// hachures occup�es par blupi
	int			m_nbStatHachPlanche;// hachures occup�es par planches
	int			m_nbStatHachTomate;	// hachures occup�es par tomates
	int			m_nbStatHachMetal;	// hachures occup�es par m�tal
	int			m_nbStatHachRobot;	// hachures occup�es par robot
	int			m_nbStatHome;		// nb de maisons
	int			m_nbStatHomeBlupi;	// maisons occup�es par blupi
	int			m_nbStatRobots;		// nb d'ennemis
	int 		m_term;				// conditions pour gagner
	int			m_winCount;			// compteur avant gagn�
	int			m_winLastHachBlupi;	// dernier nombre atteint
	int			m_winLastHachPlanche;// dernier nombre atteint
	int			m_winLastHachTomate;// dernier nombre atteint
	int			m_winLastHachMetal;	// dernier nombre atteint
	int			m_winLastHachRobot;	// dernier nombre atteint
	int			m_winLastHome;		// dernier nombre atteint
	int			m_winLastHomeBlupi;	// dernier nombre atteint
	int			m_winLastRobots;	// dernier nombre atteint
	int			m_music;			// num�ro musique
	int			m_region;			// num�ro r�gion (*)
	int			m_lastRegion;		// num�ro derni�re r�gion
	int			m_blupiHere;
	POINT		m_lastDrapeau[MAXLASTDRAPEAU];
	BOOL		m_bHideTooltips;	// TRUE -> menu pr�sent
	char		m_text[50];
	POINT		m_textLastPos;
	int			m_textCount;
	int			m_skill;
	BOOL		m_bInfo;
	int			m_infoHeight;
	POINT		m_memoPos[4];

	BYTE		m_cheminWork[MAXCELX*MAXCELY];
	int			m_cheminNbPos;
	POINT		m_cheminPos[MAXBLUPI*2];
	int			m_cheminRank[MAXBLUPI*2];

	BOOL		m_bFillFloor;
	int			m_fillSearchChannel;
	int			m_fillSearchIcon;
	int			m_fillPutChannel;
	int			m_fillPutIcon;
	char*		m_pFillMap;

    int SetBlupiChannel();
    int GetBlupiChannel();
	int GetPersonalBombIcon();
    int GetTargetLevel(int mission);
	BOOL GetShowSecret();
    void SetShowSecret(BOOL secret);
	void GetBlupiHitbox(RECT *out, POINT pos);
};

// (*)	R�gions :
//		0 -> normal
//		1 -> palmier
//		2 -> hiver
//		3 -> sapin

/////////////////////////////////////////////////////////////////////////////

POINT GetCel (int x, int y);
POINT GetCel (POINT cel, int x, int y);
BOOL IsValid (POINT cel);
POINT GetVector (int direct);
extern int table_multi_goal[];
extern short table_actions[];











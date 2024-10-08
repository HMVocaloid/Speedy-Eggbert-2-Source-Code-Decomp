// Decor.h

#pragma once

using namespace std;

#include <windows.h>
#include <minwindef.h>
#include <windef.h>
#include "def.h"
#include "network.h"
#include "jauge.h"


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
#define ICON_BUTTON_PERSONALBOMBICON 108
#define MAXMOVEOBJECT  200
 //#define MAXQUART  441
#define BLUPIFLOOR 2
#define BLUPIOFFY 4 + BLUPIFLOOR
#define BLUPISURF 12
#define BLUPISUSPEND 12
#define OVERHEIGHT 80
#define MAXQUART 441

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
	short	icon;
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
	short icon;
	short type;
}
Icon4;

typedef struct
{
	short channel;
	short blupiChannel;
	short itemChannel;
}
IconChannel;

typedef enum
{
	icon_element_chest = 6,
	icon_element_egg = 21,
	icon_element_blupiburn = 40,
	icon_blupi_life = 48,
	icon_button_personalbombyellow = 108,
	icon_element_glueball = 176,
	icon_element_gluepile = 177,
	icon_element_keyred = 215,
	icon_element_keygreen = 222,
	icon_element_keyblue = 229,
	icon_element_blupiangel = 230,
	icon_element_dynamite = 252
}
IconItem;

typedef enum
{
	STEP_STOPSTART = 1,
	STEP_ADVANCE = 2,
	STEP_STOPEND = 3,
	STEP_RECEDE = 4
}
MoveObjectStep;

typedef enum
{
	TYPE_EMPTY,
	TYPE_ASCENSEUR,
	TYPE_BOMBEDOWN,
	TYPE_BOMBEUP,
	TYPE_CAISSE,
	TYPE_GOAL,
	TYPE_CLE,
	TYPE_BLUPIHELICO,
	TYPE_BLUPITANK,
	TYPE_BALLE,
	TYPE_DOOR
}
MoveObjectType;

typedef enum
{
	WM_NOMUSIC = 1044
}
WMessage;

typedef enum
{
	DIR_LEFT,
	DIR_RIGHT
}
Direction;


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

typedef struct
{
	short	majRev;
	short	minRev;
	BOOL	bDemo;
	short	reserve1[98];
	POINT   posDecor;
	POINT	dimDecor;
	short	world;
	short	music;
	short	region;
	short	reserve2[50];
	POINT	blupiPos[100];
	int		blupiDir[100];
	char	libelle[100];
	short	reserve3[196];
}
DescFile;

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
	void	MoveStep();
	void	MoveFinish(POINT cel);
	void	MoveFinish(int rankBlupi);
	BOOL	MoveIsUsed(POINT cel);
	BOOL	MoveGetObject(POINT cel, int &channel, int &icon);
	BOOL	MovePutObject(POINT cel, int channel, int icon);

	// DecIO.cpp
	BOOL	Write(int gamer, int mission, char* rank);
	BOOL	Read(int gamer, int rank, BOOL* pbMission, BOOL* pbPrivate);
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
	void	InitDecor();
	void	InitAfterBuild();
	void	PlayPrepare(BOOL bTest);
	void	BuildPrepare();
	void	Build(RECT rect);
	BOOL	BlitzActif(int celx, int cely);
	void	DrawInfo();
	void	UpdateCaisse();
	POINT	DecorNextAction();
	void	SetInput(UINT input);
	void	SetSpeedX(double speed);
	void	SetSpeedY(double speed);
	int		SoundEnviron(int sound, int obstacle);
	void	StopSound(Sound sound);
	void	AdaptMotorVehicleSound();
	BOOL	TestPushCaisse(int i, POINT pos, BOOL bPop);
	void	SearchLinkCaisse(int rank, BOOL bPop);
	void	ResetHili();
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
	void	AdaptDoors(BOOL bPrivate, int mission);

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
	BOOL	GetNetPacked();
	BOOL	GetNetMovePredict();
	UINT	GetPhase();
	char*   GetMissionTitle();
	void	GetDims(POINT* ptr);
	void	SetDims(POINT dims);
	int		GetNbVies();
	void	SetNbVies(int lives);
	BOOL	GetPause();
	void	SetPause(BOOL bPause);
	void	GetDoors(int doors);
	void	InitalizeDoors(BYTE* doors);
	void	SetAllMissions(BOOL CheatDoors);
	void	CheatAction(int cheat, MoveObject moveObject);
	void	SetAccessBuild(BOOL build);
	void	SetNetPacked(BOOL net);
	void	SetNetMovePredict(BOOL netmove);
	BOOL	GetNetDebug();
	void	SetCelPosFromScreenPos(POINT cel);
	void	SetMulti(int multi);
	void	SetTeam(int team);
	void	MoveObjectSort();
	BOOL	BlupiIsGround();
	RECT	BlupiRect(POINT pos);
	void	BlupiAdjust();
	BOOL	BlupiBloque(POINT pos, int dir);
	void	BlupiDead(int action1, int action2);
	POINT	GetPosDecor(POINT pos);
	void	BlupiAddFifo(POINT pos);
	void	MoveObjectPlouf(POINT pos);
	void	MoveObjectTiplouf(POINT pos);
	int		GetBlupiChannelStandard();
	void	MoveObjectBlup(POINT pos);
	int		IsWorld(POINT pos);
	void	ActiveSwitch(BOOL bState, POINT cel);
	int		GetTypeBarre(POINT pos);
	BOOL	IsLave(POINT pos);
	BOOL	IsPiege(POINT pos);
	BOOL	IsGoutte(POINT pos, BOOL bAlways);
	BOOL	IsScie(POINT pos);
	BOOL	IsSwitch(POINT pos, POINT celSwitch);
	BOOL	IsEcraseur(POINT pos);
	BOOL	IsBlitz(POINT pos, BOOL bAlways);
	BOOL	IsRessort(POINT pos);
	BOOL	IsTemp(POINT pos);
	BOOL	IsBridge(POINT pos, POINT celBridge);
	int		IsDoor(POINT pos, POINT celPorte);
	int		IsTeleporte(POINT pos);
	BOOL	SearchTeleporte(POINT pos, POINT newpos);
	BOOL	IsNormalJump(POINT pos);
	BOOL	IsSurfWater(POINT pos);
	BOOL	IsDeepWater(POINT pos);
	BOOL	IsOutWater(POINT pos);
	BOOL	IsPassIcon(int icon);
	BOOL	IsBlocIcon(int icon);
	void	FlushBalleTraj();
	void	SetBalleTraj(POINT pos);
	BOOL	IsBalleTraj(POINT pos);
	void	FlushMoveTraj();
	void	SetMoveTraj(POINT pos);
	BOOL	IsMoveTraj(POINT pos);
	int		SearchDistRight(POINT pos, POINT dir, int type);
	BOOL	IsVentillo(POINT pos);
	void	StartSploutchGlu(POINT pos);
	int		ObjectStart(POINT pos, int type, int speed);
	BOOL	ObjectDelete(POINT pos, int type, int something);
	void	ModifDecor(POINT pos, int icon, BOOL bMulti);
	void	MoveObjectStep();
	void	MoveObjectStepLine(int i);
	void	MoveObjectStepIcon(int i);
	void	MoveObjectFollow(POINT pos);
	int		MoveObjectDetect(POINT pos, BOOL bNear);
	int		MoveAscenseurDetect(POINT pos, int height);
	int		MoveChargeDetect(POINT pos);
	int		MovePersoDetect(POINT pos);
	int		MoveObjectDelete(POINT cel);
	int		MoveObjectFree();
	int		SortGetType(int type);
	int		MoveObjectSearch(POINT pos);
	int		MoveObjectSearch(POINT pos, int type);
	void	VoyageInit(POINT start, POINT end, int icon, int channel);
	void	VoyageStep();
	BOOL	IsFloatingObject(int i);
	BOOL	IsRightBorder(int x, int y, int dx, int dy);
	BOOL	IsFromage(int x, int y);
	BOOL	IsGrotte(int x, int y);
	void	AdaptMidBorder(int x, int y);
	void	PosSound(POINT pos);
	void	AdaptBorder(POINT cel);
	void	GetMissionPath(char* str, int user, int mission, BOOL bUser);
	void	DynamiteStart(int i, int dx, int dy);
	int		AscenseurDetect(RECT rect, POINT oldpos, POINT newpos);
	void	BlupiSearchIcon();
	void	AscenseurVertigo(int i, BOOL bVertigoLeft, BOOL bVertigoRight);
	BOOL	AscenseurShift(int i);
	void	AscenseurSynchro(int i);
	int		CaisseInFront();
	int		CaisseGetMove(int max);
	int		MockeryDetect(POINT pos);
	BOOL	BlupiElectro(POINT pos);
	void	BlupiStep();
	POINT   ScreenPosToCelPos(POINT* pos, POINT cel);
	BOOL	DecorDetect(RECT rect);
	BOOL	DecorDetect(RECT rect, BOOL bCaisse);
	BOOL	SearchDoor(int n, POINT cel, POINT blupi);
	BOOL	SearchGold(int n, POINT cel);
	BOOL	TestPath(RECT rect, POINT start, POINT end);
	void	PlaySoundB(int sound, POINT pos, int net);
	void	OpenDoorsTresor();
	void	OpenDoor(POINT cel);
	void	OpenDoorsWin();
	void	OpenGoldsWin();
	void	DoorsLost();
	void	GetMissionsCleared();
	void	SetDemoState(BOOL demoState);
	BOOL	CurrentWrite(int gamer, int mission, BOOL bUser);
	BOOL	CurrentRead(int gamer, int mission, BOOL bUser);
	void	SetJoystickEnable(BOOL bJoystick);
	BOOL	GetShowSecret();
	BOOL	MissionStart(int gamer, int rank, BOOL bUser);

	void	MemorizeDoors(BYTE* doors);
	void	NotifPush(char* str);
	void	DeleteCel(int celX, int celY);
	void	SetGamerName(const char* playerName);
	BOOL	SomethingMissionPath(int user, int mission, BOOL bUser);
	void	MoveObjectPriority(int i);
	void	FindAndSetMenus(int menuIndex, int menuType);
	void	ChangePhase(UINT phase);


	// Network Related Functions
	void	NetMessageIndexFlush();
	void	NotifFlush();
	void	NetDataFlush();
	void	NetPlaySound(short channel, POINT pos);
	void	NetStopCloud(int rank);
	BOOL	NetMessagePush(NetMessage* message);
	BOOL	DrawMap(BOOL bPlay, int player);
	void	NetSendData(BYTE bufferSize, UCHAR send);
	void	NetPlayerCollide(POINT pos, int* out);
	void	TreatNetData();
	void	OutputNetDebug(char* text);
	void	NotifStep();
	void	NotifPop();
	void	SetNetDebug(BOOL bNetDebug);


protected:
	BOOL	GetSeeBits(POINT cel, char *pBits, int index);
	int		GetSeeIcon(char *pBits, int index);

protected:
	HWND		m_hWnd;
	CSound*		m_pSound;
	CPixmap*	m_pPixmap;
    CNetwork*   m_pNetwork;
	NetMessage	m_netMessages[20];
    MoveObject  m_moveObject[100][100];
    int         m_input;
	int			m_bJoystick;
    int         m_previousInput;
	int			m_blupiTimeShield;
	POINT		m_blupiPosMagic;
	POINT		m_blupiLastPos;
	int			m_balleTraj[1300];
	POINT		m_blupiVector;
	int			m_blupiSec;
	BOOL		m_bSuperBlupi;
	int			m_blupiRealRotation;
	int			m_blupiTransport;
	int			m_detectIcon = -1;
    POINT       m_cameraPos;
	int			m_moveTraj[1300];
	POINT		m_dimDecor;
	POINT		m_dimCelHili;
	BOOL		m_blupiRestart;
    POINT       m_worldDims;
    POINT       m_selectedCelPos;
    int         m_phase;
	int			m_voyagePhase;
	POINT		m_sucettePos;
	int			m_sucetteType;
	double		m_blupiLastSpeedY;
	int			m_blupiTimeOuf;
	double		m_blupiLastSpeedX;
	POINT		m_posCelHili;
	int			m_2ndPositionCalculationSlot;
	int			m_voyageTotal;
	POINT		m_voyageStart;
	POINT		m_voyageEnd;
	int			m_voyageChannel;
    int         m_targetMission;
    char        m_missionTitle[100];
    int         m_nbCases;
	int			m_linkCaisse[MAXMOVEOBJECT];
	POINT		m_blupiFifoPos[10];
    int         m_caseIndexes[200];
    int         m_nbSomethings;
	int			m_blupiOffsetY;
    int         m_somethingIndexes;
    POINT       m_pos;
    POINT       m_safePos;
	POINT		m_posDecor;
	RECT		m_drawBounds;
	BYTE 		m_doors[200];
    int         m_action;
    int         m_direction;
    int         m_actionFrameCount;
    POINT       m_velocity;
    Icon4       m_blupiIcon;
	POINT		m_blupiStartPos[4];
	int			m_blupiStartDir[4];
	int			m_blupiAction;
	BOOL		m_bCheatDoors;
	int			m_blupiPhase;
    /*
    undefined
    undefined
    undefined
    undefined
    */
	Cellule		m_decor[MAXCELX / 2][MAXCELY / 2];
	Cellule		m_bigDecor[100][100];
	int			m_decorAction;
	int			m_blupiLevel;
    IconChannel m_blupiChannel;
	int			m_keyPress;
    POINT       m_activeConveyorVelocity;
	int			m_decorPhase;
	int			m_nbRankCaisse;
	int			m_rankCaisse[MAXMOVEOBJECT];
	int			m_nbLinkCaisse;
    int         m_activeLiftIndex;
	double		m_blupiSpeedX;
	double		m_blupiSpeedY;
	BOOL		m_blupiFocus;
    BOOL        m_blupiAir;
    BOOL        m_blupiHelico;
    BOOL        m_blupiOver;
    BOOL        m_blupiJeep;
	BOOL		m_bJeepMarch;
	BOOL		m_bJeepStop;
    BOOL        m_blupiTank;
    BOOL        m_blupiSkate;
    BOOL        m_blupiNage;
    BOOL        m_blupiSurf;
    BOOL        m_bInWind;
	BOOL		m_blupiVent;
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
	CJauge		m_jauges[2];
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
	int			m_lastDecorIcon[200];
    int         m_glue;
    int         m_keys;
    int         m_personalBombs;
    int         m_dynamite;
    int         m_powerEnergy;
    int         m_queuedActionFrames;
    int         m_nbSafePositions;
    POINT       m_safePositions[13];
    int         m_bMulti;
    int         m_team;
    int         m_netPacketsSent;
    int         m_netPacketsSent2;
    int         m_netPacketsRecieved;
    int         m_netPacketsRecieved2;
	POINT		m_netPositions[4];
	Icon4		m_netIcons[4];
	int			m_netPlayerPacketsRecieved[4];
	int			m_netPlayerPacketsRecieved2[4];
	int			m_bNetTimeSincePacket[4];
	POINT		m_netVitesses[4];
	POINT		m_netPacketPosition;
	Icon4		m_netPacketIcon;
    NamedGUID   m_netEvents[20];
    int         m_netEventIndex1;
	int			m_netEventIndex2;
	int			m_netEventIndex3;
	int			m_netMessageIndex1;
	int			m_netMessageIndex2;
	int			m_netMessageIndex3;
	int			m_menuType;
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
	char		m_notifText[4][100];
	int			m_notifTime;
	int 		m_menuSelections[112];
	BYTE 		m_overloadProtection[100000];
	Cellule*	m_pUndoDecor;
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
	BOOL		m_bSuper;			// TRUE -> cheat code
	short		m_colors[100];
	int			m_time;				// temps relatif global
	int			m_timeConst;		// temps relatif global constant
	int			m_timeFlipOutline;	// temps quand basculer mode outline
	int			m_totalTime;		// temps total pass� sur une partie
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
	int GetBlupiChannelActual();
	int GetIconPerso();
    int GetTargetLevel(int mission);
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











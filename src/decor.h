// Decor.h
#pragma once

#include "DEF.H"
#include "JAUGE.H"
#include "SOUND.H"
#include "PIXMAP.H"
#include "network.h"

/////////////////////////////////////////////////////////////////////////////

#define MAXNETMESSAGE 20
#define MAXMOVEOBJECT	200
#define MAXNOTIF 4
#define MAXNETPLAYER 4
#define MAXPLAYER 4

#define MAXQUART		441
#define SCROLL_SPEED	8
#define SCROLL_MARGX	80
#define SCROLL_MARGY	40

#define BLUPIFLOOR		2
#define BLUPIOFFY		4 + BLUPIFLOOR
#define BLUPISURF		12
#define BLUPISUSPEND	12
#define OVERHEIGHT		80

#define TEXTDELAY	   10 // tooltip popup delay
#define NOTIFDELAY		200

typedef struct
{
	short icon;
}
Cellule;

typedef struct
{
	short   type;
	short   stepAdvance;
	short   stepRecede;
	short   timeStopStart;
	short	timeStopEnd;
	short	unknown1;
	POINT	posStart;
	POINT	posEnd;
	POINT	posCurrent;
	short	step;
	short	time;
	short	phase;
	short	channel;
	short	icon;
	short	unknown2;
}
MoveObject;

typedef struct
{
	char type;
	char data1;
	short x;
	short y;
	short channel;
}
NetMessage;

typedef struct
{
	short majRev;
	short minRev;
	BOOL  bDemo;
	short reserve1[98];
	POINT posDecor;
	POINT dimDecor;
	short world;
	short music;
	short region;
	short reserve2[50];
	POINT blupiPos[MAXPLAYER];
	int	  blupiDir[MAXPLAYER];
	char  libelle[100];
	short reserve3[196];
}
DescFile;

class CDecor
{
public:
	CDecor();
	~CDecor();

	// Decor.cpp
	void	Create(HWND hWnd, CSound *pSound, CPixmap *pPixmap,
		CNetwork *pNetwork);
	BOOL	LoadImages();
	void	InitGamer();
	void	InitDecor();
	void	SetTime(int time);
	int	    GetTime();
	void	PlayPrepare(BOOL bTest);
	void	BuildPrepare();
	int		IsTerminated();
	void	MoveStep();
	int		GetBlupiChannelStandard();
	int		GetBlupiChannelActual();
	int		GetIconPerso();
	void	Build(RECT rect);
	void	DrawInfo();
	POINT	DecorNextAction();
	void	SetInput(int keys);
	void	SetJoystickEnable(BOOL bJoystick);
	void	SetDemoPlay(BOOL param_1);
	void	PlaySound(int sound, POINT pos, BOOL bLocal);
	void	PlaySound(int sound, POINT pos); // hack
	void	StopSound(int sound);
	void	AdaptMotorVehicleSound(POINT pos);
	void	VehicleSoundsPhase(int phase);

	int		GetRegion();
	void	SetRegion(int region);
	int		GetMusic();
	void	SetMusic(int music);
	POINT	GetDim();
	void	SetDim(POINT dim);
	int		GetNbVies();
	void	SetNbVies(int nbVies);
	BOOL	GetPause();
	void	SetPause(BOOL bPause);
	void	InitializeDoors(BYTE *doors);
	void	MemorizeDoors(BYTE* doors);
	void	SetAllMissions(BOOL bAllMissions);
	void	CheatAction(int cheat);
	BOOL	GetSuperBlupi();
	void	SetSuperBlupi(BOOL bSuperBlupi);
	BOOL	GetDrawSecret();
	void	SetDrawSecret(BOOL bDrawSecret);
	void	SetBuildOfficialMissions(BOOL bBuildOfficialMissions);
	BOOL	GetNetPacked();
	void	SetNetPacked(BOOL bNetPacked);
	BOOL	GetNetMovePredict();
	void	SetNetMovePredict(BOOL bNetMovePredict);
	BOOL	GetNetDebug();
	void	SetNetDebug(BOOL bNetDebug);
	void	OutputNetDebug(char* text);
	void	SetMulti(BOOL bMulti);
	void	SetTeam(int team);
	POINT	VoyageGetPosVie(int nbVies);
	void	VoyageInit(POINT start, POINT end, int icon, int channel);
	void	VoyageStep();
	void	VoyageDraw();
	BOOL	DrawMap(BOOL bPlay, int team);

	// DecBlock.cpp
	BOOL	BlitzActif(POINT cel);
	int		SoundEnviron(int sound, int obstacle);
	int		IsWorld(POINT pos);
	void	ActiveSwitch(BOOL bState, POINT cel);
	int	GetTypeBarre(POINT pos);
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
	BOOL	IsSurfWater(POINT pos);
	BOOL	IsDeepWater(POINT pos);
	BOOL	IsOutWater(POINT pos);
	BOOL	IsPassIcon(int icon);
	BOOL	IsBlocIcon(int icon);
	BOOL	IsVentillo(POINT pos);
	void	ModifDecor(POINT pos, int icon, BOOL bMulti=TRUE);
	BOOL	IsRightBorder(POINT cel, POINT offset);
	BOOL	IsFromage(POINT cel);
	BOOL	IsGrotte(POINT cel);
	void	AdaptMidBorder(POINT cel);
	void	AdaptBorder(POINT cel);

	// DecDesign.cpp
	POINT	ScreenPosToCelPos(POINT pos);
	void	SetCelPosFromScreenPos(POINT pos);
	void	SetFieldCC38AndStuff(int _foo, int _bar);
	void	DeleteCel(POINT cel);
	void	PlaceMenuItem(short *pCel, int *pTable, int lastIndex, BYTE flags, int currentIcon, BOOL bRand);
	void	PlaceItemFromMenu1(POINT cel, int index, BYTE flags, int currentIcon);
	void	PlaceItemFromMenu2(POINT cel, int index, BYTE flags, int currentIcon);
	void	PlaceItemFromMenu3(POINT cel, int index, BYTE flags, int currentIcon);
	void	PlaceItemFromMenu4(POINT cel, int index, BYTE flags, int currentIcon);
	void	PlaceItemFromMenu5(POINT cel, int index, BYTE flags, int currentIcon);
	void	PlaceItemFromMenu6(POINT cel, int index, BYTE flags, int currentIcon);
	void	PlaceItemFromMenu7(POINT cel, int index, BYTE flags, int currentIcon);
	void	PlaceItemFromMenu8(POINT cel, int index, BYTE flags, int currentIcon);
	void	PlaceItemFromMenu9(POINT cel, int index, BYTE flags, int currentIcon);
	void	PlaceItemFromMenu10(POINT cel, int index, BYTE flags, int currentIcon);
	char*	GetMissionTitle();
	void	SetMissionTitle(char *str);

	// DecBlupi.cpp
	void	BlupiSearchIcon();
	BOOL	BlupiIsGround();
	RECT	BlupiRect(POINT pos);
	void	BlupiAdjust();
	BOOL	BlupiBloque(POINT pos, int dir);
	void	BlupiStep();
	void	BlupiDead(int action, int action2);
	POINT	GetPosDecor(POINT pos);
	void	BlupiAddFifo(POINT pos);
	BOOL	DecorDetect(RECT rect, BOOL bCaisse=TRUE);
	void	GetBlupiInfo(BOOL *pbHelico, BOOL *pbJeep, BOOL *pbSkate,
		BOOL *pbNage);

	// DecMove.cpp
	BOOL	TestPath(RECT rect, POINT start, POINT end);
	void	MoveObjectPollution();
	void	MoveObjectPlouf(POINT pos);
	void	MoveObjectTiplouf(POINT pos);
	void	MoveObjectBlup(POINT pos);
	void	FlushBalleTraj();
	void	SetBalleTraj(POINT pos);
	BOOL	IsBalleTraj(POINT pos);
	void	FlushMoveTraj();
	void	SetMoveTraj(POINT pos);
	BOOL	IsMoveTraj(POINT pos);
	int		SearchDistRight(POINT pos, POINT dir, int type);
	void	StartSploutchGlu(POINT pos);
	BOOL	ObjectStart(POINT pos, int type, int speed);
	BOOL	ObjectStart(POINT pos, int type, int speed, BOOL bMulti);
	BOOL	ObjectDelete(POINT pos, int type);
	void	MoveObjectStep();
	void	MoveObjectStepLine(int i);
	void	MoveObjectStepIcon(int i);
	void	DynamiteStart(int i, int dx, int dy);
	int		AscenseurDetect(RECT rect, POINT oldpos, POINT newpos);
	void	AscenseurVertigo(int i, BOOL *pbVertigoLeft, BOOL *pbVertigoRight);
	BOOL	AscenseurShift(int i);
	void	AscenseurSynchro(int i);
	void	UpdateCaisse();
	BOOL	TestPushCaisse(int i, POINT pos, BOOL bPop);
	BOOL	TestPushOneCaisse(int i, POINT move, int b);
	void	SearchLinkCaisse(int rank, BOOL bPop);
	BOOL	AddLinkCaisse(int rank);
	int		CaisseInFront();
	int		CaisseGetMove(int max);
	BOOL	MockeryDetect(POINT pos);
	BOOL	BlupiElectro(POINT pos);
	void	MoveObjectFollow(POINT pos);
	int		MoveObjectDetect(POINT pos, BOOL *pbNear);
	int		MoveAscenseurDetect(POINT pos, int height);
	int		MoveChargeDetect(POINT pos);
	int		MovePersoDetect(POINT pos);
	int		MoveBalleDetect(POINT pos);
	int		MoveObjectDelete(POINT pos);
	int		MoveObjectFree();
	int		SortGetType(int type);
	void	MoveObjectSort();
	void	MoveObjectPriority(int i);
	int		MoveObjectSearch(POINT pos, int type);

	// DecNet.cpp
	void	NetStopCloud(int rank);
	void	NetPlaySound(short channel, POINT pos);
	void	NetStopSound(short channel);
	void	NetDataFlush();
	void	NetFUN_155e0(BYTE _foo, short _bar);
	void	TreatNetData();
	void	DoNetSmooth(int player);
	void	NetAdjustToLift();
	void	FUN_15da0(int rank, short step);
	void	NetPlayerCollide(POINT pos, int *out);
	void	NetMessageIndexFlush();
	BOOL	NetMessagePush(NetMessage *message);
	BOOL	NetMessagePop(NetMessage *message);
	void	NotifFlush();
	void	NotifPop();
	void	NotifPush(char *str);
	void	NotifStep();

	// DecIO.cpp
	void	GetMissionPath(char *out, int gamer, int mission, BOOL bUser);
	BOOL	Write(int gamer, int mission, BOOL bUser);
	BOOL	Read(int gamer, int mission, BOOL bUser);
	BOOL	SomethingMissionPath(int gamer, int mission, BOOL bUser);
	BOOL	MissionStart(int gamer, int mission, BOOL bUser);
	BOOL	CurrentRead(int gamer, int mission, BOOL *pbMission, BOOL *pbPrivate);
	BOOL	CurrentWrite(int gamer, int mission, char* param3);
	BOOL	DeleteMission(int user, int mission, BOOL bUser);

	BOOL	SearchWorld(int world, POINT *blupi, int *dir);
	BOOL	SearchDoor(int n, POINT *cel, POINT *blupi);
	void	AdaptDoors(BOOL bPrivate, int mission);
	void	OpenDoorsTresor();
	void	OpenDoor(POINT cel);
	void	OpenDoorsWin();
	void	OpenGoldsWin();
	void	DoorsLost();
	void	InitalizeDoors(BYTE* doors);

	inline BOOL IsValidCel(POINT cel);
	inline void MoveObjectCopy(MoveObject src, MoveObject dest);
	inline void StopVehicleSound();

protected:
	HWND		m_hWnd;
	CSound*		m_pSound;
	CPixmap*	m_pPixmap;
	CNetwork*	m_pNetwork;
	Cellule		m_decor[MAXCELX][MAXCELY];
	Cellule		m_bigDecor[MAXCELX][MAXCELY];
	byte		m_balleTraj[MAXCELX * MAXCELY / 8 + 1];
	byte		m_moveTraj[MAXCELX * MAXCELY / 8 + 1];
	MoveObject  m_moveObject[MAXMOVEOBJECT];
	int         m_keyPress;
	int         m_lastKeyPress;
	POINT       m_posDecor;
	POINT       m_dimDecor;
	POINT       m_posCelHili;
	POINT		m_dimCelHili;
	int			m_2ndPositionCalculationSlot;
	int		    m_phase;
	int         m_term;
	int			m_music;
	int			m_region;
	int			m_lastRegion;
	int			m_iconLift;
	int			m_time;
	char		m_missionTitle[100];
	BOOL		m_bPause;
	int			m_nbRankCaisse;
	int			m_rankCaisse[MAXMOVEOBJECT];
	int			m_nbLinkCaisse;
	int			m_linkCaisse[MAXMOVEOBJECT];
	POINT       m_blupiPos;
	POINT       m_blupiValidPos;
	int			m_blupiAction;
	int         m_blupiDir;
	int         m_blupiPhase;
	POINT       m_blupiVitesse;
	int			m_blupiIcon;
	int			m_blupiSec;
	int			m_blupiChannel;
	POINT		m_blupiVector;
	int			m_blupiTransport;
	BOOL		m_blupiFocus;
	BOOL        m_blupiAir;
	BOOL        m_blupiHelico;
	BOOL        m_blupiOver;
	BOOL        m_blupiJeep;
	BOOL        m_blupiTank;
	BOOL        m_blupiSkate;
	BOOL        m_blupiNage;
	BOOL        m_blupiSurf;
	BOOL        m_blupiVent;
	BOOL        m_blupiSuspend;
	BOOL        m_blupiJumpAie;
	BOOL        m_blupiShield;
	BOOL        m_blupiPower;
	BOOL        m_blupiCloud;
	BOOL        m_blupiHide;
	BOOL        m_blupiInvert;
	BOOL        m_blupiBalloon;
	BOOL        m_blupiEcrase;
	POINT		m_blupiPosHelico;
	POINT		m_blupiPosMagic;
	BOOL		m_blupiRestart;
	BOOL		m_blupiFront;
	int			m_blupiBullet;
	int			m_blupiCle;
	int			m_blupiPerso;
	int			m_blupiDynamite;
	int			m_blupiNoBarre;
	int			m_blupiTimeShield;
	int			m_blupiTimeFire;
	int			m_blupiTimeNoAsc;
	int			m_blupiTimeMockery;
	int			m_blupiTimeOuf;
	int			m_blupiActionOuf;
	int			m_blupiFifoNb;
	POINT		m_blupiFifoPos[10];
	POINT		m_blupiStartPos[4];
	int			m_blupiStartDir[4];
	BOOL		m_bMulti;
	int			m_team;
	int			m_netPacketsSent;
	int			m_netPacketsSent2;
	int			m_netPacketsReceived;
	int			m_netPacketsReceived2;
	POINT		m_netPos[MAXNETPLAYER];
	int			m_netIcons[MAXNETPLAYER];
	int			m_netUnk1[MAXNETPLAYER];
	int			m_netUnk2[MAXNETPLAYER];
	int			m_netTransports[MAXNETPLAYER]; // index of lift ridden by each player, or -1
	int			m_netPlayerPacketsReceived[MAXNETPLAYER];
	int			m_netPlayerPacketsReceived2[MAXNETPLAYER];
	int			m_netTimeSincePacket[MAXNETPLAYER];
	POINT		m_netVitesses[MAXNETPLAYER];
	POINT		m_netUnk4[MAXNETPLAYER];
	POINT		m_netPacketPos;
	int			m_netPacketIcon;
	NetMessage	m_netMessages[MAXNETMESSAGE];
	int			m_netMessageIndex1;
	int			m_netMessageIndex2;
	int			m_netMessageIndex3;
	char		m_notifText[4][100];
	int			m_notifTime;
	CJauge		m_jauges[2];
	int			m_blupiLevel;
	int			m_blupiEnergyUnused;
	BOOL		m_bHelicoMarch;
	BOOL		m_bHelicoStop;
	BOOL		m_bJeepMarch;
	BOOL		m_bJeepStop;
	BOOL		m_bFoundCle;
	BOOL		m_bPrivate;
	BOOL		m_bCheatDoors;		// opendoors
	BOOL		m_bSuperBlupi;		// megablupi
	BOOL        m_bDrawSecret;  	// showsecret
	BOOL        m_bBuildOfficialMissions; 	// xmission/xnjttjpo
	BOOL        m_bNetPacked;		// netpacked
	BOOL        m_bNetMovePredict;  // ynosmooth
	BOOL        m_bNetDebug;		// znetdebug
	BOOL		m_bJoystick;
	int			m_bD814;
	int         m_mission;
	BYTE        m_doors[200];
	int         m_nbVies;
	int         m_nbTresor;
	int         m_totalTresor;
	int			m_goalPhase;
	int			m_detectIcon;
	int			m_D8F8;
	POINT       m_scrollPoint;
	POINT       m_scrollAdd;
	int         m_voyageIcon;
	int         m_voyageChannel;
	int         m_voyagePhase;
	int         m_voyageTotal;
	POINT       m_voyageStart;
	POINT       m_voyageEnd;
	int 		m_decorAction;
	int 		m_decorPhase;
	int 		m_lastDecorIndexes[200];
	int			reserve[11];
	BYTE 		dummy[100000];
};

POINT GetCel(int x, int y);
POINT GetCel(POINT cel, int x, int y);
POINT GetVector(int direct);

inline BOOL CDecor::IsValidCel(POINT cel)
{
	return cel.x >= 0 && cel.x < MAXCELX && cel.y >= 0 && cel.y < MAXCELY;
}

inline void CDecor::MoveObjectCopy(MoveObject src, MoveObject dest)
{
	memcpy(&dest, &src, sizeof(dest));
}

inline void CDecor::StopVehicleSound()
{
	StopSound(SOUND_HELICOHIGH);
	StopSound(SOUND_HELICOLOW);
	StopSound(SOUND_JEEPHIGH);
	StopSound(SOUND_JEEPLOW);
}
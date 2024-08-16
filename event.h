// Event.h



/////////////////////////////////////////////////////////////////////////////

#pragma once

using namespace std;

#include "movie.h"
#include "menu.h"
#include "button.h"


typedef struct
{
	UINT	message;
	int		type;
	int		iconMenu[20];
	int		x, y;
	int		toolTips[20];
}
Button;

typedef struct
{
	UINT	phase;
	char	backName[36];
	BOOL	bCDrom;
	Button	buttons[MAXBUTTON];
}
Phase;

typedef struct
{
	int	HeaderLength[10];
	int DoorsLength[200];
	int GamerLength[10 + 200];
	int MaxGamer[3];
	int TotalLength[10 + (10 + 200) + 3];
	BYTE data;
}
GameData;

typedef struct
{
	short	majRev;
	short	minRev;
	short	bSchool;
	short	bPrivate;
	short	world;
	short	skill;
	short	reserve1[99];
}
DemoHeader;

typedef struct
{
	int		time;
	short	input;
	UINT	message;
	WPARAM	wParam;
	LPARAM	lParam;
}
DemoEvent;

typedef enum
{
	cheat_cleanall = 2,
	cheat_funskate = 6,
	cheat_givecopter = 7,
	cheat_jeepdrive = 8,
	cheat_alltreasure = 9,
	cheat_endgoal = 10,
	cheat_roundshield = 12,
	cheat_quicklollipop = 13,
	cheat_tenbombs = 14,
	cheat_birdlime = 15,
	cheat_drivetank = 16,
	cheat_powercharge = 17,
	cheat_hidedrink = 18,
	cheat_iovercraft = 22,
	cheat_udynamite = 23,
	cheat_wellkeys = 24
}
cheat;

typedef enum
{
	KEY_NONE,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_UP,
	KEY_DOWN,
	KEY_JUMP,
	INPUT_DOWN,
	INPUT_UP,
	KEY_FIRE
};

class CEvent
{
public:
	CEvent();
	~CEvent();


	void	OutputNetDebug(const char* str);
	POINT	GetMousePos();
	void	Create(HWND hWnd, CPixmap *pPixmap, CDecor *pDecor, CSound *pSound, CMovie *pMovie, CNetwork *pNetwork);
	void	SetFullScreen(BOOL bFullScreen);
	void	SetMouseType(int mouseType);
	int		GetWorld();
	int		GetWorldGroup();
	void	SetMission(int index);
	int		GetPhysicalWorld();
	int		GetImageWorld();
	BOOL	IsHelpHide();
	BOOL	ChangePhase(UINT phase);
	WMessage GetPhase();
	void	MovieToStart();
	BOOL	NetworkNuggets(int fuck);
	void	HandleInputs();
	void	ReadInput();
	void	TryInsert();
	void	SomethingUserMissions(LPCSTR lpFileName, LPCSTR thing);
	void	RestoreGame();
	int		MissionBack();
	void	TableSomething();

	int		GetButtonIndex(int button);
	int		GetState(int button);
	void	SetState(int button, int state);
	BOOL	GetEnable(int button);
	void	SetEnable(WMessage button, int bEnable);
	void	SetSomething(int button, int bSomething);
	BOOL	GetHide(int button);
	void	SetHide(int button, BOOL bHide);
	int		GetMenu(int button);
	void	SetMenu(int button, int menu);
	void	SomethingDecor();

	void	NetSetPause(BOOL bPause, int players);
	void	NetSendLobby();

	BOOL	DrawButtons();
	BOOL	TextSomething();
	int		MousePosToSprite(POINT pos);
	void	MouseSprite(POINT pos);
	void	WaitMouse(BOOL bWait);
	void	HideMouse(BOOL bHide);
	void	FillMouse(int bFill);
	POINT	GetLastMousePos();
	BOOL	TreatEvent(UINT message, WPARAM wParam, LPARAM lParam);
	BOOL	TreatEventBase(UINT message, WPARAM wParam, LPARAM lParam);

	void	DecorAutoShift(POINT pos);
	
	BOOL	StartMovie(char *pFilename);
	void	StopMovie();
	BOOL	IsMovie();

	void	FlushInput();

	BOOL	FlipObject();

	void	Read(int message);
	void	Write(int message);

	void	SetSpeed(int speed);
	int		GetSpeed();
	BOOL	GetPause();
	void	GetDoors(int doors);
	BOOL	IsShift();
	BOOL    IsMulti();
	BOOL	IsPrivate();

	void	DemoStep();
	void	DebugDisplay(char m);

	void	IntroStep();
	void	SetLives(int lives);

	void	ReadAll();
	BOOL	SaveState(int rank);
	void	SomethingUserMissions(char* lpFilename, LPCSTR fileSomething);

	

protected:
	void	DrawTextCenter(int res, int x, int y, int font=0);
	BOOL	CreateButtons();
	BOOL	EventButtons(UINT message, WPARAM wParam, LPARAM lParam);
	BOOL	MouseOnButton(POINT pos);
	int		SearchPhase(UINT phase);
	void	DecorShift(int dx, int dy);

	BOOL	PlayDown(POINT pos, int fwKeys);
	BOOL	PlayMove(POINT pos, int fwKeys);
	BOOL	PlayUp(POINT pos, int fwKeys);
	void	ChangeButtons(int message);

	void	BuildFloor(POINT cel, int insIcon);
	void	BuildWater(POINT cel, int insIcon);
	BOOL	BuildDown(POINT pos, int fwKeys, BOOL bMix=TRUE);
	BOOL	BuildMove(POINT pos, int fwKeys);
	BOOL	BuildUp(POINT pos, int fwKeys);

	void	PrivateLibelle();
	BOOL	ReadLibelle(int world, BOOL bSchool, BOOL bHelp);
	BOOL	WriteInfo(int gamer, char* playername);
	BOOL	ReadInfo(int gamer);	
	void	TryPhase();
	void	UnTryPhase();
	int		GetTryPhase();
	BOOL	ReadPlayer();
	void	PutTextInputBox(POINT pos);
	

	void	DemoRecStart();
	void	DemoRecStop();
	BOOL	DemoPlayStart();
	void	DemoPlayStop();
	void	DemoRecEvent(UINT message, UINT input, WPARAM wParam, LPARAM lParam);

	//		Network Functions
	BOOL	NetCreate(int session);
	BOOL	NetEnumSessions();
	int		NetSearchPlayer(DPID dpid);
	void	NetStartPlay();
	void	NetSend(NetMessageType message, USHORT data);
	void	NetDraw();
	void	ChatSend();
	void	HandleChatBuffer();
	void	ChatMessageSound(char* data);

	void	MouseRelease();
	void	MouseCapture();


protected:
    int         m_speed;
    int         m_exercice;
    int         m_mission;
	char		m_gamerName[100];
	char		m_gamerNameList[10][100];
	void*		m_somethingJoystick;
	int			m_menuIndex;
	int			m_fileIndex;
	int			m_menuDecor[10];
	BOOL		m_bMouseRelease;
    int         m_private;
    int         m_maxMission;
    WMessage    m_phase;
    int         m_index;
	int			m_playerIndex;
    BOOL        m_bSchool;
    BOOL        m_bPrivate;
	BOOL 		m_bMulti;
    BOOL        m_bAccessBuild;
    BOOL        m_bFullScreen;
    int         m_mouseType;
    HWND        m_hWnd;
    CPixmap*    m_pPixmap;
    CDecor*     m_pDecor;
    CSound*     m_pSound;
    CMovie*		m_pMovie;
	CNetwork* 	m_pNetwork;
	char		m_movieToStart[MAX_PATH];
	WMessage	m_phaseAfterMovie;
	CButton		m_buttons[MAXBUTTON];
	int			m_lastFloor[MAXBUTTON];
	int			m_lastObject[MAXBUTTON];
	int			m_lastHome[MAXBUTTON];
	BOOL		m_bRunMovie;
	BOOL		m_bBuildModify;
	CJauge		m_jauges[2];
	CMenu		m_menu;
	BOOL		m_bMenu;
	POINT		m_menuPos;
	int			m_menuNb;
	int			m_menuButtons[MAXBUTTON];
	int			m_menuErrors[MAXBUTTON];
	int			m_menuPerso;
	POINT		m_menuCel;
	POINT		m_oldMousePos;
	BOOL		m_bMousePress;
	BOOL		m_bMouseDown;
	BOOL		m_bHili;
	int			m_fileWorld[10];
	int			m_fileTime[10];
	POINT		m_posToolTips;
	char		m_textToolTips[50];
	int			m_mouseSprite;
	BOOL		m_bFillMouse;
	BOOL		m_bWaitMouse;
	BOOL		m_bHideMouse;
	BOOL		m_bShowMouse;
	int			m_rankCheat;
	int			m_posCheat;
	BOOL		m_bMovie;
	BOOL		m_bSpeed;
	BOOL		m_bHelp;
	BOOL		m_bAllMissions;
	BOOL		m_bChangeCheat;
	int			m_scrollSpeed;
	BOOL		m_bPause;
	BOOL		m_bShift;
	int			m_shiftPhase;
	POINT		m_shiftVector;
	POINT		m_shiftOffset;
	char		m_libelle[1000];
    char        m_filenameBuffer[100][256];
	int			m_tryPhase;
	int			m_tryInsertCount;
	POINT		m_posInfoButton;
	POINT		m_posHelpButton;
	BOOL		m_bHiliInfoButton;
	BOOL		m_bHiliHelpButton;
	BOOL		m_bInfoHelp;
	BOOL		m_bDemoRec;
	BOOL		m_bDemoPlay;
	DemoEvent*	m_pDemoBuffer;
	int			m_demoTime;
    int         m_input;
	int			m_demoIndex;
	int			m_demoEnd;
	int			m_demoNumber;
	BOOL		m_bCtrlDown;
	POINT		m_debugPos;
	int			m_introTime;
	int 		m_joyID;
	int 		m_gamer;
	int 		m_textHiliStart;
	int 		m_textHiliEnd;
	int 		m_textCursorIndex;
	char 		m_textInput[100];
	char 		m_pPlayerName[100];
	int 		m_lives;
	int 		m_multi;
	HINSTANCE	m_hInstance;
	char		m_chatZone[100][5];
	char 		m_text[100];
};

extern
int		DirectoryThing(LPCSTR filename);
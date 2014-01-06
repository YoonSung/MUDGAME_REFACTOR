#include "stdafx.h"
#include "Printer.h"
#include "Log.h"
#include <sstream>

#define VACANT_SPACE	"□"
#define ENEMY_SPACE		"※"
#define TARGET_SPACE	"♥"
#define PLAYER_SPACE	"★"
#define NEWLINE_TWICE	"\n\n" 
#define CLEAR_MONITOR	"cls"
#define NEWLINE			"\n"
#define TAP				"\t\t\t" 
#define PRINT_INTERVAL		100
#define TIME_BETWEEN_PRINT 1000

#define PLAYER_SPACE_IN_ROOM	"□"
#define PLAYER_WITH_TARGET		"▣"
#define TARGET_SPACE_IN_ROOM	"※" 
#define VACANT_SPACE_IN_ROOM	"  "


CPrinter* g_Printer = nullptr;

//print 일반함수에서 다루어야 하기 때문에 일반변수로 선언.
bool m_Flag = true;
CPlayerCharacter* m_Printer_PC;
bool m_isCombatOccur;


//내부함수 선언
void _PrintAllThing();
void _PrintExceptEnemy();
void _Print(std::string enemySymbol);
std::string getMapView(std::string enemySymbol);
std::string convertString(int value);

std::string getStatusView()
{
	std::string view;

	CPlayerCharacter* target = NULL;

	if ( m_isCombatOccur )
	{
		target = g_Room->getPlayer();
	}
	else
	{
		target = m_Printer_PC;
	}


	view.append("┃");
	view.append("레벨 : ");
	view.append( convertString(target->GetLevel()) );
	view.append("┃");
	view.append("체력 : ");
	view.append( convertString(target->GetEnergy()) );
	view.append("┃");
	view.append("경험치 : ");
	view.append( convertString(target->GetExperience()) );
	view.append("┃");
	view.append("누적사살횟수 : ");
	view.append( convertString(target->GetTotalKillingNum()) );

	view.append(NEWLINE);

	return view;
}

std::string convertString(int value)
{
	std::stringstream out;
	out << value;

	return out.str();
}

std::string getMapView(std::string enemySymbol)
{

	std::string view;

	view.append("┏");
	for(int i = 0; i < MAP_SIZE; ++i) {
		view.append("━");
	}
	view.append("┓");

	if ( m_isCombatOccur )
	{
		view.append( TAP );
		view.append("┏");
		for(int i = 0; i < MAP_SIZE; ++i) {
			view.append("━");
		}
		view.append("┓");
	}

	view.append(NEWLINE);

	for ( int y = 0 ; y < MAP_SIZE ; ++y )
	{ 
		view.append("┃");
		for ( int x = 0 ; x < MAP_SIZE ; ++x )
		{
			if ( m_Printer_PC->GetPositionY() == y && m_Printer_PC->GetPositionX() == x )
			{
				view.append ( PLAYER_SPACE );
				continue;
			}

			if ( x == MAP_SIZE-1 && y == MAP_SIZE-1 )
			{
				view.append ( TARGET_SPACE );
				continue;
			}

			MapInfo* pMapInfo = g_GameMap->GetMapInfo( x, y );

			//기존의 왼쪽맵
			if ( pMapInfo->pMob == nullptr )
				view.append ( VACANT_SPACE );
			else
				view.append ( enemySymbol );
		}
		view.append("┃");
		//만약 전투가 시작되면 오른쪽 맵도 보여준다.
		if ( m_isCombatOccur )
		{
			view.append( TAP );
			view.append("┃");
			for ( int x = 0 ; x < MAP_SIZE ; ++x )
			{
				;
 				MapInfo* pRoomMapInfo = g_Room->GetMapInfo( x, y );
				CPlayerCharacter* playerInRoom = g_Room->getPlayer();
 				if ( playerInRoom->GetPositionY() == y && playerInRoom->GetPositionX() == x )
 				{ 					if ( pRoomMapInfo->pMob != nullptr )
 					{
 						view.append ( PLAYER_WITH_TARGET );
 					}
 					else
 					{
 						view.append ( PLAYER_SPACE_IN_ROOM );
 					}
 					continue;
 				}
 				if ( pRoomMapInfo->pMob == nullptr )
 					view.append ( VACANT_SPACE_IN_ROOM );
 				else
 					view.append ( enemySymbol );
			}
			view.append("┃");
		}
		view.append ( NEWLINE );
	}

	view.append("┗");
	for(int i = 0; i < MAP_SIZE; ++i) {
		view.append("━");
	}
	view.append("┛");

	if ( m_isCombatOccur )
	{
		view.append( TAP );
		view.append("┗");
		for(int i = 0; i < MAP_SIZE; ++i) {
			view.append("━");
		}
		view.append("┛");
	}


	view.append(NEWLINE_TWICE);

	return view;
}

void CPrinter::CombatModeON()
{
	m_isCombatOccur = true;
}

void CPrinter::CombatModeOFF()
{
	m_isCombatOccur = false;
}

void CPrinter::PrintExceptEnemy()
{
	_PrintExceptEnemy();
}

void CPrinter::PrintAllThing()
{
	_PrintAllThing();
}

void _PrintAllThing() 
{
	_Print ( ENEMY_SPACE );
}

void _PrintExceptEnemy()
{
	_Print ( VACANT_SPACE );
}

void _Print(std::string enemySymbol)
{
	std::string view;
	view.append(getMapView(enemySymbol));
	view.append(getStatusView());
	view.append(g_Logger->getLogView());
	view.append(NEWLINE);

	system ( CLEAR_MONITOR );
	printf(view.c_str());
}

unsigned int WINAPI ThreadProc( LPVOID lpParam )
{

	while ( m_Flag )
	{
		Sleep(PRINT_INTERVAL);

		if ( !m_isCombatOccur )
		{
			_PrintExceptEnemy();
			Sleep(TIME_BETWEEN_PRINT);
		}
		_PrintAllThing();
	}
	return 0;
}

void CPrinter::AutoMapDisplayON()
{
	m_Flag = true;

	DWORD dwThreadId;
	HANDLE hThread;

	hThread = ( HANDLE ) _beginthreadex( NULL, 0, ThreadProc, NULL, 0, ( unsigned int* )&dwThreadId );
	CloseHandle ( hThread );
}

void CPrinter::AutoMapDisPlayOFF()
{
	m_Flag = false;
	system ( CLEAR_MONITOR );
}

CPrinter::CPrinter(CPlayerCharacter& PC)
{
	m_Printer_PC = &PC;
	init();
}

void CPrinter::init()
{
	g_Logger->AddLogBuffer("게임을 시작합니다.");
	g_Logger->AddLogBuffer("몬스터들을 잘 피해서 목적지까지 이동하세요.");
	g_Logger->AddLogBuffer("몬스터를 만나면, 해당 좌표의 공간에서 전투가 이루어집니다.");
	g_Logger->AddLogBuffer("전투가 시작되면, 주변몹들이 플레이어의 위치를 알고 가까이 다가오니");
	g_Logger->AddLogBuffer("빨리 전투를 끝내야 합니다!!!");
	g_Logger->AddLogBuffer(" ");
	g_Logger->AddLogBuffer("부디.... 잘 살아남으시기 바랍니다.");
}

CPrinter::~CPrinter(void)
{
}

void CPrinter::PrintTextInBox( std::string value )
{

	std::string view;

	view.append("┏");

	for(int i = 0; i < MAX_LOG_LENGTH-35; ++i) {
		view.append("━");
	}
	view.append("┓");
	view.append( NEWLINE );
	view.append("┃");

	int size = value.length();

	std::string temp;

	for ( int j = 0 ; j < MAX_LOG_LENGTH-size ; ++j)
	{
		temp.append(" ");
	}

	view.append(value);
	view.append(temp);
	view.append("┃");
	view.append( NEWLINE );

	view.append("┗");
	for(int i = 0; i < MAX_LOG_LENGTH-35; ++i) {
		view.append("━");
	}
	view.append("┛");

	system ( CLEAR_MONITOR );
	printf_s(view.c_str());
	printf_s(NEWLINE);
}

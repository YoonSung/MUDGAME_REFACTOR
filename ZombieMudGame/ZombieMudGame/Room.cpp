#include "stdafx.h"
#include "Room.h"
#include "Monster.h"
#include "Printer.h"

CRoom* g_Room = nullptr;

void CRoom::Init()
{
	for ( int i = 0; i < MAP_SIZE; ++i )
	{
		for ( int j = 0; j < MAP_SIZE; ++j )
		{
			if ( m_MapInfo[i][j].pMob != nullptr )
			{
				delete m_MapInfo[i][j].pMob;
				m_MapInfo[i][j].pMob = nullptr;
			}
		}
	}

	m_CurrentMonsterNumber = 0;
}

CPlayerCharacter* CRoom::getPlayer()
{
	return m_MockPlayer;
}

bool CRoom::addMonster(CMonster& monster)
{	

	bool isAdded = false;

	MapInfo* tempMapInfo = GetMapInfo( monster.GetPosition().x, monster.GetPosition().y);

 	if ( tempMapInfo->pMob == nullptr )
 	{
 		tempMapInfo->pMob = &monster;
 		isAdded = true;
 		++m_CurrentMonsterNumber;
 
 	}
	return isAdded;
}

CRoom::CRoom(void)
{
	m_MockPlayer = new CPlayerCharacter();
	m_MockPlayer->SetPosition(0,0);
	
}

CRoom::~CRoom(void)
{
	delete m_MockPlayer;
}

void CRoom::CheckZombieCapture()
{
	int x = m_MockPlayer->GetPosition().x;
	int y = m_MockPlayer->GetPosition().y;
	MapInfo* mapInfo = GetMapInfo(x, y);

	//CPrinter* printer = CPrinter::getInstancePtr();


	if (  mapInfo->pMob != nullptr )
	{

		m_MockPlayer->KillingZombie( (mapInfo->pMob)->GetExperience() );
		//printer->AddLogBuffer("���� ��ҽ��ϴ�!!");
		delete mapInfo->pMob;
		mapInfo->pMob = nullptr;
		m_CurrentMonsterNumber--;
	}
	else
	{
		//printer->AddLogBuffer("�� ���� ����������! ���� ���� �����Դϴ�");
	}
}

int CRoom::getMonsterNumberInRoom()
{
	return m_CurrentMonsterNumber;
}

void CRoom::AttackPlayer(int damage)
{
	m_MockPlayer->AttackFromEnemy(damage);
}

bool CRoom::IsPlayerDead()
{
	return m_MockPlayer->IsPlayerDead();
}

void CRoom::SynchronizePlayer( int level, int energy, int experience, int killingNum )
{
	m_MockPlayer->SetLevel( level );
	m_MockPlayer->SetEnergy( energy );
	m_MockPlayer->SetExperience( experience );
	m_MockPlayer->SetTotalKillingNum( killingNum );
}

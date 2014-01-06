#pragma once

#include "Monster.h"
#include "GameMap.h"
#include "PlayerCharacter.h"

#define MAX_MONSTER_NUM 15

class CRoom
: public CGameMap
{
public:
	bool addMonster(CMonster& monster);
	virtual ~CRoom(void);
	CPlayerCharacter* CRoom::getPlayer();
	void CheckZombieCapture();
	int getMonsterNumberInRoom();
	void CRoom::AttackPlayer(int damage);
	bool IsPlayerDead();
	void SynchronizePlayer(int level, int energy, int experience, int killingNum);
	void CRoom::Init();
	CRoom(void);
private:
	CPlayerCharacter* m_MockPlayer;
	CMonster* m_Monster [ MAX_MONSTER_NUM ];
private:
	void destroyMonster();
	int m_CurrentMonsterNumber;
};

extern CRoom* g_Room;
#pragma once

#include "Monster.h"
#define MAP_SIZE 10

struct MapInfo
{
	CMonster* pMob;
};
class CGameMap
{
public:
	MapInfo* GetMapInfo ( int x, int y );
	void ClearMap();
	CGameMap(void);
	virtual ~CGameMap(void);
protected:
	MapInfo m_MapInfo[MAP_SIZE][MAP_SIZE];
};

extern CGameMap* g_GameMap;


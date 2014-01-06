#include "stdafx.h"
#include "GameMap.h"

CGameMap* g_GameMap = nullptr;

CGameMap::CGameMap(void)
{
	memset(m_MapInfo, 0, sizeof(m_MapInfo));
	//ZERO_MEMORY(m_MapInfo, sizeof(m_MapInfo);
}

CGameMap::~CGameMap(void)
{
	ClearMap();
}

void CGameMap::ClearMap()
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
}

MapInfo* CGameMap::GetMapInfo( int x, int y )
{
	if ( x < 0 || x >= MAP_SIZE || y < 0 || y >= MAP_SIZE )
		return nullptr;

	return &m_MapInfo[x][y];
}
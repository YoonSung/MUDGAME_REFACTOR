#include "stdafx.h"
#include "Character.h"
#include "GameMap.h"

CCharacter::CCharacter(void)
{
	m_Level = 1;
	Init();
}
void CCharacter::Init()
{
	m_Position.x = m_Position.y = 0;
	m_Energy = 300 * m_Level;
	m_Damage = 1 * m_Level;
	m_Experience = 50*m_Level;
}

CCharacter::~CCharacter(void) {}

void CCharacter::SetPosition( int x, int y )
{
	Position position = { x, y };
	SetPosition( position );
}

void CCharacter::SetPosition( Position pos )
{
	m_Position = pos;
}

void CCharacter::Move( DIRECTION dir )
{
	switch( dir )
	{
 	case DIR_UP:
 		m_Position.y = __max( m_Position.y - 1, 0 );
 		break;
 
 	case DIR_DOWN:
 		m_Position.y = __min( m_Position.y + 1, MAP_SIZE - 1 );
 		break;
 
 	case DIR_LEFT:
 		m_Position.x = __max( m_Position.x - 1, 0 );
 		break;
 
 	case DIR_RIGHT:
 		m_Position.x = __min( m_Position.x + 1, MAP_SIZE - 1 );
 		break;
 	}
}

int CCharacter::GetEnergy()
{
	return m_Energy;
}

int CCharacter::GetDamage()
{
	return m_Damage;
}

int CCharacter::GetLevel()
{
	return m_Level;
}

int CCharacter::GetExperience()
{
	return m_Experience;
}

void CCharacter::SetEnergy( int energy )
{
	m_Energy = energy;
}

void CCharacter::SetLevel( int level )
{
	m_Level = level;
}

void CCharacter::SetExperience( int experience )
{
	m_Experience = experience;
}

void CCharacter::SetDamage( int damage )
{
	m_Damage = damage;
}

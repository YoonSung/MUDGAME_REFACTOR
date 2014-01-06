#include "stdafx.h"
#include "Character.h"
#include "GameMap.h"

//��� ������ ��ġ �����
//��ġ ����ϴ� �Լ� �����
//�׸��� ���� Ű �Է¹����� ��ġ �Žñ�

CCharacter::CCharacter(void)
{
	m_level = 1;
	Init();
	
}
void CCharacter::Init()
{
	m_position.x = m_position.y = 0;
	m_energy = 300 * m_level;
	m_damage = 1 * m_level;
	m_experience = 50*m_level;
}

CCharacter::~CCharacter(void)
{
}

void CCharacter::SetPosition( int x, int y )
{
	Position position = { x, y };
	SetPosition( position );
}

void CCharacter::SetPosition( Position pos )
{
	m_position = pos;
}

void CCharacter::Move( DIRECTION dir )
{
	switch( dir )
	{
 	case DIR_UP:
 		m_position.y = __max( m_position.y - 1, 0 );
 		break;
 
 	case DIR_DOWN:
 		m_position.y = __min( m_position.y + 1, MAP_SIZE - 1 );
 		break;
 
 	case DIR_LEFT:
 		m_position.x = __max( m_position.x - 1, 0 );
 		break;
 
 	case DIR_RIGHT:
 		m_position.x = __min( m_position.x + 1, MAP_SIZE - 1 );
 		break;
 	}

	//printf_s( "current pos = ( %d, %d )\n", m_position.x, m_position.y );
}

int CCharacter::GetEnergy()
{
	return m_energy;
}

int CCharacter::GetDamage()
{
	return m_damage;
}

int CCharacter::GetLevel()
{
	return m_level;
}

int CCharacter::GetExperience()
{
	return m_experience;
}

void CCharacter::SetEnergy( int energy )
{
	m_energy = energy;
}

void CCharacter::SetLevel( int level )
{
	m_level = level;
}

void CCharacter::SetExperience( int experience )
{
	m_experience = experience;
}

void CCharacter::SetDamage( int damage )
{
	m_damage = damage;
}

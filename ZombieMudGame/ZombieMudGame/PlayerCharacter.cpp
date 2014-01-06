#include "stdafx.h"
#include "PlayerCharacter.h"


CPlayerCharacter::CPlayerCharacter(void)
{
	skill_1_num = 1;
	skill_2_num = 0;
	skill_3_num = 0;
	m_Total_Killing_num = 0;
}


CPlayerCharacter::~CPlayerCharacter(void)
{
}

int CPlayerCharacter::GetPositionX()
{
	return m_Position.x;
}

int CPlayerCharacter::GetPositionY()
{
	return m_Position.y;
}

void CPlayerCharacter::LevelUpgrade()
{
	m_Level++;
	RefreshSkillNumber();
}

void CPlayerCharacter::RefreshSkillNumber()
{
	if ( m_Level <= 5)
	{
		skill_1_num = 1;
	}
	else
	{
		skill_1_num = (int)(m_Level/3);
	}


	if ( 2 <= m_Level && m_Level <= 5 )
	{
		skill_2_num = 2;
	} 
	else if ( m_Level > 5 )
	{
		skill_2_num = (int)(m_Level/5);
	}


	if ( 5<= m_Level && m_Level <= 7)
	{
		skill_3_num = 1;
	}
	else if ( m_Level > 8 )
	{
		skill_3_num = (int)(m_Level/10);
	}
}

void CPlayerCharacter::CheckUpdate()
{
	if ( m_Experience >= 100 )
	{
		LevelUpgrade();
		m_Experience = 0;
	}
}

void CPlayerCharacter::KillingZombie( int experience )
{
	m_Experience += experience;
	m_Total_Killing_num++;
}

void CPlayerCharacter::AttackFromEnemy( int damage )
{
	m_Energy -= damage;
}

bool CPlayerCharacter::IsPlayerDead()
{
	return ( 0 >= m_Energy );
}

int CPlayerCharacter::GetTotalKillingNum()
{
	return m_Total_Killing_num;
}

void CPlayerCharacter::SetTotalKillingNum( int killingNum )
{
	m_Total_Killing_num = killingNum;
}

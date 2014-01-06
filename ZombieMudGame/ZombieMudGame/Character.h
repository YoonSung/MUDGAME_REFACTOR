#pragma once

struct Position
{
	int x;
	int y;
};

enum DIRECTION
{
	NONE,
	DIR_UP,
	DIR_DOWN,
	DIR_LEFT,
	DIR_RIGHT,
};

class CCharacter
{
public:
	CCharacter ( void );
	void CCharacter::Init();
	virtual ~CCharacter ( void );
	virtual void SetPosition ( Position pos );
	virtual void SetPosition (int x, int y);
	Position GetPosition(){return m_Position;};
	virtual void Move ( DIRECTION dir );

	void SetEnergy(int energy);
	void SetLevel(int level);
	void SetExperience(int experience);
	void SetDamage(int damage);

	int GetDamage();
	int GetEnergy();
	int GetLevel();
	int GetExperience();
protected:
	Position m_Position;
	int m_Damage;
	int m_Energy;
	int m_Level;
	int m_Experience;
};


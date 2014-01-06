#pragma once
#include "character.h"

class CMonster :
	public CCharacter
{
public:
	CMonster( int startX, int startY );
	virtual ~CMonster(void);
	void CMonster::_Move ( DIRECTION dir, bool IsCallFromRoom );
	virtual void Move ( DIRECTION dir );
	void MoveInRoom ( DIRECTION dir );
	void SetPositionInRoom (int x, int y);
	virtual void SetPosition (int x, int y);
private:
	CMonster(void);
	virtual void SetPosition ( Position pos );
};


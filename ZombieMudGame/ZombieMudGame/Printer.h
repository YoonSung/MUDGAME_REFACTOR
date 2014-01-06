#pragma once

#include "GameMap.h"
#include "PlayerCharacter.h"
#include "Room.h"

class CPrinter
{
public:
	virtual ~CPrinter(void);
	void AutoMapDisplayON();
	void AutoMapDisPlayOFF();
	void CombatModeON();
	void CombatModeOFF();
	void PrintExceptEnemy();
	void PrintAllThing();
	void init();
	void PrintTextInBox(std::string string);
	CPrinter::CPrinter(CPlayerCharacter& PC);	
};

extern CPrinter* g_Printer;
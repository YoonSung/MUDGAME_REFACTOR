// ZombieMudGame.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "GameManager.h"
#include "crtdbg.h"
#ifdef  _DEBUG
#define new new(_CLIENT_BLOCK,__FILE__, __LINE__)
#endif //  _DEBUG

int _tmain(int argc, _TCHAR* argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	CGameManager* gameManager = new CGameManager();
	gameManager->Init();
	gameManager->Run();
	delete gameManager;
	_CrtDumpMemoryLeaks();


	return 0;
}


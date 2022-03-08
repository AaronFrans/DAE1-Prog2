#include "pch.h"
#include <Windows.h>
#include <iostream>
#include "Game.h"

void ShowMenu( );
void HandleChoice(Game* pGame);
void StartHeapControl();
void DumpMemoryLeaks();

int main( )
{
	StartHeapControl();
	{
		Game* pGame{ new Game };
		HandleChoice(pGame);
		delete pGame;
	}
	DumpMemoryLeaks();

	std::cout << "Press ENTER to continue";
	std::cin.get();
	return 0;
}

void ShowMenu( )
{
	std::cout << "--> Make your choice\n";
	std::cout << "e: add enemy\n";
	std::cout << "p: add pickup\n";
	std::cout << "w: add weapon\n";
	std::cout << "r: report\n";
	std::cout << "s: report enemies\n";
	std::cout << "q: quit\n";
}
void HandleChoice(Game* pGame)
{
	bool hasQuit{ false };
	do
	{
		ShowMenu();

		char enteredChoice;
		std::cin >> enteredChoice;
		std::cin.ignore(std::cin.rdbuf()->in_avail());

		switch (enteredChoice)
		{
		case 'e':
			pGame->AddEnemy();
			break;
		case 'p':
			pGame->AddPickUp();
			break;
		case 'w':
			pGame->AddWeapon();
			break;
		case 'r':
			pGame->ReportAll();
			break;
		case 's':
			pGame->ReportEnemies();
			break;
		case 'q':
			hasQuit = true;
			break;
		default:
			std::cout << enteredChoice << " is an invalid choice\n";
			break;
		}
	} while (!hasQuit);

}


void StartHeapControl()
{
#if defined(DEBUG) | defined(_DEBUG)
	// Notify user if heap is corrupt
	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);

	// Report detected leaks when the program exits
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// Set a breakpoint on the specified object allocation order number
	//_CrtSetBreakAlloc( 156 );
#endif
}

void DumpMemoryLeaks()
{
#if defined(DEBUG) | defined(_DEBUG)
	_CrtDumpMemoryLeaks();
#endif
}


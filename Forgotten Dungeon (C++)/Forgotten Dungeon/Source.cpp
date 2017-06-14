#define CRT_SECURE_NO_WARNINGS

#include "GameLoop.h"

using namespace std;

int main()
{
	GameLoop *gameLoop = new GameLoop(720, 480);
	gameLoop->GameMenu();
	
	delete gameLoop;
	
	return 0;
}
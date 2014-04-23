#include "game.h"
#include <Windows.h>

int main()
{
	std::cout << "Loading..." << std::endl;
	srand (time(NULL));
	game mainGame;
	if (!mainGame.debug)
		FreeConsole();
	mainGame.setGameState(GameState::Uninitialized);
	mainGame.start();
	return 0;
}
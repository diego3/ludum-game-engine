#include <iostream>
#include <string>

#include "Src/Core/Game.h"
#include "Src/Core/Constants.h"

using namespace std;


int main(int argc, char* args[])
{
	std::cout << "[C++] Main" << std::endl;
	
	Game* game = new Game();
	bool initialized = game->Initialize("Game Engine", WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!initialized)
	{
		std::cout << "Initialization fails" << std::endl;
		delete game;
		return 0;
	}

	while (game->IsRunning())
	{
		game->ProcessInput();
		game->Update();
		game->Render();
	}

	game->Destroy();

	return 0;
}


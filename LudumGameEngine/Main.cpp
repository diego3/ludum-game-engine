#include <iostream>
#include <string>

#include "Src/Core/Game.h"
#include "Src/Core/Constants.h"
#include "Src/OpenGL/Instalation.h"

using namespace std;

void GameEngineApplication() {
	std::cout << "[C++] GameEngineApplication..." << std::endl;
	Game* game = new Game();
	bool initialized = game->Initialize();
	if (!initialized) {
		std::cout << "Game Initialize fails" << std::endl;
		delete game;
		return;
	}

	while (game->IsRunning()) {
		game->ProcessInput();
		game->Update();
		game->Render();
	}

	game->Destroy();
	delete game;
}

void OpenGLApplication() {
	std::cout << "[C++] OpenGLApplication..." << std::endl;
	OpenGL::Instalation* opengl = new OpenGL::Instalation();
	opengl->create();
	delete opengl;
}


int main(int argc, char* args[])
{
	std::cout << "[C++] Main..." << std::endl;
	
	GameEngineApplication();

	return 0;
}


#include <iostream>
#include <string>

#include "Src/Core/Game.h"
#include "Src/Core/Constants.h"
#include "Src/OpenGL/Instalation.h"
#include "Src/Editor/SpriteEditor.h"

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
	opengl::Instalation* openglApp = new opengl::Instalation();
	openglApp->create();
	delete openglApp;
}

void SpriteEditorApplication() {
	std::cout << "[C++] SpriteEditorApplication..." << std::endl;
	spriteditor::SpriteEditor* editor = new spriteditor::SpriteEditor();
	editor->Initialize();
	delete editor;
}

int main(int argc, char* args[])
{
	std::cout << "[C++] Main..." << std::endl;
	
	SpriteEditorApplication();

	return 0;
}


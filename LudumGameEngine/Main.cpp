#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>

#include "Src/Core/Game.h"
#include "Src/Core/Constants.h"
#include "Src/OpenGL/Instalation.h"
#include "Src/Editor/SpriteEditor.h"
#include "Src/Networking/ServerTcpChat.h"
#include "Src/Networking/ClientTcpChat.h"

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

void ChatServerApplication() {
	network::ServerTcpChat* chat = new network::ServerTcpChat();
	chat->Run();
	delete chat;
}

void ChatClientApplication() {
	network::ClientTcpChat* client = new network::ClientTcpChat();
	client->Run();
	delete client;
}


int main(int argc, char* args[])
{
	std::cout << "[C++] Main..." << std::endl;
	
	//SpriteEditorApplication();
	//ChatClientApplication();
	GameEngineApplication();
	/*
	
4x4  64x64
a{0, 0}  b{32, 0}   a{32, 0}  b{64, 0}  
c{0, 32} d{32, 32}  c{32, 32} d{64, 32}

a{0, 32} b{32, 32}   a{32, 32} b{64, 32}
c{0, 64} d{64, 64}   c{64, 64} d{64, 64}
	
	

	int height = 64;
	int width = 64;
	int size = 32;
	for (int i = 0; i <= width; i+=size) {
		printf("a{%d,%d} b{%d,%d}\n", i, i, i, i);

	}

	*/
	return 0;
}


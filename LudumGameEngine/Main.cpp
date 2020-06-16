#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>

#include "Src/Core/Game.h"
#include "Src/Core/Constants.h"
#include "Src/OpenGL/Instalation.h"
#include "Src/Editor/TileMapEditor.h"
#include "Src/Networking/ServerTcpChat.h"
#include "Src/Networking/ClientTcpChat.h"
#include "Src/Editor/TestEditor.h"
#include "Src/Editor/AudioMixerEditor.h"
#include "Src/Editor/EventQueueExperiment.h"

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

void TileMapApplication() {
	std::cout << "[C++] TileMapApplication..." << std::endl;
	editor::TileMapEditor* editor = new editor::TileMapEditor();
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

void TestApplication() {
	editor2::TestEditor* teste = new editor2::TestEditor();
	teste->Initialize();
	delete teste;
}

void AudioMixerApplication() {
	audio::AudioMixerEditor* mixerTesting = new audio::AudioMixerEditor();
	mixerTesting->Initialize();
	delete mixerTesting;
}

void EventManagerApplication() {
	experiment::EventQueueExperiment* app = new experiment::EventQueueExperiment();
	app->Initialize();
	delete app;
}

int main(int argc, char* args[])
{
	std::cout << "[C++] Main..." << std::endl;
	
	//TileMapApplication();
	//ChatClientApplication();
	//GameEngineApplication();
	//AudioMixerApplication();
	//OpenGLApplication();
	EventManagerApplication();

	return 0;
}


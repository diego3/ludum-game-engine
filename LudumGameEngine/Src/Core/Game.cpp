#include <iostream>
#include <SDL.h>
#include "../../Libs/SDL2_net-2.0.1/include/SDL_net.h"
#include "../../Libs/SDL2_image-2.0.5/include/SDL_image.h"
#include "../../Libs/SDL2_ttf-2.0.15/include/SDL_ttf.h"
#include "../../Libs/SDL2_mixer-2.0.4/include/SDL_mixer.h"
#include "../../Libs/glm/glm/vec2.hpp"

#include "Game.h"
#include "Constants.h"
#include "EntityManager.h"
#include "../Components/TransformComponent.h"

#ifdef _WIN32
#pragma comment(lib, "Libs/SDL2_net-2.0.1/lib/x86/SDL2_net.lib")
#pragma comment(lib, "Libs/SDL2_image-2.0.5/lib/x86/SDL2_image.lib")
#pragma comment(lib, "Libs/SDL2_ttf-2.0.15/lib/x86/SDL2_ttf.lib")
#pragma comment(lib, "Libs/SDL2_mixer-2.0.4/lib/x86/SDL2_mixer.lib")
#endif // WIN

using namespace std;
using namespace glm;


// GLOBALS
EntityManager* entityManager;
SDL_Renderer* Game::renderer;

Game::Game()
{
	this->isRunning = false;
	this->window = NULL;
	this->tickLastFrame = 0.0f;
}

bool Game::IsRunning() const 
{
	return this->isRunning;
}

bool Game::Initialize(const char* title, int windowWidth, int windowHeight)
{
	tickLastFrame = SDL_GetTicks();

	int sdlInit = SDL_Init(SDL_INIT_EVERYTHING);
	if (sdlInit != 0) {
		std::cout << "SDL init fails: " << SDL_GetError() << std::endl;
		return false;
	}
	this->window = SDL_CreateWindow(
		title,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		windowWidth,
		windowHeight,
		0
	);
	if (this->window == NULL) {
		std::cout << "sdl window initialization fails: " << SDL_GetError() << std::endl;
		return false;
	}
	renderer = SDL_CreateRenderer(this->window, -1, 0);
	if (renderer == NULL) {
		std::cout << "SDL Renderer error: " << SDL_GetError() << std::endl;
		return false;
	}
	
	int flags = IMG_INIT_JPG | IMG_INIT_PNG;
	int initted = IMG_Init(flags);
	if ((initted & flags) != flags) {
		printf("IMG_Init: Failed to init required jpg and png support!\n");
		printf("IMG_Init: %s\n", IMG_GetError());
	}

	if (TTF_Init() == -1) {
		printf("TTF_Init: %s\n", TTF_GetError());
	}


	// load support for the OGG and MOD sample/music formats
	int sound_flags = MIX_INIT_OGG | MIX_INIT_MOD | MIX_INIT_MP3;
	int sound_initted = Mix_Init(sound_flags);
	if (sound_initted & sound_flags != sound_flags) {
		printf("Mix_Init: Failed to init required ogg, mod and mp3 support!\n");
		printf("Mix_Init: %s\n", Mix_GetError());
	}

	if (SDLNet_Init() == -1) {
		std::cout << "SDLNet_Init: " << SDLNet_GetError() << std::endl;
		return false;
	}

	entityManager = new EntityManager();
	// 
	LoadLevel(1);

	this->isRunning = true;

	return true;
}

void Game::LoadLevel(int levelNumber)
{
	Entity* theFirstEntity = new Entity(entityManager, "gameObject1");
	theFirstEntity->AddComponent<TransformComponent>(0, 0, 10, 10, 50, 50, 1);
	entityManager->AddEntity(theFirstEntity);

	Entity* second = new Entity(entityManager, "gameObject2");
	second->AddComponent<TransformComponent>(30, 30, 20, 20, 80, 80, 1);
	entityManager->AddEntity(second);

	Entity* third = new Entity(entityManager, "gameObject3");
	third->AddComponent<TransformComponent>(0, 50, 15, 15, 40, 40, 1);
	entityManager->AddEntity(third);

	Entity* four = new Entity(entityManager, "gameObject3");
	four->AddComponent<TransformComponent>(400, 0, 0, 20, 50, 50, 1);
	entityManager->AddEntity(four);

}

void Game::ProcessInput()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
		case SDL_QUIT:
		{
			isRunning = false;
			break;
		}
		case SDL_KEYDOWN:
		{
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				this->isRunning = false;
				break;
			}
		}
		default: {
			break;
		}
	}
}

void Game::Render()
{
	SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
	SDL_RenderClear(renderer);

	entityManager->Render();

	SDL_RenderPresent(renderer);
}

void Game::Update()
{
	// sleeps the execution if we are too fast
	int timeToWait = FRAME_RATE - (SDL_GetTicks() - tickLastFrame);
	if (timeToWait > 0 && timeToWait <= FRAME_RATE) {
		SDL_Delay(timeToWait);
	}

	float deltaTime = (SDL_GetTicks() - tickLastFrame) / 1000.0f;

	tickLastFrame = SDL_GetTicks();

	entityManager->Update(deltaTime);
}

void Game::Destroy()
{
	if (renderer != NULL)
	{
		SDL_DestroyRenderer(renderer);
	}

	if (this->window != NULL)
	{
		SDL_DestroyWindow(this->window);
	}
	SDL_Quit();
}

Game::~Game() 
{
	if (this->window) {
		SDL_Quit();
	}
}
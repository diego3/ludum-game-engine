#include <iostream>
#include <SDL.h>
#include "../../Libs/SDL2_net-2.0.1/include/SDL_net.h"
#include "../../Libs/SDL2_image-2.0.5/include/SDL_image.h"
#include "../../Libs/SDL2_ttf-2.0.15/include/SDL_ttf.h"
#include "../../Libs/SDL2_mixer-2.0.4/include/SDL_mixer.h"
#include "../../Libs/glm/glm/vec2.hpp"

extern "C" {
#include "../../Libs/lua-5.3.5_Win32_dllw6_lib/include/lua.h"
#include "../../Libs/lua-5.3.5_Win32_dllw6_lib/include/lauxlib.h"
#include "../../Libs/lua-5.3.5_Win32_dllw6_lib/include/lualib.h"
}

#include "Game.h"
#include "Constants.h"
#include "EntityManager.h"
#include "AssetManager.h"
#include "LuaManager.h"
#include "Map.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/KeyboardControlComponent.h"
#include "../Components/LuaScriptComponent.h"
#include "../Components/TileMapComponent.h"

#ifdef _WIN32
#pragma comment(lib, "Libs/SDL2_net-2.0.1/lib/x86/SDL2_net.lib")
#pragma comment(lib, "Libs/SDL2_image-2.0.5/lib/x86/SDL2_image.lib")
#pragma comment(lib, "Libs/SDL2_ttf-2.0.15/lib/x86/SDL2_ttf.lib")
#pragma comment(lib, "Libs/SDL2_mixer-2.0.4/lib/x86/SDL2_mixer.lib")
#pragma comment(lib, "Libs/lua-5.3.5_Win32_dllw6_lib/liblua53.a")
#endif // WIN

using namespace std;
using namespace glm;


// GLOBALS
EntityManager* Game::entityManager = new EntityManager();;
SDL_Renderer* Game::renderer;
AssetManager* Game::assetManager; // new AssetManager(&entityManager)
SDL_Event Game::event;
LuaManager* luaManager;
SDL_Rect Game::camera = {0,0, WINDOW_WIDTH, WINDOW_HEIGHT};


Entity& player = Game::entityManager->AddEntity("chopper", PLAYER_LAYER);

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

	luaManager = new LuaManager();

	// TODO load initial config files (lua scripts)


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
	if ((sound_initted & sound_flags) != sound_flags) {
		printf("Mix_Init: Failed to init required ogg, mod and mp3 support!\n");
		printf("Mix_Init: %s\n", Mix_GetError());
	}

	if (SDLNet_Init() == -1) {
		std::cout << "SDLNet_Init: " << SDLNet_GetError() << std::endl;
		return false;
	}

	Game::assetManager = new AssetManager(entityManager);
	
	LoadLevel(1);

	this->isRunning = true;

	return true;
}


void Game::LoadLevel(int levelNumber)
{
	// Load entities script files and parse

	// load images to the memory
	assetManager->AddTexture("tank-left", "Assets/images/tank-small-left.png");
	assetManager->AddTexture("chopper-image", "Assets/images/chopper-spritesheet.png");
	assetManager->AddTexture("radar-image", "Assets/images/radar.png");
	assetManager->AddTexture("tile-map", "Assets/images/jungle.png");//Assets/tilemaps/jungle.png

	Map* tileMap = new Map("tile-map", 2, 32);
	tileMap->LoadMap("Assets/tilemaps/jungle.map", 25, 20);

	// Challenge: Draw a grid to wrap the image
	//Entity& mapa = Game::entityManager->AddEntity("Tile");
	//mapa.AddComponent<TransformComponent>(100, 250, 0, 0, 320, 96, 2);
	//mapa.AddComponent<SpriteComponent>("tile-map");

	Entity& tank = entityManager->AddEntity("tankLeft", ENEMY_LAYER);
	tank.AddComponent<TransformComponent>(0, 0, 20, 20, 32, 32, 2);
	tank.AddComponent<SpriteComponent>("tank-left");

	player.AddComponent<TransformComponent>(240, 160, 0, 0, 32, 32, 2);
	player.AddComponent<SpriteComponent>("chopper-image", 2, 90, true, false);
	//chopper.AddComponent<LuaScriptComponent>(luaManager, "Scripts/playerControl.lua");
	player.AddComponent<KeyboardControlComponent>("up", "down", "left", "right", "space");
	
	Entity& radar = entityManager->AddEntity("radar", UI_LAYER);
	radar.AddComponent<TransformComponent>(720, 15, 0, 0, 64, 64, 1);
	radar.AddComponent<SpriteComponent>("radar-image", 8, 150, false, true);
	
	entityManager->PrintAllEntities();
}

void Game::ProcessInput()
{
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

	HandleCameraMovement();
}

void Game::HandleCameraMovement() {
	TransformComponent* transform = player.GetComponent<TransformComponent>();
	
	camera.x = transform->position.x - (WINDOW_WIDTH / 2);
	camera.y = transform->position.y - (WINDOW_HEIGHT / 2);

	// Campling 
	camera.x = camera.x < 0 ? 0 : camera.x;
	camera.y = camera.y < 0 ? 0 : camera.y;
	camera.x = camera.x > camera.w ? camera.w : camera.x;
	camera.y = camera.y > camera.h ? camera.h : camera.y;

	std::cout << transform->position.x << "," << transform->position.y << std::endl;

	// Campling player
	transform->position.x = transform->position.x < 0 ? 0 : transform->position.x;
	transform->position.y = transform->position.y < 0 ? 0 : transform->position.y;
	transform->position.x = transform->position.x > (WINDOW_WIDTH * 2 - transform->width*2) ? static_cast<float>(WINDOW_WIDTH * 2 - transform->width*2) : transform->position.x;
	transform->position.y = transform->position.y > (WINDOW_HEIGHT* 2 - transform->height * 2) ? static_cast<float>(WINDOW_HEIGHT * 2 - transform->height * 2) : transform->position.y;

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

	delete assetManager;
	delete entityManager;
	delete luaManager;
	SDL_Quit();
}

Game::~Game() 
{
	if (this->window) {
		SDL_Quit();
	}
}
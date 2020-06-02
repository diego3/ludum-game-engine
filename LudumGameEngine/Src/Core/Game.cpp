#include <iostream>
#include <SDL.h>
#include <SDL_net.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "../../Libs/glm/glm/vec2.hpp"

extern "C" {
#include "../../Libs/lua-5.3.5_Win32_dllw6_lib/include/lua.h"
#include "../../Libs/lua-5.3.5_Win32_dllw6_lib/include/lauxlib.h"
#include "../../Libs/lua-5.3.5_Win32_dllw6_lib/include/lualib.h"
}

#include "../../Libs/lua-5.3.5_Win32_dllw6_lib/include/sol.hpp"

#include "Game.h"
#include "Constants.h"
#include "EntityManager.h"
#include "AssetManager.h"
//#include "LuaManager.h"
#include "Map.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/KeyboardControlComponent.h"
#include "../Components/LuaScriptComponent.h"
#include "../Components/TileMapComponent.h"
#include "../Components/CameraFollowComponent.h"
#include "../Components/CameraShakeComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/ProjectileComponent.h"

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
//LuaManager* luaManager;
SDL_Rect Game::camera = {0,0, WINDOW_WIDTH, WINDOW_HEIGHT};


bool gameLoopDebug = false;
bool loadTileMap = true;
bool Game::showCollisionsDebug = false;
bool Game::showPlayerPositionDebug = false;

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

bool Game::Initialize()
{
	tickLastFrame = SDL_GetTicks();

	//luaManager = new LuaManager();
	sol::state lua;
	lua.open_libraries(sol::lib::base);
	lua.script("print('[LUA]  bark bark bark!')");
	lua.script_file("Scripts/gameOptions.lua");
	// TODO load initial config files (lua scripts)
	sol::table options = lua["Config"];
	
	gameLoopDebug = options["gameLoopUpdateDebug"];
	loadTileMap = options["loadTileMap"];
	showPlayerPositionDebug = options["showPlayerPositionDebug"];
	showCollisionsDebug = options["showCollisionsDebug"];

	bool fullscreen = options["fullscreen"]; 
	std::string windowTitle = options["windowTitle"]; 
	int windowWidth = options["windowWidth"]; 
	int windowHeight = options["windowHeight"];
	int loadLevel = options["loadLevel"];

	int sdlInit = SDL_Init(SDL_INIT_EVERYTHING);
	if (sdlInit != 0) {
		std::cout << "SDL init fails: " << SDL_GetError() << std::endl;
		return false;
	}
	this->window = SDL_CreateWindow(
		windowTitle.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		windowWidth,
		windowHeight,
		0//SDL_WINDOW_FULLSCREEN_DESKTOP
	);

	if (fullscreen) {
		int full = SDL_SetWindowFullscreen(this->window, SDL_WINDOW_FULLSCREEN_DESKTOP);
		if (full == -1) {
			std::cout << "SDL_SetWindowFullscreen FAILED" << std::endl;
		}
	}

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
	
	LoadLevel(loadLevel);

	this->isRunning = true;

	return true;
}

void Game::LoadLevel(int levelNumber) {
	sol::state lua;
	lua.open_libraries(sol::lib::base, sol::lib::os, sol::lib::math, sol::lib::table);
	lua.script("print('[LUA] Loading....')");

	std::string levelName = "Level"+std::to_string(levelNumber);
	lua.script_file("Scripts/"+levelName+".lua");

	// Assets Loading
	sol::table levelData = lua[levelName];
	sol::table levelAssets = levelData["assets"];
	int index = 0;
	while (true) {
		sol::optional<sol::table> exists = levelAssets[index];
		if (exists == sol::nullopt) {
			break;
		}

		sol::table asset = levelAssets[index];
		std::string assetType = asset["type"];
		std::string assetId = asset["id"];
		std::string assetFile = asset["file"];
		if (assetType.compare("texture") == 0) {
			//std::cout << assetId << assetFile << std::endl;
			assetManager->AddTexture(assetId, assetFile);
		}

		index++;
	}
	

	if (loadTileMap) {
		sol::table tileMapTable = levelData["map"];
		std::string tileAssetId = tileMapTable["assetId"];
		std::string tileMapFilePath = tileMapTable["file"];
		int tileScale = static_cast<int>(tileMapTable["scale"]);
		int tileSize = static_cast<int>(tileMapTable["tileSize"]);
		int mapSizeX = static_cast<int>(tileMapTable["mapSizeX"]);
		int mapSizeY = static_cast<int>(tileMapTable["mapSizeY"]);

		Map* tileMap = new Map(tileAssetId, tileScale, tileSize);
		tileMap->LoadMap(tileMapFilePath, mapSizeX, mapSizeY);
	}
	
	sol::table entities = levelData["entities"];
	int entityIndex = 0;
	while (true) {
		sol::optional<sol::table> exists = entities[entityIndex];
		if (exists == sol::nullopt) {
			std::cout << "entity index[" << entityIndex << "] not found" << std::endl;
			break;
		}
		sol::table entityTable = entities[entityIndex];
		std::string name = entityTable["name"];
		LayerType layer = static_cast<LayerType>(entityTable["layer"]);
		// Entity
		Entity& entity = Game::entityManager->AddEntity(name, layer);
		
		//TransformComponent
		sol::table components = entityTable["components"];
		sol::optional<sol::table> transformExists = components["transform"];
		if (transformExists != sol::nullopt) {
			sol::table transform = components["transform"];
			sol::table position = transform["position"];
			int posX = static_cast<int>(position["x"].get_or(0));
			int posY = static_cast<int>(position["y"].get_or(0));
			
			sol::table velocity = transform["velocity"];
			int velX = static_cast<int>(velocity["x"].get_or(0));
			int velY = static_cast<int>(velocity["y"].get_or(0));

			int width = static_cast<int>(transform["width"].get_or(0));
			int height = static_cast<int>(transform["height"].get_or(0));
			int scale = static_cast<int>(transform["scale"].get_or(0));
			int rotate = static_cast<int>(transform["rotate"].get_or(0));

			entity.AddComponent<TransformComponent>(posX, posY,velX, velY, width, height, scale);
		}

		//SpriteComponent
		sol::optional<sol::table> spriteExists = components["sprite"];
		if (spriteExists != sol::nullopt) {
			sol::table spriteTable = components["sprite"];
			std::string id = spriteTable["assetId"];
			int numFrames = static_cast<int>(spriteTable["numFrames"]);
			int animationSpeed = static_cast<int>(spriteTable["animationSpeed"]);
			bool hasDirections = spriteTable["hasDirections"];
			bool isFixed = spriteTable["isFixed"];
			
			entity.AddComponent<SpriteComponent>(id, numFrames, animationSpeed, 
				hasDirections, isFixed);
		}

		//BoxColliderComponent
		sol::optional<sol::table> colliderExists = components["collider"];
		if (colliderExists != sol::nullopt) {
			sol::table colliderTable = components["collider"];
			std::string tag = colliderTable["tag"];

			std::string boundingAssetId = colliderTable["boundingAssetId"];
			int x = colliderTable["x"];
			int y = colliderTable["y"];
			int w = colliderTable["w"];
			int h = colliderTable["h"];
			if (x > 0 || y > 0 || w > 0 || h > 0) {
				entity.AddComponent<BoxColliderComponent>(tag, boundingAssetId, x, y, w, h);
			}
			else {
				entity.AddComponent<BoxColliderComponent>(tag, boundingAssetId);
			}
		}

		// Projectile Component
		sol::optional<sol::table> projectileExists = components["projectile"];
		if (projectileExists != sol::nullopt) {
			sol::table projectileTable = components["projectile"];
			std::string projectileAssetId = projectileTable["assetId"];
			float speed = projectileTable["speed"];
			int width = projectileTable["width"];
			int height = projectileTable["height"];
			int scale = projectileTable["scale"];
			int duration = projectileTable["duration"];
			entity.AddComponent<ProjectileComponent>(projectileAssetId, speed, width, height, scale, duration);
		}

		// MOVE THIS TO SCRIPT COMPONENT and attach it to the player entity
		sol::optional<sol::table> cameraExists = components["camera"];
		if (cameraExists != sol::nullopt) {
			sol::table camera = components["camera"];

			entity.AddComponent<CameraFollowComponent>();
		}
		
		//CameraShakeComponent
		sol::optional<sol::table> cameraShakeExists = components["cameraShake"];
		if (cameraShakeExists != sol::nullopt) {
			sol::table shakeConfig = components["cameraShake"];
			entity.AddComponent<CameraShakeComponent>(shakeConfig["algorithm"], shakeConfig["duration"]);
		}


		//Inputs
		sol::optional<sol::table> inputExists = components["input"];
		if (inputExists != sol::nullopt) {
			sol::table input = components["input"];
			//KeyboardControlComponent
			sol::optional<sol::table> keyboardExists = input["keyboard"];
			if (keyboardExists != sol::nullopt) {
				sol::table keyboard = input["keyboard"];

				std::string up = keyboard["up"];
				std::string down = keyboard["down"];
				std::string left = keyboard["left"];
				std::string right = keyboard["right"];
				std::string shoot = keyboard["shoot"];

				entity.AddComponent<KeyboardControlComponent>(up, down, left, right, shoot);
			}

			//MouseControlComponent
			sol::optional<sol::table> mouseExists = input["mouse"];
			if (mouseExists != sol::nullopt) {
				sol::table mouse = input["mouse"];


			}
		}
		
		entityIndex++;
	}
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
	if (gameLoopDebug) {
		std::cout << "\n******\nSDL_GetTicks() = " << SDL_GetTicks() << std::endl;
	}
	int timeToWait = FRAME_RATE - (SDL_GetTicks() - tickLastFrame);

	if (gameLoopDebug) {
		std::cout << "FPS = " << FPS << std::endl;
		std::cout << "FRAME_RATE = " << FRAME_RATE << std::endl;
		std::cout << "SDL_GetTicks() - tickLastFrame = " << SDL_GetTicks() - tickLastFrame << std::endl;
		std::cout << "timeToWait = " << timeToWait << std::endl;
	}

	if (timeToWait > 0 && timeToWait <= FRAME_RATE) {
		if (gameLoopDebug) {
			std::cout << "SDL_Delay(" << timeToWait << ")" << std::endl;
		}
		SDL_Delay(timeToWait);
	}

	float deltaTime = (SDL_GetTicks() - tickLastFrame) / 1000.0f;
	if (gameLoopDebug) {
		std::cout << "deltaTime = " << deltaTime << std::endl;
	}

	tickLastFrame = SDL_GetTicks();
	if (gameLoopDebug) {
		std::cout << "tickLastFrame = " << tickLastFrame << std::endl;
	}
	entityManager->Update(deltaTime);

	CheckCollisions();
}

void Game::CheckCollisions() {
	CollisionType collision = entityManager->CheckCollisions();
	switch (collision) {
		case CollisionType::PLAYER_ENEMY: {
			std::cout << "CollisionType::PLAYER_ENEMY " << std::endl;
		}
		case CollisionType::PLAYER_PROJECTILE: {

		}
		case CollisionType::PLAYER_TRIGGER: {

		}
		case CollisionType::NEXT_LEVEL: {

		}
		case CollisionType::NONE: {
			std::cout << "" << std::endl;
		}
	}
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
	//delete luaManager;
	SDL_Quit();
}

Game::~Game() 
{
	if (this->window) {
		SDL_Quit();
	}
}
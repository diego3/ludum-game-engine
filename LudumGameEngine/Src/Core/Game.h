#pragma once

#include <SDL.h>
#include "AssetManager.h"
#include "InputManager.h"

class AssetManager;

class Game {
protected:
	bool isRunning;
	SDL_Window* window;

	int tickLastFrame;
public:
	Game();
	~Game();

	static SDL_Renderer* renderer;
	static AssetManager* assetManager;
	static SDL_Event event;
	static EntityManager* entityManager;
	static SDL_Rect camera;
	static InputManager* inputManager;
	
	static bool showPlayerPositionDebug;
	static bool showCollisionsDebug;

	bool Initialize();
	bool IsRunning() const;
	void ProcessInput();
	void Update();
	void Render();
	void Destroy();

	void LoadLevel(int levelNumber);
	void CheckCollisions();
};
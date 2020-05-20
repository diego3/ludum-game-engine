#pragma once

#include <SDL.h>
#include "AssetManager.h"

class AssetManager;

class Game {
protected:
	bool isRunning;
	SDL_Window* window;

	float tickLastFrame;
public:
	Game();
	~Game();

	static SDL_Renderer* renderer;
	static AssetManager* assetManager;
	static SDL_Event event;
	static EntityManager* entityManager;
	static SDL_Rect camera;

	bool Initialize(const char *title, int windowWidth, int windowHeight);
	bool IsRunning() const;
	void ProcessInput();
	void Update();
	void Render();
	void Destroy();

	void HandleCameraMovement();

	void LoadLevel(int levelNumber);
};
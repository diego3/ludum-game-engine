#pragma once

#include <SDL.h>

class Game {
protected:
	bool isRunning;
	SDL_Window* window;

	float tickLastFrame;
public:
	Game();
	~Game();

	static SDL_Renderer* renderer;

	bool Initialize(const char *title, int windowWidth, int windowHeight);
	bool IsRunning() const;
	void ProcessInput();
	void Update();
	void Render();
	void Destroy();

	void LoadLevel(int levelNumber);
};
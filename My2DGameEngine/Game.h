#pragma once

#include <SDL.h>

class Game {
protected:
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;

	float tickLastFrame;
public:
	Game();
	~Game();


	bool Initialize(const char *title, int windowWidth, int windowHeight);
	bool IsRunning() const;
	void ProcessInput();
	void Update();
	void Render();
	void Destroy();
};
#include <iostream>
#include <SDL.h>
#include "Game.h"
#include "Constants.h"
#include "Libs/glm/glm/vec2.hpp"

using namespace std;
using namespace glm;


float velocity = 10.0f;
vec2 pos = vec2(0.0f, 0.0f);

Game::Game()
{
	this->isRunning = false;
	this->window = NULL;
	this->renderer = NULL;
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
	if (sdlInit != 0)
	{
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

	if (this->window == NULL)
	{
		std::cout << "sdl window initialization fails: " << SDL_GetError() << std::endl;
		return false;
	}

	this->renderer = SDL_CreateRenderer(this->window, -1, 0);
	if (this->renderer == NULL) {
		std::cout << "SDL Renderer error: " << SDL_GetError() << std::endl;
		return false;
	}

	this->isRunning = true;

	return true;
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
	SDL_SetRenderDrawColor(this->renderer, 50, 50, 50, 255);
	SDL_RenderClear(this->renderer);

	SDL_Rect rect {
		(int)pos.x, (int)pos.y, 20, 20
	};

	SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(this->renderer, &rect);

	SDL_RenderPresent(this->renderer);
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
	pos += velocity * deltaTime;
}

void Game::Destroy()
{
	if (this->renderer != NULL)
	{
		SDL_DestroyRenderer(this->renderer);
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
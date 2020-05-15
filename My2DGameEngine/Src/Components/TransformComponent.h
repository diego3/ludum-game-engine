#pragma once
#include <iostream>
#include <SDL.h>
#include "Libs/glm/glm/ext/vector_float2.hpp"

#include "Component.h"
#include "Game.h"

class TransformComponent : public Component
{
public:
	glm::vec2 position;
	glm::vec2 velocity;
	int width;
	int height;
	int scale;

	TransformComponent(int posX, int posY, int velX, int velY, int w, int h, int s)
	{
		position = glm::vec2(posX, posY);
		velocity = glm::vec2(velX, velY);
		width = w;
		height = h;
		scale = s;
	}

	void Initialize() 
	{
		name = "TransformComponent";
	}

	void Render()
	{
		SDL_Rect rectangle = {
			(int)position.x,
			(int)position.y,
			width, height
		};

		SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(Game::renderer, &rectangle);
	}

	void Update(float deltaTime) override 
	{
		position += velocity * deltaTime;
	};
};
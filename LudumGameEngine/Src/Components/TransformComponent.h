#pragma once
#include <iostream>
#include <SDL.h>
#include "../../Libs/glm/glm/ext/vector_float2.hpp"

#include "../Core/Component.h"
#include "../Core/Game.h"

class TransformComponent : public Component
{
public:
	glm::vec2 position;
	glm::vec2 velocity;
	int width;
	int height;
	int scale;

	SDL_Rect box;
	bool showBox;

	TransformComponent(int posX, int posY, int velX, int velY, int w, int h, int s)
	{
		position = glm::vec2(posX, posY);
		velocity = glm::vec2(velX, velY);
		width = w;
		height = h;
		scale = s;
		box = {posX, posY, w*s, h*s};
		showBox = false;
	}

	void Initialize() override
	{

	}

	void Render() override {
		if (showBox) {
			SDL_SetRenderDrawColor(Game::renderer, 0, 255, 0, 255);
			SDL_RenderDrawRect(Game::renderer, &box);
		}
	}

	void Update(float deltaTime) override 
	{
		position += velocity * deltaTime;

		if (showBox) {
			box.x = (int)position.x - Game::camera.x;
			box.y = (int)position.y - Game::camera.y;
		}
	};
};
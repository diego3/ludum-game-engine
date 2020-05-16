#pragma once

#include <string>
#include <SDL.h>
#include "../Core/Game.h"
#include "../Core/Component.h"
#include "TransformComponent.h"
#include "../Core/TextureManager.h"

class SpriteComponent: public Component
{
public:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect source;
	SDL_Rect destination;
	SDL_RendererFlip flip = SDL_FLIP_NONE;

	SpriteComponent(std::string filePath) {
		SetTexture(filePath);
	}

	void SetTexture(std::string assetTextureId) {
		texture = Game::assetManager->GetTexture(assetTextureId);
	}

	void Initialize() override {
		transform = owner->GetComponent<TransformComponent>();
		source.x = 0;
		source.y = 0;
		source.w = transform->width;
		source.h = transform->height;
	}

	void Update(float deltaTime) override {
		destination.x = (int)transform->position.x;
		destination.y = (int)transform->position.y;
		destination.w = transform->width * transform->scale;
		destination.h = transform->height * transform->scale;
	}

	void Render() override {
		TextureManager::Draw(texture, source, destination, flip);

		/* pasted from transform component, just in case
		SDL_Rect rectangle = {
			(int)position.x,
			(int)position.y,
			width, height
		};

		SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(Game::renderer, &rectangle);*/
	}
};
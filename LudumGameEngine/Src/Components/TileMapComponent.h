#pragma once

#include <SDL.h>
#include "../Core/Component.h"
#include "../Core/TextureManager.h"
#include "../Core/AssetManager.h"
#include "../Core/EntityManager.h"
#include "../Core/Game.h"
#include "../../Libs/glm/glm/glm.hpp"

class TileMapComponent: public Component{
public:
	SDL_Texture* textura;
	SDL_Rect source;
	SDL_Rect destination;
	glm::vec2 position;
	std::string assetTextureId;

	TileMapComponent(int sourceX, int sourceY, int x, int y, int tileSize,
		int tileScale, std::string textId) {
		
		assetTextureId = textId;
		textura = Game::assetManager->GetTexture(assetTextureId);
		if (textura == NULL) {
			std::cout << assetTextureId << " NAO CARREGOU " << std::endl;
		}

		source.x = sourceX;
		source.y = sourceY;
		source.w = tileSize;
		source.h = tileSize;

		destination.x = x;
		destination.y = y;
		destination.w = tileSize * tileScale;
		destination.h = tileSize * tileScale;

		position.x = x;
		position.y = y;
	}
	
	~TileMapComponent() {
		SDL_DestroyTexture(textura);
	}

	void Initialize() override {
		
		
	}

	void Update(float deltaTime) override {
		destination.x = position.x - Game::camera.x;
		destination.y = position.y - Game::camera.y;
	}

	void Render() override {
		TextureManager::Draw(textura, source, destination, SDL_FLIP_NONE);
	}
};

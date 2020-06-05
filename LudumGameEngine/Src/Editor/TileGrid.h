#pragma once

#include <vector>
#include <SDL.h>

#include "Tile.h"
#include "SpriteSheet.h"

namespace editor {
	class TileGrid {
	private:
		std::vector<Tile*> tiles;
		int width;
		int height;
		int rectSize;

		int gridSizeX;
		int gridSizeY;

		SDL_Renderer* renderer;
		SpriteSheet* sprite;
	public:
		TileGrid(SDL_Renderer* render, SpriteSheet* sprite, int sizeX, int sizeY, int rectSize) {
			this->renderer = render;
			this->sprite = sprite;
			this->width = sizeX;
			this->height = sizeY;
			this->rectSize = rectSize;
			this->gridSizeX = width / rectSize;//  800/32 = 25units
			this->gridSizeY = height / rectSize;// 600/32 = 18.75units or 19
		}

		bool Initialize() {
			
			for (int i = 0; i < gridSizeY; i++) {
				for (int j = 0; j < gridSizeX; j++) {
					//SDL_Rect p1 = { 400 + (j * rectSize), (i*rectSize), rectSize, rectSize};
					Tile* t = new Tile(0, 0, 400 + (j * rectSize), (i * rectSize));
					tiles.push_back(t);
				}
			}

			return true;
		}


		Tile* GetBlockPosition(SDL_Point point) {
			for (Tile* tile : tiles) {
				SDL_bool inside = SDL_PointInRect(&point, &tile->destination);
				if (inside == SDL_TRUE) {
					return tile;
				}
			}
			
			return NULL;
		}

		void Render() {
			SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
			for (int i = 0; i < gridSizeX; i++) {
				SDL_RenderDrawLine(renderer, 400, i * rectSize, width + 400, i * rectSize);
				SDL_RenderDrawLine(renderer, 400 + (i * rectSize), 0, 400 + (i * rectSize), height);
			}

			// draw each tile
			for (Tile* tile : tiles) {
				if (tile->IsSelected) {
					SDL_RenderCopyEx(renderer, sprite->texture, &tile->source, &tile->destination, 0.0f, NULL, SDL_FLIP_NONE);
				}
			}
		}
	
	};
}
#pragma once

#include <vector>
#include <SDL.h>

#include "Tile.h"

namespace editor {
	class TileGrid {
	private:
		std::vector<SDL_Rect> blocks;
		int width;
		int height;
		int rectSize;

		int gridSizeX;
		int gridSizeY;

		SDL_Renderer* renderer;
	public:
		TileGrid(SDL_Renderer* render, int sizeX, int sizeY, int rectSize) {
			this->renderer = render;
			this->width = sizeX;
			this->height = sizeY;
			this->rectSize = rectSize;
			this->gridSizeX = width / rectSize;//  800/32 = 25units
			this->gridSizeY = height / rectSize;// 600/32 = 18.75units or 19
		}

		bool Initialize() {
			
			for (int i = 0; i < gridSizeY; i++) {
				for (int j = 0; j < gridSizeX; j++) {
					SDL_Rect p1 = { 400 + (j * rectSize), (i*rectSize), rectSize, rectSize};
					blocks.push_back(p1);
				}
			}

			return true;
		}


		SDL_Rect GetBlockPosition(SDL_Point point) {
			for (SDL_Rect rect : blocks) {
				SDL_bool inside = SDL_PointInRect(&point, &rect);
				if (inside == SDL_TRUE) {
					return rect;
				}
			}
			
			SDL_Rect zero = { 0,0,0,0 };
			return zero;
		}

		void Render() {
			SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
			for (int i = 0; i < gridSizeX; i++) {
				SDL_RenderDrawLine(renderer, 400, i * rectSize, width + 400, i * rectSize);
				SDL_RenderDrawLine(renderer, 400 + (i * rectSize), 0, 400 + (i * rectSize), height);
			}
		}
	
	};
}
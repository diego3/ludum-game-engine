#pragma once

#include <vector>
#include <SDL.h>

#include "Tile.h"

namespace editor {
	class TileGrid {

	public:
		TileGrid(SDL_Renderer* render, int sizeX, int sizeY, int rectSize) {
			this->renderer = render;
			this->width = sizeX;
			this->height = sizeY;
			this->rectSize = rectSize;
			this->gridSize = width / rectSize;//800x600=25units
		}

		bool Initialize() {
			//TODO Initialize all the rect blocks, for future collision with the user click at grid position
			
			int y = 0;
			int gridSizeY = height / rectSize;//18.75units or 19
			for (int i = 0; i < gridSizeY; i++) {
				for (int j = 0; j < 25; j++) {
					SDL_Rect p1 = { 400 + (j * rectSize), (i*rectSize), 32, 32 };
					///printf("block %d x pos = %d\n", i, 400 + (i * rectSize));
					blocks.push_back(p1);
				}
			}
			
			/*	y = 32;
			for (int i = 0; i < 25; i++) {
				SDL_Rect p1 = { 400 + (i * rectSize), y, 32, 32 };
				///printf("block %d x pos = %d\n", i, 400 + (i * rectSize));
				blocks.push_back(p1);
			}*/
			//PrintGridPositions();

			return true;
		}


		SDL_Rect GetBlockPosition(SDL_Point point) {
			for (SDL_Rect rect : blocks) {
				SDL_bool inside = SDL_PointInRect(&point, &rect);
				if (inside == SDL_TRUE) {
					printf("inside: {%d, %d}\n", rect.x, rect.y);
					return rect;
				}
			}
			printf("ZERO\n");
			SDL_Rect zero = { 0,0,0,0 };
			return zero;
		}

		//int i = 0;
		//int d = 30;
		void Render() {
			SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
			for (int i = 0; i < gridSize; i++) {
				SDL_RenderDrawLine(renderer, 400, i * rectSize, width + 400, i * rectSize);
				SDL_RenderDrawLine(renderer, 400 + (i * rectSize), 0, 400 + (i * rectSize), height);
			}

			//i++;
			//d--;
			//if (i >= 25) i = 0;
			//if (d <= 0) d = 30;
		}
	private:
		std::vector<SDL_Rect> blocks;
		int width;
		int height;
		int rectSize;

		int gridSize;

		SDL_Renderer* renderer;
	};
}
#pragma once

#include <vector>
#include <SDL.h>

#include "Tile.h"


class TileGrid {

public:

	std::vector<SDL_Rect> blocks;
	int width;
	int height;
	int rectSize;

	int gridSize;

	SDL_Renderer* renderer;

	TileGrid(SDL_Renderer* render, int sizeX, int sizeY, int rectSize) {
		this->renderer = render;
		this->width = sizeX;
		this->height = sizeY;
		this->rectSize = rectSize;
		this->gridSize = width / rectSize;//800x600=25units
	}

	bool Initialize() {


		//PrintGridPositions();

		return true;
	}

	void Render() {
		SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
		for (int i = 0; i < gridSize; i++) {
			SDL_RenderDrawLine(renderer, 400, i * rectSize, width+400, i * rectSize);
			SDL_RenderDrawLine(renderer, 400 + (i * rectSize), 0, 400 + (i * rectSize), height);
		}
	}
private:
	void PrintGridPositions() {
		for (int i = 0; i < gridSize; i++) {
			// 400, 432, 1200, 432
			// 400,0  432,0
			int colX1 = 400;
			int colY1 = i * rectSize;
			int colX2 = width;
			int colY2 = colY1;

			int rowX1 = 400 + (i * rectSize);
			int rowY1 = 0;
			int rowX2 = rowX1;
			int rowY2 = height;
			//top {x1:400, y1:0,  x2:432, y2:0}
			//dow{ x1:400, y1 : 32, x2 : 432, y2 : 32 }

			//printf("i = %d row[%d,%d,%d,%d]\n", i, colX1, colY1, colX2, colY2);
			//printf("i = %d col[%d,%d,%d,%d]\n", i, rowX1, rowY1, rowX2, rowY2);
			printf("top{%d,%d,%d,%d}\ndown{%d,%d,%d,%d}\n\n", 400, i * rectSize, 400 + (i * rectSize), i * rectSize, 400, i * rectSize, 400 + rectSize, i * rectSize);
		}
	}
};
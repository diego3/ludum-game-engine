#pragma once

#include <SDL.h>

class Tile {
public:
	SDL_Rect source;
	SDL_Rect destination;
	int index;

	Tile(int x, int y, int dx, int dy) {
		source = { x, y, 32,32 };//texture coordinate
		destination = { dx, dy, 32, 32 };//screen coordinate
		index = 0;
	}

	Tile(int x, int y, int dx, int dy, int index) {
		source = { x, y, 32,32 };//texture coordinate
		destination = { dx, dy, 32, 32 };//screen coordinate
		this->index = index;
	}
};
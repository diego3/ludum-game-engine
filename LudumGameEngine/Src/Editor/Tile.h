#pragma once

#include <SDL.h>

class Tile {
public:
	SDL_Rect source;
	SDL_Rect destination;
	Tile(int x, int y, int dx, int dy) {
		source = { x, y, 32,32 };//texture coordinate
		destination = { dx, dy, 32, 32 };//screen coordinate
	}
};
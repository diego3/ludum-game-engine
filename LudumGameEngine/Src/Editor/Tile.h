#pragma once

#include <SDL.h>

class Tile {
public:
	SDL_Rect source;
	SDL_Rect destination;
	int index;
	int size;
	bool IsSelected;

	Tile(int x, int y, int dx, int dy) {
		size = 32;
		source = { x, y, 32, 32};//texture coordinate
		destination = { dx, dy, 32, 32};//screen coordinate
		index = 0;
		IsSelected = false;
	}

	Tile(int x, int y, int dx, int dy, int index) {
		size = 32;
		source = { x, y, 32,32 };//texture coordinate
		destination = { dx, dy, 32, 32 };//screen coordinate
		this->index = index;
		IsSelected = false;
	}
};
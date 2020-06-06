#pragma once

#include <SDL.h>

class Collision {
public:

	static bool CheckRectangleCollision(SDL_Rect& a, SDL_Rect& b);
};
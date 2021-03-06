#pragma once

#include <SDL.h>
#include "../Core/Collision.h"

//https://editor.p5js.org/gustavocp/sketches/PEAwEgwT
bool Collision::CheckRectangleCollision(SDL_Rect& a, SDL_Rect& b) {
	return (
		a.x + a.w > b.x &&
		b.x + b.w > a.x &&
		a.y + a.h > b.y &&
		b.y + b.h > a.y
	);
}
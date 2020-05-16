#pragma once

#include <SDL.h>
#include <string>

class TextureManager {

public:
	static SDL_Texture* LoadTexture(std::string fileName);
	static void Draw(SDL_Texture* texture, SDL_Rect source, 
		SDL_Rect destination, SDL_RendererFlip flip);
};
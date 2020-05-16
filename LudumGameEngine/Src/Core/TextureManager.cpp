#include "Game.h"
#include "TextureManager.h"
#include "../../Libs/SDL2_image-2.0.5/include/SDL_image.h"

SDL_Texture* TextureManager::LoadTexture(std::string fileName)
{
	SDL_Surface* surface = IMG_Load(fileName.c_str());
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
	return texture;
}

void TextureManager::Draw(SDL_Texture* texture, SDL_Rect source, 
	SDL_Rect destination, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(Game::renderer, texture, &source, &destination, 0.0f, NULL, flip);
}

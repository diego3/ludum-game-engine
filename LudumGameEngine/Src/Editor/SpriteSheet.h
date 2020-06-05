#pragma once

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>


class SpriteSheet {
public:
	int index = 0;
	SDL_Texture* texture;
	SDL_Rect source;
	SDL_Rect destination;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	SDL_Renderer* renderer;// *****

	int width;
	int height;
	int tileSize;
	int queryWidth;
	int queryHeight;

	bool loadTextureError = false;
	std::string loadError;

	SpriteSheet(SDL_Renderer* render, std::string textureFilePath, int width, int height, int tileSize) {
		this->renderer = render;
		this->width = width;
		this->height = height;
		this->tileSize = tileSize;
		loadError = "";
		texture = LoadTexture(textureFilePath);
		if (texture) {
			SDL_QueryTexture(texture, NULL, NULL, &queryWidth, &queryHeight);
			printf("spritesheet {%d, %d}\n", queryWidth, queryHeight);
			source = { 0,0, width, height };
			destination = { 0,0, width,height };
		}
	}

	~SpriteSheet() {
		if (texture) {
			SDL_DestroyTexture(texture);
		}
	}

	void Render() {
		if (!texture) return;
		SDL_RenderCopyEx(renderer, texture, &source, &destination, 0.0f, NULL, flip);
	}

	SDL_Texture* LoadTexture(std::string fileName)
	{
		SDL_Surface* surface = IMG_Load(fileName.c_str());
		if (!surface) {
			printf("IMG_Load: %s\n", IMG_GetError());
			loadError = IMG_GetError();
			loadTextureError = true;
			return NULL;
		}
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);//*******
		return texture;
	}

};
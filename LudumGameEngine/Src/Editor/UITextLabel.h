#pragma once

#include <string>
#include <SDL.h>
#include <SDL_ttf.h>


class UITextLabel {
public:
	std::string text;
	std::string fontFilePath;
	TTF_Font* font;
	int fontSize;
	SDL_Texture* textTexture;
	SDL_Surface* textSurface;
	SDL_Rect* position;
	SDL_Color textColor;
	
	SDL_Renderer* renderer;

	bool textChanged = false;

	UITextLabel(SDL_Renderer* render, std::string fontPath, int size, SDL_Rect* pos, SDL_Color color) {
		renderer = render;
		fontFilePath = fontPath;
		fontSize = size;
		position = pos;
		textColor = color;
	}

	~UITextLabel(){
		if (font) {
			TTF_CloseFont(font);
		}
	}

	bool Initialize() {
		font = TTF_OpenFont(fontFilePath.c_str(), fontSize);
		if (!font) {
			printf("TTF_OpenFont error %s\n", TTF_GetError());
			return false;
		}
		//text = "Hello";
		textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
		textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		SDL_QueryTexture(textTexture, NULL, NULL, &position->w, &position->h);

		//printf("text pos {%d,%d,%d,%d}\n", position->x, position->y, position->w, position->h);
		return true;
	}

	void Render() {
		if (textChanged) {
			SDL_DestroyTexture(textTexture);
			textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
			textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
			if (textSurface) {
				SDL_FreeSurface(textSurface);
			}
			SDL_QueryTexture(textTexture, NULL, NULL, &position->w, &position->h);
			textChanged = false;
		}


		SDL_RenderCopy(renderer, textTexture, NULL, position);
	}


	void SetText(std::string val) {
		if (val.compare(this->text) != 0) {
			textChanged = true;
		}
		this->text = val;
	}

	std::string GetText() {
		return this->text;
	}
};
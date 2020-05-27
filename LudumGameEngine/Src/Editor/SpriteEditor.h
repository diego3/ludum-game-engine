#pragma once

//extern "C" {
//#include "../../Libs/lua-5.3.5_Win32_dllw6_lib/include/lua.h"
//#include "../../Libs/lua-5.3.5_Win32_dllw6_lib/include/lauxlib.h"
//#include "../../Libs/lua-5.3.5_Win32_dllw6_lib/include/lualib.h"
//}
//#include "../../Libs/lua-5.3.5_Win32_dllw6_lib/include/sol.hpp"
#ifdef _WIN32
//#pragma comment(lib, "Libs/lua-5.3.5_Win32_dllw6_lib/liblua53.a")
#endif // WIN



#include <iostream>
#include <SDL.h>
#include <vector>
#include "../../Libs/SDL2_image-2.0.5/include/SDL_image.h"
//#include "../../Libs/SDL2_ttf-2.0.15/include/SDL_ttf.h"
//#include "../../Libs/glm/glm/vec2.hpp"
#include "../Core/EntityManager.h"
#include "../Core/Map.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/KeyboardControlComponent.h"
#include "../Components/TileMapComponent.h"
#include "../Components/CameraFollowComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Core/Collision.h"


namespace spriteditor {

	const int FPS = 60;
	const int FRAME_RATE = 1000 / FPS;
	const unsigned int WINDOW_WIDTH = 1200;
	const unsigned int WINDOW_HEIGHT = 600;
	float lastFrame = 0.0f;
	bool isRunning = true;
	bool IS_MOUSE_PRESSED = false;

	SDL_Color textColor;

	int mouseX = 0;
	int mouseY = 0;
	int mouseClickPointX = 0;
	int mouseClickPointY = 0;
	bool isLeft = false;
	bool isRight = false;
	bool isUp = false;
	bool isDown = false;
	int gridPosition = 0;
	
	int timer = 60;


	class Tile {
	public:
		SDL_Rect source;
		SDL_Rect destination;
		Tile(int x, int y, int dx, int dy) {
			source = { x, y, 32,32 };//texture coordinate
			destination = { dx, dy, 32, 32 };//screen coordinate
		}
	};


	std::vector<Tile> grid;

	class SpriteEditor {
	public:
		SDL_Window* window;
		SDL_Renderer* renderer;
		SDL_Rect source;
		SDL_Rect destination;
		SDL_RendererFlip flip = SDL_FLIP_NONE;
		SDL_Texture* texture;
		int spriteSize = 32;
		SDL_Rect rectSource;

		SDL_Rect UIArea;

		//TTF_Font* font;
		//SDL_Texture* textTexture;

		~SpriteEditor() {
			if (texture) {
				SDL_DestroyTexture(texture);
			}
			if (renderer) {
				SDL_DestroyRenderer(renderer);
			}
			SDL_DestroyWindow(window);
		}

		void Initialize() {
			if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
				std::cout << "SDL init fails: " << SDL_GetError() << std::endl;
				return;
			}
			window = SDL_CreateWindow(
				"Sprite Editor",
				SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED,
				WINDOW_WIDTH,
				WINDOW_HEIGHT,
				0
			);

			if (window == NULL) {
				std::cout << "sdl window initialization fails: " << SDL_GetError() << std::endl;
				return;
			}
			renderer = SDL_CreateRenderer(window, -1, 0);
			if (renderer == NULL) {
				std::cout << "SDL Renderer error: " << SDL_GetError() << std::endl;
				return;
			}
			
			/*
			if (TTF_Init() == -1) {
				printf("TTF_Init: %s\n", TTF_GetError());
				return;
			}
			textColor = {255,255,255};
			font  = TTF_OpenFont("Assets/fonts/carriot.ttf", 24);
			SDL_Surface* textSurface = TTF_RenderText_Solid(font, "TEXTO", textColor);
			textTexture = SDL_CreateTextureFromSurface(renderer, textSurface); */

			UIArea = {0, 0, 400, 600};

			texture = LoadTexture("Assets/images/jungle.png");//320x96
			source = {0,0, 320, 96};
			destination = {0,0,320,96};
			rectSource = { source.x, source.y, spriteSize, spriteSize };

			lastFrame = SDL_GetTicks();
			while (isRunning) {
				float elapsed = SDL_GetTicks() - lastFrame;
				if (elapsed < FRAME_RATE) {
					SDL_Delay(FRAME_RATE - elapsed);
				}

				float deltaTime = (SDL_GetTicks() - lastFrame) / 1000.0f;
				//std::cout << "deltaTime: " << deltaTime << std::endl;

				ProcessInputs();
				Update(deltaTime);
				Render();

				lastFrame = SDL_GetTicks();

				timer--;
				if (timer <= 0) timer = 60;
			}

		}

		void Update(float deltaTime) {
			if (isRight) {printf("isRight true\n");}
			if (isLeft) {printf("isLeft true\n");}


			if (timer == 60) {
				printf("tiles = %d\n", grid.size());
			}

			//std::cout << "grid " << gridPosition << std::endl;
			//printf("source {x:%d, y:%d}", source.x, source.y);
		}


		void Render() {
			SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
			SDL_RenderClear(renderer);
			
			// UI Background
			//SDL_SetRenderDrawColor(renderer, 200, 200, 200, 1);
			//SDL_RenderFillRect(renderer, &UIArea);

			//SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
			//int x1 = mouseClickPointX;
			//int y1 = mouseClickPointY;
			//int x2 = mouseX;
			//int y2 = mouseY;
			//SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
			//SDL_RenderDrawLine(renderer, 300, 300, 350, 300);
			//SDL_RenderDrawLine(renderer, 300, 350, 350, 350);
			//SDL_RenderDrawLine(renderer, 300, 300, 300, 350);
			//SDL_RenderDrawLine(renderer, 350, 300, 350, 350);

			// Tiles sprite sheet source
			SDL_RenderCopyEx(renderer, texture, &source, &destination, 0.0f, NULL, flip);


			SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
			for (int i = 0; i < (WINDOW_WIDTH/spriteSize); i++) {
				SDL_RenderDrawLine(renderer, 400, i * spriteSize, WINDOW_WIDTH, i * spriteSize);
				SDL_RenderDrawLine(renderer, 400+(i * spriteSize), 0, 400+(i * spriteSize), WINDOW_HEIGHT);
			}

			// draw each tile
			for (Tile tile : grid) {
				SDL_RenderCopyEx(renderer, texture, &tile.source, &tile.destination, 0.0f, NULL, flip);
			}

			
			// separator line between UI area and grid area
			SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
			SDL_RenderDrawLine(renderer, 400, 0, 400, WINDOW_HEIGHT);

			// green navigator rect
			SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
			SDL_RenderDrawRect(renderer, &rectSource);

			SDL_RenderPresent(renderer);
		}

		void ProcessInputs() {
			SDL_Event event;
			if (SDL_PollEvent(&event) > 0) {
				switch (event.type) {
					case SDL_QUIT:
					{
						isRunning = false;
						break;
					}
					case SDL_KEYDOWN:
					{
						if (event.key.keysym.sym == SDLK_ESCAPE) {
							isRunning = false;
							break;
						}
						if (event.key.keysym.sym == SDLK_LEFT) {
							gridPosition--;
							//source.x = gridPosition * spriteSize;
							rectSource.x -= spriteSize;
							isLeft = true;
						}
						if (event.key.keysym.sym == SDLK_RIGHT) {
							gridPosition++;
							//source.x = gridPosition * spriteSize;
							rectSource.x += spriteSize;
							isRight = true;
						}
						if (event.key.keysym.sym == SDLK_UP) {
							rectSource.y -= spriteSize;
							isUp = true;
						}
						if (event.key.keysym.sym == SDLK_DOWN) {
							rectSource.y += spriteSize;
							isDown = true;
						}
					}
					case SDL_KEYUP: {
						if (event.key.keysym.sym == SDLK_LEFT) {
							isLeft = false;
						}
						if (event.key.keysym.sym == SDLK_RIGHT) {
							isRight = false;
						}
						if (event.key.keysym.sym == SDLK_UP) {
							isUp = false;
						}
						if (event.key.keysym.sym == SDLK_DOWN) {
							isDown = false;
						}
					}
					case SDL_MOUSEBUTTONDOWN:
					{
						if (event.button.button == SDL_BUTTON_LEFT
							&& event.button.state == SDL_PRESSED) {
							IS_MOUSE_PRESSED = true;

							mouseClickPointX = event.button.x;
							mouseClickPointY = event.button.y;
							//AddTile(mouseClickPointX, mouseClickPointY);
							
							mouseX = event.button.x;
							mouseY = event.button.y;
							//printf("x[%d] y[%d]\n", event.button.x, event.button.y);
						}
					}
					case SDL_MOUSEBUTTONUP:
					{
						if (event.button.button == SDL_BUTTON_LEFT
							&& event.button.state == SDL_RELEASED) {
							//std::cout << "button UP" << std::endl;
							IS_MOUSE_PRESSED = false;
						}
					}
					case SDL_MOUSEMOTION:
					{
						if (IS_MOUSE_PRESSED) {
							mouseX = event.button.x;
							mouseY = event.button.y;

							AddTile(mouseX, mouseY);
							//printf("x[%d] y[%d]\n", event.button.x, event.button.y);
						}
					}
				}
			}

		}

		void AddTile(int x, int y) {
			SDL_Rect mousePos = { x -(spriteSize/2),y-(spriteSize/2),spriteSize, spriteSize};
			bool intersect = Collision::CheckRectangleCollision(mousePos, UIArea);
			if (intersect) {
				printf("no draw area\n");
				return;
			}
			Tile t(rectSource.x, rectSource.y, x-(spriteSize/2), y-(spriteSize/2));

			grid.push_back(t);
		}

		SDL_Texture* LoadTexture(std::string fileName)
		{
			SDL_Surface* surface = IMG_Load(fileName.c_str());
			SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
			return texture;
		}
	};
}
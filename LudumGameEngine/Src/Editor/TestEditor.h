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
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "../../Libs/glm/glm/vec2.hpp"
#include "../../Libs/glm/glm/ext.hpp"


namespace editor2 {

	const int FPS = 60;
	const int FRAME_RATE = 1000 / FPS;
	const unsigned int WINDOW_WIDTH = 1200;
	const unsigned int WINDOW_HEIGHT = 600;
	int lastFrame = 0;
	bool isRunning = true;
	bool IS_MOUSE_PRESSED = false;

	int mouseX = 0;
	int mouseY = 0;
	int mouseClickPointX = 0;
	int mouseClickPointY = 0;

	int gridPosition = 0;

	int timer = 60;

	class TestEditor {
	public:
		SDL_Window* window;
		SDL_Renderer* renderer;
		SDL_Rect source;
		SDL_Rect destination;
		SDL_Texture* texture;
		int spriteSize = 64;
		SDL_Rect rectSource;

		SDL_Rect UIArea;

		TestEditor() {
			UIArea = {0,0,0,0};
			renderer = NULL;
			window = NULL;
			texture = NULL;
			rectSource = {0,0,0,0};
			source = {0,0,0,0};
			destination = {0,0,0,0};
		}

		~TestEditor() {
			
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
				"Test Editor",
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


			if (TTF_Init() == -1) {
				printf("TTF_Init: %s\n", TTF_GetError());
				return;
			}

			lastFrame = SDL_GetTicks();
			while (isRunning) {
				int elapsed = SDL_GetTicks() - lastFrame;
				if (elapsed < FRAME_RATE) {
					SDL_Delay(FRAME_RATE - elapsed);
				}

				float deltaTime = (float)(SDL_GetTicks() - lastFrame) / 1000.0f;
				std::cout << "deltaTime: " << deltaTime << std::endl;

				ProcessInputs();
				Update(deltaTime);
				Render();

				lastFrame = SDL_GetTicks();

				timer--;
				if (timer <= 0) timer = 60;
			}

		}

		void Update(float deltaTime) {
			

			if (timer == 60) {
				
			}

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
			//SDL_RenderCopyEx(renderer, texture, &source, &destination, 0.0f, NULL, flip);

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
							rectSource.x -= spriteSize;

						}
						if (event.key.keysym.sym == SDLK_RIGHT) {
							gridPosition++;
							rectSource.x += spriteSize;
						}
						if (event.key.keysym.sym == SDLK_UP) {
							rectSource.y -= spriteSize;
						}
						if (event.key.keysym.sym == SDLK_DOWN) {
							rectSource.y += spriteSize;
						}
					}
					case SDL_KEYUP: {
						if (event.key.keysym.sym == SDLK_LEFT) {

						}
						if (event.key.keysym.sym == SDLK_RIGHT) {

						}
						if (event.key.keysym.sym == SDLK_UP) {

						}
						if (event.key.keysym.sym == SDLK_DOWN) {

						}
					}
					case SDL_MOUSEBUTTONDOWN:
					{
						if (event.button.button == SDL_BUTTON_LEFT
							&& event.button.state == SDL_PRESSED) {
							IS_MOUSE_PRESSED = true;

							mouseClickPointX = event.button.x;
							mouseClickPointY = event.button.y;

							mouseX = event.button.x;
							mouseY = event.button.y;
							printf("x[%d] y[%d]\n", event.button.x, event.button.y);
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
							//printf("x[%d] y[%d]\n", event.button.x, event.button.y);
						}
					}
				}
			}

		}


		SDL_Texture* LoadTexture(std::string fileName)
		{
			SDL_Surface* surface = IMG_Load(fileName.c_str());
			SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
			return texture;
		}
	};
}
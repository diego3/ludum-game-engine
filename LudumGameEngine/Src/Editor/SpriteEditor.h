#pragma once

#include <iostream>
#include <SDL.h>
#include "../../Libs/SDL2_image-2.0.5/include/SDL_image.h"
#include "../../Libs/SDL2_ttf-2.0.15/include/SDL_ttf.h"
#include "../../Libs/glm/glm/vec2.hpp"

extern "C" {
#include "../../Libs/lua-5.3.5_Win32_dllw6_lib/include/lua.h"
#include "../../Libs/lua-5.3.5_Win32_dllw6_lib/include/lauxlib.h"
#include "../../Libs/lua-5.3.5_Win32_dllw6_lib/include/lualib.h"
}

#include "../../Libs/lua-5.3.5_Win32_dllw6_lib/include/sol.hpp"

#include "../Core/EntityManager.h"
//#include "LuaManager.h"
#include "../Core/Map.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/KeyboardControlComponent.h"
#include "../Components/TileMapComponent.h"
#include "../Components/CameraFollowComponent.h"
#include "../Components/BoxColliderComponent.h"

#ifdef _WIN32
#pragma comment(lib, "Libs/SDL2_image-2.0.5/lib/x86/SDL2_image.lib")
#pragma comment(lib, "Libs/SDL2_ttf-2.0.15/lib/x86/SDL2_ttf.lib")
#pragma comment(lib, "Libs/lua-5.3.5_Win32_dllw6_lib/liblua53.a")
#endif // WIN

namespace spriteditor {

	const int FPS = 60;
	const int FRAME_RATE = 1000 / FPS;
	const unsigned int WINDOW_WIDTH = 800;
	const unsigned int WINDOW_HEIGHT = 600;
	float lastFrame = 0.0f;
	bool isRunning = true;
	bool IS_MOUSE_PRESSED = false;

	int mouseX = 0;
	int mouseY = 0;
	int mouseClickPointX = 0;
	int mouseClickPointY = 0;
	bool isLeft = false;
	bool isRight = false;
	bool isUp = false;
	bool isDown = false;
	int gridPosition = 0;
	
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
				Render(deltaTime);

				lastFrame = SDL_GetTicks();
			}

		}

		void Update(float deltaTime) {
			if (isRight) {
				printf("isRight true\n");

			}
			if (isLeft) {
				printf("isLeft true\n");
				
			}

			//std::cout << "grid " << gridPosition << std::endl;
			//printf("source {x:%d, y:%d}", source.x, source.y);
		}


		void Render(float deltaTime) {
			SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
			SDL_RenderClear(renderer);
			/* pasted from transform component, just in case
				SDL_Rect rectangle = {
					(int)position.x,
					(int)position.y,
					width, height
				};

				SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
				SDL_RenderFillRect(Game::renderer, &rectangle);
			*/
			SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
			// acho q precisa de 4 linhas que devem ser desenhadas
			// ao mesmo tempo mas cada uma em sua direção e posição
			// duas pra direita e duas na vertical
			int x1 = mouseClickPointX;
			int y1 = mouseClickPointY;
			int x2 = mouseX;
			int y2 = mouseY;
			SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
			SDL_RenderDrawLine(renderer, 300, 300, 350, 300);
			SDL_RenderDrawLine(renderer, 300, 350, 350, 350);
			SDL_RenderDrawLine(renderer, 300, 300, 300, 350);
			SDL_RenderDrawLine(renderer, 350, 300, 350, 350);
			SDL_RenderCopyEx(renderer, texture, &source, &destination, 0.0f, NULL, flip);

			
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
							mouseX = event.button.x;
							mouseY = event.button.y;
							std::cout << "x[" << event.button.x
								<< "]y[" << event.button.y << "]" << std::endl;
						}
					}
					case SDL_MOUSEBUTTONUP:
					{
						if (event.button.button == SDL_BUTTON_LEFT
							&& event.button.state == SDL_RELEASED) {
							std::cout << "button UP" << std::endl;
							IS_MOUSE_PRESSED = false;
							//mouseX = 0;
							//mouseY = 0;
						}
					}
					case SDL_MOUSEMOTION:
					{
						if (IS_MOUSE_PRESSED) {
							mouseX = event.button.x;
							mouseY = event.button.y;
							std::cout << "paiting x[" << event.button.x
								<< "]y[" << event.button.y << "]" << std::endl;
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
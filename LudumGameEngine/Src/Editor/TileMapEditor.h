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
#include <vector>

#include <SDL.h>
#include <SDL_image.h>

#include "../Core/Collision.h"
#include "Tile.h"
#include "TileGrid.h"
#include "UITextLabel.h"
#include "SpriteSheet.h"

namespace editor {

	const int FPS = 60;
	const int FRAME_RATE = 1000 / FPS;
	const unsigned int WINDOW_WIDTH = 1200;
	const unsigned int WINDOW_HEIGHT = 600;
	const char* saveMapFilePath = "Assets/tilemaps/save-test.map";
	float lastFrame = 0.0f;
	bool isRunning = true;
	bool IS_MOUSE_PRESSED = false;
	bool IsCRTLDown = false;

	int mouseX = 0;
	int mouseY = 0;
	int mouseClickPointX = 0;
	int mouseClickPointY = 0;

	bool isLeft = false;
	bool isRight = false;
	bool isUp = false;
	bool isDown = false;

	int gridPositionX = 0;
	int gridPositionY = 0;
	int gridMaxX = 0;
	int gridMaxY = 0;


	int timer = 60;

	class SpriteRectNav {
		int curIndex;
		int size;
		SDL_Rect pos;
		SDL_Renderer* renderer;

		SpriteRectNav(SDL_Renderer* render, int index, int size) {
			renderer = render;
			curIndex = index;
			this->size = size;
		}
		
		void Render() {
			SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
			SDL_RenderDrawRect(renderer, &pos);
		}
	};


	class TileMapEditor {
	public:
		SDL_Window* window;
		SDL_Renderer* renderer;
		SDL_Rect source;
		SDL_Rect destination;
		int spriteSize = 32;
		SDL_Rect rectSource;

		SDL_Rect UIArea;
		TileGrid* grid;

		int usedBlocks = 0;

		UITextLabel* text1;
		UITextLabel* tilesLabel;
		UITextLabel* tilesQtd;
		
		SpriteSheet* sprite;

		int elapsedSeconds = 0;

		SDL_Joystick* joy;
		SDL_GameController* controller;

		~TileMapEditor() {
			if (sprite) {
				delete sprite;
			}
			if (grid) {
				delete grid;
			}

			if (text1) {
				delete text1;
			}
			if (tilesLabel) {
				delete tilesLabel;
			}
			if (tilesQtd) {
				delete tilesQtd;
			}

			if (joy && SDL_JoystickGetAttached(joy)) {
				SDL_JoystickClose(joy);
			}
			if (controller) {
				SDL_GameControllerClose(controller);
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
				"Tile Map Editor",
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
				printf("TTF_Init fails: %s\n", TTF_GetError());
				return;
			}

			
			// TODO  Panel UI Component to group this text labels
			SDL_Color textColor = { 255, 0, 0, 255 };
			SDL_Rect textPosition = { 10, 200, 20, 100 };
			text1 = new UITextLabel(renderer, "Assets/fonts/higher-jump.regular.ttf",
				10, &textPosition, textColor);
			if (!text1->Initialize()) {
				return;
			}

			SDL_Rect pos2 = { 10, 150, 20, 100 };
			tilesLabel = new UITextLabel(renderer, "Assets/fonts/arial.ttf",
				20, &pos2, textColor);
			if (!tilesLabel->Initialize()) {
				return;
			}
			tilesLabel->SetText("Tiles: ");

			SDL_Rect pos3 = {70, 150, 20, 100 };
			tilesQtd = new UITextLabel(renderer, "Assets/fonts/arial.ttf",
				20, &pos3, textColor);
			if (!tilesQtd->Initialize()) {
				return;
			}
			tilesQtd->SetText("0");

			UIArea = { 0, 0, 400, 600 };

			sprite = new SpriteSheet(renderer, "Assets/images/jungle.png", 320, 96, spriteSize);
			gridMaxX = sprite->width / spriteSize;
			gridMaxY = sprite->height / spriteSize;
			printf("maxes: {%d, %d}\n", gridMaxX, gridMaxY);

			grid = new TileGrid(renderer, sprite, 800, 600, spriteSize);
			if (!grid->Initialize()) {
				printf("Tile grid initialize fails\n");
				return;
			}
			rectSource = {sprite->source.x, sprite->source.y, spriteSize, spriteSize};



			//JoystickInitialization();

			Looping();

		}

		void JoystickInitialization() {
			for (int i = 0; i < SDL_NumJoysticks(); ++i) {
				if (SDL_IsGameController(i)) {
					printf("Joystick %i is supported by the game controller interface!\n", i);

					char* mapping;
					controller = SDL_GameControllerOpen(i);
					mapping = SDL_GameControllerMapping(controller);
					std::cout << "mapping " << mapping << std::endl;

					int r = SDL_GameControllerRumble(controller, 0xFFFF, 0xFFFF, 500);
					if (r == -1) {
						printf("Rumble is not supported\n");
					}
				}
			}

			joy = SDL_JoystickOpen(0);

			if (joy) {
				printf("Opened Joystick 0\n");
				printf("Name: %s\n", SDL_JoystickNameForIndex(0));
				printf("Number of Axes: %d\n", SDL_JoystickNumAxes(joy));
				printf("Number of Buttons: %d\n", SDL_JoystickNumButtons(joy));
				printf("Number of Balls: %d\n", SDL_JoystickNumBalls(joy));
				printf("Number of Hats: %d\n", SDL_JoystickNumHats(joy));
			}
			else {
				printf("Couldn't open Joystick 0\n");
			}

			// Close if opened
			//if (SDL_JoystickGetAttached(joy)) {
			//	SDL_JoystickClose(joy);
			//}
		}

		void Looping() {
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
			
			if (timer == 60) {
				elapsedSeconds++;

				text1->SetVal(elapsedSeconds);
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
			sprite->Render();
			// draw the grid with the selected tiles
			grid->Render();


			text1->Render();
			tilesLabel->Render();
			tilesQtd->Render();

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
							if (gridPositionX > 0) {
								gridPositionX--;
								rectSource.x -= spriteSize;
							}
							//printf("x %d\n", gridPositionX);
						}
						if (event.key.keysym.sym == SDLK_RIGHT) {
							if (gridPositionX < gridMaxX-1) {//until 9 (-1 becouse we start at 0 index)
								gridPositionX++;
								rectSource.x += spriteSize;
							}
							//printf("x %d\n", gridPositionX);
						}
						if (event.key.keysym.sym == SDLK_UP) {
							if (gridPositionY > 0) {
								gridPositionY--;
								rectSource.y -= spriteSize;
							}
							//printf("y %d\n", gridPositionY);
						}
						if (event.key.keysym.sym == SDLK_DOWN) {
							if (gridPositionY < (gridMaxY-1)) {
								gridPositionY++;
								rectSource.y += spriteSize;
							}
							//printf("y %d\n", gridPositionY);
						}
						if (event.key.keysym.sym == SDLK_LCTRL && event.key.state == SDL_PRESSED) {
							IsCRTLDown = true;
						}
						
						if (event.key.keysym.sym == SDLK_s && IsCRTLDown) {
							printf("Saving...");
							grid->Save(saveMapFilePath);
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
						if (event.key.keysym.sym == SDLK_LCTRL && event.key.state != SDL_PRESSED) {
							IsCRTLDown = false;
						}
					}
					
					case SDL_MOUSEBUTTONDOWN:
					{
						if (event.button.button == SDL_BUTTON_LEFT && event.button.state == SDL_PRESSED) {
							IS_MOUSE_PRESSED = true;

							mouseClickPointX = event.button.x;
							mouseClickPointY = event.button.y;
							//AddTile(mouseClickPointX, mouseClickPointY);

							mouseX = event.button.x;
							mouseY = event.button.y;
							printf("x[%d] y[%d]\n", event.button.x, event.button.y);
						}
					}
					case SDL_MOUSEBUTTONUP:
					{
						if (event.button.button == SDL_BUTTON_LEFT && event.button.state == SDL_RELEASED) {
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

					case SDL_CONTROLLERBUTTONDOWN: {
						if (event.cbutton.state == SDL_PRESSED) {
							//printf("*****BUTTON*****\n\n");
							switch (event.cbutton.button) {
								case SDL_CONTROLLER_BUTTON_A: {
									//printf("SDL_CONTROLLER_BUTTON_A\n"); break;
								}
								case SDL_CONTROLLER_BUTTON_B: {
									//printf("SDL_CONTROLLER_BUTTON_B\n"); break;
								}
								case SDL_CONTROLLER_BUTTON_X: {
									//printf("SDL_CONTROLLER_BUTTON_X\n"); break;
								}
								case SDL_CONTROLLER_BUTTON_Y: {
									//printf("SDL_CONTROLLER_BUTTON_Y\n"); break;
								}
								case SDL_CONTROLLER_BUTTON_BACK: {
									//printf("SDL_CONTROLLER_BUTTON_BACK\n"); break;
								}
								case SDL_CONTROLLER_BUTTON_START: {
									//printf("SDL_CONTROLLER_BUTTON_START\n"); break;
								}
								case SDL_CONTROLLER_BUTTON_GUIDE: {
									//printf("SDL_CONTROLLER_BUTTON_GUIDE\n"); break;
								}
								case SDL_CONTROLLER_BUTTON_INVALID: {
									//printf("SDL_CONTROLLER_BUTTON_INVALID\n"); break;
								}
								case SDL_CONTROLLER_BUTTON_LEFTSHOULDER: {
									//printf("SDL_CONTROLLER_BUTTON_LEFTSHOULDER\n"); break;
								}
								case SDL_CONTROLLER_BUTTON_LEFTSTICK: {
									//printf("SDL_CONTROLLER_BUTTON_LEFTSTICK\n"); break;
								}
								case SDL_CONTROLLER_BUTTON_MAX: {
									//printf("SDL_CONTROLLER_BUTTON_MAX\n"); break;
								}
								case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER: {
									//printf("SDL_CONTROLLER_BUTTON_RIGHTSHOULDER\n"); break;
								}
								case SDL_CONTROLLER_BUTTON_RIGHTSTICK: {
									//printf("SDL_CONTROLLER_BUTTON_RIGHTSTICK\n"); break;
								}
								case SDL_CONTROLLER_BUTTON_DPAD_DOWN: {
									//printf("SDL_CONTROLLER_BUTTON_DPAD_DOWN\n"); break;
								}
								case SDL_CONTROLLER_BUTTON_DPAD_UP: {
									//printf("SDL_CONTROLLER_BUTTON_DPAD_UP\n"); break;
								}
								case SDL_CONTROLLER_BUTTON_DPAD_LEFT: {
									//printf("SDL_CONTROLLER_BUTTON_DPAD_LEFT\n"); break;
								}
								case SDL_CONTROLLER_BUTTON_DPAD_RIGHT: {
									//printf("SDL_CONTROLLER_BUTTON_DPAD_RIGHT\n"); break;
								}
							}
							//printf("\n\n\n");
						}
					}
					case SDL_CONTROLLERAXISMOTION: {
						//printf("*****AXIS*****\n\n");
						//std::cout << "caxis index: " << event.caxis.axis << std::endl;
						//std::cout << "caxis value: " << event.caxis.value << std::endl;
						if (event.caxis.axis == SDL_CONTROLLER_AXIS_LEFTX) {
							//std::cout << "AXIS_LEFTX" << std::endl;
						}
					}
				}
				
			}

		}

		void AddTile(int x, int y) {
			SDL_Rect mousePos = { x , y , spriteSize, spriteSize };
			bool intersect = Collision::CheckRectangleCollision(mousePos, UIArea);
			if (intersect) {
				printf("no draw area\n");
				return;
			}

			int tileX = x - (spriteSize / 2);
			int tileY = y - (spriteSize / 2);
			SDL_Point clicked = {x, y};
			Tile* tile = grid->GetTileAtPosition(clicked);
			if (!tile) {
				return;
			}

			if (!tile->IsSelected) {
				++usedBlocks;
			}

			tile->IsSelected = true;

			tile->source.x = rectSource.x;
			tile->source.y = rectSource.y;

			int calculatedIndex = gridPositionX + ((gridPositionY * gridMaxX));

			//printf("{%d, %d} = %d\n", gridPositionX, gridPositionY, calc);

			tile->index = calculatedIndex;

			tilesQtd->SetVal(usedBlocks);
		}

		
	};
}
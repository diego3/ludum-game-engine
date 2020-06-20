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
#include "../../Libs/glm/glm/vec2.hpp"
#include "../../Libs/glm/glm/ext.hpp"
#include "../Decoupling/EventManager.h"
#include <memory>

namespace experiment {

	const int FPS = 60;
	const int FRAME_RATE = 1000 / FPS;
	const unsigned int WINDOW_WIDTH = 1200;
	const unsigned int WINDOW_HEIGHT = 600;
	int lastFrame = 0;
	bool isRunning = true;
	bool IS_MOUSE_PRESSED = false;

	int mouseX = 0;
	int mouseY = 0;

	

	class Player {
	public:
		void MoveLeft(IEventData evtData) {
			printf("player move left, %s\n", evtData.name);
		}
		void MoveRight(IEventData evtData) {
			printf("player move right, %s\n", evtData.name);
		}

		void OnCollisionEnter(IEventData evtData) {
			EventCollision evt = dynamic_cast<EventCollision>(evtData);
			
			std::cout << "OnCollisionEnter" << &evt.other << std::endl;
		}
	};

	class EventCollision : public IEventData {
	public:
		Player other;
		EventCollision(EventType type, const char* name, Player object)
			: IEventData(type, name)
		{
			other = object;
		}
	};

	class EventQueueExperiment {
	public:
		SDL_Window* window;
		SDL_Renderer* renderer;

		Player* player;

		EventQueueExperiment() {
			renderer = NULL;
			window = NULL;
			player = NULL;
		}

		~EventQueueExperiment() {

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
			window = SDL_CreateWindow("Event Queue Experiment", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT,0);

			if (window == NULL) {
				std::cout << "sdl window initialization fails: " << SDL_GetError() << std::endl;
				return;
			}
			renderer = SDL_CreateRenderer(window, -1, 0);
			if (renderer == NULL) {
				std::cout << "SDL Renderer error: " << SDL_GetError() << std::endl;
				return;
			}

			player = new Player();

			EventManager::Get()->AddListener(EventType::PLAYER_MOVE_LEFT, std::bind(&Player::MoveLeft, player, std::placeholders::_1));
			EventManager::Get()->AddListener(EventType::PLAYER_MOVE_RIGHT, std::bind(&Player::MoveRight, player, std::placeholders::_1));
			EventManager::Get()->AddListener(EventType::COLLISION_ENTER, std::bind(&Player::OnCollisionEnter, player, std::placeholders::_1));

			lastFrame = SDL_GetTicks();
			while (isRunning) {
				int elapsed = SDL_GetTicks() - lastFrame;
				if (elapsed < FRAME_RATE) {
					SDL_Delay(FRAME_RATE - elapsed);
				}

				float deltaTime = (float)(SDL_GetTicks() - lastFrame) / 1000.0f;
				//std::cout << "deltaTime: " << deltaTime << std::endl;

				ProcessInputs();
				Update(deltaTime);
				Render();

				lastFrame = SDL_GetTicks();
			}

			delete player;
			delete EventManager::Get();
		}

		void Update(float deltaTime) {
			EventManager::Get()->Update(deltaTime);

			
		}


		void Render() {
			SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
			SDL_RenderClear(renderer);


			// separator line between UI area and grid area
			SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
			SDL_RenderDrawLine(renderer, 400, 0, 400, WINDOW_HEIGHT);


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
						IEventData eventData(EventType::PLAYER_MOVE_LEFT, "x = -1");
						EventManager::Get()->QueueEvent(eventData);
						
					}
					if (event.key.keysym.sym == SDLK_RIGHT) {
						IEventData eventData(EventType::PLAYER_MOVE_RIGHT, "x = +1");
						EventManager::Get()->QueueEvent(eventData);

					}
					if (event.key.keysym.sym == SDLK_UP) {
						EventCollision colEventData(EventType::COLLISION_ENTER, "collision Enter with player", *player);
						EventManager::Get()->QueueEvent(colEventData);
					}
					if (event.key.keysym.sym == SDLK_DOWN) {

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
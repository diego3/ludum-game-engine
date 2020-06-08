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
#include <SDL_mixer.h>
#include "../../Libs/glm/glm/vec2.hpp"
#include "../../Libs/glm/glm/ext.hpp"
#include "../Core/AudioManager.h"

namespace audio {

	const int FPS = 60;
	const int FRAME_RATE = 1000 / FPS;
	const unsigned int WINDOW_WIDTH = 1200;
	const unsigned int WINDOW_HEIGHT = 600;
	int lastFrame = 0;
	bool isRunning = true;
	bool IS_MOUSE_PRESSED = false;

	int mouseX = 0;
	int mouseY = 0;

	int timer = 60;

	std::string acousticThemePath = "Assets/sounds/acoustic-theme.ogg";
	std::string gun1Path = "Assets/sounds/Shooting An MP5-SoundBible.com.mp3";
	std::string gun2Path = "Assets/sounds/Machine_Gun4.mp3";

	//https://soundprogramming.net/programming/tutorial-using-sdl2-and-sdl_mixer-to-play-samples/
	class AudioMixerEditor {
	public:
		SDL_Window* window;
		SDL_Renderer* renderer;
		Mix_Chunk* chunk;
		AudioManager* audioManager;

		AudioMixerEditor() {
			renderer = NULL;
			window = NULL;
			chunk = NULL;
			audioManager = NULL;
		}

		~AudioMixerEditor() {
			if (audioManager) {
				delete audioManager;
			}

			if (chunk) {
				Mix_FreeChunk(chunk);
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
				"Audio Mixer Editor",
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

			audioManager = new AudioManager();
			if (!audioManager->Initialize()) {
				return;
			}

			chunk = AudioManager::LoadAudio(gun1Path.c_str());
			if (!chunk) {
				return;
			}


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


					}
					if (event.key.keysym.sym == SDLK_RIGHT) {

					}
					if (event.key.keysym.sym == SDLK_UP) {

					}
					if (event.key.keysym.sym == SDLK_DOWN) {

					}
					if (event.key.keysym.sym == SDLK_p) {
						printf("play audio\n");
						audioManager->PlayOnce(chunk);
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
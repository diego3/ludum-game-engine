#pragma once

//force to use the dedicated graphics card
//extern "C" {
//	__declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
//}

#include <stdio.h>
#include <iostream>
#include <SDL.h>
#include <GL/glew.h>
#include <fstream>
#include "../Util/FileUtil.h"
#include "Exercice.h"

// SDL_GL_GetDrawableSize.
namespace opengl {

	const int FPS = 60;
	const int FRAME_RATE = 1000 / FPS;
	const unsigned int WINDOW_WIDTH = 800;
	const unsigned int WINDOW_HEIGHT = 600;
	int lastFrame = 0;
	bool isRunning = true;

	class Instalation {
	public:
		SDL_Window* window;
		Exercice* shader;

		Instalation() {
			window = NULL;
			shader = NULL;
		}

		~Instalation() {
			if (shader) {
				delete shader;
			}

			if (window) {
				SDL_DestroyWindow(window);
			}
			SDL_Quit();
		}

		bool create() {
			if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
				std::cout << "SDL init fails: " << SDL_GetError() << std::endl;
				return false;
			}

			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

			/*How this stuffs really works????
			Turn on double buffering with a 24bit Z buffer. You may need to change this to 16 or 32 for your system */
			//SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
			//SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

			window = SDL_CreateWindow(
				"OpenGL",
				SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED,
				WINDOW_WIDTH,
				WINDOW_HEIGHT,
				SDL_WINDOW_OPENGL
			);

			if (!window) {
				printf("SDL Windows initialization fails");
				return false;
			}

			
			SDL_GLContext openGLContext = SDL_GL_CreateContext(window);
			if (!openGLContext) {
				printf("SDL_GL_CreateContext fails: %s", SDL_GetError());
				return false;
			}


			glewExperimental = GL_TRUE;
			GLenum error = glewInit();
			if (error != GLEW_OK) {
				printf("glewInit failed");
				SDL_DestroyWindow(window);
				SDL_GL_DeleteContext(openGLContext);
				return false;
			}

			int w;
			int h;
			SDL_GL_GetDrawableSize(window, &w, &h);
			printf("drawable size w:%d, h:%d\n", w, h);

			/* This makes our buffer swap syncronized with the monitor's vertical refresh */
			SDL_GL_SetSwapInterval(1);

			glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
			// 4.6 \0/
			std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

			// ********* APPLICATION CODE ***************
			std::string vShader = FileUtil::ReadFile("Src/OpenGL/vertexShader.vert");
			std::string fShader = FileUtil::ReadFile("Src/OpenGL/fragmentShader.frag");

			shader = new Exercice(vShader.c_str(), fShader.c_str());
			shader->Initialize();

			

			lastFrame = SDL_GetTicks();
			while (isRunning) {
				int elapsed = SDL_GetTicks() - lastFrame;
				if (elapsed < FRAME_RATE) {
					SDL_Delay(FRAME_RATE - elapsed);
				}

				float deltaTime = (float)((SDL_GetTicks() - lastFrame) / 1000.0f);
				//std::cout << "deltaTime: " << deltaTime << std::endl;

				ProcessInputs();
				Update(deltaTime);
				Render();

				lastFrame = SDL_GetTicks();
			}


			SDL_GL_DeleteContext(openGLContext);
			return true;
		}

		void Update(float deltaTime) {
			shader->Update(deltaTime);
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
				}
				}
			}

		}

		void Render() {
			glClearColor(0.f, 0.f, 0.f, 1.f);
			glClear(GL_COLOR_BUFFER_BIT);


			// rendering tasks go here....
			shader->Render();


			SDL_GL_SwapWindow(window);

		}
	};

}
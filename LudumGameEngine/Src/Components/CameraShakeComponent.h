#pragma once

#include <SDL.h>
#include "../Core/Component.h"
#include "TransformComponent.h"
#include "../Core/Game.h"
#include <ctime>

/*
https://jonny.morrill.me/en/blog/gamedev-how-to-implement-a-camera-shake-effect/

*/
class CameraShakeComponent : public Component {
public:
	int from = 0;
	int to = 0;
	int cameraShakingUpdatesLeft = 0;
	int shakeRateX = 1;
	int shakeRateY = 1;
	int duration = 30;
	int algorithm = 2;

	CameraShakeComponent(int algo, int dur) {
		algorithm = algo;
		duration = dur;
	}

	void Initialize() override {
		
		srand((int)time(0));
	}

	void Update(float deltaTime) override {
		if (Game::event.type == SDL_KEYDOWN) {
			std::string keyCode = std::to_string(Game::event.key.keysym.sym);
			if (keyCode.compare("107") == 0) {
				std::cout << "K shake " << std::endl;
				cameraShakingUpdatesLeft = duration;
			}
		}

		switch (algorithm) {
			case 1: {
				Algorithm1();
			}
			case 2: {
				Algorithm2();
			}

		}
	}

	void Render() override {

	}

	void Destroy() {

	}


	void Algorithm1() {
		// https://www.gamedev.net/forums/topic/494297-does-anybody-have-a-good-and-simple-2d-camera-shaking-algorithm/
		// During an update shake the camera (executed 60 times per second)
		if (cameraShakingUpdatesLeft != 0) {
			  // get random number between -15 and 15
			int xAdjustment = (rand() % (30) + (-15)); 
			int yAdjustment = (rand() % (30) + (-15)); 

			Game::camera.x += xAdjustment;
			Game::camera.y += yAdjustment;

			cameraShakingUpdatesLeft--;
		}
	}

	void Algorithm2() {
		/*
		If you want something more smooth, you could use waves.
		To get more random looking smooth waves,
		just add sin/cos waves of differing frequencies together.
		*/
		if (cameraShakingUpdatesLeft != 0) {
			float shakeFreqX = 10;  float shakeFreqY = 8;
			float shakeFreqY2 = 20;  float shakeSizeX = 15;
			float shakeSizeY = 10;  float shakeSizeY2 = 5;
			float t = SDL_GetTicks();
			int xAdjustment = (int)sin(t * shakeRateX) * shakeSizeX;
			int yAdjustment = (int)sin(t * shakeRateY) * shakeSizeY + cos(t * shakeFreqY2) * shakeSizeY2;
			Game::camera.x += xAdjustment;
			Game::camera.y += yAdjustment;
			cameraShakingUpdatesLeft--;
		}
	}
};


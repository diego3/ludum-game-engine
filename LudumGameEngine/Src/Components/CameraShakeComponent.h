#pragma once

#include "../Core/Component.h"
#include "TransformComponent.h"
#include "../Core/Game.h"
#include <ctime>

/*
https://jonny.morrill.me/en/blog/gamedev-how-to-implement-a-camera-shake-effect/

*/
class CameraShakeComponent : public Component {
public:
	TransformComponent* transform;
	

	int from = 0;
	int to = 0;

	void Initialize() override {
		
		srand((int)time(0));
	}

	int Next(int a, int b) {
		return (rand() % (b*2) + (a));
	}

	int NextPositives(int a, int b) {
		return (rand() % a + (b));
	}

	void Update(float deltaTime) override {
		
		//std::cout << "Random:" << (rand() % 30 + (-15)) << std::endl;
		//std::cout << "Random:" << Next(1, 10) << std::endl;

		/* https://www.gamedev.net/forums/topic/494297-does-anybody-have-a-good-and-simple-2d-camera-shaking-algorithm/
		// During an update shake the camera (executed 60 times per second)
		if (cameraShakingUpdatesLeft != 0)
		{
		  xAdjustment = rnd.Next(-15, 15); // get random number between -15 and 15
		  yAdjustment = rnd.Next(-15, 15); // get random number between -15 and 15

		  camera.X += xAdjustment;
		  camera.Y += yAdjustment;

		  cameraShakingUpdatesLeft--;
		}
		
		*/
		/*
		If you want something more smooth, you could use waves. 
		To get more random looking smooth waves, 
		just add sin/cos waves of differing frequencies together.
		*/
		/*if (cameraShakingUpdatesLeft != 0) { 
			float shakeFreqX = 10;  float shakeFreqY = 8;  
			float shakeFreqY2 = 20;  float shakeSizeX = 15;  
			float shakeSizeY = 10;  float shakeSizeY2 = 5;  
			float t = theCurrentTimeInSeconds;  
			xAdjustment = sin(t * shakeRateX) * shakeSizeX;  
			yAdjustment = sin(t * shakeRateY) * shakeSizeY + cos(t * shakeFreqY2) * shakeSizeY2;  
			camera.X += xAdjustment;  
			camera.Y += yAdjustment;  cameraShakingUpdatesLeft--; 
		}
		*/

	}

	void Render() override {

	}

	void Destroy() {

	}
};


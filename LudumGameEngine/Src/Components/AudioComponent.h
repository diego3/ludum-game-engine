#pragma once 

#include <string>
#include "../Core/Component.h"
#include "../../Libs/SDL2_mixer-2.0.4/include/SDL_mixer.h"


class AudioComponent : public Component {
public:
	bool playOnAwake;
	bool looping;
	std::string audioSourceId;

	void Initialize() override {
		
	}

	void Update(float deltaTime) override {

	}

	void Render() override {

	}

	void Destroy() {

	}
};
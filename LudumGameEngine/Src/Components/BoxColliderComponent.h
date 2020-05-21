#pragma once 

#include <iostream>
#include <string>
#include <SDL.h>
#include "../Core/Component.h"
#include "../Core/EntityManager.h"
#include "../Core/Entity.h"
#include "TransformComponent.h"

// https://developer.mozilla.org/en-US/docs/Games/Techniques/3D_collision_detection
class BoxColliderComponent : public Component {
public:


	void Initialize() override {

	}


	void Update(float deltaTime) override {
		// aabb collision check?

	}

	void Destroy() {

	}
};
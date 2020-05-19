#pragma once 

#include <iostream>
#include <string>
#include <SDL.h>
#include "../Core/Component.h"
#include "../Core/EntityManager.h"
#include "../Core/Entity.h"
#include "TransformComponent.h"

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
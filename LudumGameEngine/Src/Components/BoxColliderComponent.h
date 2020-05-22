#pragma once 

#include <iostream>
#include <string>
#include <SDL.h>
#include "../Core/Component.h"
#include "../Core/EntityManager.h"
#include "../Core/Entity.h"
#include "TransformComponent.h"
#include "../Core/Collision.h"

// https://developer.mozilla.org/en-US/docs/Games/Techniques/3D_collision_detection
class BoxColliderComponent : public Component {
public:
	TransformComponent* transform;
	std::string colliderTag;
	SDL_Rect collider;
	SDL_Rect source;
	SDL_Rect destination;

	BoxColliderComponent(std::string tag) {
		colliderTag = tag;
		collider = {0, 0, 0, 0};
	}

	BoxColliderComponent(std::string tag, int x, int y, int w, int h) {
		colliderTag = tag;
		collider = {x, y, w, h};
	}

	void Initialize() override {
		if (!HasTransform()) {
			return;
		}

		transform = owner->GetComponent<TransformComponent>();
		source = {0, 0, transform->width, transform->height};
		destination = {collider.x, collider.y, collider.w, collider.h};

		collider.x = static_cast<int>(transform->position.x);
		collider.y = static_cast<int>(transform->position.y);
		collider.w = transform->width * transform->scale;
		collider.h = transform->height * transform->scale;
		destination.x = collider.x - Game::camera.x;
		destination.y = collider.y - Game::camera.y;

		std::cout << owner->name << " initial collider = {" <<
			collider.x << "," <<
			collider.y << "," <<
			collider.w << "," <<
			collider.h << "}" << std::endl;
	}


	void Update(float deltaTime) override {
		if (!HasTransform()) {
			return;
		}

		collider.x = static_cast<int>(transform->position.x);
		collider.y = static_cast<int>(transform->position.y);
		collider.w = transform->width * transform->scale;
		collider.h = transform->height * transform->scale;
		destination.x = collider.x - Game::camera.x;
		destination.y = collider.y - Game::camera.y;
	}

	void Destroy() {

	}

private:
	bool HasTransform() {
		if (!owner->HasComponent<TransformComponent>()) {
			std::cout << "[" << owner->name<< "] missing transform (on BoxColliderComponent)" << std::endl;
			return false;
		}
		return true;
	}
};
#pragma once

#include "../Core/Component.h"
#include "TransformComponent.h"
#include "../Core/Game.h"

// melhoria: deverá estar num script component
class CameraFollowComponent : public Component {
public:
	TransformComponent* transform;

	void Initialize() override {
		if (!owner->HasComponent<TransformComponent>()) {
			std::cout << "player has no transform component" << std::endl;
			return;
		}

		transform = owner->GetComponent<TransformComponent>();
	}

	void Update(float deltaTime) override {
		if (!transform) return;

		Game::camera.x = transform->position.x - (WINDOW_WIDTH / 2);
		Game::camera.y = transform->position.y - (WINDOW_HEIGHT / 2);

		// Campling 
		Game::camera.x = Game::camera.x < 0 ? 0 : Game::camera.x;
		Game::camera.y = Game::camera.y < 0 ? 0 : Game::camera.y;
		Game::camera.x = Game::camera.x > Game::camera.w ? Game::camera.w : Game::camera.x;
		Game::camera.y = Game::camera.y > Game::camera.h ? Game::camera.h : Game::camera.y;

		// just for debugging
		//std::cout << transform->position.x << "," << transform->position.y << std::endl;

		// Campling player
		transform->position.x = transform->position.x < 0 ? 0 : transform->position.x;
		transform->position.y = transform->position.y < 0 ? 0 : transform->position.y;
		transform->position.x = transform->position.x > (WINDOW_WIDTH * 2 - transform->width * 2) ? static_cast<float>(WINDOW_WIDTH * 2 - transform->width * 2) : transform->position.x;
		transform->position.y = transform->position.y > (WINDOW_HEIGHT * 2 - transform->height * 2) ? static_cast<float>(WINDOW_HEIGHT * 2 - transform->height * 2) : transform->position.y;
	}

	void Render() override {

	}

	void Destroy() {

	}
};

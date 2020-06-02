#pragma once

#include "../Core/Game.h"
#include "../Core/Component.h"
#include "TransformComponent.h"
#include "../../glm/glm/glm.hpp"
#include "../../glm/glm/ext.hpp"

class RotationFollowComponent : public Component {
public:
	TransformComponent* transform;
	TransformComponent* target;

	void Initialize() override {
		transform = owner->GetComponent<TransformComponent>();
		target = Game::entityManager->FindEntityByName("player")->GetComponent<TransformComponent>();
		if (!target) {
			printf("Target transform FAILS\n");
		}
	}

	void Update(float deltaTime) override {
		if (!target) return;

	}

	void Render() override {
		if (!target) return;

	}

	void Destroy() {

	}

};
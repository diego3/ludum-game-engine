#pragma once

#include "../Core/Game.h"
#include "../Core/Component.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "../../glm/glm/glm.hpp"
#include "../../glm/glm/ext.hpp"
#include "../../glm/glm/gtx/vector_angle.hpp"

class RotationFollowComponent : public Component {
public:
	TransformComponent* transform;
	TransformComponent* target;
	SpriteComponent* sprite;

	float angleRad;
	float speed = 10;
	float intervalo = 360.0f;
	float contador = 360.0f;

	float x;

	RotationFollowComponent() {
		angleRad = glm::radians(0.0f);
		x = 0;
		transform = NULL;
		target = NULL;
		sprite = NULL;
	}

	void Initialize() override {
		transform = owner->GetComponent<TransformComponent>();
		sprite = owner->GetComponent<SpriteComponent>();
		target = Game::entityManager->FindEntityByName("player")->GetComponent<TransformComponent>();
		if (!target) {
			printf("Target transform FAILS\n");
		}
	}

	// https://stackoverflow.com/questions/31064234/find-the-angle-between-two-vectors-from-an-arbitrary-origin
	void Update(float deltaTime) override {
		if (!target) return;
		contador += 1.0f;
		//printf("contador %2.f\n", contador);
		glm::vec2 direction = target->position - transform->position;
		glm::vec2 dirNormal = glm::normalize(direction);
		float angle = Angle(glm::vec2(0, 1), dirNormal);
	
		//std::cout << "angle = " << glm::degrees(angle) << std::endl;
		//sprite->rotation = contador;
		float dot = glm::dot(target->position, transform->position);
		//printf("dot %2.f\n", dot);
		glm::vec2 rotation = Rotate(glm::vec2(0, 1), glm::radians(contador));
		//sprite->destination.x = (int)rotation.x;
		//sprite->destination.y = (int)rotation.y;
		//printf("%d %d\n", rotation.x, rotation.y);

		//transform->position += rotation * 0.1f * deltaTime;
		transform->position += rotation;// movimento circular

		if (contador >= intervalo) {
			contador = 0;
		}
	}

	// returns in radians
	float Angle(glm::vec2 a, glm::vec2 b) {
		float dot = glm::dot(a, b);
		float d1 = glm::distance(glm::vec2(0, 0), a);
		float d2 = glm::distance(glm::vec2(0, 0), b);
		float x = dot / (d1 * d2);
		float angle = glm::acos(x);
		return angle;
	}

	// angle in radians
	glm::vec2 Rotate(glm::vec2 v, float angle) {
		float x = v.x * glm::cos(angle) - v.y * glm::sin(angle);
		float y = v.x * glm::sin(angle) + v.y * glm::cos(angle);
		return glm::vec2(x, y);
	}

	void Render() override {
		if (!target) return;

	}

	void Destroy() {

	}

};
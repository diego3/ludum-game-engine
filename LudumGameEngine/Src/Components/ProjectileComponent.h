#pragma once

#include "../Core/Component.h"
#include "TransformComponent.h"
#include "../Core/AssetManager.h"
#include "../../Libs/glm/glm/glm.hpp"
#include "../Core/Game.h"
#include "../Core/TextureManager.h"


class ProjectileComponent : public Component {
public:
	TransformComponent* transform;
	std::string assetId;
	SDL_Texture* texture;
	float speed;

	glm::vec2 direction;
	glm::vec2 position;

	SDL_Rect source;
	SDL_Rect destination;

	int width;
	int height;
	int scale;

	bool playing = false;
	int duration;
	int timer;

	ProjectileComponent(std::string assetId, float speed, int width, int height, int scale, int duration) {
		this->assetId = assetId;
		this->speed = speed;
		direction = glm::vec2(1, 0);// right
		position = glm::vec2(0, 0);// zero
		this->width = width;
		this->height = height;
		this->scale = scale;
		this->duration = duration;
		if (this->duration <= 0) duration = 120;//2frames
		this->timer = duration;
	}

	~ProjectileComponent() {
		if (texture) {
			SDL_DestroyTexture(texture);
		}
	}

	void Initialize() override {
		transform = owner->GetComponent<TransformComponent>();
		texture = Game::assetManager->GetTexture(this->assetId);

		//direction = glm::vec2(transform->position.x, transform->position.y);
		position = glm::vec2(transform->position.x, transform->position.y);

		source = {0,0, this->width, this->height};
		destination = {(int)position.x, (int)position.y, this->width * this->scale, this->height * this->scale };
	}

	void Update(float deltaTime) override {
		timer--;
		if (!playing) {
			return;
		}

		position += speed * direction * deltaTime;

		destination.x = static_cast<int>(position.x);
		destination.y = static_cast<int>(position.y);

		if (timer <= 0) {
			// TODO destroy entity or reset
			position = glm::vec2(transform->position.x, transform->position.y);
			destination = { (int)position.x, (int)position.y, this->width * this->scale, this->height * this->scale };
			playing = false;
			timer = duration;
		}

		printf("bullet time: %d\n", timer);
	}



	void Render() override {
		if (playing) {
			TextureManager::Draw(texture, source, destination, SDL_FLIP_NONE);
		}
	}

	void Destroy() {

	}
};
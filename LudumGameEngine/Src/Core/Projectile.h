#pragma once

#include <ctime>
#include <string>
#include <SDL.h>
#include "../../glm/glm/glm.hpp"
#include "../../glm/glm/ext.hpp"
#include "../Components/TransformComponent.h"

class Projectile {
public:
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
	TransformComponent* transform;

	Projectile(std::string assetId, float speed, int width, int height, int scale, int duration) {
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

		srand((int)time(0));
	}

	~Projectile() {
		if (texture) {
			SDL_DestroyTexture(texture);
		}
	}

	void Initialize(TransformComponent* transform)  {
		this->transform = transform;
		//direction = glm::vec2(transform->position.x, transform->position.y);
		texture = Game::assetManager->GetTexture(this->assetId);

		//direction = glm::vec2(transform->position.x, transform->position.y);
		position = glm::vec2(10, (rand() % (400) + (200)));

		speed = (float)(rand() % (800) + (400));

		source = { 0,0, this->width, this->height };
		destination = { (int)position.x, (int)position.y, this->width * this->scale, this->height * this->scale };

	}

	void Update(float deltaTime)  {
		timer--;
		//if (!playing) {
		//	return;
		//}

		position += speed * direction * deltaTime;
		
		destination.x = static_cast<int>(position.x);
		destination.y = static_cast<int>(position.y);

		if (timer <= 0) {
			Reset();
		}

		//printf("bullet time: %d\n", timer);
	}

	void Reset() {
		position = glm::vec2(10, (rand() % (400) + (200)));
		destination = {(int)position.x, (int)position.y, this->width * this->scale, this->height * this->scale };
		playing = false;
		timer = duration;
		speed = (float)(rand() % (800) + (400));
	}

	void Render()  {
		//if (playing) {
			TextureManager::Draw(texture, source, destination, SDL_FLIP_NONE);
		//}
	}
};
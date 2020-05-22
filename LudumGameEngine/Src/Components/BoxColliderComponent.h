#pragma once 

#include <iostream>
#include <string>
#include <SDL.h>
#include "../Core/Component.h"
#include "../Core/TextureManager.h"
#include "../Core/AssetManager.h"
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
	
	std::string boundingAssetId;
	SDL_Texture* boundingBoxTexture;
	SDL_Rect source;
	SDL_Rect destination;

	BoxColliderComponent(std::string tag, std::string assetId) {
		colliderTag = tag;
		collider = {0, 0, 0, 0};
		boundingAssetId = assetId;
	}

	BoxColliderComponent(std::string tag, std::string assetId, int x, int y, int w, int h) {
		colliderTag = tag;
		collider = {x, y, w, h};
		boundingAssetId = assetId;
	}

	void Initialize() override {
		if (!HasTransform()) {
			return;
		}
		if (!boundingAssetId.empty()) {
			boundingBoxTexture = Game::assetManager->GetTexture(boundingAssetId);
		}
		transform = owner->GetComponent<TransformComponent>();
		source = {0, 0, transform->width, transform->height};
		destination = {collider.x, collider.y, collider.w, collider.h };
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

	void Render() override {
		if (boundingBoxTexture) {
			/*std::cout << "draw bounding " << boundingAssetId << std::endl;
			if (owner->name.compare("player") == 0) {
				TransformComponent* t = owner->GetComponent<TransformComponent>();
				std::cout << "player {" << t->position.x << ", " << t->position.y << "}" << std::endl;
			}
			std::cout << "source {"<<source.x<<","<<source.y << "," <<source.w << "," <<source.h << "}" << std::endl;
			std::cout << "destination {"<< destination.x<<","<< destination.y << "," << destination.w << "," << destination.h << "}" << std::endl;
			*/
			TextureManager::Draw(boundingBoxTexture, source, destination, SDL_FLIP_NONE);
		}
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
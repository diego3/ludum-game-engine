#pragma once

#include <string>
#include <map>
#include <SDL.h>
#include "../Core/Game.h"
#include "../Core/Component.h"
#include "TransformComponent.h"
#include "../Core/TextureManager.h"
#include "../Core/Animation.h"

class SpriteComponent: public Component
{
public:
	SDL_Texture* texture;
	SDL_Rect source;
	SDL_Rect destination;
	SDL_RendererFlip flip = SDL_FLIP_NONE;


	TransformComponent* transform;

	//animation stuffs
	bool isAnimated;
	int numFrames;
	int animationSpeed;
	bool isFixed;
	std::map<std::string, Animation> animations;
	std::string currentAnimationName;
	unsigned int animationIndex = 0;

	SpriteComponent(std::string filePath) {
		this->isAnimated = false;
		this->isFixed = false;
		SetTexture(filePath);
	}

	SpriteComponent(std::string id, int numFrames, int animationSpeed,
		bool hasDirections, bool isFixed) {
		this->isAnimated = true;
		this->numFrames = numFrames;
		this->animationSpeed = animationSpeed;
		this->isFixed = isFixed;
		this->animationIndex = 0;

		if (hasDirections) {
			Animation downAnim = Animation(0, numFrames, animationSpeed);
			Animation rightAnim = Animation(1, numFrames, animationSpeed);
			Animation leftAnim = Animation(2, numFrames, animationSpeed);
			Animation upAnim = Animation(3, numFrames, animationSpeed);

			animations.emplace("downAnim", downAnim);
			animations.emplace("rightAnim", rightAnim);
			animations.emplace("leftAnim", leftAnim);
			animations.emplace("upAnim", upAnim);

			this->currentAnimationName = "downAnim";
		}
		else {
			Animation single = Animation(0, numFrames, animationSpeed);
			animations.emplace("SingleAnimation", single);
			this->currentAnimationName = "SingleAnimation";
		}

		Play(this->currentAnimationName);
		SetTexture(id);
	}

	void Play(std::string animationName) {
		numFrames = animations[animationName].numFrame;
		animationIndex = animations[animationName].index;
		animationSpeed = animations[animationName].animationSpeed;
		currentAnimationName = animationName;
	}

	void SetTexture(std::string assetTextureId) {
		texture = Game::assetManager->GetTexture(assetTextureId);
	}

	void Initialize() override {
		transform = owner->GetComponent<TransformComponent>();
		source.x = 0;
		source.y = 0;
		source.w = transform->width;
		source.h = transform->height;
	}

	void Update(float deltaTime) override {
		if (isAnimated) {
			int ax = source.w * (static_cast<int>(SDL_GetTicks() / animationSpeed) % numFrames);
			//std::cout << "ax = " << ax << std::endl;
			source.x = ax;
		}
		source.y = animationIndex * transform->height;

		int camerax = isFixed ? 0 : Game::camera.x;
		int cameray = isFixed ? 0 : Game::camera.y;
		destination.x = static_cast<int>(transform->position.x) - camerax;
		destination.y = static_cast<int>(transform->position.y) - cameray;
		
		destination.w = transform->width * transform->scale;
		destination.h = transform->height * transform->scale;
	}

	void Render() override {
		TextureManager::Draw(texture, source, destination, flip);
	}
};
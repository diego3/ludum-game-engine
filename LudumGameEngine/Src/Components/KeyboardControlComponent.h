#pragma once

#include <string>
#include <map>
#include <iostream>
#include "../Core/Game.h"
#include "../Core/Component.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "LuaScriptComponent.h"
#include "../../Libs/glm/glm/ext/vector_float2.hpp"
#include "ProjectileComponent.h"
#include "CameraShakeComponent.h"

class KeyboardControlComponent : public Component {
public:
	//std::string upKey;
	//std::string downKey;
	///std::string leftKey;
	//std::string rightKey;
	//std::string shootKey;
	TransformComponent* transform;
	SpriteComponent* sprite;
	//LuaScriptComponent* luaScript;
	ProjectileComponent* bullet;
	CameraShakeComponent* camShake;

	int speed = 150;

	// https://wiki.libsdl.org/SDLKeycodeLookup
	std::map<std::string, std::string> keycodes;

	
	KeyboardControlComponent(std::string up, std::string down, std::string left,
		std::string right, std::string shoot) {
		
		//this->upKey = GetSDLKeyStringCode(up);
		//this->downKey = GetSDLKeyStringCode(down);
		//this->leftKey = GetSDLKeyStringCode(left);
		//this->rightKey = GetSDLKeyStringCode(right);
		//this->shootKey = GetSDLKeyStringCode(shoot);
	}

	void Initialize() override {
		transform = owner->GetComponent<TransformComponent>();
		sprite = owner->GetComponent <SpriteComponent>();
		//luaScript = owner->GetComponent<LuaScriptComponent>();
		bullet = owner->GetComponent<ProjectileComponent>();

		camShake = new CameraShakeComponent(1, 15);
	}

	void Update(float deltaTime) override {
		//return;

		if (Game::inputManager->IsRight) {
			transform->velocity += glm::vec2(speed, 0) * deltaTime;
			sprite->Play("rightAnim");
		}
		if (Game::inputManager->IsLeft) {
			transform->velocity += glm::vec2(-speed, 0) * deltaTime;
			sprite->Play("leftAnim");
		}
		if (Game::inputManager->IsUp) {
			transform->velocity += glm::vec2(0, -speed) * deltaTime;
			sprite->Play("upAnim");
		}
		if (Game::inputManager->IsDown) {
			transform->velocity += glm::vec2(0, speed) * deltaTime;
			sprite->Play("downAnim");
		}

		camShake->Update(deltaTime);
	}

	void SDLEventHandler() {
		/*if (Game::event.type == SDL_KEYDOWN) {
			std::string keyCode = std::to_string(Game::event.key.keysym.sym);

			if (keyCode.compare(this->upKey) == 0) {
				transform->velocity += glm::vec2(0, -speed) * deltaTime;
				sprite->Play("upAnim");
			}
			if (keyCode.compare(this->downKey) == 0) {
				transform->velocity += glm::vec2(0, speed) * deltaTime;
				sprite->Play("downAnim");
			}
			if (keyCode.compare(this->leftKey) == 0) {
				transform->velocity += glm::vec2(-speed, 0) * deltaTime;
				sprite->Play("leftAnim");
			}
			if (keyCode.compare(this->rightKey) == 0) {
				transform->velocity += glm::vec2(speed, 0) * deltaTime;
				sprite->Play("rightAnim");
			}
			if (keyCode.compare(this->shootKey) == 0) {
				//luaScript->lua->dumpStack();
				//int top = lua_gettop(luaScript->lua->L);
				//std::cout << "top = " << top << std::endl;

				//Entity* projectile = Instantiate("projectile");

				bullet->Play = true;
			}
		}
		if (Game::event.type == SDL_KEYUP) {
			std::string keyCode = std::to_string(Game::event.key.keysym.sym);
			if (keyCode.compare(this->upKey) == 0) {
				//transform->velocity -= glm::vec2(0, -speed/10);
			}
			if (keyCode.compare(this->downKey) == 0) {
				//transform->velocity -= glm::vec2(0, speed/10);
			}
			if (keyCode.compare(this->leftKey) == 0) {
				//transform->velocity -= glm::vec2(-speed/10, 0);
			}
			if (keyCode.compare(this->rightKey) == 0) {
				//transform->velocity -= glm::vec2(speed/10, 0);
			}
			if (keyCode.compare(this->shootKey) == 0) {
				//bullet->Play = false;
			}
		}*/
	}


	void Destroy() {
		delete camShake;
	}

};
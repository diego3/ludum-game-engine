#pragma once

#include <iostream>
#include <map>
#include <string>
#include <SDL.h>
#include "Game.h"
#include "InputManager.h"


InputManager::InputManager() {
	keycodes.emplace("up", "1073741906");
	keycodes.emplace("down", "1073741905");
	keycodes.emplace("left", "1073741904");
	keycodes.emplace("right", "1073741903");
	keycodes.emplace("p", "112");
	keycodes.emplace("space", "32");

	IsLeft = false;
	IsRight = false;
	IsUp = false;
	IsDown = false;
}

void InputManager::ProcessInput() {
	if (Game::event.type == SDL_KEYDOWN) {
		std::string keyCode = std::to_string(Game::event.key.keysym.sym);

		if (keyCode.compare(keycodes["up"]) == 0) {
			IsUp = true;
		}
		if (keyCode.compare(keycodes["down"]) == 0) {
			IsDown = true;
		}
		if (keyCode.compare(keycodes["left"]) == 0) {
			IsLeft = true;
		}
		if (keyCode.compare(keycodes["right"]) == 0) {
			IsRight = true;
		}

	}
	if (Game::event.type == SDL_KEYUP) {
		std::string keyCode = std::to_string(Game::event.key.keysym.sym);
		if (keyCode.compare("1073741906") == 0) {
			IsUp = false;
		}
		if (keyCode.compare("1073741905") == 0) {
			IsDown = false;
		}
		if (keyCode.compare(keycodes["left"]) == 0) {
			IsLeft = false;
		}
		if (keyCode.compare(keycodes["right"]) == 0) {
			IsRight = false;
		}
	}
}

std::string InputManager::GetSDLKeyStringCode(std::string val) {
	if (keycodes.count(val) > 0) {
		return keycodes[val];
	}
	return std::to_string(static_cast<int>(val[0]));
}

bool InputManager::GetButtonDown(int button) {

	return false;
}

bool InputManager::GetButtonUp(int button) {

	return false;
}

bool InputManager::GetKeyDown(int button) {

	return false;
}

bool InputManager::GetKeyUp(int button) {

	return false;
}
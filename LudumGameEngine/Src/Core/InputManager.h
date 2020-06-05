#pragma once

#include <iostream>
#include <map>
#include <string>
#include <SDL.h>

class InputManager {
	
public:
	bool IsLeft;
	bool IsRight;
	bool IsUp;
	bool IsDown;

	InputManager();

	void ProcessInput();
	bool GetButtonDown(int id);
	bool GetButtonUp(int id);
	bool GetKeyDown(int id);
	bool GetKeyUp(int id);

	std::string GetSDLKeyStringCode(std::string val);
private:
	// https://wiki.libsdl.org/SDLKeycodeLookup
	std::map<std::string, std::string> keycodes;
	std::map<std::string, bool> keys;
};
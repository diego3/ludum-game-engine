#pragma once

extern "C" {
	#include "../../Libs/lua-5.3.5_Win32_dllw6_lib/include/lua.h"
	#include "../../Libs/lua-5.3.5_Win32_dllw6_lib/include/lauxlib.h"
	#include "../../Libs/lua-5.3.5_Win32_dllw6_lib/include/lualib.h"
}

#include <iostream>
#include <string>
#include "../Core/Component.h"
#include "../Core/Game.h"
#include "../Core/EntityManager.h"
#include "../Core/LuaManager.h"

class LuaScriptComponent : public Component {
public:
	std::string filePath;
	LuaManager* lua;
	bool file_error;

	int x;

	LuaScriptComponent(LuaManager* luaVM, std::string file) {
		x = 0;
		filePath = file;
		lua = luaVM;
		file_error = false;
	}


	void Initialize() override {
		int ok = luaL_dostring(lua->L, "x = 0");
		if (ok != LUA_OK) {
			std::cout << "simple do string fails" << std::endl;
		}

		lua_getglobal(lua->L, "x");
	}


	void Update(float deltaTime) override {
		if (this->file_error || !lua->doFile(this->filePath)) {
			file_error = true; return;
		}

		if (Game::event.type == SDL_KEYDOWN) {
			std::string keyCode = std::to_string(Game::event.key.keysym.sym);
			if (keyCode.compare("112") == 0) {
				std::cout << "apertei P" << std::endl;
				lua_pushstring(lua->L, "move");
			}
		}

		//transX
		lua_getglobal(lua->L, "x");
		//if (lua_isinteger(lua->L, -1)) {
		x = (int)lua_tonumber(lua->L, -1);
		lua_pop(lua->L, 1);
		//std::cout << "x = " << x << std::endl;
		//}

		
	}

	void Destroy() {

	}

};
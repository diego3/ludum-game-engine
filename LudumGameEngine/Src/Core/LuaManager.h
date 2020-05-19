#pragma once

#include <iostream>
#include <string>

extern "C" {
	#include "../../Libs/lua-5.3.5_Win32_dllw6_lib/include/lua.h"
	#include "../../Libs/lua-5.3.5_Win32_dllw6_lib/include/lauxlib.h"
	#include "../../Libs/lua-5.3.5_Win32_dllw6_lib/include/lualib.h"
}

class LuaManager {
public:
	lua_State* L;

	LuaManager();
	~LuaManager();

	void teste();
	bool check(int r);
	bool doFile(std::string fileName);
	void dumpStack();
};
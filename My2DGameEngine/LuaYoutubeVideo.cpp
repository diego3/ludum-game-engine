#include <iostream>
#include <string>

extern "C" {
	#include "Libs/lua-5.3.5_Win32_dllw6_lib/include/lua.h"
	#include "Libs/lua-5.3.5_Win32_dllw6_lib/include/lauxlib.h"
	#include "Libs/lua-5.3.5_Win32_dllw6_lib/include/lualib.h"
}

#ifdef _WIN32
#pragma comment(lib, "Libs/lua-5.3.5_Win32_dllw6_lib/liblua53.a")
#endif // WIN

void step1() {
	std::string cmd = "a = 5 + 5";

	lua_State* L = luaL_newstate();

	int r = luaL_dostring(L, cmd.c_str());
	lua_getglobal(L, "a");
	if (lua_isinteger(L, -1)) {
		std::cout << "r = " << lua_tointeger(L, -1) << std::endl;
	}


	system("pause");
	lua_close(L);
}
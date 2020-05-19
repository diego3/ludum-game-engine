#pragma once
#include <iostream>
#include <string>
#include "LuaManager.h"

extern "C" {
#include "../../Libs/lua-5.3.5_Win32_dllw6_lib/include/lua.h"
#include "../../Libs/lua-5.3.5_Win32_dllw6_lib/include/lauxlib.h"
#include "../../Libs/lua-5.3.5_Win32_dllw6_lib/include/lualib.h"
}

LuaManager::LuaManager() {
	L = luaL_newstate();
	luaL_openlibs(L);
}
LuaManager::~LuaManager() {
	lua_close(L);
}


void LuaManager::teste() {
	std::string cmd = "a = 5 + 5";

	int r = luaL_dostring(L, cmd.c_str());
	lua_getglobal(L, "a");
	if (lua_isinteger(L, -1)) {
		std::cout << "r = " << lua_tointeger(L, -1) << std::endl;
	}
}

bool LuaManager::doFile(std::string fileName) {
    if (luaL_dofile(L, fileName.c_str())) {
        std::cout << "luaL_dofile fails: " << lua_tostring(L, -1) << std::endl;
        return false;
    }
    return true;
}

bool LuaManager::check(int r) {
    if (r != LUA_OK) {
        std::string error_msg = lua_tostring(L, -1);
        std::cout << error_msg << std::endl;
        return false;
    }
    return true;
}

void LuaManager::dumpStack() {
    int i;
    int top = lua_gettop(L); /* depth of the stack */
    for (i = 1; i <= top; i++) { /* repeat for each level */
        int t = lua_type(L, i);
        switch (t) {
            case LUA_TSTRING: { /* strings */
                printf("'%s'", lua_tostring(L, i));
                break;
            }
            case LUA_TBOOLEAN: { /* Booleans */
                printf(lua_toboolean(L, i) ? "true" : "false");
                break;
            }
            case LUA_TNUMBER: { /* numbers */
                printf("%g", lua_tonumber(L, i));
                break;
            }
            default: { /* other values */
                printf("%s", lua_typename(L, t));
                break;
            }
        }
        printf(" "); /* put a separator */
    }
    printf("\n"); /* end the listing */
}
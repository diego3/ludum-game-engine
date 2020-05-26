#pragma once

#include <iostream>
#include <SDL.h>
#include "../../Libs/SDL2_net-2.0.1/include/SDL_net.h"
#include "../../Libs/SDL2_image-2.0.5/include/SDL_image.h"
#include "../../Libs/SDL2_ttf-2.0.15/include/SDL_ttf.h"
#include "../../Libs/SDL2_mixer-2.0.4/include/SDL_mixer.h"
#include "../../Libs/glm/glm/vec2.hpp"

extern "C" {
#include "../../Libs/lua-5.3.5_Win32_dllw6_lib/include/lua.h"
#include "../../Libs/lua-5.3.5_Win32_dllw6_lib/include/lauxlib.h"
#include "../../Libs/lua-5.3.5_Win32_dllw6_lib/include/lualib.h"
}

#include "../../Libs/lua-5.3.5_Win32_dllw6_lib/include/sol.hpp"

#include "../Core/EntityManager.h"
#include "../Core/AssetManager.h"
//#include "LuaManager.h"
#include "../Core/Map.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/KeyboardControlComponent.h"
#include "../Components/TileMapComponent.h"
#include "../Components/CameraFollowComponent.h"
#include "../Components/BoxColliderComponent.h"

#ifdef _WIN32
#pragma comment(lib, "Libs/SDL2_net-2.0.1/lib/x86/SDL2_net.lib")
#pragma comment(lib, "Libs/SDL2_image-2.0.5/lib/x86/SDL2_image.lib")
#pragma comment(lib, "Libs/SDL2_ttf-2.0.15/lib/x86/SDL2_ttf.lib")
#pragma comment(lib, "Libs/SDL2_mixer-2.0.4/lib/x86/SDL2_mixer.lib")
#pragma comment(lib, "Libs/lua-5.3.5_Win32_dllw6_lib/liblua53.a")
#endif // WIN

class SpriteEditor {
public:

	void Initialize() {

	}

	void Update() {

	}


	void Render() {

	}

};
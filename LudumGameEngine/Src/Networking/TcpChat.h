#pragma once


//extern "C" {
//#include "../../Libs/lua-5.3.5_Win32_dllw6_lib/include/lua.h"
//#include "../../Libs/lua-5.3.5_Win32_dllw6_lib/include/lauxlib.h"
//#include "../../Libs/lua-5.3.5_Win32_dllw6_lib/include/lualib.h"
//}
//#include "../../Libs/lua-5.3.5_Win32_dllw6_lib/include/sol.hpp"
#ifdef _WIN32
//#pragma comment(lib, "Libs/lua-5.3.5_Win32_dllw6_lib/liblua53.a")
#endif // WIN

#include <iostream>
#include <vector>

#include <SDL.h>
#include "../../Libs/SDL2_net-2.0.1/include/SDL_net.h"

// https://www.libsdl.org/projects/SDL_net/docs/SDL_net_frame.html
//https://stephenmeier.net/2015/12/29/sdl-2-0-tutorial-06-networking-3/
namespace network {

	class TcpChat {
	public:
		TcpChat() {};

		void Run() {
			int sdlInit = SDL_Init(SDL_INIT_EVERYTHING);
			if (sdlInit != 0) {
				std::cout << "SDL init fails: " << SDL_GetError() << std::endl;
				return;
			}

			if (SDLNet_Init() == -1) {
				std::cout << "SDLNet_Init: " << SDLNet_GetError() << std::endl;
				return;
			}

			printf("SDLNet ok\n\n");
		}
	};
}
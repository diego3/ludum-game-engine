#pragma once

#include <iostream>
#include <vector>

#include <SDL.h>
#include "../../Libs/SDL2_net-2.0.1/include/SDL_net.h"

namespace network {
	class ClientTcpChat {
	public:
		ClientTcpChat() {};
		~ClientTcpChat() {

			SDLNet_Quit();
		}

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

			IPaddress address;
			int hostResult = SDLNet_ResolveHost(&address, "localhost", 8080);
			if (hostResult == -1) {
				printf("SDLNET_ResolveHost Error: %s\n", SDLNet_GetError());
				return;
			}
			std::cout << "IPaddress: " << address.host << ":" << address.port << std::endl;
			if (hostResult == INADDR_NONE) {
				printf("Resolve Host is ANADDR_NONE\n");
			}

			TCPsocket socket = SDLNet_TCP_Open(&address);
			if (!socket) {
				printf("SDLNet_TCP_Open Error: %s\n", SDLNet_GetError());
				return;
			}

			printf("Socket CREATED\n");









			SDLNet_TCP_Close(socket);
		}
	};

}
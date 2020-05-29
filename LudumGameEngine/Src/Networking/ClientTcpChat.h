#pragma once

#include <iostream>
#include <vector>

#include <SDL.h>
#include "../../Libs/SDL2_net-2.0.1/include/SDL_net.h"

namespace network {

	const int MESSAGE_LENGTH = 100;
	const int CHAT_MSG_LEN = 10;

	class ClientTcpChat {
	public:
		TCPsocket socket;
		SDLNet_SocketSet set;

		ClientTcpChat() {};
		~ClientTcpChat() {

			SDLNet_Quit();
		}

		bool Connect(static const char* host, int port) {
			int sdlInit = SDL_Init(SDL_INIT_EVERYTHING);
			if (sdlInit != 0) {
				std::cout << "SDL init fails: " << SDL_GetError() << std::endl;
				return false;
			}

			if (SDLNet_Init() == -1) {
				std::cout << "SDLNet_Init: " << SDLNet_GetError() << std::endl;
				return false;
			}

			IPaddress address;
			int hostResult = SDLNet_ResolveHost(&address, host, port);
			if (hostResult == -1) {
				printf("SDLNET_ResolveHost Error: %s\n", SDLNet_GetError());
				return false;
			}
			std::cout << "IPaddress: " << address.host << ":" << address.port << std::endl;
			if (hostResult == INADDR_NONE) {
				printf("Resolve Host is ANADDR_NONE\n");
			}

			socket = SDLNet_TCP_Open(&address);
			if (!socket) {
				printf("SDLNet_TCP_Open Error: %s\n", SDLNet_GetError());
				return false;
			}

			set = SDLNet_AllocSocketSet(1);
			if (!set) {
				printf("SDLNet_AllocSocketSet Error: %s\n", SDLNet_GetError());
				return false;
			}
			if (SDLNet_TCP_AddSocket(set, socket) == -1) {
				printf("SDLNet_TCP_AddSocket Error: %s\n", SDLNet_GetError());
				return false;
			}

			return true;
		}

		void Run() {
			if (!Connect("localhost", 8080)) {
				printf("Connect fails\n");
				return;
			}
	
			char input[MESSAGE_LENGTH];
			printf("user name: ");
			scanf("%s", &input);
			SDLNet_TCP_Send(socket, input, MESSAGE_LENGTH);

			while (true) {
				char msg[CHAT_MSG_LEN];
				printf("me> ");
				scanf("%s", &msg);
				SDLNet_TCP_Send(socket, msg, CHAT_MSG_LEN);
				
				std::string data = Receive();
				if (!data.empty()) {
					std::cout << "server>" << data << std::endl;
				}

				if (strcmp(msg, "exit") == 0) {
					break;
				}
			}
			
			printf("saindo...");
			SDL_Delay(1000);
			SDLNet_TCP_Close(socket);
			SDLNet_DelSocket(set, (SDLNet_GenericSocket)socket);
		}

		std::string Receive() {
			std::string ret;
			// check if there are some bit of data to read :)
			if (SDLNet_CheckSockets(set, 0) > 0 && SDLNet_SocketReady(socket)) {
				char data[CHAT_MSG_LEN];
				int res = SDLNet_TCP_Recv(socket, data, CHAT_MSG_LEN);
				if (res > 0) {
					ret.append(data, sizeof(data));
					return ret;
				}
			}
			return ret;
		}
	};

}
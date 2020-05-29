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
// https://www.geeksforgeeks.org/socket-programming-in-cc-handling-multiple-clients-on-server-without-multi-threading/
namespace network {

	class ServerTcpChat {
	public:
		ServerTcpChat() {};
		~ServerTcpChat() {
			
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

			printf("SDLNet INIT OK\n\n");

			IPaddress address;
			int hostResult = SDLNet_ResolveHost(&address, INADDR_ANY, 8080);
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
		
			SDLNet_SocketSet set = SDLNet_AllocSocketSet(10);
			if (!set) {
				printf("SDLNet_AllocSocketSet Error: %s\n", SDLNet_GetError());
				return;
			}
			if (SDLNet_TCP_AddSocket(set, socket) == -1) {
				printf("SDLNet_TCP_AddSocket Error: %s\n", SDLNet_GetError());
				return;
			}

			std::vector<TCPsocket> clients;
			//clients.push_back(socket);
			
			int numready = 0;
			while (true) {
				numready = SDLNet_CheckSockets(set, 1000);
				printf("SDLNet_CheckSockets = %d\n", numready);

				if (numready == -1) {
					printf("SDLNet_CheckSockets error: %s\n", SDLNet_GetError());
					perror(SDLNet_GetError());
				}

				if (numready > 0) {
					if (SDLNet_SocketReady(socket)) {
						// Houve atividade no socket master, é uma nova conexão
						// This is the server TCPsocket which was previously created by SDLNet_TCP_Open.
						// This is a non-blocking call, so if no connections are there to be accepted, 
						// you will get a NULL TCPsocket and the program will continue going.
						TCPsocket newSocket = SDLNet_TCP_Accept(socket);
						if (newSocket) {
							printf("Accept socket SUCCESS\n");
							if (SDLNet_TCP_AddSocket(set, newSocket) == -1) {
								printf("SDLNet_TCP_AddSocket Error: %s\n", SDLNet_GetError());
								continue;
							}

							const char* data = "Welcome";
							SDLNet_TCP_Send(newSocket, data, strlen(data));
							clients.push_back(newSocket);
						}
						else {
							printf("SDLNet_TCP_Accept Error: %s\n", SDLNet_GetError());
						}
					}

					for (TCPsocket client : clients) {
						if (SDLNet_SocketReady(client)) {
							char dataR[10];
							int res = SDLNet_TCP_Recv(client, dataR, 10);
							std::cout << "SDLNet_TCP_Recv = " << res << std::endl;

							if (res > 0) {
								printf("\tclient says: %s\n", dataR);
							}
							else if(res <= 0){
								std::cout << "error os disconnection = " << res << std::endl;
								printf("closing a socket with o recv bytes\n");
								SDLNet_TCP_Close(client);
								SDLNet_DelSocket(set, (SDLNet_GenericSocket)client);
							}
						}
					}
				}
			}

			
			SDLNet_FreeSocketSet(set);
			SDLNet_TCP_Close(socket);
		}
	};
}
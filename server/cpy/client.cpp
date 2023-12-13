//
// Created by je_gi on 2023-12-05.
//

#include <iostream>
#include <cstring>
#include <SDL2/SDL_net.h>
#include <SDL2/SDL.h>

int main(int argc, char** argv) {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDLNet_Init();

    IPaddress ip;
    int port;
    char address[] = "127.0.0.1";
    if(argc==2)
        port = atoi(argv[1]);
    else {
        SDLNet_Quit();
        SDL_Quit();
        std::cerr << "Provide port (only)\n";
        return 1; 
    }   
    
    SDLNet_ResolveHost(&ip, address, port);
    TCPsocket server = SDLNet_TCP_Open(&ip);
    char name[]="Jhonny";
    SDLNet_TCP_Send(server, name, strlen(name+1));
    char text[100];
    while(true) {
        int bytesReceived = SDLNet_TCP_Recv(server, text, 99);
        if(bytesReceived > 0) {
            std::cout << text << '\n';
            break;
        }
    }
    while(true) {
        int bytesReceived = SDLNet_TCP_Recv(server, text, 99);
        if(bytesReceived > 0) {
            std::cout << text << '\n';
            break;
        }
    }

    SDLNet_TCP_Close(server);
    SDLNet_Quit();
    SDL_Quit();
    return 0;
}
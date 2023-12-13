//
// Created by je_gi on 2023-12-05.
//

#include <iostream>
#include <cstring>
#include <SDL2/SDL_net.h>
#include <SDL2/SDL.h>
#include "Connection.hpp"

int main(int argc, char** argv) {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDLNet_Init();
    IPaddress ip;
    int port;
    char address[20] = "127.0.0.1";
    if(argc==3)
        strcpy(address, argv[1]);

    if(argc>=2)
        port = atoi(argv[argc-1]);
    else {
        SDLNet_Quit();
        SDL_Quit();
        std::cerr << "Provide ip address(optional) and port\n";
        return 1; 
    }
    
    std::cout << address << ' ' << port << '\n';
    
    ConnectionToServer *srv = new ConnectionToServer(address, port, "Jhonny");
    std::cout << srv->Receive();

    srv->Send("Client closing connection\n");

    delete srv;
    
    SDLNet_Quit();
    SDL_Quit();
    return 0;
}
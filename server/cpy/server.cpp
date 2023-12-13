//
// Created by je_gi on 2023-12-05.
//

#include <iostream>
#include <cstring>
#include <SDL2/SDL_net.h>
#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include <boost/thread/thread.hpp>

#include "Connection.hpp"

int main(int argc, char** argv) {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDLNet_Init();

    int port;
    int peer_no;

    if(argc==3) {
        port = atoi(argv[1]);
        peer_no = atoi(argv[2]);
    }
    else {
        SDLNet_Quit();
        SDL_Quit();
        std::cerr << "Provide port and number of peers\n";
        return 1;
    }

    static ServerSocket srvsock(port);
    std::vector<boost::thread*> threads;
    for(int i = 1; i <= peer_no; ++i) 
        threads.push_back(srvsock.AwaitAuthenticationAsync());
    
    for(auto &thrd_ptr : threads) {
        thrd_ptr->join();
        delete thrd_ptr;
    }
    threads.clear();

    for(int i = 1; i <= srvsock.clients.size(); ++i)
        srvsock.Send(srvsock.clients[0], std::string(std::to_string(i)));

    /*IPaddress ip;
    int port;
    if(argc==2)
        port = atoi(argv[1]);
    else {
        SDLNet_Quit();
        SDL_Quit();
        std::cerr << "Provide port (only)\n";
        return 1;
    }

    SDLNet_ResolveHost(&ip, NULL, port);

    TCPsocket server = SDLNet_TCP_Open(&ip);
    TCPsocket client;
    const char* text = "HELLO CLIENT!\n";
    char recv_text[100];
    while(true) {
        client = SDLNet_TCP_Accept(server);
        if(client) {
            SDLNet_TCP_Recv(client,recv_text,99);
            std::cout << recv_text;
            SDLNet_TCP_Send(client,text,strlen(text)+1);
            SDLNet_TCP_Close(client);
            break;
        }
    }

    SDLNet_TCP_Close(server);*/
    SDLNet_Quit();
    SDL_Quit();
    return 0;
}
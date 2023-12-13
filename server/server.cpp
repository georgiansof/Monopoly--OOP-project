//
// Created by je_gi on 2023-12-05.
//

#include <iostream>
#include <cstring>
#include <SDL2/SDL_net.h>
#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include <map>
#include <thread>

#include "Connection.hpp"

/// TODO connect handshake timeout (clientside)
/// TODO listen & send thread with event or buffer & checkBuffer function. (bool wasModifiedSinceLastRead)

std::vector<ConnectionToClient*> connections;

void AwaitHandshakeAsync(ConnectionToClient *context) {
    context->AwaitHandshake();
    std::cout<< "Port " << context->getPort()<< " connected to " << context->getPeerAddress() << '\n';
}

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

    std::cout << "Server up\n\n";

    for(int i = 1; i <= peer_no; ++i) {
        std::cout << "Port " << port + Connection::getConnectionCount() << " listening \n";
        connections.push_back(new ConnectionToClient(port + Connection::getConnectionCount()));
    }
    std::cout<<'\n';

    std::vector<std::thread*> threads;
    for(int i = 0; i < peer_no; ++i)
        threads.push_back(new std::thread(AwaitHandshakeAsync, connections[i]));
    for(int i = 0; i < threads.size(); ++i) {
        threads[i]->join();
        delete threads[i];
    }
    threads.clear();
    std::cout<<'\n';
    
    for(int i = 0; i < peer_no; ++i) {
        connections[i]->Send("test\n");
        std::cout << "Message sent to " << connections[i]->getPeerAddress() << ':' << connections[i]->getPort() << '\n';
    }
    std::cout<<'\n';

    for(int i = 0; i < peer_no; ++i)
        std::cout << connections[i]->Receive();

    std::cout << "Server shutting down\n\n";
    for(auto &conn : connections)
        delete conn;
    connections.clear();
    SDLNet_Quit();
    SDL_Quit();
    return 0;
}
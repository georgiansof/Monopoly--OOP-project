#ifndef __SOCKETS_H
#define __SOCKETS_H

#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>
#include <boost/thread/thread.hpp> /// libboost-thread-dev

class Connection;

#define NAMEMAXLEN 50

class ServerSocket {
    TCPsocket server;
public:
    std::vector<Connection> clients;
    ServerSocket(int port);
    ~ServerSocket();
    boost::thread* AwaitAuthenticationAsync();
    void AwaitAuthentication();
    std::string Receive(Connection &client, int MAXLEN = 1024);
    void Send(Connection &client, std::string text);
    void RemoveConnection(std::string clientName);
    static ServerSocket* getInstancePtr();
};

class Connection {
    std::string remote_name;
    TCPsocket remote;
public:
    Connection() = delete;
    Connection(TCPsocket remote, std::string name);
    ~Connection();
    TCPsocket getSocket() const;
    std::string getName() const;
};

#endif
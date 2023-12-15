#ifndef __SOCKETS_H
#define __SOCKETS_H

#include <map>
#include <vector>
#include <string>
#include "../../headers/external/SDL2/SDL.h"
#include "../../headers/external/SDL2/SDL_net.h"
#include <thread>

#define NAMEMAXLEN 50
#define TIMEOUT_THRESHOLD 5.0f

class Connection {
protected:
    static int count;
    static std::map<int, std::thread*> threads;
    TCPsocket remote;
    int port;
    std::string remote_name; /// first receive after accept
public:
    Connection() = default;
    virtual ~Connection();
    std::string Receive(float timeout = TIMEOUT_THRESHOLD, int MAXLEN = 1024);
    void Send(std::string text);
    static int getConnectionCount();
    int getPort() const;
    std::string getPeerName() const;
};

class ConnectionToServer : public Connection {
public:
    ConnectionToServer(std::string address, int port, std::string self_name, int MAXREQ = 1024);
};

class ConnectionToClient : public Connection {
private:
    TCPsocket local;
    std::thread *connectThread = 0;
    std::thread *listenerThread = 0;
public:
    ConnectionToClient(int port);
    ~ConnectionToClient();
    void AwaitClient();
    void AwaitHandshake();
    std::string getPeerAddress();
};

#endif
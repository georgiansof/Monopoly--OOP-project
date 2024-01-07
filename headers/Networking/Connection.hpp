#ifndef OOP_CONNECTION_HPP
#define OOP_CONNECTION_HPP

#include <map>
#include <vector>
#include <string>
//#include "../../headers/external/SDL2/SDL.h"
//#include "../../headers/external/SDL2/SDL_net.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>
#include <thread>
#include "../../constants.hpp"

#define NAMEMAXLEN 50

class Connection {
protected:
    static int count;
    static std::map<int, std::thread*> threads;
    TCPsocket remote;
    int port = 0;
    std::string remote_name; /// first receive after accept
public:
    virtual ~Connection();
    std::string Receive(float timeout = DEFAULT_TIMEOUT, int MAXLEN = 1024);
    int Send(std::string text);
    static int getConnectionCount();
    [[nodiscard]] int getPort() const;
    [[nodiscard]] std::string getPeerName() const;
};

class ConnectionToServer : public Connection {
public:
    ConnectionToServer(std::string address, int port, std::string self_name);
};

class ConnectionToClient : public Connection {
private:
    TCPsocket local;
    std::thread *connectThread = nullptr;
    //std::thread *listenerThread = nullptr;
public:
    explicit ConnectionToClient(int port);
    ~ConnectionToClient() override;
    void AwaitClient();
    void AwaitHandshake();
    std::string getPeerAddress();
};

#endif
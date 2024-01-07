#include <iostream>
#include <cstring>
#include "../../headers/Networking/Connection.hpp"
#include <chrono>
#include "../../headers/Game.hpp"
#include "../../constants.hpp"

int Connection::count = 0;
std::map<int, std::thread*> Connection::threads;

int Connection::Send(std::string text) {
    char buffer[MAX_TCP_MESSAGE_SIZE];
    strcpy(buffer, text.c_str());
    return SDLNet_TCP_Send(remote, buffer, strlen(buffer) + 1);
}

std::string Connection::Receive(float timeout, int MAXLEN) {
    if(MAXLEN > MAX_TCP_MESSAGE_SIZE)
        throw "MAXLEN > MAX_TCP_MESSAGE_SIZE";
    char buffer[MAX_TCP_MESSAGE_SIZE];
    int bytesReturned;
    auto start = std::chrono::steady_clock::now();
    std::chrono::duration<float> timer;
    SDLNet_SocketSet socketSet;
    socketSet = SDLNet_AllocSocketSet(1);
    SDLNet_TCP_AddSocket(socketSet, remote);
    while(true) {
        if(SDLNet_CheckSockets(socketSet, timeout == NO_TIMEOUT ? INT_MAX : (int)(timeout * 1000))) {
            bytesReturned = SDLNet_TCP_Recv(remote, buffer, MAXLEN);
            if (bytesReturned > 0)
                return std::string(buffer);
        }
        if(timeout != NO_TIMEOUT) {
            timer = std::chrono::steady_clock::now() - start;
            if (timer.count() > timeout)
                return "timeout";
        }
    }
}



ConnectionToServer::ConnectionToServer(std::string address, int port, std::string self_name) {
    this->port = port;
    IPaddress ip;
    char caddress[20];
    strcpy(caddress, address.c_str());
    SDLNet_ResolveHost(&ip, caddress, port);
    remote = SDLNet_TCP_Open(&ip);

    this->Send(self_name);
    std::string recvmsg = this->Receive(2.0f);
    if(recvmsg == "timeout")
        throw ConnectionTimedOutException();
    if(recvmsg == "nametaken")
        throw NameTakenException();

    (new std::thread([this] () {
        /// wait for signal that everyone connected
        std::string recv = this->Receive(NO_TIMEOUT);
        if(recv.starts_with(ALL_CONNECTED_MSG)) {
            Game::getInstancePtr()->clientEventAllConnected(
                    recv.substr(recv.find_first_of('\n') + 1)
                    );
        }
    }))->detach();
}

void AwaitClientWrapper(ConnectionToClient* context) {
    context->AwaitClient();
}

void ConnectionToClient::AwaitClient() {
    char buffer[NAMEMAXLEN + 1];
    do
        remote = SDLNet_TCP_Accept(local);
    while(!remote);
    SDLNet_TCP_Recv(remote, buffer, NAMEMAXLEN);
    this->remote_name = std::string(buffer);
    char reply[] = "Authentication successful\n";
    bool retry = false;
    if(Game::getInstancePtr()->isNameTaken(remote_name)) {
        strcpy(reply, "nametaken");
        retry = true;
    }

    SDLNet_TCP_Send(remote, reply, strlen(reply) + 1);
    if(retry)
        ConnectionToClient::AwaitClient();
}


ConnectionToClient::ConnectionToClient(int port) {
    this->port = port;
    ++count;
    IPaddress ip;
    SDLNet_ResolveHost(&ip, nullptr, port);
    local = SDLNet_TCP_Open(&ip);
    connectThread = new std::thread(AwaitClientWrapper, this);

    auto result = threads.insert(std::make_pair(port, connectThread));
    if(!result.second)
        throw std::runtime_error("Connection to client failed");
}

void ConnectionToClient::AwaitHandshake() {
    this->connectThread->join();
    delete connectThread;
    connectThread = nullptr;
}

ConnectionToClient::~ConnectionToClient() {
    std::cout << "Connection with " << this->getPeerAddress() << ':' << port << " ended\n";
    delete connectThread;
    SDLNet_TCP_Close(local);
}

std::string ConnectionToClient::getPeerAddress() {
    IPaddress *ipaddr = SDLNet_TCP_GetPeerAddress(this->remote);
    return SDLNet_ResolveIP(ipaddr);
}

int Connection::getConnectionCount() {
    return Connection::count;
}

Connection::~Connection() {
    SDLNet_TCP_Close(remote);
}

int Connection::getPort() const {
    return this->port;
}

std::string Connection::getPeerName() const {
    return remote_name;
}
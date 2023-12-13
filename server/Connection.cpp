#include <iostream>
#include "Connection.hpp"
#include <chrono>

int Connection::count = 0;
std::map<int, std::thread*> Connection::threads;

void Connection::Send(std::string text) {
    char buffer[text.size() + 1];
    strcpy(buffer, text.c_str());
    SDLNet_TCP_Send(remote, buffer, strlen(buffer) + 1);
}

std::string Connection::Receive(float timeout, int MAXLEN) {
    char buffer[MAXLEN + 1];
    int bytesReturned = 0;
    auto start = std::chrono::steady_clock::now();
    std::chrono::duration<float> timer;
    while(true) {
        bytesReturned = SDLNet_TCP_Recv(remote, buffer, MAXLEN);
        if(bytesReturned > 0)
            return std::string(buffer);
        timer = std::chrono::steady_clock::now() - start;
        std::cout<<timer.count() - timeout;
        if(timer.count() > timeout)
            return "timeout";
    }
}


ConnectionToServer::ConnectionToServer(std::string address, int port, std::string self_name, int MAXREQ) {
    this->port = port;
    IPaddress ip;
    char caddress[20];
    strcpy(caddress, address.c_str());
    SDLNet_ResolveHost(&ip, caddress, port);
    remote = SDLNet_TCP_Open(&ip);

    this->Send(self_name);
    std::cout << this->Receive();
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
    remote_name = std::string(buffer);
    char success_text[] = "Authentication successful\n";

    SDLNet_TCP_Send(remote, success_text, strlen(success_text) + 1);
}


ConnectionToClient::ConnectionToClient(int port) {
    this->port = port;
    ++count;
    IPaddress ip;
    SDLNet_ResolveHost(&ip, NULL, port);
    local = SDLNet_TCP_Open(&ip);
    connectThread = new std::thread(AwaitClientWrapper, this);
    auto result = threads.insert(std::make_pair(port, connectThread));
    //if(result.second == false)
        ///throw ...
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
#include "Connection.hpp"
#include <iostream>

ServerSocket::ServerSocket(int port) {
    IPaddress ip;
    SDLNet_ResolveHost(&ip, NULL, port);
    this->server = SDLNet_TCP_Open(&ip);
}

ServerSocket::~ServerSocket() {
    SDLNet_TCP_Close(server);
}

void AwaitAuthenticationWrapper(ServerSocket *context) {
    context->AwaitAuthentication();
}

void ServerSocket::AwaitAuthentication() {
    char buffer[NAMEMAXLEN + 1];
    TCPsocket client;
    do
        client = SDLNet_TCP_Accept(server);
    while(!client);
    SDLNet_TCP_Recv(client, buffer, NAMEMAXLEN);

    char success_text[] = "Authentication successful";

    SDLNet_TCP_Send(client, success_text, strlen(success_text) + 1);

    clients.emplace_back(client, std::string(buffer));
}

boost::thread* ServerSocket::AwaitAuthenticationAsync() {
    boost::thread *thrd_ptr = new boost::thread(AwaitAuthenticationWrapper, this);
    return thrd_ptr;
}


std::string ServerSocket::Receive(Connection &client, int maxMessageLen) {
    char received_text[maxMessageLen];
    SDLNet_TCP_Recv(client.getSocket(), received_text, maxMessageLen - 1);
    return std::string(received_text);
}

void ServerSocket::Send(Connection &client, std::string text) {
    char ctext[text.size() + 2];
    strcpy(ctext, text.c_str());
    SDLNet_TCP_Send(client.getSocket(), ctext, strlen(ctext) + 1);
}

void ServerSocket::RemoveConnection(std::string clientName) {
    for(auto it = this->clients.begin(); it != this->clients.end(); ++it)
        if((*it).getName() == clientName)
            this->clients.erase(it);
}

Connection::Connection(TCPsocket remote, std::string name) : remote(remote), remote_name(std::move(name)) {

}

Connection::~Connection() {
    if(remote)
        SDLNet_TCP_Close(remote);
}

TCPsocket Connection::getSocket() const {
    return this->remote;
}

std::string Connection::getName() const {
    return this->remote_name;
}
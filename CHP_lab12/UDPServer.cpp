#include "UDPServer.h"
#include <stdexcept>
#include <cstring>

UDPServer::UDPServer(unsigned short serverport) : UDPSocket(), mServerPort(serverport)
{
    memset((char*)&mServer, 0, sizeof(mServer));
    mServer.sin_family = AF_INET;
    mServer.sin_addr.s_addr = INADDR_ANY;
    mServer.sin_port = htons(mServerPort);

    if (bind(s, (struct sockaddr*)&mServer, sizeof(mServer)) == SOCKET_ERROR)
    {
        throw std::runtime_error("Bind failed with error code: " + std::to_string(WSAGetLastError()));
    }
}

UDPServer::~UDPServer() {}

unsigned short UDPServer::GetPort() const
{
    return mServerPort;
}

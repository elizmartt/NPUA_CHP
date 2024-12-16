#pragma once
#include "UDPSocket.h"

class UDPServer : public UDPSocket
{
private:
    unsigned short mServerPort;
    struct sockaddr_in mServer;

    UDPServer(); // Prevent default constructor

public:
    UDPServer(unsigned short serverport);
    virtual ~UDPServer();

    unsigned short GetPort() const;
};


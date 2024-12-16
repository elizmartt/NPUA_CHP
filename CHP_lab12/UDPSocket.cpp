#include "UDPSocket.h"
#include <stdexcept>
#include <cstring> // For memset on non-Windows systems

int UDPSocket::WSAInit()
{
    static unsigned int count = 0;
    if (count++)
        return 0;

#ifdef _WIN32
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("Failed to initialize Winsock. Error Code: %d\n", WSAGetLastError());
        return -1;
    }
#endif
    return 0;
}

UDPSocket::UDPSocket()
{
    if (WSAInit() != 0)
        throw std::runtime_error("Failed to initialize socket library.");

    s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (s == INVALID_SOCKET)
        throw std::runtime_error("Socket creation failed with error: " + std::to_string(WSAGetLastError()));
}

UDPSocket::~UDPSocket()
{
#ifdef _WIN32
    closesocket(s);
    WSACleanup();
#else
    close(s);
#endif
}

int UDPSocket::SendDatagram(const char* msg, unsigned int msglen, struct sockaddr* si_dest, unsigned int slen)
{
    if (sendto(s, msg, (int)msglen, 0, si_dest, slen) == SOCKET_ERROR)
    {
        printf("sendto() failed with error code: %d\n", WSAGetLastError());
        return -1;
    }
    return 0;
}

int UDPSocket::RecvDatagram(char* buf, unsigned int buflen, struct sockaddr* si_dest, int* slen)
{
    if (recvfrom(s, buf, (int)buflen, 0, si_dest, slen) == SOCKET_ERROR)
    {
        printf("recvfrom() failed with error code: %d\n", WSAGetLastError());
        return -1;
    }
    return 0;
}

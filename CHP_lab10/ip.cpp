#include "ip.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstring> // For memset

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#endif

std::vector<std::string> getIPAddress() {
    char hostname[256];
    if (gethostname(hostname, sizeof(hostname)) != 0) {
        return {"Failed to get hostname."};
    }

    struct addrinfo hints, *res = nullptr;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC; // Support both IPv4 and IPv6
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(hostname, nullptr, &hints, &res) != 0) {
        return {"Failed to get address info."};
    }

    std::vector<std::string> ipAddresses;
    char ipStr[INET6_ADDRSTRLEN];

    for (struct addrinfo* p = res; p != nullptr; p = p->ai_next) {
        void* addr;
        if (p->ai_family == AF_INET) { // IPv4
            struct sockaddr_in* ipv4 = (struct sockaddr_in*)p->ai_addr;
            addr = &(ipv4->sin_addr);
        } else if (p->ai_family == AF_INET6) { // IPv6
            struct sockaddr_in6* ipv6 = (struct sockaddr_in6*)p->ai_addr;
            addr = &(ipv6->sin6_addr);
        } else {
            continue; // Skip unknown address families
        }

        inet_ntop(p->ai_family, addr, ipStr, sizeof(ipStr));
        ipAddresses.push_back(std::string(ipStr));
    }

    freeaddrinfo(res);
    return ipAddresses;
}
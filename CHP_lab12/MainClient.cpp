#include "UDPSocket.h"
#include <stdio.h>
#include <string.h>

#define SERVER "127.0.0.1"
#define PORT 8888

int main(int argc, char* argv[])
{
    struct sockaddr_in si_other;
    int slen = sizeof(si_other);
    char buf[BUFLEN];
    char message[BUFLEN];

    const char* srv_ip = (argc > 1) ? argv[1] : SERVER;
    unsigned short srv_port = (argc > 2) ? atoi(argv[2]) : PORT;

    memset((char*)&si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(srv_port);
    si_other.sin_addr.s_addr = inet_addr(srv_ip);

    UDPSocket client_sock;

    while (1)
    {
        printf("Enter message: ");
        if (fgets(message, BUFLEN, stdin) != nullptr)
        {
            message[strcspn(message, "\n")] = 0;
            client_sock.SendDatagram(message, (int)strlen(message), (struct sockaddr*)&si_other, slen);

            memset(buf, '\0', BUFLEN);
            client_sock.RecvDatagram(buf, BUFLEN, (struct sockaddr*)&si_other, &slen);

            printf("Server reply: %s\n", buf);
        }
    }

    return 0;
}

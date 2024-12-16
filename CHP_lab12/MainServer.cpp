#include <stdio.h>
#include "UDPServer.h"

#define PORT 8888

int main(int argc, char* argv[])
{
    struct sockaddr_in si_other;
    unsigned short srvport;
    int slen;
    char buf[BUFLEN];
    char msg[BUFLEN];

    srvport = (argc == 1) ? PORT : atoi(argv[1]);
    UDPServer server(srvport);
    slen = sizeof(si_other);

    while (1)
    {
        printf("Waiting for data...\n");
        fflush(stdout);

        memset(buf, '\0', BUFLEN);
        server.RecvDatagram(buf, BUFLEN, (struct sockaddr*)&si_other, &slen);

        printf("Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
        printf("Data: %s\n", buf);

        if (strcmp(buf, "exit") == 0)
        {
            printf("Shutting down server.\n");
            break;
        }

        printf("Reply: ");
        if (fgets(msg, BUFLEN, stdin) != nullptr)
        {
            msg[strcspn(msg, "\n")] = 0;
            server.SendDatagram(msg, (int)strlen(msg), (struct sockaddr*)&si_other, slen);
        }
    }

    return 0;
}

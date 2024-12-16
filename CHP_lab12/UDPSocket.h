#pragma once
#include <stdio.h>
#ifndef _WIN32
using SOCKET = int;
#define WSAGetLastError() 1
#else
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib") //Winsock Library
#endif

#define SERVER "127.0.0.1"	//ip address of udp server
#define BUFLEN 	1024		//Max length of buffer
#define PORT 8888			//The port on which to listen for incoming data

class UDPSocket
{
#pragma once
#include <stdio.h>

#ifndef _WIN32
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
	using SOCKET = int;
#define SOCKET_ERROR -1
#define INVALID_SOCKET -1
#define WSAGetLastError() errno
#else
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib") // Winsock Library
#endif

#define BUFLEN 1024

	class UDPSocket
	{
	protected:
		SOCKET s;

	public:
		static int WSAInit();

		UDPSocket();
		virtual ~UDPSocket();

		int SendDatagram(const char* msg, unsigned int msglen, struct sockaddr* si_dest, unsigned int slen);
		int RecvDatagram(char* buf, unsigned int buflen, struct sockaddr* si_dest, int* slen);
	};

protected:
	SOCKET s;

public:
	static int WSAInit();

	UDPSocket();
	virtual ~UDPSocket();

	int SendDatagram(char* msg, unsigned int msglen, struct sockaddr* si_dest, unsigned int slen);
	int RecvDatagram(char* buf, unsigned int buflen, struct sockaddr* si_dest, int *slen);
};

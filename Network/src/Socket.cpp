#include "Socket.h"

#include <cstdio>

Socket::Socket(ID id)
	:
	id(id)
{}
Socket::~Socket()
{
	closesocket(this->socketObject);
	WSACleanup();
}

bool Socket::Compare(DNode* DNode)
{
	return this->id == ((Socket*)DNode)->id;
}

void Socket::Print()
{
	DNode::Print();

	printf("\tSocket Name: ");
	switch (this->id)
	{
	case ID::client1:
		printf("client1\n");
		break;
	case ID::client2:
		printf("client2\n");
		break;
	case ID::server1:
		printf("server1\n");
		break;
	case ID::server2:
		printf("server2\n");
		break;
	default:
		break;
	}

	char* ip = inet_ntoa(this->targetAddress.sin_addr);
	printf("\tTarget IP Address: %s\n", ip);

	printf("\tTarget Port Number: %u\n", ntohs(this->targetAddress.sin_port));
}

void Socket::SetTargetAddress(const char* ip, int port)
{
	this->targetAddress.sin_family = AF_INET;
	this->targetAddress.sin_addr.s_addr = inet_addr(ip);
	this->targetAddress.sin_port = htons((u_short)port);
}
void Socket::SetTargetAddress(ULONG ip, int port)
{
	this->targetAddress.sin_family = AF_INET;
	this->targetAddress.sin_addr.s_addr = ip;
	this->targetAddress.sin_port = htons((u_short)port);
}
void Socket::Bind()
{
	if (bind(this->socketObject, (SOCKADDR*)&this->targetAddress, sizeof(this->targetAddress)) == SOCKET_ERROR)
	{
		printf("Socket failed to bind with error code: %d\n", WSAGetLastError());
	}
	printf("Socket bound.\n");
}

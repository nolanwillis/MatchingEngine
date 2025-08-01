#include "SocketTCP.h"

#include <cstdio>
#include <assert.h>

SocketTCP::SocketTCP(ID id)
	: 
	Socket(id)
{
	this->socketObject = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (this->socketObject == INVALID_SOCKET)
	{
		printf("Failed to create TCP socket with error code: %ld.", WSAGetLastError());
		WSACleanup();
		assert(false);
	}
}

void SocketTCP::Print()
{
	Socket::Print();
	printf("\tSocket Type: TCP\n");
}

void SocketTCP::Send(const char* src, const int srcSize)
{
	if (send(this->socketObject, src, srcSize, 0) == SOCKET_ERROR) 
	{
		printf("TCP socket failed to send with error code: %d\n", WSAGetLastError());
	}
}
int SocketTCP::Receive(char* dst, const int dstSize)
{
	int iResult = recv(this->socketObject, dst, dstSize, 0);
	if (iResult == 0)
	{
		printf("TCP socket connection closed.\n");
	}
	return iResult;
}

void SocketTCP::Connect()
{
	if (connect(this->socketObject, (SOCKADDR*)&this->targetAddress, sizeof(this->targetAddress)) == SOCKET_ERROR)
	{
		printf("TCP socket failed to connect with error code: %ld.\n", WSAGetLastError());
	}
	printf("TCP socket connected.\n");
}
void SocketTCP::Listen()
{
	listen(this->socketObject, 0);
	printf("TCP socket set to listen.\n");
}
void SocketTCP::Accept(SocketTCP& clientSocket)
{
	printf("Waiting for connection...\n");
	SOCKADDR_IN clientAddress = {};
	int clientAddressSize = sizeof(clientAddress);
	SOCKET clientSocketObject = accept(this->socketObject, (SOCKADDR*)&clientAddress, &clientAddressSize);
	printf("Client socket connected.\n");

	clientSocket.socketObject = clientSocketObject;
	clientSocket.targetAddress = clientAddress;
}

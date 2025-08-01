#include "SocketUDP.h"

#include <cstdio>
#include <assert.h>

SocketUDP::SocketUDP(ID id)
	:
	Socket(id)
{
	this->socketObject = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (this->socketObject == INVALID_SOCKET)
	{
		std::printf("Failed to create UDP socket with error code: %ld.", WSAGetLastError());
		WSACleanup();
		assert(false);
	}
}

void SocketUDP::Print()
{
	Socket::Print();

	std::printf("\tSocket Type: UDP\n");
}
void SocketUDP::Send(const char* src, const int srcSize)
{
	if (sendto(this->socketObject, src, srcSize, 0, (SOCKADDR*)&this->targetAddress, 
		sizeof(this->targetAddress)) == SOCKET_ERROR)
	{
		std::printf("UDP socket failed to send with error code: %d\n", WSAGetLastError());
	}
}
int SocketUDP::Receive(char* dst, const int dstSize)
{
	int addressSize = sizeof(this->targetAddress);

	int iResult = recvfrom(this->socketObject, dst, dstSize, 0, 
		(SOCKADDR*)&this->targetAddress, &addressSize);

	return iResult;
}

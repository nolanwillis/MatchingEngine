#ifndef SOCKET_UDP_H
#define SOCKET_UDP_H

#include "Socket.h"

class SocketUDP : public Socket
{
public:
	SocketUDP() = delete;
	SocketUDP(ID id);
	SocketUDP(const SocketUDP& rhs) = delete;
	SocketUDP& operator=(const Socket& rhs) = delete;
	virtual ~SocketUDP() = default;

	virtual void Print() override;
	virtual void Send(const char* src, const int srcSize) override;
	virtual int Receive(char* dst, const int dstSize) override;
};

#endif 

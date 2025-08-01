#ifndef SOCKET_TCP_H
#define SOCKET_TCP_H

#include "Socket.h"

class SocketTCP : public Socket
{
public:
	SocketTCP() = delete;
	SocketTCP(ID id);
	SocketTCP(const SocketTCP& rhs) = delete;
	SocketTCP& operator=(const Socket& rhs) = delete;
	virtual ~SocketTCP() = default;
	
	virtual void Print() override;
	virtual void Send(const char* src, const int srcSize) override;
	virtual int Receive(char* dst, const int dstSize) override;

	void Connect();
	void Listen();
	void Accept(SocketTCP& clientSocket);
};

#endif 

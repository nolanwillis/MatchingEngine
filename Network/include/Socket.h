#ifndef SOCKET_H
#define SOCKET_H

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include "DNode.h"

#include <winsock2.h>

class Socket : public DNode
{
public:
	enum class ID
	{
		client1, 
		client2,
		server1,
		server2
	};
	
	ID id;
	SOCKET socketObject;
	SOCKADDR_IN targetAddress;
	
	virtual ~Socket();
	virtual bool Compare(DNode* pDNode) override;
	virtual void Print() override;

	void Bind();
	void SetTargetAddress(const char* ip, int port);
	void SetTargetAddress(ULONG ip, int port);
	
	virtual void Send(const char* src, const int srcSize) = 0;
	virtual int Receive(char* dst, const int dstSize) = 0;

protected:
	Socket() = delete;
	Socket(ID id);
	Socket(const Socket& rhs) = delete;
	Socket& operator=(const Socket& rhs) = delete;
};

#endif 

#ifndef PACKET_H
#define PACKET_H

class Socket;
class Message;

class Packet
{
public:
	enum class Type
	{
		START,
		END,
		ITEM,
		ACK,
		UNINITIALIZED
	};

	Type type;
	int index;
	size_t payloadSize;

	Packet();
	Packet(const Packet& rhs) = delete;
	Packet& operator=(const Packet& rhs) = delete;
	~Packet();

	// Sends this packet through the passed in socket with the given payload.
	void Send(Socket& socket, Type typeIn, Message* message = nullptr);
	// Receives a packet through the passed in socket and deserializes it's payload 
	// into the given payload (this packet "becomes" the received packet).
	void Receive(Socket& socket, Message* message);
	void Print(bool wasSent);

private:
	char* payloadBytes;

	void Serialize(char* buffer);
	void Deserialize(char* buffer);
	void WaitForACK(Socket& socket);
	void SendACK(Socket& socket);
};

#endif 

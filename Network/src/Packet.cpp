#include "Packet.h"
#include "Socket.h"
#include "Message.h"
#include "NetworkManager.h"

#include <cstdio>
#include <random>

Packet::Packet()
	:
	type(Packet::Type::UNINITIALIZED),
	index(-1),
	payloadBytes(nullptr)
{}
Packet::~Packet()
{
	if (this->payloadBytes != nullptr)
	{
		delete[] this->payloadBytes;
	}
}

void Packet::Send(Socket& socket, Type typeIn, Message* message)
{
	// Delete the payloadBytes array if one exists (calling send twice in a row).  
	if (this->payloadBytes)
	{
		delete[] this->payloadBytes;
		this->payloadBytes = nullptr;
	}

	// Set the packet data.
	this->type = typeIn;
	this->index = NetworkManager::GetPacketIndex();
	if (type == Packet::Type::ITEM)
	{
		this->payloadSize = message->GetSerializedSize();
		this->payloadBytes = new char[this->payloadSize];
		message->Serialize(this->payloadBytes);
	}
	else
	{
		this->payloadSize = 0;
	}

	// Serialize this packet into an array of bytes.
	char* packetBytes = new char[1500];
	this->Serialize(packetBytes);

	if (NetworkManager::Settings().shouldDuplicate)
	{
		socket.Send(packetBytes, 1500);
		if (NetworkManager::Settings().shouldPrintPackets) this->Print(true);

		float randomValue = static_cast<float>(std::rand()) / RAND_MAX * 100.0f;
		if (randomValue < NetworkManager::Settings().duplicatePercent)
		{
			socket.Send(packetBytes, 1500);
			if (NetworkManager::Settings().shouldPrintPackets) this->Print(true);
		}
	}
	else
	{
		socket.Send(packetBytes, 1500);
		if (NetworkManager::Settings().shouldPrintPackets) this->Print(true);
	}

	// If we should ACK and the sent packet is an item, wait for an ACK.
	if (NetworkManager::Settings().shouldACK && this->type == Type::ITEM)
	{
		WaitForACK(socket);
	}

	delete[] packetBytes;

	// Only increment the packet order index if an item packet is sent.
	if (this->type == Type::ITEM)
	{
		NetworkManager::SetPacketIndex(NetworkManager::GetPacketIndex() + 1);
	}
}
void Packet::Receive(Socket& socket, Message* message)
{
	//// Delete the payloadBytes array if one exists.  
	//if (this->payloadBytes)
	//{
	//	delete[] this->payloadBytes;
	//	this->payloadBytes = nullptr;
	//}

	// Spin until we receive the packet with the correct index; 
	while (true)
	{
		char* packetBytes = new char[1500];
		socket.Receive(packetBytes, 1500);
		this->Deserialize(packetBytes);
		if (NetworkManager::Settings().shouldPrintPackets) this->Print(false);

		delete[] packetBytes;

		//printf("Received packet with id: %d\n", this->index);

		if (this->index == NetworkManager::GetPacketIndex())
		{
			message->Deserialize(this->payloadBytes);
			break;
		}
	}

	// If we should ACK and the received packet is an item, wait for an ACK.
	if (NetworkManager::Settings().shouldACK && this->type == Type::ITEM)
	{
		SendACK(socket);
	}

	// Only increment the packet order index if an item packet is received.
	if (this->type == Type::ITEM)
	{
		NetworkManager::SetPacketIndex(NetworkManager::GetPacketIndex() + 1);
	}
}
void Packet::Print(bool wasSent)
{
	printf("\n\n");
	printf("------------------------\n");

	if (wasSent)
	{
		printf("SENT --> Packet: %d\n", this->index);
	}
	else
	{
		printf("RECEIVED <-- Packet: %d\n", this->index);
	}

	if (this->type == Type::ITEM)
	{
		printf("\tType: ITEM\n");
	}
	else if (this->type == Type::ACK)
	{
		printf("\tType: ACK\n");
	}
	printf("\tPayload: (%p)\n", this->payloadBytes);
	printf("\tPayload Size: %d\n", this->payloadSize);
	printf("------------------------");
}

void Packet::Serialize(char* buffer)
{
	memcpy_s(buffer, sizeof(Type), &this->type, sizeof(Type));
	memcpy_s(buffer + sizeof(Type), sizeof(int), &index, sizeof(int));
	memcpy_s(buffer + sizeof(Type) + sizeof(int), sizeof(size_t),
		&this->payloadSize, sizeof(size_t));
	if (type == Packet::Type::ITEM)
	{
		memcpy_s(buffer + sizeof(Type) + sizeof(int) + sizeof(size_t), this->payloadSize,
			this->payloadBytes, this->payloadSize);
	}
}
void Packet::Deserialize(char* buffer)
{
	memcpy_s(&this->type, sizeof(Type), buffer, sizeof(Type));
	memcpy_s(&this->index, sizeof(int), buffer + sizeof(Type), sizeof(int));
	memcpy_s(&this->payloadSize, sizeof(size_t), buffer + sizeof(Type) + sizeof(int),
		sizeof(size_t));
	if (this->type == Packet::Type::ITEM)
	{
		if (this->payloadBytes)
		{
			delete[] this->payloadBytes;
			this->payloadBytes = nullptr;
		}

		this->payloadBytes = new char[this->payloadSize];
		memcpy_s
		(
			this->payloadBytes,
			this->payloadSize,
			buffer + sizeof(Type) + sizeof(int) + sizeof(size_t),
			this->payloadSize
		);
	}
}
void Packet::WaitForACK(Socket& socket)
{
	while (true)
	{
		Message message;
		this->Receive(socket, &message);
		if (this->type == Packet::Type::ACK)
		{
			if (this->index == NetworkManager::GetPacketIndex())
			{
				this->type = Type::ITEM;
				break;
			}
		}
	}
}
void Packet::SendACK(Socket& socket)
{
	this->Send(socket, Type::ACK);
	this->type = Type::ITEM;
}

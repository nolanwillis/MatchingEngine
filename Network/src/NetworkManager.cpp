#include "NetworkManager.h"
#include "DNode.h"

#include <cstdio>
#include <random>
#include <assert.h>

NetworkManager::NetworkManager()
	:
	packetIndex(0),
	iResult(-1),
	wsaData(),
	socketList()
{}

void NetworkManager::Create()
{

	NetworkManager& instance = NetworkManager::GetInstance();
	instance.iResult = WSAStartup(MAKEWORD(2, 2), &instance.wsaData);
	if (instance.iResult != 0) 
	{
		printf("WSAStartup failed: %d\n", instance.iResult);
	}
	
	// Seed random number generator for network simulation.
	std::srand((unsigned int)std::time(nullptr));
}
void NetworkManager::Destroy(){}
Socket* NetworkManager::AddSocket(Socket* const socket)
{
	NetworkManager& instance = NetworkManager::GetInstance();
	instance.socketList.AddToEnd(socket);
	return socket;
}
int NetworkManager::GetPacketIndex()
{
	NetworkManager& instance = NetworkManager::GetInstance();
	return instance.packetIndex;
}
void NetworkManager::SetPacketIndex(const int newIndex)
{
	assert(newIndex >= 0);
	NetworkManager& instance = NetworkManager::GetInstance();
	instance.packetIndex = newIndex;
}
NetworkSettings& NetworkManager::Settings()
{
	static NetworkManager instance;
	return instance.settings;
}
void NetworkManager::PrintSocketList()
{
	NetworkManager& instance = NetworkManager::GetInstance();
	instance.socketList.Print();
}

NetworkManager& NetworkManager::GetInstance()
{
	static NetworkManager instance;
	return instance;
}

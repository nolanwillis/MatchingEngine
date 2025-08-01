#ifndef NETWORK_MANAGER
#define NETWORK_MANAGER

#include "DNodeList.h"
#include "Socket.h"

#pragma comment(lib, "Ws2_32.lib")

struct NetworkSettings
{
	bool shouldPrintPackets;
	bool shouldDuplicate;
	bool shouldACK;
	int duplicatePercent;
};

class NetworkManager
{
public:
	static void Create();
	static void Destroy();
	static Socket* AddSocket(Socket* const socket);
	static int GetPacketIndex();
	static void SetPacketIndex(const int newIndex);
	static NetworkSettings& Settings();
	static void PrintSocketList();

private:
	int packetIndex;
	int iResult;
	WSADATA wsaData;
	DNodeList socketList;
	NetworkSettings settings;

	NetworkManager();
	NetworkManager(const NetworkManager& rhs) = default;
	NetworkManager& operator=(const NetworkManager& rhs) = default;
	~NetworkManager() = default;

	static NetworkManager& GetInstance();
};

#endif
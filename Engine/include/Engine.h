#ifndef ENGINE_H
#define ENGINE_H

#define ASIO_STANDALONE
#define _WEBSOCKETPP_CPP11_STL_

#include "Message.h"
#include "EngineWorker.h"

#include <asio.hpp>
#include <condition_variable>
#include <gtest/gtest.h>
#include <mutex>
#include <queue>
#include <set>
#include <thread>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

using websocketpp::connection_hdl;
using message_ptr = websocketpp::server<websocketpp::config::asio>::message_ptr;
using WebSocketServer = websocketpp::server<websocketpp::config::asio>;

class EngineTests;
class Trade;

class Engine
{
public:
	friend class EngineWorker;
	
	friend class ::EngineTests;
	FRIEND_TEST(EngineTests, WebsocketMessageWorks);

	static void Create();
	static void Destroy();

	static void Run(uint16_t port, int threadCount = 4);
	static void BroadcastTrade(Trade& trade);

private:
	static Engine* instance;

	WebSocketServer webSocketServer;
	std::set<connection_hdl, std::owner_less<connection_hdl>> connections;
	std::mutex connectionMtx;
	
	std::queue<std::unique_ptr<Message>> routingQueue;
	std::mutex routingQueueMtx;
	std::condition_variable routingQueueCV;
	
	std::vector<std::unique_ptr<EngineWorker>> workers;
	std::promise<void> stopSignal; 

	static Engine& GetInstance();
	
	Engine();
	Engine(const Engine& rhs) = delete;
	Engine& operator=(const Engine& rhs) = delete;
	~Engine();
	
	void HandleMessage(connection_hdl handle, message_ptr message);
	void CreateWorkers(int numWorkers);
};

#endif

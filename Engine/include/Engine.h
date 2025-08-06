#ifndef ENGINE_H
#define ENGINE_H

#include "MessageHandler.h"

class Message;
class OrderBook;

class MessageRouter : public MessageHandler
{
public:
	void HandleMessage(Message* msg);
};

#endif
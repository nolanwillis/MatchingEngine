#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include "Message.h"

class MessageHandler
{
public:
	virtual void HandleMessage(Message* msg) = 0;
};

#endif

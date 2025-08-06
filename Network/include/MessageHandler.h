#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

class Message;

class MessageHandler
{
public:
	virtual void HandleMessage(Message* msg) = 0;
};

#endif

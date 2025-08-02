#ifndef TEST_MESSAGE_H
#define TEST_MESSAGE_H

#include "Message.h"

class TestMessage : public Message
{
public:
	int value;

	TestMessage() = delete;
	TestMessage(int value);
	TestMessage(const TestMessage& rhs) = delete;
	TestMessage& operator=(const TestMessage& rhs) = delete;
	virtual ~TestMessage() = default;

	virtual void Serialize(char* buffer) override;
	virtual void Deserialize(char* buffer) override;
	virtual size_t GetSerializedSize() const override;
	virtual void Print() const override;
};

#endif

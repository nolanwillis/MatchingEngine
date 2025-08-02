#include "TestMessage.h"

#include <assert.h>
#include <string>

TestMessage::TestMessage(int value)
	:
	Message(Message::Type::Test),
	value(value)
{}

void TestMessage::Serialize(char* buffer)
{
	memcpy_s(buffer, sizeof(int), &this->value, sizeof(int));
}
void TestMessage::Deserialize(char* buffer)
{
	memcpy_s(&this->value, sizeof(int), buffer, sizeof(int));
}
size_t TestMessage::GetSerializedSize() const
{
	return sizeof(int);
}
void TestMessage::Print() const
{
	printf("%d\n", this->value);
}

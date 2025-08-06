#include "Message.h"

#include <string>

Message::Message(Type type)
	:
	messageType(type)
{}
Message::Message(const Message& rhs)
	:	
	messageType(rhs.messageType)
{}
Message& Message::operator=(const Message& rhs)
{
	if (&rhs != this)
	{
		this->messageType = rhs.messageType;
	}

	return *this;
}

void Message::Serialize(char* buffer)
{
	memcpy_s(
		buffer,
		sizeof(Type),
		&this->messageType,
		sizeof(Type)
	);

}
void Message::Deserialize(char* buffer)
{
	memcpy_s(
		&this->messageType,
		sizeof(Type),
		buffer,
		sizeof(Type)
	);
}
size_t Message::GetSerializedSize() const
{
	return sizeof(Type);
}
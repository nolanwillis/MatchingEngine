#ifndef MESSAGE_H
#define MESSAGE_H

class Message
{
public:
	enum class Type
	{
		Null,
		Test,
		PlaceOrder
	};
	Type messageType;

	Message() = delete;
	Message(Message::Type type);
	Message(const Message& rhs);
	Message& operator=(const Message& rhs);
	virtual ~Message() = default;

	// Serialized object into an array of bytes.
	virtual void Serialize(char* buffer);
	// Deserialized object from an array of bytes.
	virtual void Deserialize(char* buffer);
	// Returns the size of the serialized object.
	virtual size_t GetSerializedSize() const;
	virtual void Print() const {};
	
	Type GetType() const { return messageType; };
};

#endif

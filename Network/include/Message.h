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

	Message() = delete;
	Message(Message::Type type) : type(type) {};
	Message(const Message& rhs) = delete;
	Message& operator=(const Message& rhs) = delete;
	virtual ~Message() = default;

	// Serialized object into an array of bytes.
	virtual void Serialize(char* buffer) { buffer; /* Do nothing by default. */ };
	// Deserialized object from an array of bytes.
	virtual void Deserialize(char* buffer) { buffer; /* Do nothing by default.*/ };
	// Returns the size of the serialized object.
	virtual size_t GetSerializedSize() const { return 0; };
	virtual void Print() const {};
	
	Type GetType() const { return type; };

private:
	Type type;
};

#endif

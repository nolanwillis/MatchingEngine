#ifndef MESSAGE_H
#define MESSAGE_H

class Message
{
public:
	Message() = default;
	Message(const Message& rhs) = delete;
	Message& operator=(const Message& rhs) = delete;
	virtual ~Message() = default;

	virtual void Execute() {};
	// Serialized object into an array of bytes.
	virtual void Serialize(char* buffer) { buffer; /* Do nothing by default. */ };
	// Deserialized object from an array of bytes.
	virtual void Deserialize(char* buffer) { buffer; /* Do nothing by default.*/ };
	// Returns the size of the serialized object.
	virtual size_t GetSerializedSize() { return 0; };
};

#endif

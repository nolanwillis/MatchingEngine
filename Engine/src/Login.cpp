#include "Login.h"

size_t Login::usernameSize = 32;

Login::Login()
	:
	Message(Message::Type::Login),
	username(new char[usernameSize]),
	userID(0),
	loginType(Login::Type::Null)
{}

Login::Login(const char* username, unsigned int userID, Login::Type LoginType)
	:
	Message(Message::Type::Login),
	username(new char[usernameSize]),
	userID(userID),
	loginType(loginType)
{
	memcpy_s(this->username, usernameSize, username, usernameSize);
}
Login::~Login()
{
	delete[] this->username;
	this->username = nullptr;
}

void Login::Serialize(char* buffer)
{
	Message::Serialize(buffer);

	// username
	memcpy_s(
		buffer + sizeof(Message::Type),
		usernameSize,
		this->username,
		usernameSize
	);
	// userID
	memcpy_s(
		buffer + sizeof(Message::Type) + usernameSize,
		sizeof(unsigned int),
		&this->userID,
		sizeof(unsigned)
	);
	// loginType
	memcpy_s(
		buffer + sizeof(Message::Type) + usernameSize + sizeof(unsigned int),
		sizeof(Login::Type),
		&this->loginType,
		sizeof(Login::Type)
	);
}

void Login::Deserialize(char* buffer)
{
	Message::Deserialize(buffer);

	// username
	memcpy_s(
		this->username,
		usernameSize,
		buffer + sizeof(Message::Type),
		usernameSize
	);
	// userID
	memcpy_s(
		&this->userID,
		sizeof(unsigned int),
		buffer + sizeof(Message::Type) + usernameSize,
		sizeof(unsigned int)
	);
	// loginType
	memcpy_s(
		&this->loginType,
		sizeof(Login::Type),
		buffer + sizeof(Message::Type) + usernameSize + sizeof(unsigned int),
		sizeof(Login::Type)
	);
}
size_t Login::GetSerializedSize() const
{
	return Message::GetSerializedSize() + usernameSize + sizeof(unsigned int)
		+ sizeof(Login::Type);
}
void Login::Print() const
{
	printf("[Username]: %s, [User ID]: %u, ");
	if (loginType == Login::Type::Request)
	{
		printf("[Type]: Request\n");
	}
	else if (loginType == Login::Type::Acknowledgment)
	{
		printf("[Type]: Acknowledgement\n");
	}
	else
	{
		printf("[Type]: Null\n");
	}
}

#ifndef LOGIN_H
#define LOGIN_H

#include "Message.h"

#include <string>

class Login : public Message
{
public:
	enum class Type
	{
		Null,
		Request,
		Acknowledgment
	};

	static size_t usernameSize;

	char* username;
	unsigned int userID;
	Login::Type loginType;

	Login();
	Login(const char* username, unsigned int userID, Login::Type LoginType);
	Login(const Login& rhs) = default;
	Login& operator=(const Login& rhs) = default;
	virtual ~Login();

	virtual void Serialize(char* buffer) override;
	virtual void Deserialize(char* buffer) override;
	virtual size_t GetSerializedSize() const override;
	virtual void Print() const override;
};

#endif

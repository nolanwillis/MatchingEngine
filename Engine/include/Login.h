#ifndef LOGIN_H
#define LOGIN_H

#define ASIO_STANDALONE
#define _WEBSOCKETPP_CPP11_STL_

#include "Message.h"

#include <asio.hpp>
#include <string>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

using websocketpp::connection_hdl;

class Login : public Message
{
public:
	enum class Type
	{
		Null,
		Acknowledge,
		Reject
	};

	static size_t usernameSize;

	char* username;
	unsigned int userID;
	Login::Type loginType;
	connection_hdl connectionHandle;

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

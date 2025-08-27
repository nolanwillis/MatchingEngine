#ifndef USER_H
#define USER_H

#include <string>

struct User
{
	unsigned int userID;
	std::string username;

	User() : userID(0), username("") {};
	User(unsigned int userID, const std::string& username) 
		: userID(userID), username(username) {};
	User(const User& rhs) = default;
	User& operator=(const User& rhs) = default;
	~User() = default;
};

#endif

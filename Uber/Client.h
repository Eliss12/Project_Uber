#pragma once
#include "User.h"

class Client: public User
{
public:
	Client();

	Client(const MyString& type, const MyString& userName, const MyString& password,
		const MyString& firstName, const MyString& lastName);

	friend std::istream& operator>>(std::istream& is, Client& client);
};

std::ostream& operator<<(std::ostream& os, const Client& client);
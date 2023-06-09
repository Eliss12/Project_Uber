#include "Client.h"

Client::Client() : User() {}

Client::Client(const MyString& type, const MyString& userName, const MyString& password,
	const MyString& firstName, const MyString& lastName):User(type, userName, password, 
		                                                     firstName, lastName)
{

}
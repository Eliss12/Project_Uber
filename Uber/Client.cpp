#include "Client.h"

Client::Client() : User() {}

Client::Client(const MyString& type, const MyString& userName, const MyString& password,
	const MyString& firstName, const MyString& lastName):User(type, userName, password, 
		                                                     firstName, lastName)
{

}

std::istream& operator>>(std::istream& is, Client& client)
{
	is >> client._type;
	is >> client._userName;
	is >> client._password;
	is >> client._firstName;
	is >> client._lastName;
	is >> client._account;
	return is;
}

std::ostream& operator<<(std::ostream& os, const Client& client)
{
	return os << client.getType() << " " << client.getUserName() << " " << client.getPassword() << " " <<
		client.getFirstName() << " " << client.getLastName() << " " << client.getAccount();
}
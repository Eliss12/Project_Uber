#include "User.h"

User::User(const MyString& type, const MyString& userName, const MyString& password, const MyString& firstName, const MyString& lastName)
{
	setType(type);
	setUserName(userName);
	setPassword(password);
	setFirstName(firstName);
	setLastName(lastName);
}

const MyString& User::getType() const  
{
	return _type;
}

const MyString& User::getUserName() const
{
	return _userName;
}

const MyString& User::getPassword() const
{
	return _password;
}

const MyString& User::getFirstName() const
{
	return _firstName;
}

const MyString& User::getLastName() const
{
	return _lastName;
}

double User::getAccount() const
{
	return _account;
}

void User::setType(const MyString& type)
{
	_type = type;
}

void User::setUserName(const MyString& userName)
{
	_userName = userName;
}

void User::setPassword(const MyString& password)
{
	_password = password;
}

void User::setFirstName(const MyString& firstName)
{
	_firstName = firstName;
}

void User::setLastName(const MyString& lastName)
{
	_lastName = lastName;
}

void User::setAccount(double account)
{
	_account = account;
}
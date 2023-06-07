#pragma once
#include "MyString.h"

class User
{
protected:
	MyString _type = "";
	MyString _userName = "";
	MyString _password = "";
	MyString _firstName = "";
	MyString _lastName = "";
	double _account;

public:
	User() = default;
	User(const MyString& type, const MyString& userName, const MyString& password, const MyString& firstName, const MyString& lastName);

	const MyString& getType() const;
	const MyString& getUserName() const;
	const MyString& getPassword() const;
	const MyString& getFirstName() const;
	const MyString& getLastName() const;
	double getAccount() const;

	void setType(const MyString& type);
	void setUserName(const MyString& userName);
	void setPassword(const MyString& password);
	void setFirstName(const MyString& firstName);
	void setLastName(const MyString& lastName);
	void setAccount(double account);
	
};

#pragma once
#include <iostream>
#include "Vector.hpp"
#include "SharedPtr.hpp"
#include "Client.h"
#include "Driver.h"
#include "Order.h"

class System
{
	Vector<SharedPtr<Client>> clients;
	Vector<SharedPtr<Driver>> drivers;
	Vector<SharedPtr<Order>> orders;
	SharedPtr<Client> currentClient;
	SharedPtr<Driver> currentDriver;

public:
	bool checkUserName(const MyString& userName) const;
	bool registers(const MyString& type, const MyString& userName, const MyString& password,
		const MyString& firstName, const MyString& lastName);
	bool registers(const MyString& type, const MyString& userName, const MyString& password,
		const MyString& firstName, const MyString& lastName,
		const MyString& carNumber, const MyString& phoneNumber);

	bool login(const MyString& userName, const MyString& password);
	void logout();
	void checkClientNotifications() const;
	void checkDriverNotifications() const;
	
};

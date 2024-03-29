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

	void sortDrivers(const Address& address);
	const Driver& findDriver(const Address& address);
	void order(const Address& address, const Address& destination, unsigned int travelersCount);

	void checkMessages() const;
	bool acceptOrder(unsigned int ID, int minutes);
	bool declineOrder(unsigned int ID);
	void changeAddress(const Address& address);
	bool finishOrder(unsigned int ID);
	bool cancelOrder(unsigned int ID);

	void checkOrder(unsigned int ID) const;
	void addMoney(double amount);
	bool pay(unsigned int ID, double amount);
	bool acceptPayment(unsigned int ID);

	bool rate(const MyString& driverName, short rating);
	void findDriver(const MyString& driverName, short rating);

	bool readClients(const char* fileName);
	bool readDrivers(const char* fileName);
	bool readOrders(const char* fileName);
	bool writeClients(const char* fileName);
	bool writeDrivers(const char* fileName);
	bool writeOrders(const char* fileName);
};

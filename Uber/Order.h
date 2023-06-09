#pragma once
#include "Client.h"
#include "Driver.h"
#include "Address.h"

class Order
{
	Driver _driver;
	Client _client;
	Address _address;
	Address _destination;
	unsigned int _travelersCount = 0;
	unsigned int _ID = 0;
	bool accepted = false;
	bool canceled = false;
	bool finished = false;
	int _minutes = 0;
	double moneyToBePaid = 0;
	bool isPaid = false;

public:
	Order() = default;
	Order(const Client& client, const Address& address, const Address& destination, unsigned int travelersCount);
	void setID(unsigned int ID);
	void setDriver(const Driver& driver);
	void setAccepted(bool accepted);
	void setCanceled(bool canceleded);
	void setFinished(bool finished);
	void setMinutes(int minutes);
	void setMoneyToBePaid(double amount);
	void setIsPaid(bool isPaid);

	double getMoneyToBePaid() const;
	int getMinutes() const;
	const Driver& getDriver() const;
	const Client& getClient() const;
	const Address& getAddress() const;
	const Address& getDestination() const;
	unsigned int getID() const;
	bool getAccepted() const;
	bool getCanceled() const;
	bool getFinished() const;
	bool getIsPaid() const;
};

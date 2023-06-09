#include "Order.h"

Order::Order(const Client& client, const Address& address, const Address& destination, unsigned int travelersCount)
{
	_address = address;
	_destination = destination;
	_travelersCount = travelersCount;
	_client = client;
}

void Order::setID(unsigned int ID)
{
	_ID = ID;
}

unsigned int Order::getID() const
{
	return _ID;
}

void Order::setAccepted(bool accepted)
{
	this->accepted = accepted;
}

void Order::setCanceled(bool canceled)
{
	this->canceled = canceled;
}

void Order::setFinished(bool finished)
{
	this->finished = finished;
}

void Order::setDriver(const Driver& driver)
{
	_driver = driver;
}

const Driver& Order::getDriver() const
{
	return _driver;
}

const Client& Order::getClient() const
{
	return _client;
}

const Address& Order::getAddress() const
{
	return _address;
}

const Address& Order::getDestination() const
{
	return _destination;
}

bool Order::getAccepted() const
{
	return accepted;
}

bool Order::getCanceled() const
{
	return canceled;
}

bool Order::getFinished() const
{
	return finished;
}

void Order::setMinutes(int minutes)
{
	if (minutes <= 0)
		_minutes = 1;
	_minutes = minutes;
}

int Order::getMinutes() const
{
	return _minutes;
}

void Order::setMoneyToBePaid(double amount)
{
	moneyToBePaid = amount;
}

double Order::getMoneyToBePaid() const
{
	return moneyToBePaid;
}
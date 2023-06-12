#include "System.h"
const double EPSILON = -0.00001;
const double POSITIVE_EPSILON = 0.00001;

bool System::checkUserName(const MyString& userName) const
{
	size_t clientsSize = clients.getSize();
	for (size_t i = 0; i < clientsSize; i++)
	{
		if ((*clients[i]).getUserName() == userName)
		{
			return true;
		}
	}

	size_t driversSize = drivers.getSize();
	for (size_t i = 0; i < driversSize; i++)
	{
		if ((*drivers[i]).getUserName() == userName)
		{
			return true;
		}

	}

	return false;
}

bool System::registers(const MyString& type, const MyString& userName, const MyString& password,
	const MyString& firstName, const MyString& lastName)
{
	if (checkUserName(userName) == false)
	{
		SharedPtr<Client> client(new Client(type, userName, password, firstName, lastName));
		clients.pushBack(client);
		return true;
	}
	
	std::cout << "Please, enter new username because there is already a user with this username!" << std::endl;
	return false;
}

bool System::registers(const MyString& type, const MyString& userName, const MyString& password,
	const MyString& firstName, const MyString& lastName,
	const MyString& carNumber, const MyString& phoneNumber)
{
	if (checkUserName(userName) == false)
	{
		SharedPtr<Driver> driver(new Driver(type, userName, password, firstName, lastName, carNumber, phoneNumber));
		drivers.pushBack(driver);
		return true;
	}
	
	std::cout << "Please, enter new username because there is already a user with this username!" << std::endl;
	return false;
}

bool System::login(const MyString& userName, const MyString& password)
{
	if (currentClient.isNotNullptr() || currentDriver.isNotNullptr())
	{
		std::cout << "Please, logout the previous user to login new one!";
		return false;
	}

	size_t clientsSize = clients.getSize();
	for (size_t i = 0; i < clientsSize; i++)
	{
		if ((*clients[i]).getUserName() == userName && (*clients[i]).getPassword() == password)
		{
			currentClient = clients[i];
			checkClientNotifications();
			return true;
		}
	}

	size_t driversSize = drivers.getSize();
	for (size_t i = 0; i < driversSize; i++)
	{
		if ((*drivers[i]).getUserName() == userName && (*drivers[i]).getPassword() == password)
		{
			currentDriver = drivers[i];
			checkDriverNotifications();
			return true;
		}

	}
	std::cout << "Incorrect username or password!" << std::endl;
	return false;

}

void System::logout()
{
	currentClient = nullptr;
	currentDriver = nullptr;
}

void System::checkClientNotifications() const
{
	size_t ordersSize = orders.getSize();
	for (size_t i = 0; i < ordersSize; i++)
	{
		if (currentClient->getUserName() == (*orders[i]).getClient().getUserName() && (*orders[i]).getAccepted() == true &&
			(*orders[i]).getFinished() == false && (*orders[i]).getCanceled() == false)
		{
			std::cout << "Your driver " << orders[i]->getDriver().getFirstName() << " " << orders[i]->getDriver().getLastName() <<
				" will arive in " << orders[i]->getMinutes() << " minutes!" << std::endl;
		}
	}
}

void System::checkDriverNotifications() const
{
	size_t ordersSize = orders.getSize();
	for (size_t i = 0; i < ordersSize; i++)
	{
		if ((*currentDriver).getUserName() == (*orders[i]).getDriver().getUserName() && (*orders[i]).getCanceled() == true)
		{
			std::cout << "Order with ID " << (*orders[i]).getID() << " was canceled!" << std::endl;
		}
	}
}
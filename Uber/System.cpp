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

void System::sortDrivers(const Address& address)
{
	size_t driversSize = drivers.getSize();
	double* distance = new double[driversSize] {};
	for (size_t i = 0; i < driversSize; i++)
	{
		distance[i] = address.getPoint().getDist((*drivers[i]).getAddress().getPoint());
	}

	for (size_t i = 0; i < driversSize - 1; i++)
	{
		int minIndex = i;
		for (size_t j = i; j < driversSize; j++)
		{
			if (distance[j] < distance[minIndex])
				minIndex = j;
		}
		if (minIndex != i)
		{
			std::swap(drivers[i], drivers[minIndex]);
			std::swap(distance[i], distance[minIndex]);
		}
	}
}

const Driver& System::findDriver(const Address& address)
{
	sortDrivers(address);
	size_t driversSize = drivers.getSize();
	if (!currentDriver.isNotNullptr())
	{
		for (size_t i = 0; i < driversSize; i++)
		{
			if ((*drivers[i]).getIsFree())
				return (*drivers[i]);
		}
		return (*drivers[0]);
	}

	size_t i = 0;
	for (i; i < driversSize; i++)
	{
		if ((*currentDriver).getUserName() == (*drivers[i]).getUserName())
			break;
	}
	if (i != driversSize - 1)
	{
		i++;
		for (i; i < driversSize; i++)
		{
			if ((*drivers[i]).getIsFree())
				return (*drivers[i]);
		}
		return (*drivers[0]);
	}
	else
		return (*drivers[0]);
}

void System::order(const Address& address, const Address& destination, unsigned int travelersCount)
{
	SharedPtr<Order> order(new Order((*currentClient), address, destination, travelersCount));
	(*order).setID(orders.getSize() + 1);
	(*order).setDriver(findDriver(address));
	orders.pushBack(order);
	std::cout << std::endl << "Order ID: " << (*order).getID() << std::endl;
}

void System::checkMessages() const
{
	size_t ordersSize = orders.getSize();
	for (size_t i = 0; i < ordersSize; i++)
	{
		if ((*currentDriver).getUserName() == (*orders[i]).getDriver().getUserName() && (*orders[i]).getAccepted() == false &&
			(*orders[i]).getCanceled() == false && (*orders[i]).getFinished() == false)
		{
			std::cout << (*orders[i]).getClient().getFirstName() << " " << (*orders[i]).getClient().getLastName() <<
				" has made an order from:" << std::endl;
			std::cout << (*orders[i]).getAddress() << std::endl;
			std::cout << "To:" << std::endl << (*orders[i]).getDestination() << std::endl;
			std::cout << "Order ID: " << (*orders[i]).getID() << std::endl;
		}
	}
}

bool System::acceptOrder(unsigned int ID, int minutes)
{
	size_t ordersSize = orders.getSize();
	for (size_t i = 0; i < ordersSize; i++)
	{
		if ((*currentDriver).getUserName() == (*orders[i]).getDriver().getUserName() && (*orders[i]).getID() == ID &&
			(*orders[i]).getCanceled() == false && (*orders[i]).getFinished() == false)
		{
			if ((*currentDriver).getIsFree())
			{
				(*orders[i]).setAccepted(true);
				(*orders[i]).setMinutes(minutes);
				(*currentDriver).setIsFree(false);
				return true;
			}
			std::cout << "You have not finished your previous order!" << std::endl;
			return true;
		}

	}
	std::cout << "You do not have an order with this ID!";
	return false;
}

bool System::declineOrder(unsigned int ID)
{
	size_t ordersSize = orders.getSize();
	for (size_t i = 0; i < ordersSize; i++)
	{
		if ((*currentDriver).getUserName() == (*orders[i]).getDriver().getUserName() && (*orders[i]).getID() == ID &&
			(*orders[i]).getCanceled() == false && (*orders[i]).getFinished() == false)
		{
			(*orders[i]).setAccepted(false);
			(*orders[i]).setDriver(findDriver((*orders[i]).getAddress()));
			return true;
		}

	}
	std::cout << "You do not have an order with this ID!" << std::endl;
	return false;
}

void System::changeAddress(const Address& address)
{
	currentDriver->setAddress(address);
}

bool System::finishOrder(unsigned int ID)
{
	size_t ordersSize = orders.getSize();
	for (size_t i = 0; i < ordersSize; i++)
	{
		if ((*currentDriver).getUserName() == (*orders[i]).getDriver().getUserName() && (*orders[i]).getID() == ID &&
			(*orders[i]).getAccepted() == true)
		{
			(*orders[i]).setFinished(true);
			changeAddress(orders[i]->getDestination());
			(*currentDriver).setIsFree(true);
			return true;
		}

	}
	std::cout << "You do not have an order with this ID!" << std::endl;
	return false;
}
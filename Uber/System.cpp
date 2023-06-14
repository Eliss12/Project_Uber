#include "System.h"
#include <fstream>
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
		std::cout << "Your registration was successful!" << std::endl;
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
		std::cout << "Your registration was successful!" << std::endl;
		return true;
	}
	
	std::cout << "Please, enter new username because there is already a user with this username!" << std::endl;
	return false;
}

bool System::login(const MyString& userName, const MyString& password)
{
	if (currentClient.isNotNullptr() || currentDriver.isNotNullptr())
	{
		std::cout << "Please, logout the previous user to login new one!" << std::endl;
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
	std::cout << "You do not have an order with this ID!" << std::endl;
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

bool System::cancelOrder(unsigned int ID)
{
	size_t ordersSize = orders.getSize();
	for (size_t i = 0; i < ordersSize; i++)
	{
		if ((*currentClient).getUserName() == (*orders[i]).getClient().getUserName() && (*orders[i]).getID() == ID &&
			(*orders[i]).getFinished() == false)
		{
			(*orders[i]).setCanceled(true);
			return true;
		}

	}
	std::cout << "You do not have an order with this ID!" << std::endl;
	return false;
}

void System::checkOrder(unsigned int ID) const
{
	size_t ordersSize = orders.getSize();
	for (size_t i = 0; i < ordersSize; i++)
	{
		if ((*currentClient).getUserName() == (*orders[i]).getClient().getUserName() &&
			(*orders[i]).getID() == ID && (*orders[i]).getAccepted())
		{
			if ((*orders[i]).getFinished())
			{
				std::cout << "This order is finished!" << std::endl;
				return;
			}
			else if ((*orders[i]).getCanceled())
			{
				std::cout << "This order is canceled!" << std::endl;
				return;
			}
			std::cout << "Driver: " << (*orders[i]).getDriver().getFirstName() << " " << (*orders[i]).getDriver().getLastName();
			std::cout << std::endl << "Car number: " << (*orders[i]).getDriver().getCarNumber();
			std::cout << std::endl << "Phone number: " << (*orders[i]).getDriver().getPhoneNumber();
			std::cout << std::endl << "Rating: " << (*orders[i]).getDriver().myRating.getRating() << std::endl;
			return;
		}
		else if ((*currentClient).getUserName() == (*orders[i]).getClient().getUserName() &&
			(*orders[i]).getID() == ID && !(*orders[i]).getAccepted())
		{
			std::cout << "Your order is in process!" << std::endl;
			return;
		}
	}
	std::cout << "You do not have an order with this ID!" << std::endl;
}

void System::addMoney(double amount)
{
	(*currentClient).setAccount((*currentClient).getAccount() + amount);
}

bool System::pay(unsigned int ID, double amount)
{
	size_t ordersSize = orders.getSize();
	for (size_t i = 0; i < ordersSize; i++)
	{
		if (orders[i]->getID() == ID && orders[i]->getClient().getUserName() == currentClient->getUserName() &&
			orders[i]->getFinished() == true && !orders[i]->getIsPaid())
		{
			if (currentClient->getAccount() - amount <= EPSILON)
			{
				std::cout << "You do not have enough money in your bank account!" << std::endl;
				return false;
			}

			orders[i]->setMoneyToBePaid(amount);
			orders[i]->setIsPaid(true);
			currentClient->setAccount(currentClient->getAccount() - amount);
			return true;
		}
	}
	std::cout << "You are not allowed to pay the order with this ID!" << std::endl;
	return false;
}

bool System::acceptPayment(unsigned int ID)
{
	size_t ordersSize = orders.getSize();
	for (size_t i = 0; i < ordersSize; i++)
	{

		if (orders[i]->getID() == ID && orders[i]->getDriver().getUserName() == currentDriver->getUserName() &&
			orders[i]->getFinished() == true && orders[i]->getIsPaid())
		{
			currentDriver->setAccount(orders[i]->getMoneyToBePaid());
			std::cout << "You successfully added " << orders[i]->getMoneyToBePaid() << " leva to your bank account!" << std::endl;
			return true;
		}
	}
	std::cout << "You are not allowed to accept payment from order with this ID!" << std::endl;
	return false;
}

bool System::rate(const MyString& driverName, short rating)
{
	size_t ordersSize = orders.getSize();
	for (size_t i = 0; i < ordersSize; i++)
	{
		if (currentClient->getUserName() == orders[i]->getClient().getUserName() &&
			orders[i]->getDriver().getUserName() == driverName && orders[i]->getFinished())
		{
			findDriver(driverName, rating);
			return true;
		}

	}
	std::cout << "You are not allowed to rate this driver!" << std::endl;
	return false;
}

void System::findDriver(const MyString& driverName, short rating)
{
	size_t driversSize = drivers.getSize();
	for (size_t i = 0; i < driversSize; i++)
	{
		if ((*drivers[i]).getUserName() == driverName)
			(*drivers[i]).myRating.addRating(rating);
	}
}

bool System::readClients(const char* fileName)
{
	std::ifstream ifs(fileName);
	if (!ifs.is_open())
		return false;
	
	size_t size = 0;
	ifs >> size;
	ifs.ignore();
	Client myClient;

	for (size_t i = 0; i < size; i++)
	{
		ifs >> myClient;
		clients.pushBack(SharedPtr<Client>(new Client(myClient)));
		ifs.ignore();
	}
	
	ifs.close();
	return true;
}

bool System::readDrivers(const char* fileName)
{
	std::ifstream ifs(fileName);
	if (!ifs.is_open())
		return false;

	size_t size = 0;
	ifs >> size;
	ifs.ignore();
	Driver myDriver;

	for (size_t i = 0; i < size; i++)
	{
		ifs >> myDriver;
		drivers.pushBack(SharedPtr<Driver>(new Driver(myDriver)));
		ifs.ignore();
	}

	ifs.close();
	return true;
}

bool System::readOrders(const char* fileName)
{
	std::ifstream ifs(fileName);
	if (!ifs.is_open())
		return false;

	size_t size = 0;
	ifs >> size;
	ifs.ignore();
	Order myOrder;

	for (size_t i = 0; i < size; i++)
	{
		ifs >> myOrder;
		orders.pushBack(SharedPtr<Order>(new Order(myOrder)));
		ifs.ignore();
	}

	ifs.close();
	return true;
}

bool System::writeClients(const char* fileName)
{
	std::ofstream ofs(fileName);
	if (!ofs.is_open())
		return false;

	size_t size = clients.getSize();
	ofs << size << std::endl;
	for (size_t i = 0; i < size; i++)
	{
		ofs << (*clients[i]) << std::endl;
	}

	ofs.close();
	return true;
}

bool System::writeDrivers(const char* fileName)
{
	std::ofstream ofs(fileName);
	if (!ofs.is_open())
		return false;

	size_t size = drivers.getSize();
	ofs << size << std::endl;
	double sum = 0;

	for (size_t i = 0; i < size; i++)
	{
		ofs << (*drivers[i]) << std::endl;
		sum += drivers[i]->getAccount();
	}
	ofs << "Company profit: " << sum;
	ofs.close();
	return true;
}

bool System::writeOrders(const char* fileName)
{
	std::ofstream ofs(fileName);
	if (!ofs.is_open())
		return false;

	size_t size = orders.getSize();
	ofs << size << std::endl;


	for (size_t i = 0; i < size; i++)
	{
		ofs << (*orders[i]) << std::endl;
	}

	ofs.close();
	return true;
}
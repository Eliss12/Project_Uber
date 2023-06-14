#include "Engine.h"
const int DATA_SIZE = 4;

bool Engine::checkNames(const MyString& name)
{
	if (name[0] < 'A' || name[0] > 'Z')
		return false;
	size_t length = name.length();
	for (size_t i = 1; i < length; i++)
	{
		if (name[i] < 'a' || name[i] > 'z')
			return false;
	}
	return true;
}

MyString* Engine::registerUser()
{
	static MyString data[DATA_SIZE];
	for (int i = 0; i < DATA_SIZE; i++)
	{
		data[i] = "\0";
	}
	std::cout << "Username: ";
	std::cin >> data[0];
	
	std::cout << "Password: ";
	std::cin >> data[1];
	while (data[1].length() < 8)
	{
		std::cout << "Your password should be at least 8 characters!" << std::endl;
		std::cout << "Password: ";
		std::cin >> data[1];
	}

	std::cout << "First Name: ";
	std::cin >> data[2];
	while (checkNames(data[2]) == false)
	{
		std::cout << "Your name should start with capital letters and the other should be lowercase!" << std::endl;
		std::cout << "First Name: ";
		std::cin >> data[2];
	}

	std::cout << "Last Name: ";
	std::cin >> data[3];
	while (checkNames(data[3]) == false)
	{
		std::cout << "Your name should start with capital letters and the other should be lowercase!" << std::endl;
		std::cout << "Last Name: ";
		std::cin >> data[3];
	}
	return data;
}

void Engine::printOptions()
{
	std::cout << "If you are a client by pressing letters (a-f) you can: " << std::endl;
	std::cout << "a. Order by entering current address, destination and number of passengers." << std::endl;
	std::cout << "b. Check your order by its ID." << std::endl;
	std::cout << "c. Cancel an order by its ID." << std::endl;
	std::cout << "d. Pay for an order by its ID and amount of money." << std::endl;
	std::cout << "e. Rate a driver by his user name and rating." << std::endl;
	std::cout << "f. Add money to your bank account by entering amount of money." << std::endl << std::endl;

	std::cout << "If you are a driver by pressing letters (g-l) you can: " << std::endl;
	std::cout << "g. Change address by entering address." << std::endl;
	std::cout << "h. Check messages." << std::endl;
	std::cout << "i. Accept an order by entering order's ID and minutes to take the client." << std::endl;
	std::cout << "j. Decline an order by its ID." << std::endl;
	std::cout << "k. Finish an order by its ID." << std::endl;
	std::cout << "l. Accept payment by order's ID." << std::endl << std::endl;
	std::cout << "All users can logout by pressing \"q\"!" << std::endl;
}

Address Engine::makeAddress()
{
	std::cout << "If you do not have any additional information, please write \"nothing\"!" << std::endl;
	MyString addressName;
	std::cout << "Address name: ";
	std::cin >> addressName;
	double x, y;
	std::cout << "Coordinates: ";
	std::cin >> x >> y;
	Address::Point point(x, y);
	
	std::cout << "Additional information: ";
	char buff[1024];
	std::cin.ignore();
	std::cin.getline(buff, 1024);
	MyString addInf(buff);
	if (addInf == "nothing")
		addInf = "";
	Address address(point, addressName, addInf);
	return address;
}

unsigned int Engine::returnID()
{
	unsigned int ID;
	std::cout << "ID: ";
	std::cin >> ID;
	return ID;
}

void Engine::makeOrder(System& mySystem)
{
	std::cout << "Enter current address information: " << std::endl;
	Address current = makeAddress();
	std::cout << "Enter destination information: " << std::endl;
	Address destination = makeAddress();
	unsigned int passCount = 0;
	std::cout << "Passengers: ";
	std::cin >> passCount;
	mySystem.order(current, destination, passCount);
}

void Engine::clientOptions(System& mySystem, char option)
{
	if (option == 'a')
	{
		makeOrder(mySystem);
	}
	else if (option == 'b')
	{
		unsigned int ID = returnID();
		mySystem.checkOrder(ID);
	}
	else if (option == 'c')
	{
		unsigned int ID = returnID();
		mySystem.cancelOrder(ID);
	}
	else if (option == 'd')
	{
		unsigned int ID = returnID();
		double amount;
		std::cout << "Amount: ";
		std::cin >> amount;
		mySystem.pay(ID, amount);
	}
	else if (option == 'e')
	{
		MyString name;
		std::cout << "Driver's name: ";
		std::cin >> name;
		short rating;
		std::cout << "Rating: ";
		std::cin >> rating;
		mySystem.rate(name, rating);
	}
	else if (option == 'f')
	{
		double amount;
		std::cout << "Amount: ";
		std::cin >> amount;
		mySystem.addMoney(amount);
	}
}

void Engine::driverOptions(System& mySystem, char option)
{
	if (option == 'g')
	{
		std::cout << "Enter new address information: " << std::endl;
		Address address = makeAddress();
		mySystem.changeAddress(address);
	}
	else if (option == 'h')
	{
		mySystem.checkMessages();
	}
	else if (option == 'i')
	{
		unsigned int ID = returnID();
		int minutes = 0;
		std::cout << "Minutes: ";
		std::cin >> minutes;
		mySystem.acceptOrder(ID, minutes);
	}
	else if (option == 'j')
	{
		unsigned int ID = returnID();
		mySystem.declineOrder(ID);
	}
	else if (option == 'k')
	{
		unsigned int ID = returnID();
		mySystem.finishOrder(ID);
	}
	else if (option == 'l')
	{
		unsigned int ID = returnID();
		mySystem.acceptPayment(ID);
	}
}

void Engine::actionsAfterLogIn(System& mySystem)
{
	char option;
	while (true)
	{
		printOptions();
		std::cin >> option;
		
		if (option >= 'a' && option <= 'f')
		{
			clientOptions(mySystem, option);
		}
		else if (option >= 'g' && option <= 'l')
		{
			driverOptions(mySystem, option);
		}
		else if (option == 'q')
		{
			mySystem.logout();
			break;
		}
		else
		{
			std::cout << "Invalid letter!" << std::endl;
			continue;
		}

	}
}

void Engine::readFiles(System& mySystem)
{
	mySystem.readClients("myClients.txt");
	mySystem.readDrivers("myDrivers.txt");
	mySystem.readOrders("myOrders.txt");
}

void Engine::writeFiles(System& mySystem)
{
	mySystem.writeClients("myClients.txt");
	mySystem.writeDrivers("myDrivers.txt");
	mySystem.writeOrders("myOrders.txt");
}

bool Engine::checkPhoneNumber(const MyString& number)
{
	size_t length = number.length();
	for (size_t i = 0; i < length; i++)
	{
		if (number[i] < '0' || number[i] > '9')
			return false;
	}
	return true;
}

void Engine::registerDriver(System& mySystem, const MyString& type)
{
	MyString* data = registerUser();
	MyString carNumber;
	std::cout << "Car Number: ";
	std::cin >> carNumber;
	MyString phoneNumber;
	std::cout << "Phone Number: ";
	std::cin >> phoneNumber;
	while (checkPhoneNumber(phoneNumber) == false)
	{
		std::cout << "Your phone number should include only numbers!" << std::endl;
		std::cout << "Phone Number: ";
		std::cin >> phoneNumber;
	}
	mySystem.registers(type, data[0], data[1], data[2], data[3], carNumber, phoneNumber);
}

void Engine::execute()
{
	System mySystem;
	readFiles(mySystem);
	MyString option = "";

	while (true)
	{
		std::cout << "Hello, press 1 or 2 to make registration or login!" << std::endl;
		std::cout << "If you want to close the app, enter \"c\"!" << std::endl;
		std::cin >> option;
		if (option == "1")
		{
			MyString type;
			std::cout << "Type: ";
			std::cin >> type;

			if (type == "client")
			{
				MyString* data = registerUser();
				mySystem.registers(type, data[0], data[1], data[2], data[3]);
			}
			else if (type == "driver")
			{
				registerDriver(mySystem, type);
			}
			else
				std::cout << "Invalid type!";
		}
		else if (option == "2")
		{
			MyString userName;
			std::cout << "Username: ";
			std::cin >> userName;
			MyString password;
			std::cout << "Password: ";
			std::cin >> password;
			bool check = mySystem.login(userName, password);
			if (check == 1)
			{
				actionsAfterLogIn(mySystem);
			}
		}
		else if (option == "c")
		{
			writeFiles(mySystem);
			break;
		}
	}
}
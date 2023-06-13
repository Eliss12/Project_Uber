#include "Driver.h"

Driver::Driver():User()
{
	_carNumber = "";
	_phoneNumber = "";
}

Driver::Driver(const MyString& type, const MyString& userName, const MyString& password,
	const MyString& firstName, const MyString& lastName, const MyString& carNumber,
	const MyString& phoneNumber) :User(type, userName, password, firstName, lastName)
{
	setCarNumber(carNumber);
	setPhoneNumber(phoneNumber);
	_myAddress._point;
}

void Driver::setCarNumber(const MyString& carNumber)
{
	_carNumber = carNumber;
}

void Driver::setPhoneNumber(const MyString& phoneNumber)
{
	_phoneNumber = phoneNumber;
}

void Driver::setAddress(const Address& address)
{
	_myAddress = address;
}

const Address& Driver::getAddress() const
{
	return _myAddress;
}

const MyString& Driver::getCarNumber() const
{
	return _carNumber;
}

const MyString& Driver::getPhoneNumber() const
{
	return _phoneNumber;
}

void Driver::setIsFree(bool isFree)
{
	this->isFree = isFree;
}

bool Driver::getIsFree() const
{
	return isFree;
}

std::istream& operator>>(std::istream& is, Driver& driver)
{
	is >> driver._type;
	is >> driver._userName;
	is >> driver._password;
	is >> driver._firstName;
	is >> driver._lastName;
	is >> driver._account;
	is >> driver._carNumber;
	is >> driver._phoneNumber;
	is >> driver._myAddress;
	is >> driver.isFree;
	is >> driver.myRating.sum >> driver.myRating.count;

	return is;
}

std::ostream& operator<<(std::ostream& os, const Driver& driver)
{
	return os << driver.getType() << " " << driver.getUserName() << " " << driver.getPassword() << " " <<
		driver.getFirstName() << " " << driver.getLastName() << " " << driver.getAccount() << " " << 
		driver.getCarNumber() << " " << driver.getPhoneNumber() << " " << driver.getAddress() << " " <<
		driver.getIsFree() << " " << driver.myRating.sum << " " << driver.myRating.count;
}


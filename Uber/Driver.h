#pragma once
#include "User.h"
#include "Address.h"

class Driver:public User
{
	MyString _carNumber = "";
	MyString _phoneNumber = "";
	Address _myAddress;
	bool isFree = true;
	
public:
	struct Rating
	{
	public:
		unsigned long long sum = 1;
		size_t count = 1;
	public:
		
		void addRating(short rating)
		{
			sum += rating;
			count++;
		}
		double getRating() const
		{
			return (double)(sum) / (double)(count);
		}
	};
	Rating myRating;

public:
	Driver();

	Driver(const MyString& type, const MyString& userName, const MyString& password,
		const MyString& firstName, const MyString& lastName, const MyString& carNumber, const MyString& phoneNumber);
	void setCarNumber(const MyString& carNumber);
	void setPhoneNumber(const MyString& phoneNumber);
	void setAddress(const Address& address);
	void setIsFree(bool isFree);
	
	const Address& getAddress() const;
	const MyString& getCarNumber() const;
	const MyString& getPhoneNumber() const;
	bool getIsFree() const;

	friend std::istream& operator>>(std::istream& is, Driver& driver);
	
};

std::ostream& operator<<(std::ostream& os, const Driver& driver);

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
	private:
		unsigned long long sum;
		size_t count;
	public:
		Rating() :sum(1), count(1) {};
		Rating(unsigned long long sum, size_t count) :sum(sum), count(count) {};
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
	
};

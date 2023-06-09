#pragma once
#include <iostream>
#include "MyString.h"

class Address
{
	MyString _addressName = "";
	MyString _additionalInf = "";
	
public:
	struct Point
	{
		Point() :x(0), y(0) {}
		Point(double x, double y) :x(x), y(y) {}
		double x;
		double y;
		double getDist(const Point& other) const
		{
			double dx = x - other.x;
			double dy = y - other.y;

			return sqrt(dx * dx + dy * dy);
		}
	};

	Point _point;

public:
	Address() = default;
	Address(const Point& point, const MyString& addressName, const MyString& additionalInf);
	void setPoint(const Point& point);
	const Point& getPoint() const;
	void setAddressName(const MyString& addressName);
	const MyString& getAddressName() const;
	void setAdditionalInf(const MyString& additionalInf);
	const MyString& getAdditionalInf() const;
	friend std::istream& operator>>(std::istream& is, Address& address);
};
std::ostream& operator<<(std::ostream& os, const Address& address);

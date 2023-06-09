#include "Address.h"

Address::Address(const Address::Point& point, const MyString& addressName, const MyString& additionalInf)
{
	setPoint(point);
	setAddressName(addressName);
	setAdditionalInf(additionalInf);
}

void Address::setPoint(const Point& point)
{
	_point = point;
}

const Address::Point& Address::getPoint() const
{
	return _point;
}

void Address::setAddressName(const MyString& addressName)
{
	_addressName = addressName;
}

const MyString& Address::getAddressName() const
{
	return _addressName;
}

void Address::setAdditionalInf(const MyString& additionalInf)
{
	_additionalInf = additionalInf;
}

const MyString& Address::getAdditionalInf() const
{
	return _additionalInf;
}

std::istream& operator>>(std::istream& is, Address& address)
{
	is >> address._addressName;
	is >> address._point.x;
	is >> address._point.y;
	is >> address._additionalInf;

	return is;
}

std::ostream& operator<<(std::ostream& os, const Address& address)
{
	return os << address.getAddressName() << " " << address.getPoint().x << " " << address.getPoint().y << " " << address.getAdditionalInf();
}

#pragma once
#include "System.h"
#include <iostream>

class Engine
{
	MyString* registerUser();
	void printOptions();
	Address makeAddress();
	unsigned int returnID();
	void actionsAfterLogIn(System& mySystem);
	void readFiles(System& mySystem);
	void writeFiles(System& mySystem);
	void registerDriver(System& mySystem, const MyString& type);
	void makeOrder(System& mySystem);
	void clientOptions(System& mySystem, char option);
	void driverOptions(System& mySystem, char option);
	static bool checkNames(const MyString& name);
	static bool checkPhoneNumber(const MyString& number);
public:
	void execute();
};

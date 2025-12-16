#include "Customer.h"

Customer::Customer(const string& name, const string& phoneNumber, const string& email) 
	: Person(name, phoneNumber), email(email) {}

Customer::~Customer() {}

string Customer::getEmail() const
{
	return this->email;
}

void Customer::showInfo() const
{
	cout << "Customer: " << getName() <<
	", Phone: " << getPhoneNumber() << ", Email: " << email << endl;
}

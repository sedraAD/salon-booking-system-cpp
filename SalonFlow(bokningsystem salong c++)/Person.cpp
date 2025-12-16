#include "Person.h"

Person::Person(const string& name, const string& phoneNumber) : name(name), phoneNumber(phoneNumber) {}

Person::~Person() {}

string Person::getName() const
{
    return this->name;
}

string Person::getPhoneNumber() const
{
    return this->phoneNumber;
}

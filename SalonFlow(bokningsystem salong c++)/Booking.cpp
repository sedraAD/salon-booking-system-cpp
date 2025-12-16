#include "Booking.h"

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

Booking::Booking(Person* customer, Person* hairdresser, Treatment* treatment, Time* time)
	: customer(customer), hairdresser(hairdresser), treatment(treatment), time(time) {}

Booking::~Booking()
{
	delete customer;
	delete time;
}

Person* Booking::getCustomer() const
{
	return this->customer;
}

Person* Booking::getHairdresser() const
{
	return this->hairdresser;
}

Treatment* Booking::getTreatment() const
{
	return this->treatment;
}

Time* Booking::getTime() const
{
	return this->time;
}


void Booking::showInfo() const
{
	cout << "Booking information:" << endl;
	customer->showInfo();
	hairdresser->showInfo();
	treatment->showInfo();
	cout << "Time: " << time->convertTimeToString() << endl;
}

string Booking::bookingFileString() const
{
	ostringstream oss;
	oss << "Customer info: " << customer->getName() << ", "
		<< customer->getPhoneNumber() << ","
		<< (dynamic_cast<Customer*>(customer))->getEmail() << ", "
		<< "Hairdresser info: " << hairdresser->getName() << ","
		<< hairdresser->getPhoneNumber() << ","
		<< dynamic_cast<Hairdresser*>((hairdresser))->GetSpeciality() << ", "
		<< "Treatment: " << treatment->getName() << ", "
		<< "Price: " << treatment->getPrice() << ", "
		<< "Duration: " << treatment->getDuration() << ", "
		<< "Time: " << time->convertTimeToString() << endl;
	return oss.str();
}

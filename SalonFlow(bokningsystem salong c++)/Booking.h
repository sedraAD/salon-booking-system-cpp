#ifndef BOOKING_H
#define BOOKING_H

#include "Customer.h"
#include "Hairdresser.h"
#include "Treatment.h"
#include "Time.h"

class Booking {
private:
	Person* customer;
	Person* hairdresser;
	Treatment* treatment;
	Time* time;

public:
	Booking(Person* customer, Person* hairdresser, Treatment* treatment, Time* time);
	virtual ~Booking();

	Person* getCustomer() const;
	Person* getHairdresser() const;
	Treatment* getTreatment() const;
	Time* getTime() const;

	void showInfo() const;
	string bookingFileString() const;
};

#endif // !BOOKING_H

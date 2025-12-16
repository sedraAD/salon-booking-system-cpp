#ifndef SALON_H
#define SALON_H

#include <fstream>
#include <vector>
#include <string>
#include "Booking.h"

using namespace std;

class Salon {
private:
	vector<Treatment*> treatments;
	vector<Booking*> bookings;
	vector<Person*> hairdressers;

public:
	Salon();
	virtual ~Salon();

	void addTreatment(Treatment* treatment);
	void addBooking(Booking* booking);
	void addHairDresser(Person* hairdresser);

	void removeTreatment(Treatment* treatment);
	void removeHairDresser(Person* hairdresser);

	void showAllTreatments() const;
	void showAllHairDressers() const;

	vector<Treatment*> getTreatment() const;
	vector<Booking*> getBooking() const;
	vector<Person*> getHairdresser() const;

	void saveBookingsToFile(const string& filename = "booking.txt") const;
	void loadBookingsFromFile(const string& filename = "booking.txt");

	vector <string> getAvailableTimes(const string& filename) const;
	void updateAvailableTimes(const string& filename, const string& bookedTime);

	pair<vector<string>, vector<int>> getBookingsForCustomer(const string& customerName, const string& filename = "booking.txt");
};

#endif // !SALON_H

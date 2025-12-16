#include "Salon.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Booking.h"
#include <string>

using namespace std;

Salon::Salon() {}

Salon::~Salon()
{
	for (Booking* booking : bookings) {
		if (booking) { 
			delete booking;
		}
	}
	bookings.clear();


	for (Treatment* treatment : treatments) {
		if (treatment) {
			delete treatment;
		}
	}
	treatments.clear();

	for (Person* hairdresser : hairdressers) {
		if (hairdresser) { 
			delete hairdresser;
		}
	}
	hairdressers.clear();
}


void Salon::addTreatment(Treatment* treatment)
{
	treatments.push_back(treatment);
}

void Salon::addBooking(Booking* booking)
{
	bookings.push_back(booking);
	saveBookingsToFile();
}

void Salon::addHairDresser(Person* hairdresser)
{
	hairdressers.push_back(hairdresser);
}

void Salon::removeTreatment(Treatment* treatment)
{
	auto it = find(treatments.begin(), treatments.end(), treatment);
	if (it != treatments.end()) {
		delete* it;
		treatments.erase(it);
	}
}

void Salon::removeHairDresser(Person* hairdresser)
{
	auto it = find(hairdressers.begin(), hairdressers.end(), hairdresser);
	if (it != hairdressers.end()) {
		delete* it;
		hairdressers.erase(it);
	}
}

vector<Treatment*> Salon::getTreatment() const
{
	return this->treatments;
}

vector<Booking*> Salon::getBooking() const
{
	return this->bookings;
}

vector<Person*> Salon::getHairdresser() const
{
	return this->hairdressers;
}

void Salon::showAllTreatments() const
{
	for (const auto& treatment : treatments) {
		treatment->showInfo();
	}
}

void Salon::showAllHairDressers() const
{
	for (const auto& hairdresser : hairdressers) {
		hairdresser->showInfo();
	}
}

void Salon::saveBookingsToFile(const string& filename) const
{
	ofstream file(filename);
	if (file.is_open()) {
		for (const auto& booking : bookings) {
			file << booking->bookingFileString() << endl;
		}
		file.close();
	}
	else {
		throw runtime_error("Failed to open file for saving.");
	}
}

void Salon::loadBookingsFromFile(const string& filename)
{
	ifstream file(filename);
	if (!file.is_open()) {
		throw runtime_error("Failed to open file for loading");
	}
	string line;
	int index = 0;
	cout << "All booking from file: " << endl;
	while (getline(file, line)) {
		cout << index << ". " << line << endl;
		index++;
	}
	file.close();
}

vector<string> Salon::getAvailableTimes(const string& filename) const
{
	vector<string> times;

	ifstream file(filename);
	if (!file.is_open()) {
		cerr << "Cannot open the file" << filename << endl;
		return times;
	}
	string time;
	while (getline(file, time)) {
		times.push_back(time);
	}
	file.close();
	return times;
}

void Salon::updateAvailableTimes(const string& filename, const string& bookedTime)
{
	vector<string> times = getAvailableTimes(filename);
	ofstream file(filename);
	if (!file.is_open()) {
		cout << "Cannot open the file" << filename << endl;
		return;
	}
	for (const string& time : times) {
		if (time != bookedTime) {
			file << time << endl;
		}
	}
	file.close();
}

pair<vector<string>, vector<int>> Salon::getBookingsForCustomer(const string& customerName, const string& filename)
{
	ifstream file(filename);
	if (!file) {
		throw runtime_error("Error: Could not open bookings file.");
	}

	vector<string> allBookings;
	vector<int> customerBookingIndexes;
	string line;
	int lineIndex = 0;

	while (getline(file, line)) {
		allBookings.push_back(line);

		if (line.find(customerName) != string::npos) {
			customerBookingIndexes.push_back(lineIndex);
		}
		lineIndex++;
	}
	file.close();

	return  { allBookings, customerBookingIndexes };
}

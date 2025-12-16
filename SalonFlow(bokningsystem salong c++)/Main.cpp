#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <cctype>g
#include "Customer.h"
#include "Hairdresser.h"
#include "Treatment.h"
#include "Time.h"
#include "Booking.h"
#include "Salon.h"

using namespace std;

void printMenu(); 
Person* getCustomerInfo();
Treatment* selectTreatment(Salon& salon);
Person* selectHairdresser(map<Person*, string>& hairdresserFiles, Treatment* chosenTreatment);
Time* selectTime(Salon& salon, const string& hairDresserFile);
void bookTreatment(Salon& salon, map<Person*, string>& hairdresserFiles);
void createAndSaveBooking(Salon& salon, Person* customer, Person* hairdresser, Treatment* treatment, Time* time);
void cancelBooking(Salon& salon);
void showBookingsCustomer(Salon& salon);

int main() {
    Salon salon;

    Person* hairdresser1 = new Hairdresser("Sedra", "070428446", "Massage");
    Person* hairdresser2 = new Hairdresser("Tala", "0736434423", "Haircut");
    Person* hairdresser3 = new Hairdresser("Lisa", "0713423131", "Nails");

    Treatment* treatment1 = new Treatment("Massage", 500, 60);
    Treatment* treatment2 = new Treatment("Haircut", 300, 60);
    Treatment* treatment3 = new Treatment("Nails", 400, 30);

    salon.addHairDresser(hairdresser1);
    salon.addHairDresser(hairdresser2);
    salon.addHairDresser(hairdresser3);

    salon.addTreatment(treatment1);
    salon.addTreatment(treatment2);
    salon.addTreatment(treatment3);

    cout << "Welcome to our salon booking system!" << endl;

    map<Person*, string> hairdresserFiles = {
        {hairdresser1, "hairDresser1_times.txt"},
        {hairdresser2, "hairDresser2_times.txt"},
        {hairdresser3, "hairDresser3_times.txt"}
    };

    while (true) {
        int choice;
        cout << endl << "Please enter choice: " << endl << endl;
        printMenu();
        cin >> choice;

        if (choice == 0) {
            cout << "Thank you for using the salon booking system. Goodbye!" << endl;
            break;
        }

        switch (choice) {
        case 1: {
            bookTreatment(salon, hairdresserFiles);
            break;
        }
        case 2: {
            cancelBooking(salon);
            break;
        }
        case 3: {
            showBookingsCustomer(salon);
            break;
        }
        case 4: {
            cout << "Available treatments: " << endl;
            salon.showAllTreatments();
            break;
        }
        case 5: {
            cout << "All our hairdressers: " << endl;
            salon.showAllHairDressers();
            break;
        }
        case 6: {
            salon.loadBookingsFromFile();
            break;
        }
        default: {
            cout << "Invalid choice, please try again." << endl;
            break;
        }
        }
    }

    return 0;
}
 

void printMenu()
{
    cout << "1. Book a treatement." << endl;
    cout << "2. Cancel a booking." << endl;
    cout << "3. Show all bookings for customer." << endl;
    cout << "4. Show all treatments." << endl;
    cout << "5. Show our hairdressers." << endl;
    cout << "6. Show all bookings (for salon workers)." << endl;
    cout << "0. Exit." << endl;
}

Person* getCustomerInfo() {
    string name, phone, email, choiceTreatment;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Please enter your name: ";
    getline(cin, name);
    cout << "Please enter phone number: ";
    getline(cin, phone);
    cout << "Please enter email: ";
    getline(cin, email);
    cout << endl;

    return new Customer(name, phone, email);
}


Treatment* selectTreatment(Salon& salon) {

    cout << "Available treatments: " << endl;
    salon.showAllTreatments();

    string treatmentName;
    cout << "Choose treatment (enter treatment name): ";

    getline(cin, treatmentName);
    cout << endl;

    for (Treatment* treatment : salon.getTreatment()) {
        if (treatment->getName() == treatmentName) {
             return treatment;
        }
    }
    cout << "Treatment not found." << endl;
    return nullptr;
}


Person* selectHairdresser(map<Person*, string>& hairdresserFiles, Treatment* chosenTreatment) {
    for (auto& pair : hairdresserFiles) {
        if ((dynamic_cast<Hairdresser*>(pair.first))->GetSpeciality() == chosenTreatment->getName()) {
            pair.first->showInfo();
            return pair.first;
        }
    }
    cout << "No hairdresser available for the selected treatment." << endl;
    return nullptr;
}

Time* selectTime(Salon& salon, const string& hairDresserFile) {
    vector<string> availableTimes = salon.getAvailableTimes(hairDresserFile);

    if (availableTimes.empty()) {
        cout << "No available times for this treatment and hairdresser." << endl;
        return nullptr;
    }

    cout << "Available times: " << endl;
    for (size_t i = 0; i < availableTimes.size(); i++) {
        cout << i + 1 << ". " << availableTimes[i] << endl;
    }

    int choiceTime;
    cout << "Choose a time (enter the number): ";
    cin >> choiceTime;

    if (choiceTime < 1 || choiceTime > availableTimes.size()) {
        cout << "Invalid choice, try again: ";
        return nullptr;
    }
    cout << endl;

    string chosenTimeStr = availableTimes[choiceTime - 1];
    cout << "You have chosen time: " << chosenTimeStr << endl;

    salon.updateAvailableTimes(hairDresserFile, chosenTimeStr);

    try {
        return Time::createTimeFromString(chosenTimeStr);
    }
    catch (const invalid_argument& e) {
        cout << e.what() << endl;
        return nullptr;
    }
}


void createAndSaveBooking(Salon& salon, Person* customer, Person* hairdresser, Treatment* treatment, Time* time) {

    Booking* booking1 = new Booking(customer, hairdresser, treatment, time);
    salon.addBooking(booking1);
    cout << endl;
    booking1->showInfo();
    cout << endl;

    try {
        salon.saveBookingsToFile();
        cout << "Bookings saved to file." << endl;
    }
    catch (const runtime_error& e) {
        cout << "Error saving bookings to file: " << e.what() << endl;
    }
}


void bookTreatment(Salon& salon, map<Person*, string>& hairdresserFiles) {
    Person* customer = getCustomerInfo();
    if (!customer) {
        cout << "Error collecting customer information. Returning to menu" << endl;
        return;
    }
    Treatment* chosenTreatment = selectTreatment(salon);
    if (!chosenTreatment) {
        cout << "Inavlid treatment choice. Returning to menu" << endl;
        delete customer;
        return;
    }
    Person* selectedHairdresser = selectHairdresser(hairdresserFiles, chosenTreatment);
    if (!selectedHairdresser) {
        cout << "Invalid hairdresserchoice. Returning to menu." << endl;
        delete customer;
        return;
    }

    Time* selectedTime = selectTime(salon, hairdresserFiles[selectedHairdresser]);
    if (!selectedTime) {
        cout << "Invalid or unavailable time. Returning to main menu." << endl;
        delete customer;
        return;
    }
    createAndSaveBooking(salon, customer, selectedHairdresser, chosenTreatment, selectedTime);
    cout << "Booking completed successfully. Thank you!" << endl;
}

void cancelBooking(Salon& salon)
{
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string customerName;
    cout << "Enter the customer's name for whom you want to cancel the booking: ";
    getline(cin, customerName);

    vector<string> allBookings;
    vector<int> customerBookingIndexes;

    try {
        tie(allBookings, customerBookingIndexes) = salon.getBookingsForCustomer(customerName);

        if (customerBookingIndexes.empty()) {
            cout << "No bookings found for the name: " << customerName << endl;
            return;
        }

        cout << "Here are your bookings:" << endl;
        for (size_t i = 0; i < customerBookingIndexes.size(); i++) {
            cout << i + 1 << ". " << allBookings[customerBookingIndexes[i]] << endl;
        }

        int bookingChoice;
        cout << endl << "Choose a booking to cancel (enter number): ";
        cin >> bookingChoice;

        if (bookingChoice < 1 || bookingChoice>customerBookingIndexes.size()) {
            cout << "Invalid choice. Returning to main menu." << endl;
            return;
        }

        cout << "You have chosen to cancel the following booking:" << endl;
        cout << endl << allBookings[customerBookingIndexes[bookingChoice - 1]] << endl;
        cout << endl << "Are you sure? (y/n): ";
        char confirmation;
        cin >> confirmation;

        if (confirmation == 'y' || confirmation == 'Y') {
            allBookings.erase(allBookings.begin() + bookingChoice - 1);

            ofstream outFile("booking.txt");
            if (!outFile) {
                cout << "Error: Could not open bookings file for writing." << endl;
                return;
            }

            for (const string& bookingLine : allBookings) {
                outFile << bookingLine << endl;
            }
            outFile.close();

            cout << endl << "Booking successfully canceled and removed from file." << endl << endl;
        }
        else {
            cout << "Cancellation aborted. Returning to main menu." << endl;
        }
    }
    catch (const runtime_error& e) {
        cout << e.what() << endl;
    }
}

void showBookingsCustomer(Salon& salon)
{
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string customerName;
    cout << "Enter the customer's name for whom you want see all bookings: ";
    cin >> customerName;
    cout << endl;

    vector<string> allBookings;
    vector<int> customerBookingIndexes;

    try {
        tie(allBookings, customerBookingIndexes) = salon.getBookingsForCustomer(customerName);

        if (customerBookingIndexes.empty()) {
            cout << "No bookings found for the name: " << customerName << endl;
            return;
        }

        cout << "Here are your bookings:" << endl;
        for (size_t i = 0; i < customerBookingIndexes.size(); i++) {
            cout << i + 1 << ". " << allBookings[customerBookingIndexes[i]] << endl;
        }
    }
    catch (const runtime_error& e) {
        cout << e.what() << endl;
    }
}

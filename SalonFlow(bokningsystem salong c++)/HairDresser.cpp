#include "HairDresser.h"
#include <iostream>

using namespace std;

Hairdresser::Hairdresser(const string& name, const string& phoneNumber, const string& speciality)
    : Person(name, phoneNumber), speciality(speciality) {}

Hairdresser::~Hairdresser() {}

string Hairdresser::GetSpeciality() const
{
    return this->speciality;
}

void Hairdresser::setSpeciality(const string& speciality)
{
    this->speciality = speciality;
}

void Hairdresser::showInfo() const
{
    cout << "Hairdresser: " << getName() << ", Phone: " << getPhoneNumber()
    << ", Speciality: " << speciality << endl;
}

#ifndef HAIRDRESSER_H
#define HAIRDRESSER_H

#include "Person.h"

using namespace std;

class Hairdresser : public Person {
private:
	string speciality;

public:
	Hairdresser(const string& name, const string& phoneNumber, const string& speciality);
	virtual ~Hairdresser();

	string GetSpeciality() const;
	void setSpeciality(const string& speciality);

	void showInfo() const override;
};

#endif // !HAIRDRESSER_H

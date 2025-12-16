#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>

using namespace std;

class Person {
private:
	string name;
	string phoneNumber;

public:
	Person(const string& name, const string& phoneNumber);
	virtual ~Person();

	virtual void showInfo() const = 0;

	string getName() const;
	string getPhoneNumber() const;
};

#endif // !PERSON_H

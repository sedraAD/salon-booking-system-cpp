#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "Person.h"

using namespace std;

class Customer : public Person {
private:
	string email;

public:
	Customer(const string& name, const string& phoneNumber, const string& email);
	virtual ~Customer();

	string getEmail() const;

	void showInfo() const override;
};

#endif // !CUSTOMER_H
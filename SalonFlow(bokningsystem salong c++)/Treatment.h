#ifndef TREATMENT_H
#define TREATMENT_H

#include <string>

using namespace std;

class Treatment {
private:
	string name;
	double price;
	int duration;

public:
	Treatment(const string& name, double price, int duration);
	virtual ~Treatment();

	string getName() const;
	void setName(const string& name);

	double getPrice() const;
	void setPrice(double price);

	int getDuration() const;
	void setDuration(int duration);

	void showInfo() const;
};

#endif // !TREATMENT_H

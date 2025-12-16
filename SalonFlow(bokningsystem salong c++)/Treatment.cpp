#include "Treatment.h"
#include <iostream>

using namespace std;

Treatment::Treatment(const string& name, double price, int duration)
	: name(name), price(price), duration(duration) {}

Treatment::~Treatment() {}

string Treatment::getName() const
{
	return this->name;
}

void Treatment::setName(const string& name)
{
	this->name = name;
}

double Treatment::getPrice() const
{
	return this->price;
}

void Treatment::setPrice(double price)
{
	this->price = price;
}

int Treatment::getDuration() const
{
	return this->duration;
}

void Treatment::setDuration(int duration)
{
	this->duration = duration;
}

void Treatment::showInfo() const
{
	cout << "Treatment: " << name
		<< ", Price: " << price << " SEK"
		<< ", Duration: " << duration << " minutes"
		<< endl;
}

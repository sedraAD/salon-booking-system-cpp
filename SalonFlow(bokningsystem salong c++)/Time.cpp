#include "Time.h"

using namespace std;

Time::Time(int hour, int minute) : hour(hour), minute(minute) {}

Time::~Time() {}

int Time::getHour() const
{
	return this->hour;
}

int Time::getMinute() const
{
	return this->minute;
}

string Time::convertTimeToString() const
{
	stringstream ss;
	ss << setfill('0') << setw(2) << hour << ":" << setw(2) << minute;
	return ss.str();
}

Time* Time::createTimeFromString(const string& timeStr)
{
	int hour, minute;
	char delimiter;
	istringstream timeStream(timeStr);
	timeStream >> hour >> delimiter >> minute;

	if (timeStream.fail() || delimiter != ':' || hour < 0 || hour > 23 || minute < 0 || minute > 59) {
		throw invalid_argument("Invalid time format, please try again. ");
	}
	return new Time(hour, minute);
}

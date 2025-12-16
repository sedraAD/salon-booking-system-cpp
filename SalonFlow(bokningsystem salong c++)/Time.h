#ifndef TIME_H
#define TIME_H

#include <string>
#include <iomanip>
#include <sstream>

using namespace std;

class Time {
private:
	int hour;
	int minute;

public:
	Time(int hour, int minute);
	virtual ~Time();

	int getHour() const;
	int getMinute() const;

	string convertTimeToString() const;
	static Time* createTimeFromString(const string& timeStr);
};

#endif // !TIME_H

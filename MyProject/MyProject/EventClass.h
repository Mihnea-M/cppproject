#pragma once
#include "LocationClass.h"
class EventClass
{
	string name = "";
	char date[11] = "dd.mm.yyyy";
	char time[6] = "hh:mm";
	LocationClass location;

public:

	void setName(const string name);

	void setDate(const char* date);

	void setTime(const char* time);

	void setLocation(const LocationClass &loc);

	string getName();

	char* getDate();

	char* getTime();

	int getTotalSeats();

	LocationClass *getLocation();

	EventClass(const string name, const char* date, const char* time, const LocationClass &loc);

	bool operator>(EventClass& ev2);

};

void operator<<(ostream& console, EventClass& event);

void operator>>(istream& console, EventClass& event);
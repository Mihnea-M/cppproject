#pragma once
#include "LocationClass.h"

class EventClass
{
	string name = "";
	string date = "dd.mm.yyyy";
	string time = "hh:mm";
	int durationInMinutes = 0;
	int locationId = 0;

	static constexpr char EVENTFILE[] = "events.dat";

	EventClass();
public:

	void setName(const string name);

	void setDate(const string date);

	void setTime(const string time);

	void setLocation(const int locationId);

	void setDuration(const int minutes);

	string getName();

	string getDate();

	string getTime();

	int getDuration();

	int getLocationId();

	//writes to file and returns the id of the location in the file
	int writeInfo();

	static EventClass* getEventFromId(int searchId);

	static void createEvent();

	static void printSavedEvents();

	

	EventClass(const string name,const string date, const string time, const int locationId);

};

void operator<<(ostream& console, EventClass& event);

void operator>>(istream& console, EventClass& event);
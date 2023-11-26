#pragma once
#include <iostream>
#include <string>
#include <string.h>

using namespace std;

class LocationClass
{
	char* name=nullptr;
	int noZones=0;
	string* zoneNames = nullptr;
	int* zoneNoSeats = nullptr;
	double lat = 0, lon = 0;

	static const int MIN_NAME_SIZE = 3;
	static const int MAX_NAME_SIZE = 35;
	static const int MIN_ZONE = 1;

public:
	void setName(const char* name);

	void setZones(const int noZones, const string* zoneNames, const int* zoneNoSeats);

	void addZoze(const string zoneName, const int zoneNoSeat);

	void addressToCoord(const string address);

	string generateLink();


	char* getName();

	int getNoZones();

	string* getZoneNames();

	int* getNoSeats();

	

	LocationClass();

	LocationClass(const char* name, const int noZones, const string* zoneNames, const int* zoneNoSeats, const string address);

	~LocationClass();

	LocationClass(const LocationClass& source);

	void operator= (const LocationClass& source);

	int operator[](int index);

	explicit operator int();
};

void operator<<(ostream& console, LocationClass& loc);

void operator>>(istream& console, LocationClass& loc);
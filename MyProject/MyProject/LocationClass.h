#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <string.h>

#include "LocationLayout.h"
#include "APICall.h"

using namespace std;

class LocationClass
{

	char* name=nullptr;
	int noZones=0;
	ZoneClass** zones = nullptr;
	Coordinates coords;


	static const int MIN_NAME_SIZE = 3;
	static const int MAX_NAME_SIZE = 35;
	static const int MIN_ZONE = 1;
	static constexpr char LOCFILE[] = "locations.dat";
public:
	LocationClass();

public:
	void setName(const char* name);

	void setZones(int noZones, ZoneClass** zones);

	void addZone(const ZoneClass& zone);

	void setCoord(const string address);

	string generateLink();

	char* getName();

	int getNoZones();

	int getNoOfSeatsOfZone(int zoneNo);

	int getTotalNoOfSeats();

	static LocationClass* getLocationFromId(int searchId);

	static void printSavedLocations();

	static int getNoOfSavedLocs();

	//writes to file and returns the id of the location in the file
	int writeInfo();

private:
	void checkAvailability();

public:

	LocationClass(const char* name, const int noZones, ZoneClass** zones, const string address);

	~LocationClass();

	LocationClass(const LocationClass& source);

	void operator= (const LocationClass& source);

	bool operator== (const LocationClass& loc);
};

void operator<<(ostream& console, LocationClass& loc);

void operator>>(istream& console, LocationClass& loc);
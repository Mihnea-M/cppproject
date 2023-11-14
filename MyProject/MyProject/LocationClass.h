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

	static const int MIN_NAME_SIZE = 7;
	static const int MAX_NAME_SIZE = 35;
	static const int MIN_ZONE = 1;

	void setName(char* name);

	void setZones(int noZones, string* zoneNames, int* zoneNoSeats);

	void addZoze(string zoneName, int zoneNoSeat);
public:
	void addressToCoord(string address);

	void generateAndPrintLink();

	LocationClass();

	LocationClass(char* name, int noZones, string* zoneNames, int* zoneNoSeats, string address);

	~LocationClass();

	LocationClass(const LocationClass* source);
};


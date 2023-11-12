#include "LocationClass.h"

void LocationClass::setName(char* name)
{
	int lenght = strlen(name) + 1;
	if (lenght<LocationClass::MIN_NAME_SIZE || lenght > LocationClass::MAX_NAME_SIZE)
		throw exception("Invalid name");
	else
	{
		delete[] this->name;
		this->name = new char[lenght];
		strcpy_s(this->name, lenght, name);
	}
}

void LocationClass::setZones(int noZones, string* zoneNames, int* zoneNoSeats) 
{
	if (noZones < LocationClass::MIN_ZONE)
		throw exception("Invalid no. of zones");
	else
	{
		this->noZones = noZones;

		delete[] this->zoneNames;
		delete[] this->zoneNoSeats;

		this->zoneNames = new string[noZones];
		this->zoneNoSeats = new int[noZones];
		for (int i=0;i < noZones;i++)
			this->zoneNames[i] = zoneNames[i];
		memcpy(this->zoneNoSeats, zoneNoSeats, sizeof(int) * noZones);
	}
}

void LocationClass::addZoze(string zoneName, int zoneNoSeat) {
	string* tempNames = new string[this->noZones + 1];
	int* tempNo = new int[this->noZones + 1];
	int i;
	for (i=0;i < this->noZones;i++)
		tempNames[i] = this->zoneNames[i];
	tempNames[this->noZones] = zoneName;

	memcpy(tempNo, this->zoneNoSeats, sizeof(int) * noZones);
	tempNo[this->noZones] = zoneNoSeat;

	delete[] this->zoneNames;
	delete[] this->zoneNoSeats;

	this->noZones++;
	this->zoneNames = tempNames;
	this->zoneNoSeats = tempNo;
}

void LocationClass::addressToCoord(const string address) {
	//TODO: find smth to make an api call to the google maps geocoding api
	//until
	this->lat = 44.447961;
	this->lon = 26.099141;
}

void LocationClass::generateAndPrintLink() {
	cout << endl << "http://www.google.com/maps/place/" << this->lat << "," << this->lon << endl;
}

LocationClass::LocationClass()
{

}

LocationClass::LocationClass(char* name, int noZones, string* zoneNames, int* zoneNoSeats) {
	this->setName(name);
	this->setZones(noZones, zoneNames, zoneNoSeats);
}

LocationClass::~LocationClass() {
	delete[] this->name;
	delete[] this->zoneNames;
	delete[] this->zoneNoSeats;
}
#include "LocationClass.h"

void LocationClass::setName(const char* name)
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

void LocationClass::setZones(const int noZones, const string* zoneNames, const int* zoneNoSeats)
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

void LocationClass::addZoze(const string zoneName, const int zoneNoSeat) {
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

void LocationClass::setCoord(const string address) {
	Coordinates coord = extractCoord(apiCall(address));
	this->coords.lat = coord.lat;
	this->coords.lon = coord.lon;
}

string LocationClass::generateLink() {
	string link;
	link = "http://www.google.com/maps/place/" + to_string(this->coords.lat) + "," + to_string(this->coords.lon);
	return link;
}

char* LocationClass::getName() {
	char* name = new char[strlen(this->name) + 1];
	strcpy_s(name, strlen(this->name) + 1, this->name);
	return name;
}

int LocationClass::getNoZones() {
	return this->noZones;
}

string* LocationClass::getZoneNames() {
	string* names = new string[this->noZones];
	int i = 0;
	for (i = 0;i < this->noZones;i++)
		names[i] = this->zoneNames[i];
	return names;
}

int* LocationClass::getNoSeats() {
	int* no = new int[this->noZones];
	int i = 0;
	for (i = 0;i < this->noZones;i++)
		no[i] = this->zoneNoSeats[i];
	return no;
}


LocationClass::LocationClass()
{

}

LocationClass::LocationClass(const char* name, const int noZones, const string* zoneNames, const int* zoneNoSeats, const string address) {
	this->setName(name);
	this->setZones(noZones, zoneNames, zoneNoSeats);
	this->setCoord(address);
}

LocationClass::~LocationClass() {
	delete[] this->name;
	delete[] this->zoneNames;
	delete[] this->zoneNoSeats;
}

LocationClass::LocationClass(const LocationClass& source) {
	delete[] this->name;
	delete[] this->zoneNames;
	delete[] this->zoneNoSeats;

	this->name = new char[strlen(source.name) + 1];
	strcpy_s(this->name, strlen(source.name) + 1, source.name);

	this->noZones = source.noZones;

	this->zoneNames = new string[this->noZones];
	for (int i = 0; i < this->noZones; i++) {
		this->zoneNames[i] = source.zoneNames[i];
	}

	this->zoneNoSeats = new int[this->noZones];
	memcpy(this->zoneNoSeats, source.zoneNoSeats, sizeof(int) * this->noZones);

	this->lat = source.lat;
	this->lon = source.lon;
}

void LocationClass::operator=(const LocationClass& source) {
	if (this == &source) {
		return;
	}
	delete[] this->name;
	delete[] this->zoneNames;
	delete[] this->zoneNoSeats;

	this->name = new char[strlen(source.name) + 1];
	strcpy_s(this->name, strlen(source.name) + 1, source.name);

	this->noZones = source.noZones;

	this->zoneNames = new string[this->noZones];
	for (int i = 0; i < this->noZones; i++) {
		this->zoneNames[i] = source.zoneNames[i];
	}

	this->zoneNoSeats = new int[this->noZones];
	memcpy(this->zoneNoSeats, source.zoneNoSeats, sizeof(int) * this->noZones);

	this->lat = source.lat;
	this->lon = source.lon;
}

int LocationClass::operator[](int index) {
	if (index >= this->noZones)
	{
		throw exception("Invalid index");	
	}
	else
		return this->zoneNoSeats[index];
}

LocationClass::operator int() {
	int sum = 0;
	for (int i = 0;i < this->noZones;i++)
		sum += zoneNoSeats[i];
	return sum;
}

void operator<<(ostream& console, LocationClass& loc) {
	int noZones = loc.getNoZones();
	char* name = loc.getName();
	string* zoneNames = loc.getZoneNames();
	int* zoneNoSeats = loc.getNoSeats();
	string adresss = loc.generateLink();
	console << endl << "---------------" << endl;
	console << "Name: " << name << endl;
	console << "Number of zones: " << noZones << endl;
	for (int i = 0;i < noZones;i++) {
		console << endl << "Zone " << i + 1 << " info:" << endl;
		console << "Name-" << zoneNames[i] << endl;
		console << "Number of seats-" << zoneNoSeats[i] << endl;
	}
	console << endl << "Link to adress: " << endl << adresss;
	console << endl << "---------------" << endl;

	delete[] name;
	delete[] zoneNames;
	delete[] zoneNoSeats;
}

void operator>>(istream& console, LocationClass& loc) {
	int noZones;
	char buffer[40];

	cout << "New location name: ";
	console.getline(buffer, 40);
	console.clear();

	loc.setName(buffer);

	cout << "Number of zones: ";
	console >> noZones;

	string* zoneNames = new string[noZones];
	int* zoneNoSeats = new int[noZones];

	for (int i = 0;i < noZones;i++) {
		cout << "Zone " << i+1 << " name: ";
		console >> zoneNames[i];
		cout << "Zone " << i+1 << " no of seats: ";
		console >> zoneNoSeats[i];
	}

	loc.setZones(noZones, zoneNames, zoneNoSeats);

	delete[] zoneNames;
	delete[]  zoneNoSeats;
	cout << "Adress: ";
	console.getline(buffer,40);
	console.clear();
	loc.setCoord(buffer);

}

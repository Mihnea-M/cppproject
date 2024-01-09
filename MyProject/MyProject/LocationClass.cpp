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

void LocationClass::setZones( int noZones, ZoneClass** zones) {
	if (noZones < LocationClass::MIN_ZONE)
		throw exception("Invalid no. of zones");
	int i;

	for (i = 0;i < this->noZones;i++) {
		delete this->zones[i];
	}
	delete[] this->zones;

	this->noZones = noZones;
	this->zones = new ZoneClass * [this->noZones];
	for (i = 0;i < this->noZones;i++) {
		this->zones[i] = new ZoneClass(*zones[i]);
	}
}

void LocationClass::addZone(const ZoneClass& zone) {

	ZoneClass** newZones = new ZoneClass * [this->noZones + 1];

	for (int i = 0; i < this->noZones; ++i) {
		newZones[i] = this->zones[i];
	}
	newZones[noZones] = new ZoneClass(zone);

	delete[] zones;
	this->zones = newZones;
	this->noZones++;
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

int LocationClass::getNoOfSeatsOfZone(int zoneNo) {
	return this->zones[zoneNo - 1]->getNoSeats();
}

int LocationClass::getTotalNoOfSeats() {
	int no = 0;
	for (int i = 0;i<this->noZones;i++)
		no+= this->zones[i]->getNoSeats();
	return no;
}

LocationClass* LocationClass::getLocationFromId(int searchId) {
	ifstream file;
	file.open(LocationClass::LOCFILE, ios::in, ios::binary);
	LocationClass* location;
	int id;
	if (file.is_open()) {
		
		file.read((char*)&id, sizeof(int));
		if (id < searchId) {
			file.close();
			throw exception("Invalid search id.");
		}
		while (file.read((char*)&id, sizeof(int))) {//id
			LocationClass* location = new LocationClass;
			//size of name and name
			int size;
			file.read((char*)&size, sizeof(int));
			location->name = new char[size];
			file.read(location->name, size);

			//no of zones
			int noZones;
			file.read((char*)&noZones, sizeof(int));
			location->noZones = noZones;
			location->zones = new ZoneClass * [noZones];

			for (int i = 0;i < noZones;i++) {
				//size of zone name and name
				int zoneNameSize;
				file.read((char*)&zoneNameSize, sizeof(int));
				char* zoneName = new char[zoneNameSize];
				file.read(zoneName, zoneNameSize);

				//price
				float price;
				file.read((char*)&price, sizeof(float));

				//no of rows
				int noRows;
				file.read((char*)&noRows, sizeof(int));

				//no of seats for each row
				RowClass** rows = new RowClass * [noRows];
				for (int j = 0;j < noRows;j++) {
					int seats;
					file.read((char*)&seats, sizeof(int));
					RowClass* tempRow = new RowClass(seats);
					rows[j] = tempRow;
				}
				ZoneClass* zone = new ZoneClass(zoneName, price, noRows, rows);
				location->zones[i] = zone;
			}
			//coords
			file.read((char*)&location->coords.lon, sizeof(float));
			file.read((char*)&location->coords.lat, sizeof(float));

			if (id == searchId) {
				file.close();
				return location;
			}
			delete location;

		}
	}
	file.close();
}
//file structure
	//an integer containing total no of locations
	//Location info
	//location file id
	//size of name and name
	//no of zones
	//size of zone name and name
	//price
	//no of rows
	//no of seats for each row
	//coordinates
int LocationClass::writeInfo() {
	this->checkAvailability();
	fstream file;
	file.open(LocationClass::LOCFILE, ios::out | ios::in, ios::binary);

	int noOfLoc = 0;

	if (!file.is_open()) {
		file.open(LocationClass::LOCFILE, ios::out, ios::binary);
	}
	else {
		
		file.read((char*)&noOfLoc, sizeof(int));
	}

	noOfLoc++;
	file.seekp(0, ios::beg);
	file.write((char*)&noOfLoc, sizeof(int));
	file.seekp(0, ios::end);

	file.write((char*)&noOfLoc, sizeof(int));
	int size = strlen(name) + 1;
	file.write((char*)&size, sizeof(int));
	file.write(name, size);

	file.write((char*)&noZones, sizeof(int));

	for (int i = 0;i < noZones;i++) {
		this->zones[i]->writeToFile(file);
	}
	file.write((char*)&coords.lon, sizeof(float));
	file.write((char*)&coords.lat, sizeof(float));
	file.close();
	return noOfLoc;
}


void LocationClass::checkAvailability() {
	ifstream file;
	file.open(LocationClass::LOCFILE, ios::in, ios::binary);
	LocationClass* location;
	int id;
	if (file.is_open()) {
		file.read((char*)&id, sizeof(int));
		while (file.read((char*)&id, sizeof(int))) {//id
			LocationClass* location = new LocationClass;

			//size of name and name
			int size;
			file.read((char*)&size, sizeof(int));
			location->name = new char[size];
			file.read(location->name, size);

			//no of zones
			int noZones;
			file.read((char*)&noZones, sizeof(int));
			location->noZones = noZones;
			location->zones = new ZoneClass * [noZones];

			for (int i = 0;i < noZones;i++) {
				//size of zone name and name
				int zoneNameSize;
				file.read((char*)&zoneNameSize, sizeof(int));
				char* zoneName = new char[zoneNameSize];
				file.read(zoneName, zoneNameSize);

				//price
				float price;
				file.read((char*)&price, sizeof(float));

				//no of rows
				int noRows;
				file.read((char*)&noRows, sizeof(int));

				//no of seats for each row
				RowClass** rows = new RowClass * [noRows];
				for (int j = 0;j < noRows;j++) {
					int seats;
					file.read((char*)&seats, sizeof(int));
					RowClass* tempRow = new RowClass(seats);
					rows[j] = tempRow;
				}
				ZoneClass *zone =new ZoneClass(zoneName,price,noRows,rows);
				location->zones[i] = zone;
			}
			//coords
			file.read((char*)&location->coords.lon, sizeof(float));
			file.read((char*)&location->coords.lat, sizeof(float));

			if (*this == *location){
				delete location;
				file.close();
				throw exception("Location already in memory");
			}
			else{
				delete location;
			}

		}
	}
	
	file.close();
}

void LocationClass::printSavedLocations() {
	ifstream file;
	file.open(LocationClass::LOCFILE, ios::in, ios::binary);
	LocationClass* location = nullptr;
	int id;
	if (file.is_open()) {
		
		file.read((char*)&id, sizeof(int));
		while (file.read((char*)&id, sizeof(int))) {//id
			LocationClass* location = new LocationClass;
			
			//size of name and name
			int size;
			file.read((char*)&size, sizeof(int));
			location->name = new char[size];
			file.read(location->name, size);

			//no of zones
			int noZones;
			file.read((char*)&noZones, sizeof(int));
			location->noZones = noZones;
			location->zones = new ZoneClass * [noZones];

			for (int i = 0;i < noZones;i++) {
				//size of zone name and name
				int zoneNameSize;
				file.read((char*)&zoneNameSize, sizeof(int));
				char* zoneName = new char[zoneNameSize];
				file.read(zoneName, zoneNameSize);

				//price
				float price;
				file.read((char*)&price, sizeof(float));

				//no of rows
				int noRows;
				file.read((char*)&noRows, sizeof(int));

				//no of seats for each row
				RowClass** rows = new RowClass * [noRows];
				for (int j = 0;j < noRows;j++) {
					int seats;
					file.read((char*)&seats, sizeof(int));
					RowClass* tempRow = new RowClass(seats);
					rows[j] = tempRow;
				}
				ZoneClass* zone = new ZoneClass(zoneName, price, noRows, rows);
				location->zones[i] = zone;
			}
			//coords
			file.read((char*)&location->coords.lon, sizeof(float));
			file.read((char*)&location->coords.lat, sizeof(float));

			cout << "Location Id: " << id << endl << "Location name: " << location->name << endl
				<<"Location total no. of seats: " <<location->getTotalNoOfSeats() << endl 
				<<"Google Maps link: " << location->generateLink() << endl << endl;

			delete location;
		}
	}
}

int LocationClass::getNoOfSavedLocs() {
	ifstream file;
	file.open(LocationClass::LOCFILE, ios::in, ios::binary);
	int id = 0;
	if (file.is_open()) {
		file.read((char*)&id, sizeof(int));
		file.close();
	}
	return id;
}

LocationClass::LocationClass()
{

}

LocationClass::LocationClass(const char* name, const int noZones, ZoneClass** zones, const string address) {
	this->setName(name);
	this->setZones(noZones, zones);
	this->setCoord(address);
}

LocationClass::~LocationClass() {
	delete[] this->name;
	for (int i = 0;i < this->noZones;i++) {
		delete this->zones[i];
	}
	delete[] this->zones;
}

LocationClass::LocationClass(const LocationClass& source) {
	if (this == &source)
		return;
	delete[] this->name;
	for (int i = 0;i < this->noZones;i++) {
		delete this->zones[i];
	}
	delete[] this->zones;

	this->name = new char[strlen(source.name) + 1];
	strcpy_s(this->name, strlen(source.name) + 1, source.name);

	this->noZones = source.noZones;

	this->setZones(source.noZones, source.zones);

	this->coords.lat = source.coords.lat;
	this->coords.lon = source.coords.lon;
}

void LocationClass::operator=(const LocationClass& source) {
	if (this == &source) {
		return;
	}
	delete[] this->name;
	for (int i = 0;i < this->noZones;i++) {
		delete this->zones[i];
	}
	delete[] this->zones;

	this->name = new char[strlen(source.name) + 1];
	strcpy_s(this->name, strlen(source.name) + 1, source.name);

	this->noZones = source.noZones;

	this->setZones(source.noZones, source.zones);

	this->coords.lat = source.coords.lat;
	this->coords.lon = source.coords.lon;
}

bool LocationClass::operator== (const LocationClass& loc) {
	if (strcmp(this->name, loc.name) == 0 || (this->coords.lat == loc.coords.lat && this->coords.lat == loc.coords.lat))
		return true;
	return false;
}

void operator<<(ostream& console, LocationClass& loc) {
	cout << endl << "Location name: " << loc.getName() << endl
		<< "Location total no. of seats: " << loc.getTotalNoOfSeats() << endl
		<< "Google Maps link: " << loc.generateLink() << endl << endl;
}

void operator>>(istream& console, LocationClass& loc) {
	while (1) {
		try {
			char buffer[100];
			console.ignore();
			cout << "Location name: ";
			console.getline(buffer, 100);
			console.clear();
			loc.setName(buffer);

			int noZones;
			cout << "Number of zones: ";
			console >> noZones;
			cout << endl;
			ZoneClass** zones = new ZoneClass * [noZones];
			ZoneClass* zone;

			for (int i = 0;i < noZones; i++) {
				cout << "Zone " << i + 1 << " info:";
				zone = new ZoneClass;
				console >> *zone;
				zones[i] = zone;
			}
			cout << endl;
			loc.setZones(noZones, zones);
			console.clear();

			console.ignore();
			cout << "Address: ";
			console.getline(buffer, 100);
			console.clear();
			loc.setCoord(buffer);
			cout << endl;

			break;
		}
		catch (exception e) {
			system("cls");
			cout << e.what()<< endl;
		}
	}
}
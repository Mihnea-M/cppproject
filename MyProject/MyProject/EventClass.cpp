#include "EventClass.h"

void EventClass::setName(const string name) {
	if (name == "")
		throw exception("Invalid name");
	this->name = name;
}

void EventClass::setDate(const string date) {
	if (date.length() != 10 || date[2] != '.' || date[5] != '.')
		throw exception("Invalid date");

	int day = std::stoi(date.substr(0, 2));
	int month = std::stoi(date.substr(3, 2));
	int year = std::stoi(date.substr(6, 4));

	if (month < 1 || month > 12)
		throw exception("Invalid month");

	if (day < 1 || day > 31)
		throw exception("Invalid date");

	this->date = date;
}

void EventClass::setTime(string time) {
	if (time.length() != 5 || time[2] != ':')
		throw exception("Invalid time format");

	int hour = stoi(time.substr(0, 2));
	int minute = stoi(time.substr(3, 2));

	if (hour < 0 || hour > 23 || minute < 0 || minute > 59)
		throw exception("Invalid time value");

	this->time = time;
}

void EventClass::setLocation(const int locationId) {
	if (locationId < LocationClass::getNoOfSavedLocs())
		throw exception("Invalid Location Id");
	this->locationId = locationId;
}

void EventClass::setDuration(const int minutes) {
	if (minutes < 1)
		throw exception("Invalid duration");
	this->durationInMinutes = minutes;
}

string EventClass::getName() {
	return this->name;
}

string EventClass::getDate() {
	return this->date;
}

string EventClass::getTime() {
	return this->time;
}

int EventClass::getDuration() {
	return this->durationInMinutes;
}

int EventClass::getLocationId() {
	return this->locationId;
}

int EventClass::writeInfo() {
	fstream file;
	file.open(EventClass::EVENTFILE, ios::out | ios::in, ios::binary);

	int noOfEvents = 0;

	if (!file.is_open()) {
		file.open(EventClass::EVENTFILE, ios::out, ios::binary);
	}
	else {

		file.read((char*)&noOfEvents, sizeof(int));
	}

	noOfEvents++;
	file.seekp(0, ios::beg);
	file.write((char*)&noOfEvents, sizeof(int));
	file.seekp(0, ios::end);

	file.write((char*)&noOfEvents, sizeof(int));

	int size = name.length() + 1;
	file.write((char*)&size, sizeof(int));
	file.write(name.c_str(), size);

	file.write(date.c_str(), 11 * sizeof(char));
	file.write(time.c_str(), 6 * sizeof(char));

	file.write((char*)&durationInMinutes, sizeof(int));
	file.write((char*)&locationId, sizeof(int));
	
	file.close();
	return noOfEvents;
}

EventClass* EventClass::getEventFromId(int searchId) {
	ifstream file;
	file.open(EventClass::EVENTFILE, ios::in, ios::binary);
	EventClass* event;
	int id;
	if (file.is_open()) {

		file.read((char*)&id, sizeof(int));
		if (id < searchId) {
			file.close();
			throw exception("Invalid search id.");
		}
		while (file.read((char*)&id, sizeof(int))) {//id
			event = new EventClass;
			//size of name and name
			int size;
			file.read((char*)&size, sizeof(int));
			char* name = new char[size];
			file.read(name, size);
			event->name = name;

			char date[11];
			file.read(date, 11 * sizeof(char));
			event->date = date;

			char time[6];
			file.read(time, 6 * sizeof(char));
			event->time = time;

			int intBuf;
			file.read((char*)&intBuf, sizeof(int));
			event->durationInMinutes = intBuf;

			file.read((char*)&intBuf, sizeof(int));
			event->locationId = intBuf;

			if (id == searchId) {
				file.close();
				return event;
			}
			delete event;
		}
	}
	file.close();
}

void EventClass::createEvent() {
	EventClass event;
	cin >> event;
	event.writeInfo();
}

void EventClass::printSavedEvents() {
	ifstream file;
	file.open(EventClass::EVENTFILE, ios::in, ios::binary);
	EventClass* event;
	int id;
	if (file.is_open()) {

		file.read((char*)&id, sizeof(int));

		while (file.read((char*)&id, sizeof(int))) {//id
			event = new EventClass;
			//size of name and name
			int size;
			file.read((char*)&size, sizeof(int));
			char* name = new char[size];
			file.read(name, size);
			event->name = name;

			char date[11];
			file.read(date, 11 * sizeof(char));
			event->date = date;

			char time[6];
			file.read(time, 6 * sizeof(char));
			event->time = time;

			int intBuf;
			file.read((char*)&intBuf, sizeof(int));
			event->durationInMinutes = intBuf;

			file.read((char*)&intBuf, sizeof(int));
			event->locationId = intBuf;
			cout << endl;
			cout << "Event id: " << id;
			cout << *event;
			
			delete event;
		}
	}
	file.close();
}

EventClass::EventClass() {

}

EventClass::EventClass(const string name, string date, string time, const int locationId) {
	this->setName(name);
	this->setDate(date);
	this->setTime(time);
	this->setLocation(locationId);
}


void operator<<(ostream& console, EventClass& event) {
	console << endl << "----------------------------------" << endl;
	console << "Name of the event: " << event.getName() << endl;
	string date = event.getDate();
	string time = event.getTime();
	console << "The event will take place at " << time << " on " << date << "." << endl;
	LocationClass* location = LocationClass::getLocationFromId(event.getLocationId());
	console << *location;
	delete location;
	console << "---------------------------------" << endl;
}

void operator>>(istream& console, EventClass& event) {
	char buffer[100];
	string response;
	int intBuffer;
	while(1){
		try{
			cout << endl << "New event name: ";
			console.getline(buffer, 100);
			console.clear();
			event.setName(buffer);

			cout << endl << "Date (dd.mm.yyyy): ";
			console.getline(buffer, 100);
			console.clear();
			event.setDate(buffer);

			cout << endl << "Time (hh:mm): ";
			console.getline(buffer, 100);
			console.clear();
			event.setTime(buffer);

			cout << endl << "Duration in mintues: ";
			console >> intBuffer;
			console.clear();
			event.setDuration(intBuffer);

			if (LocationClass::getNoOfSavedLocs() != 0){
				while(1)
				{
					cout << endl << "Do you want to use a saved location or create a new one?" << endl << "Type \"view\" to view the list of existing locations"
						<< endl << "Type \"create\" to create a new location or \"saved\" to use an existing location." << endl;
					console >> response;
					if (response == "view") {
						LocationClass::printSavedLocations();
						cout << endl << "Type \"create\" to create a new location or \"saved\" to use an existing location." << endl;
						console >> response;
					}
					if (response == "saved") {
						cout << "Type the id of the event you want to use: ";
						console >> intBuffer;
						event.setLocation(intBuffer);
						break;
					}
					else if (response == "create") {
						LocationClass loc;
						console >> loc;
						event.setLocation(loc.writeInfo());
						break;
					}
					cout << "Please provide a valid input." << endl;
				}
			}
			else {
				LocationClass loc;
				console >> loc;
				event.setLocation(loc.writeInfo());
			}
			break;
		}
		catch (exception e) {
			system("cls");
			cout << e.what() << endl << endl;
		}
	}
}
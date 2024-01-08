//#include "EventClass.h"
//
//void EventClass::setName(const string name) {
//	this->name = name;
//}
//
//void EventClass::setDate(const char* date) {
//	if (strlen(date) != 10 || date[2] != '.' || date[5] != '.')
//		throw exception("Invalid date");
//	else
//		strcpy_s(this->date, 11, date);
//}
//
//void EventClass::setTime(const char* time) {
//	if (strlen(time) != 5 || time[2] != ':')
//		throw exception("Invalid date");
//	else
//		strcpy_s(this->time, 6, time);
//}
//
//void EventClass::setLocation(const LocationClass &loc) {
//	this->location = loc;
//}
//
//string EventClass::getName() {
//	return this->name;
//}
//
//char* EventClass::getDate() {
//	char* copy = new char[11];
//	strcpy_s(copy, 11, this->date);
//	return copy;
//}
//
//char* EventClass::getTime() {
//	char* copy = new char[6];
//	strcpy_s(copy, 6, this->time);
//	return copy;
//}
//
//
//LocationClass *EventClass::getLocation() {
//	LocationClass *loc = new LocationClass(this->location);
//	return loc;
//}
//
//EventClass::EventClass(const string name, const char* date, const char* time, const LocationClass &loc) {
//	this->setName(name);
//	this->setDate(date);
//	this->setTime(time);
//	this->setLocation(loc);
//}
//
//bool EventClass::operator>(EventClass& ev2) {
//	if (this->getTotalSeats() > ev2.getTotalSeats())
//		return true;
//	else
//		return false;
//}
//
//void operator<<(ostream& console, EventClass& event) {
//	console << endl << "----------------------------------" << endl;
//	console << "Name of the event: " << event.getName() << endl;
//	char* date = event.getDate();
//	char* time = event.getTime();
//	console << "The event will take place at " << time << " on " << date << "." << endl;
//	LocationClass *loc;
//	loc = event.getLocation();
//	console << *loc;
//	delete loc;
//	console << "---------------------------------" << endl;
//	delete[] date;
//	delete[] time;
//}
//
//void operator>>(istream& console, EventClass& event) {
//	char buffer[100];
//	cout << endl << "New event name: ";
//	console.getline(buffer, 100);
//	console.clear();
//	event.setName(buffer);
//	cout << endl << "New date: ";
//	console.getline(buffer, 100);
//	console.clear();
//	event.setName(buffer);
//	cout << endl << "New time: ";
//	console.getline(buffer, 100);
//	console.clear();
//	event.setName(buffer);
//	LocationClass loc;
//	console >> loc;
//	event.setLocation(loc);
//}
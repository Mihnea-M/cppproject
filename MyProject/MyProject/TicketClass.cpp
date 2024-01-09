#include "TicketClass.h"

TicketClass::TicketClass() {

}

TicketClass::TicketClass(int user, int event, int zone, int row, int seat) {
	srand(time(NULL));
	this->randIdentifier = 100 + rand() % 900;  
	this->user = user;
	this->event = event;
	this->zone = zone;
	this->row = row;
	this->seat = seat;
}

TicketClass::TicketClass(int rand, int user, int event, int zone, int row, int seat){
	this->randIdentifier = rand;
	this->user = user;
	this->event = event;
	this->zone = zone;
	this->row = row;
	this->seat = seat;
}

void TicketClass::writeInfo() {
	ofstream file(TicketClass::TICKETFILE, ios::app, ios::binary);
	file.write((char*)&this->randIdentifier, sizeof(int));
	file.write((char*)&this->user, sizeof(int));
	file.write((char*)&this->event, sizeof(int));
	file.write((char*)&this->zone, sizeof(int));
	file.write((char*)&this->row, sizeof(int));
	file.write((char*)&this->seat, sizeof(int));
	file.close();
}

string TicketClass::generateTicketId() {
	string ticketId = "";
	ticketId += to_string(this->randIdentifier);
	ticketId += to_string(this->user);
	ticketId += to_string(this->event);
	ticketId += to_string(this->zone);
	ticketId += to_string(this->row);
	ticketId += to_string(this->seat);
	return ticketId;

}

bool TicketClass::checkIfTaken(int event, int zone, int row, int seat) {
	ifstream file(TicketClass::TICKETFILE, ios::app, ios::binary);
	TicketClass fileTicket;
	while (file.read((char*)&fileTicket.randIdentifier, sizeof(int))) {
		file.read((char*)&fileTicket.user, sizeof(int));
		file.read((char*)&fileTicket.event, sizeof(int));
		file.read((char*)&fileTicket.zone, sizeof(int));
		file.read((char*)&fileTicket.row, sizeof(int));
		file.read((char*)&fileTicket.seat, sizeof(int));

		if (event == fileTicket.event && zone == fileTicket.zone && row == fileTicket.row && seat == fileTicket.seat)
			return true;
	}
	return false;
}

bool TicketClass::checkTicket(string ticket) {
	//ticket look like - rand.user.event.zone.row.seat
	int result[6];
	int find = 0;
	string temp = "";
	for (char ch : ticket) {
		if (ch == '.') {
			result[find++] = stoi(temp);
			temp = "";
		}
		else {
			temp += ch;
		}
	}
	TicketClass newTicket(result[0], result[1], result[2], result[3], result[4], result[5]);

	ifstream file(TicketClass::TICKETFILE, ios::app, ios::binary);
	TicketClass fileTicket;
	while(file.read((char*)&fileTicket.randIdentifier, sizeof(int))){

		file.read((char*)&fileTicket.user, sizeof(int));
		file.read((char*)&fileTicket.event, sizeof(int));
		file.read((char*)&fileTicket.zone, sizeof(int));
		file.read((char*)&fileTicket.row, sizeof(int));
		file.read((char*)&fileTicket.seat, sizeof(int));

		if (fileTicket == newTicket){
			file.close();
			return true;
		}
	}
	file.close();
	return false;
}

bool TicketClass::operator==(TicketClass& ticket) {
	if (this->randIdentifier = ticket.randIdentifier && this->user == ticket.user
		&& this->event == ticket.event && this->zone == ticket.zone && this->row == ticket.row && this->seat == ticket.seat) {
		return true;
	}
	return false;

}

void TicketClass::buyTicket(int userId) {
	while(1){
		try {
			EventClass::printSavedEvents();
			cout << "Id of event you want to buy the ticket for: ";
			int id, zone, row, seat;
			cin >> id;
			EventClass* event = EventClass::getEventFromId(id);
			LocationClass* loc = LocationClass::getLocationFromId(event->getLocationId());
			loc->printDetailedDescription();
			cout << "Where do you want your ticket? Type only the number for the following: " << endl;


			cout << "Zone: ";
			cin >> zone;

			if (zone > loc->getNoZones())
				throw exception("Invalid zone no.");

			cout << "Row: ";
			cin >> row;

			if (row > loc->getNoRowsOfZone(zone))
				throw exception("Invalid row no.");

			cout << "Seat: ";
			cin >> seat;
			cout << endl;
			if (seat > loc->getNoOfSeatOfRow(zone,row))
				throw exception("Invalid seat no.");
			if (TicketClass::checkIfTaken(id, zone, row, seat) == true) {
				throw exception("We're sorry but this seat is already taken!");
			}
			else {
				TicketClass ticket(userId, id, zone, row, seat);
				cout << "Ticket succesfully purchased!" << endl << endl;
				cout << "-----------------------------------------------------------------" << endl;
				cout << "Unique ticket id (you may want to write this down): " << ticket.generateTicketId()<< endl;
				cout << "-----------------------------------------------------------------" << endl;
				ticket.writeInfo();
			}
			break;
		}
		catch (exception e) {
			system("cls");
			cout << e.what() << endl;
		}
	}
}
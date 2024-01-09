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
	ticketId += ".";
	ticketId += to_string(this->user);
	ticketId += ".";
	ticketId += to_string(this->event);
	ticketId += ".";
	ticketId += to_string(this->zone);
	ticketId += ".";
	ticketId += to_string(this->row);
	ticketId += ".";
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
	result[find++] = stoi(temp);
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

void TicketClass::buyTicket(UserClass* user) {
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
				TicketClass ticket(user->getId(), id, zone, row, seat);
				cout << "Ticket succesfully purchased!" << endl << endl;
				cout << "-----------------------------------------------------------------" << endl;
				cout << "Unique ticket id (you may want to write this down): " << ticket.generateTicketId()<< endl;
				cout << "-----------------------------------------------------------------" << endl;
				ticket.writeInfo();
				ticket.createTicketPDF(user, event, loc);
			}
			break;
		}
		catch (exception e) {
			system("cls");
			cout << e.what() << endl;
		}
	}
}

void error_handler(HPDF_STATUS error_no, HPDF_STATUS detail_no, void* user_data) {
	std::cerr << "Error: error_no=" << error_no << ", detail_no=" << detail_no << endl;

}

void TicketClass::createTicketPDF(UserClass* user, EventClass* event, LocationClass* loc) {
	HPDF_Doc  pdf = HPDF_New(error_handler, NULL); 


	HPDF_Page page = HPDF_AddPage(pdf);

	// Set font and size
	HPDF_Font font = HPDF_GetFont(pdf, "Times-Roman", NULL);

	HPDF_Page_SetFontAndSize(page, font, 18);

	HPDF_Page_BeginText(page);
	string title = event->getName() + " Ticket";
	//computing title coordonates so that it is centered
	
	float pageWidth = HPDF_Page_GetWidth(page);
	float textWidth = HPDF_Page_TextWidth(page, title.c_str());
	float xPos = (pageWidth - textWidth) / 2;

	HPDF_Page_TextOut(page, xPos, 800, title.c_str());
	HPDF_Page_EndText(page);

	HPDF_Page_SetFontAndSize(page, font, 12);

	HPDF_Page_BeginText(page);
	string ticketId = "Unique ticket Id: " + this->generateTicketId();
	textWidth = HPDF_Page_TextWidth(page, ticketId.c_str());
	xPos = (pageWidth - textWidth) / 2;
	HPDF_Page_TextOut(page, xPos, 750, ticketId.c_str());
	HPDF_Page_EndText(page);

	HPDF_Page_BeginText(page);
	string location = "Location: ";
	location += loc->getName();
	HPDF_Page_TextOut(page, 100, 650, location.c_str());
	HPDF_Page_EndText(page);
	
	HPDF_Page_BeginText(page);
	string date = "Date: " + event->getDate();
	HPDF_Page_TextOut(page, 100, 625, date.c_str());
	HPDF_Page_EndText(page);

	HPDF_Page_BeginText(page);
	string time = "Time: " + event->getTime();
	HPDF_Page_TextOut(page, 100, 600, time.c_str());
	HPDF_Page_EndText(page);

	HPDF_Page_BeginText(page);
	string username = "Username: " + user->getUsername();
	HPDF_Page_TextOut(page, 100, 550, username.c_str());
	HPDF_Page_EndText(page);

	HPDF_Page_BeginText(page);
	string email = "Email: " + user->getEmail();
	HPDF_Page_TextOut(page, 100, 525, email.c_str());
	HPDF_Page_EndText(page);

	HPDF_Page_SetFontAndSize(page, font, 14);

	HPDF_Page_BeginText(page);
	string text = "How do I get there? Click the link bellow: ";
	HPDF_Page_TextOut(page, 100, 450, text.c_str());
	HPDF_Page_EndText(page);

	HPDF_Page_BeginText(page);
	string url = loc->generateLink();
	HPDF_Page_TextOut(page, 100, 425, url.c_str());
	HPDF_Page_EndText(page);

	string pdfName = "ticket " +this->generateTicketId() + ".pdf";
	HPDF_SaveToFile(pdf, pdfName.c_str());

	HPDF_Free(pdf);
}
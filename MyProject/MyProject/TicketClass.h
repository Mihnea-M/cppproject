#pragma once
#include <fstream>
#include <cstdlib> 
#include <ctime>
#include <string>
#include "EventClass.h"
using namespace std;

class TicketClass
{
	//ticket look like - rand.user.event.zone.row.seat
	int randIdentifier = 0;
	int user = 0;
	int event = 0;
	int zone = 0;
	int row = 0;
	int seat = 0;

	static constexpr char TICKETFILE[] = "tickets.dat";

	TicketClass();

	TicketClass(int rand, int user, int event, int zone, int row, int seat);

public:
	TicketClass(int user, int event, int zone, int row, int seat);

	void writeInfo();

	string generateTicketId();

	static bool checkIfTaken(int event, int zone, int row, int seat);

	static bool checkTicket(string ticket);

	static void buyTicket(int userId);

	bool operator==(TicketClass& ticket);
};


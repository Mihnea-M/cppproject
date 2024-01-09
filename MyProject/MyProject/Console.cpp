#include "Console.h"

void Console::start() {
	printIntroduction();
	UserClass* user = nullptr;
	//cin >> &user;
	AccountCommands accountCommand = returnAccountCommands();
	user = readUser(accountCommand);
	printCommands(user->getType());
	EventCommands command = getCommand(user->getType());
	while (command != EventCommands::QUIT)
	{
		switch (command)
		{
		case EventCommands::CREATE:
		{
			EventClass::createEvent();
			break;
		}
		case EventCommands::VIEW:
		{
			EventClass::printSavedEvents();
			break;
		}
		case EventCommands::BUY:
		{
			TicketClass::buyTicket(user->getId());
			break;
		}
		case EventCommands::TICKET:
		{
			cout << endl << "Please enter your ticket id: ";
			string ticket;
			cin >> ticket;
			cout << endl;
			if (TicketClass::checkTicket(ticket) == true)
				cout << "You have a valid ticket";
		}
		case EventCommands::USER:
		{
			cout << user;
			break;
		}
		case EventCommands::QUIT:
			break;
		}
		printCommands(user->getType());
		command = getCommand(user->getType());
		system("cls");
	}
}
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
			EventClass::createEvent();
		case EventCommands::VIEW:
			EventClass::printSavedEvents();
		case EventCommands::BUY:
			break;
		case EventCommands::TICKET:
			break;
		case EventCommands::USER:
			cout << user;
		case EventCommands::QUIT:
			break;
		}
		printCommands(user->getType());
		command = getCommand(user->getType());
		system("cls");
	}
}
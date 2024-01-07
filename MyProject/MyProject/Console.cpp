#include "Console.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include <string>
#include "UserClass.h"
#include "TextFunctions.h"
#include "LocationClass.h"
#include "EventClass.h"

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
			break;
		case EventCommands::VIEW:
			break;
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
	}
}
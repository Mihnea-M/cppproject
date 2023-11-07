#include "TextFunctions.h"

char* transformInput(const char* word)
{
	char* newWord;
	int i;
	int Lenght = strlen(word) + 1;
	newWord = new char[Lenght];
	for (i = 0; i < Lenght; i++)
	{
		if (word[i] >= 'A' && word[i] <= 'Z')
		{
			newWord[i] = word[i] + 32;
		}
		else
			newWord[i] = word[i];
	}
	return newWord;
}

void printIntroduction() {
	cout << "Welcome to the ticketing application." << endl << endl;
	cout << "Would you like to log in, create a new accout or join as a guest? (type \"log in\", \"create\" or \"guest\")" << endl;
}

UserClass returnUser() 
{
	string username;
	char* password = new char[20];
	//this should be included later in user 
	char* response = new char[20];
	while(1)
	{
		cin.getline(response, 20);

		response = transformInput(response);

		if (strcmp(response, "log in") == 0)
		{
					cout << "Enter username: ";
					cin >> username;
					cout << "Enter password: ";
					cin >> password;
					UserClass newUser(username, password, USERFILE, AccountCommands::LOGIN);
					delete[] response;
					delete[] password;
					return newUser;

		}
		else if (strcmp(response, "create") == 0)
		{
			cout << "New username: ";
			cin >> username;
			cout << "New password: ";
			cin >> password;
			UserClass newUser(username, password, USERFILE, AccountCommands::CREATE);
			delete[] response;
			delete[] password;
			return newUser;
		}
		else if (strcmp(response, "admin") == 0) {
			cout << "Enter admin password: ";
			cin >> password;
			UserClass newUser(password);
			delete[] response;
			delete[] password;
			return newUser;
		}
		else if (strcmp(response, "guest") == 0)
		{
			UserClass newUser;
			delete[] response;
			delete[] password;
			system("cls");
			cout << "Logged is as guest.";
			return newUser;
		}
		//system("cls");
		cout << "Please provide a valid input!" << endl << endl;
		cout << "Would you like to log in, create a new accout or join as a guest? (type \"log in\", \"create\" or \"guest\")" << endl;
	}

}

void printCommands(UserTypes type) {
	
	switch (type)
	{
	case UserTypes::ADMIN:
	{
		cout << endl << "Type \"Create\" to create an event, \"view\" to see all available events, \"buy\" to buy a ticket or \"ticket\" to view an existing ticket." << endl;
		cout << "You can also type \"quit\" to exit." << endl;
		break;
	}
	case UserTypes::BASIC:
	{
		cout << endl << "Type \"view\" to see all available events, \"buy\" to buy a ticket or \"ticket\" to view an existing ticket." << endl;
		cout << "You can also type \"quit\" to exit." << endl;
		break;
	}
	case UserTypes::GUEST:
	{
		cout << endl << "Type \"view\" to see all available events or \"ticket\" to view an existing ticket." << endl;
		cout << "You can also type \"quit\" to exit." << endl;
		break;
	}
	}
}

EventCommands getCommand(UserTypes type) {
	string command;
	cin >> command;
	command = transformInput(command.c_str());
	if (command == "quit")
		return EventCommands::QUIT;
	if (type == UserTypes::ADMIN)
	{
		while (1) {
			if (command == "create")
				return EventCommands::CREATE;
			else if (command == "view")
				return EventCommands::VIEW;
			else if (command == "buy")
				return EventCommands::BUY;
			else if (command == "ticket")
				return EventCommands::TICKET;
			system("cls");
			cout << endl << "Please provide a valid input." << endl;
			printCommands(type);
			cin >> command;
			command = transformInput(command.c_str());
		}
	}
	else if (type == UserTypes::BASIC)
	{
		while (1) {
			 if (command == "view")
				return EventCommands::VIEW;
			else if (command == "buy")
				return EventCommands::BUY;
			else if (command == "ticket")
				return EventCommands::TICKET;
			system("cls");
			cout << endl << "Please provide a valid input." << endl;
			printCommands(type);
			cin >> command;
			command = transformInput(command.c_str());
		}
	}
	else if (type == UserTypes::GUEST)
	{
		while (1) {
			if (command == "view")
				return EventCommands::VIEW;
			else if (command == "ticket")
				return EventCommands::TICKET;
			system("cls");
			cout << endl << "Please provide a valid input." << endl;
			printCommands(type);
			cin >> command;
			command = transformInput(command.c_str());
		}
	}
}
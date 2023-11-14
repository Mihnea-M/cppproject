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

UserClass readUser(UserTypes type, AccountCommands command = AccountCommands::CREATE) {
	bool success = 0;
	string username;
	char* password = new char[20];
	string email;
	int age;

	while (!success) 
	{
		switch (type)
		{
		case UserTypes::ADMIN:
		{
			cout << "Enter admin password: ";
			cin >> password;
			try
			{
				UserClass newUser(password);
				newUser.checkAdminPass();
				delete[] password;
				system("cls");
				cout << endl << "Logged in as admin." << endl;
				return &newUser;
			}
			catch (exception e) {
				system("cls");
				cout << endl << e.what() << endl << endl << "Logging is as guest." << endl;
				UserClass newUser;
				return &newUser;
			}

		}
		case UserTypes::BASIC:
		{
			switch (command)
			{
			case AccountCommands::LOGIN:
			{
				cout << "Enter username: ";
				cin >> username;
				cout << "Enter password: ";
				cin >> password;
				while (!success)
				{
					try
					{
						UserClass newUser (username, password);
						newUser.checkUser();
						delete[] password;
						success = 1;
						system("cls");
						cout << endl << "Succesfully logged in." << endl;
						return &newUser;
						
					}
					catch (exception e) {
						if (strcmp(e.what(), "Data file not found") == 0)
						{
							system("cls");
							cout << endl << e.what() << endl << endl << "Logging is as guest." << endl;
							UserClass newUser;
							return newUser;
						}
						system("cls");
						cout << endl << e.what() << endl << endl;
						cout << "Enter username: ";
						cin >> username;
						cout << "Enter password: ";
						cin >> password;
					}
				}
				
			}
			case AccountCommands::CREATE:
			{
				cout << "New username: ";
				cin >> username;
				//if age < 14 print You are not allowed to use the platform, but due to limited budget you are not restricted access.
				cout << "Your password must contain at least a capital letter, a small letter and a number. New password: ";
				cin >> password;
				cout << "Email: ";
				cin >> email;
				cout << "Age: ";
				cin >> age;
				while (!success)
				{
					try
					{
						UserClass* newUser;
						newUser = CreateAccount::newUser(username, email, password, age);
						//newUser.saveUser();
						success = 1;
						//UserClass newUser(username, password, email, age);
						system("cls");
						cout << endl << "Succesfully created new account." << endl;
						return newUser;
					}
					catch (exception e) {
						system("cls");
						cout << endl << e.what() << endl << endl;
						cout << "Enter username: ";
						cin >> username;
						cout << "Enter password: ";
						cin >> password;
						cout << "Email: ";
						cin >> email;
						cout << "Age: ";
						cin >> age;
					}
				}
			}
			}
		}
		case UserTypes::GUEST:
		{
			UserClass newUser;
			cout << "Logged is as guest."<< endl;
			return &newUser;
		}
		}
	}
}

void printIntroduction() {
	cout << "Welcome to the ticketing application." << endl << endl;
	cout << "Would you like to log in, create a new accout or join as a guest? (type \"login\", \"create\" or \"guest\")" << endl;
}

//tranform this function in the main loop which constantly waits for commands and processes them 
//make 2 different cases: when you type event you get access to event commands, when you type account you get access to account commands
UserClass returnUser() 
{

	char* response = new char[20];
	while(1)
	{
		cin >> response;
		system("cls");
		response = transformInput(response);

		if (strcmp(response, "login") == 0)
		{
			
			return readUser(UserTypes::BASIC, AccountCommands::LOGIN);
		}
		else if (strcmp(response, "create") == 0)
		{
			
			return readUser(UserTypes::BASIC, AccountCommands::CREATE);
		}
		else if (strcmp(response, "admin") == 0) {
			return readUser(UserTypes::ADMIN);
		}
		else if (strcmp(response, "guest") == 0)
		{	
			return readUser(UserTypes::GUEST);
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
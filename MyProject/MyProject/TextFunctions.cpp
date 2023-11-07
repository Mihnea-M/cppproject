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
	const string fileName = "users.txt";
	//this should be included later in user 
	char* response = new char[20];
	UserClass newUser;
	cin.getline(response, 20);

	response = transformInput(response);

	if (strcmp(response, "log in") == 0)
	{
		cout << "Enter username: ";
		cin >> username;
		cout << "Enter password: ";
		cin >> password;
		UserClass newUser(username, password, fileName, Commands::LOGIN);
	}
	else
		if (strcmp(response, "create") == 0)
		{
			cout << "New username: ";
			cin >> username;
			cout << "New password: ";
			cin >> password;
			UserClass newUser(username, password, fileName, Commands::CREATE);
		}
		else
			UserClass newUser();

	delete[] response;
	delete[] password;
	return newUser;
}
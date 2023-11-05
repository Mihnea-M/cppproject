#include <iostream>
#include <fstream>
#include <string.h>
#include <string>
using namespace std;

enum class UserTypes { ADMIN, LOGGED, GUEST };

class User{
	string userName = "";
	char* password = nullptr;
	UserTypes type = UserTypes::GUEST;


};

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
	cout << "Welcome to the ticketing application." << endl << endl << "Would you like to log in, create a new accout or join as a guest? (type \"log in\", \"create\" or \"guest\")" << endl;
}



int main()
{
	printIntroduction();


	//this should be included later in user 
	char* response = new char[20];
	cin.getline(response, 20);

	response = transformInput(response);

	if (strcmp (response, "log in") == 0)
	{
		cout << endl << "enter password";
	}
	else if (strcmp(response, "guest") == 0)
	{
		cout << endl << "go ahead";
	}
	else
		cout << response << endl << "wrong input";
	//until here

	delete[] response;
	
}
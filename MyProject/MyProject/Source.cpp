#include <iostream>
#include <fstream>
#include <string.h>
#include <string>
using namespace std;

enum class UserTypes { ADMIN, BASIC, GUEST };

class User{
public:
	string userName = "";
	char* password = nullptr;
	UserTypes type = UserTypes::GUEST;

	static const int MIN_USER_SIZE = 4;
	static const int MAX_USER_SIZE = 20;
	static const int MIN_PSWD_SIZE = 6;
	static const int MAX_PSWD_SIZE = 30;

public:
	void setUserName(const string name) {
		if (name.length() < User::MIN_USER_SIZE || name.length() > User::MAX_USER_SIZE || !( (name[0] >= 'a' && name[0] <= 'z') || (name[0] >= 'A' && name[0] <= 'Z') ) )
			throw exception("Invalid username");
		//exception to be created
		else
			this->userName = name;
	}

	void setPassword(const char* pass) {
		bool uppCaseChar = 0, lowCaseChar= 0, numChar = 0;

		if (strlen(pass)<User::MIN_PSWD_SIZE || strlen(pass)>User::MAX_PSWD_SIZE)
			throw exception("Invalid passowrd");

		if (!((pass[0] >= 'a' && pass[0] <= 'z') || (pass[0] >= 'A' && pass[0] <= 'Z') || (pass[0] >= '0' && pass[0] <= 9)))
			throw exception("Invalid passowrd");

		for (int i = 0;i <= strlen(pass);i++) {
			if (pass[i] >= 'A' && pass[i] <= 'Z')
				uppCaseChar = 1;
			if (pass[i] >= 'a' && pass[i] <= 'z')
				lowCaseChar = 1;
			if (pass[i] >= '0' && pass[i] <= '9')
				numChar = 1;
		}

		if (!(numChar && lowCaseChar && uppCaseChar))
			throw exception("Invalid passowrd");

		delete[] this->password;
		this->password = new char[strlen(pass) + 1];
		strcpy_s(this->password, strlen(pass) + 1, pass);
	}

	void saveUser(const string fileName)
	{
		ofstream file;
		file.open(fileName, ios::app);
		//file << this->userName << " " << this->password << endl;
		//file.write((char*)this, sizeof(User));
		file << this;
		file.close();
	}

	User() {

	}

	User(const string name, const char* pass) {
		this->setUserName(name);
		this->setPassword(pass);
	}

	~User() {
		delete[]this->password;
	}

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
	cout << "Welcome to the ticketing application." << endl << endl;
	cout << "Would you like to log in, create a new accout or join as a guest? (type \"log in\", \"create\" or \"guest\")" << endl;
}


int main()
{
	printIntroduction();
	
	string username;
	char* password = new char[20];
	fstream TestFile;
	string fileName = "testfile.txt";

	//this should be included later in user 
	char* response = new char[20];
	cin.getline(response, 20);

	response = transformInput(response);

	if (strcmp(response, "log in") == 0)
	{
		cout << "Enter username: ";
		cin >> username;
		cout << "Enter password: ";
		cin >> password;
		User existingUser(username,password);
	}
	else 
		if (strcmp(response, "guest") == 0)
	{
		User guestUser();
	}
	else 
			if (strcmp(response, "create") == 0)
	{
		cout << "New username: ";
		cin >> username;
		cout << "New password: ";
		cin >> password;
		User newUser(username, password);
		newUser.saveUser(fileName);

	}
	else
	{
		if (strcmp(response, "read") == 0)
		{
			User user;
			ifstream file;
			file.open(fileName, ios::out);
			//file << this->userName << " " << this->password << endl;
			//file.read((char*)&user, sizeof(User));
			file >> user.userName >> user.password;
			file.close();
			cout << user.password;
		}
	}

	delete[] response;
	delete[] password;
	
	//until here

	
	
}
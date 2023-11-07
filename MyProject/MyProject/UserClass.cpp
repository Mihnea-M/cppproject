#include "UserClass.h"


void UserClass::setUserName(const string name) {
	if (name.length() < UserClass::MIN_USER_SIZE || name.length() > UserClass::MAX_USER_SIZE || !((name[0] >= 'a' && name[0] <= 'z') || (name[0] >= 'A' && name[0] <= 'Z')))
		throw exception("Invalid username");
	//exception to be created
	else
		this->userName = name;
}

void UserClass::setPassword(const char* pass) {
	bool uppCaseChar = 0, lowCaseChar = 0, numChar = 0;

	if (strlen(pass) < UserClass::MIN_PSWD_SIZE || strlen(pass) > UserClass::MAX_PSWD_SIZE)
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

	void UserClass::saveUser(const string fileName)
	{
		if (this->checkUserName(fileName) == 1)
		{
			system("cls");
			cout << endl << "Succesfully created new account." << endl;
			ofstream file;
			file.open(fileName, ios::app, ios::binary);

			int nameSize = (this->userName).size() + 1;
			int passSize = strlen(this->password) + 1;


			file.write((char*)&nameSize, sizeof(int));
			file.write((this->userName).c_str(), nameSize);


			file.write((char*)&passSize, sizeof(int));
			file.write(this->password, passSize);

			file.close();
		}
		else
		{
			system("cls");
			throw exception("Existing username");
		}
		
	}

	void UserClass::checkUser(const string fileName)
	{
		bool test = 0;
		int sizeUser, sizePass;
		char* usernameArr = nullptr, * passwordArr = nullptr;

		ifstream file;
		file.open(fileName, ios::in, ios::binary);

		while (!file.eof()) 
		{
			//reading size of username and username
			file.read((char*)&sizeUser, sizeof(int));
			usernameArr = new char[sizeUser];
			file.read(usernameArr, sizeof(char) * sizeUser);

			//reading size of password and password
			file.read((char*)&sizePass, sizeof(int));
			passwordArr = new char[sizePass];
			file.read(passwordArr, sizeof(char) * sizePass);

			//checking if the log in credentials are correct
			if (strcmp((this->userName).c_str(), usernameArr) == 0 && strcmp(this->password, passwordArr) == 0)
			{
				test = 1;
				this->type = UserTypes::BASIC;
				system("cls");
				cout << endl << "Succesfully logged in." << endl;
			}

			delete[] usernameArr;
			delete[] passwordArr;
		}

		file.close();

		if (test == 0)
		{
			system("cls");
			throw exception ("Wrong username/password!");
		}

	}

	bool UserClass::checkUserName(const string fileName) {
		bool test = 0;
		int sizeUser, sizePass;
		char* usernameArr = nullptr, * passwordArr = nullptr;
		ifstream file;
		file.open(fileName, ios::in, ios::binary);

		while (!file.eof()) {

			file.read((char*)&sizeUser, sizeof(int));
			usernameArr = new char[sizeUser];
			file.read(usernameArr, sizeof(char) * sizeUser);

			file.read((char*)&sizePass, sizeof(int));
			passwordArr = new char[sizePass];
			file.read(passwordArr, sizeof(char) * sizePass);

			if (strcmp((this->userName).c_str(), usernameArr) == 0)
			{
				test = 1;
			}
			delete[] usernameArr;
			delete[] passwordArr;
		}

		file.close();

		if (test == 1)
		{
			//username taken
			return 0;
		}
		else
		{
			//available username
			return 1;
		}
	}

	UserTypes UserClass::getType() {
		return this->type;
		
	}

	UserClass::UserClass() {

	}

	UserClass::UserClass(const char* pass) {
		this->setPassword(pass);
		if (strcmp(this->password, "Pass123") == 0)
		{
			this->userName = "Admin";
			this->type = UserTypes::ADMIN;
			system("cls");
			cout << endl << "Logged in as admin." << endl;
		}
		else
		{
			system("cls");
			cout << "Wrong password. Logging is as guest.";
		}
	}

	UserClass::UserClass(const string name, const char* pass, const string filename, AccountCommands command) {
		this->setUserName(name);
		this->setPassword(pass);

		if (command == AccountCommands::CREATE)
			this->saveUser(filename);
		else if (command == AccountCommands::LOGIN)
			this->checkUser(filename);

		this->type = UserTypes::BASIC;
	}

	UserClass::UserClass(class UserClass* user) {
		delete[] this->password;
		this->password = new char[strlen(user->password) + 1];
		strcpy_s(this->password, strlen(user->password) + 1, user->password);
		this->type = user->type;
		this->userName = user->userName;
	}

	void UserClass::operator=(UserClass source) {
		if (this == &source)
			return;
		this->userName = source.userName;
		this->type = source.type;
		delete[] this->password;
		if (source.password)
		{
			this->password = new char[strlen(source.password) + 1];
			strcpy_s(this->password, strlen(source.password) + 1, source.password);
		}
		else
			this->password = nullptr;
		this->type = source.type;
	}

	UserClass::~UserClass() {
		delete[]this->password;
	}

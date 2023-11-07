#include "UserClass.h"

//Validate if username is valid and available
bool UserClass::checkUserName(string newUser) {
	if (newUser.length() < UserClass::MIN_USER_SIZE || newUser.length() > UserClass::MAX_USER_SIZE || !((newUser[0] >= 'a' && newUser[0] <= 'z') || (newUser[0] >= 'A' && newUser[0] <= 'Z')))
	{
		//invalid username
		return 1;
	}
	bool test = 0;
	int sizeUser=0, sizePass=0;
	char* usernameArr = nullptr, * passwordArr = nullptr;
	ifstream file;
	file.open(UserClass::USERFILE, ios::in, ios::binary);

	while (!file.eof()) {

		file.read((char*)&sizeUser, sizeof(int));
		usernameArr = new char[sizeUser];
		file.read(usernameArr, sizeof(char) * sizeUser);

		file.read((char*)&sizePass, sizeof(int));
		passwordArr = new char[sizePass];
		file.read(passwordArr, sizeof(char) * sizePass);

		if (strcmp((newUser).c_str(), usernameArr) == 0)
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
		return 1;
	}
	else
	{
		//available username
		return 0;
	}
}

//Validating passwords
bool UserClass::checkPassword(const char* pass) {
	bool uppCaseChar = 0, lowCaseChar = 0, numChar = 0;

	if (strlen(pass) < UserClass::MIN_PSWD_SIZE || strlen(pass) > UserClass::MAX_PSWD_SIZE)
	{
		return 1;
	}

	if (!((pass[0] >= 'a' && pass[0] <= 'z') || (pass[0] >= 'A' && pass[0] <= 'Z') || (pass[0] >= '0' && pass[0] <= 9)))
	{
		return 1;
	}

	for (int i = 0;i <= strlen(pass);i++) {
		if (pass[i] >= 'A' && pass[i] <= 'Z')
			uppCaseChar = 1;
		if (pass[i] >= 'a' && pass[i] <= 'z')
			lowCaseChar = 1;
		if (pass[i] >= '0' && pass[i] <= '9')
			numChar = 1;
	}
	if (!(numChar && lowCaseChar && uppCaseChar))
	{
		return 1;
	}
	return 0;
}

void UserClass::setUserName(const string name) {
	if (UserClass::checkUserName(name) == 0)
		this->userName = name;
}
void UserClass::setPassword(const char* pass) {
	if (UserClass::checkPassword(pass) == 0)
	{
		delete[] this->password;
		this->password = new char[strlen(pass) + 1];
		strcpy_s(this->password, strlen(pass) + 1, pass);
	}
}

	void UserClass::saveUser()
	{
			ofstream file;
			file.open(UserClass::USERFILE, ios::app, ios::binary);

			int nameSize = (this->userName).size() + 1;
			int passSize = strlen(this->password) + 1;


			file.write((char*)&nameSize, sizeof(int));
			file.write((this->userName).c_str(), nameSize);


			file.write((char*)&passSize, sizeof(int));
			file.write(this->password, passSize);

			file.close();
			//UserClass::noRegisteredUsers++;
			system("cls");
			cout << endl << "Succesfully created new account." << endl;
	}

	void UserClass::checkUser()
	{
		bool test = 0;
		int sizeUser=0, sizePass=0;
		char* usernameArr = nullptr, * passwordArr = nullptr;

		ifstream file;
		file.open(UserClass::USERFILE, ios::in, ios::binary);

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

	

	UserTypes UserClass::getType() {
		return this->type;
		
	}

	UserClass::UserClass() {

	}

	//to be deleted
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

	UserClass::UserClass(const string name, const char* pass) {
		this->setUserName(name);
		this->setPassword(pass);
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

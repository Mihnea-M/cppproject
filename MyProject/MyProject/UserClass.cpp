#include "UserClass.h"

int UserClass::noRegisteredUsers = 0;



void UserClass::setUserName(const string name) {
	if (name.length() < UserClass::MIN_USER_SIZE || name.length() > UserClass::MAX_USER_SIZE || !((name[0] >= 'a' && name[0] <= 'z') || (name[0] >= 'A' && name[0] <= 'Z')))
	{
		throw exception("Invalid username");
	}
	else
		this->userName = name;
}

void UserClass::setPassword(const char* pass) {
	if (UserClass::checkPassword(pass) == 0)
	{
		delete[] this->password;
		this->password = new char[strlen(pass) + 1];
		strcpy_s(this->password, strlen(pass) + 1, pass);
	}
	else
		throw exception("Invalid password");
}

void UserClass::setEmail(const string email) {
	if (UserClass::checkEmail(email) == 0)
		this->email = email;
	else
		throw exception("Invalid email");
}

void UserClass::setAge(int age)
{
	if (age<UserClass::MIN_AGE || age > UserClass::MAX_AGE)
		throw exception("Invalid age");
	else
		this->age = age;
}

void UserClass::saveUser()
{
	if (UserClass::checkCredentialAvaliability(this->userName, this->email) == 1)
	{
		throw exception("Username or email taken");
	}
	else
	{
		//setting the user as being logged in
		this->type = UserTypes::BASIC;

		ofstream file;
		file.open(UserClass::USERFILE, ios::app, ios::binary);

		int nameSize = (this->userName).size() + 1;
		int passSize = strlen(this->password) + 1;
		int emailSize = (this->email).size() + 1;

		//saving username size and username
		file.write((char*)&nameSize, sizeof(int));
		file.write((this->userName).c_str(), nameSize);

		//saving password size and password
		file.write((char*)&passSize, sizeof(int));
		file.write(this->password, passSize);

		//saving emailsize and email
		file.write((char*)&emailSize, sizeof(int));
		file.write((this->email).c_str(), emailSize);

		//saving age
		file.write((char*)(&this->age), sizeof(int));

		file.close();

		UserClass::noRegisteredUsers++;


	}
}

	/*
	UserClass UserClass::readUserFromFile(ifstream file){
		int sizeUser = 0, sizePass = 0, sizeEmail = 0, age;
		char* usernameArr = nullptr, * passwordArr = nullptr, * emailArr = nullptr;

		//reading size of username and username
		file.read((char*)&sizeUser, sizeof(int));
		usernameArr = new char[sizeUser];
		file.read(usernameArr, sizeof(char) * sizeUser);

		//reading size of password and password
		file.read((char*)&sizePass, sizeof(int));
		passwordArr = new char[sizePass];
		file.read(passwordArr, sizeof(char) * sizePass);

		//reading size of email and email
		file.read((char*)&sizeEmail, sizeof(int));
		emailArr = new char[sizeEmail];
		file.read(emailArr, sizeof(char) * sizeEmail);

		//reading age
		file.read((char*)&age, sizeof(int));

		return UserClass(usernameArr, passwordArr, emailArr, age);
		//memory leak?? from transforming the char array into a string?
	}
	*/
	void UserClass::checkUser()
	{
		bool test = 0;
		int sizeUser=0, sizePass=0, sizeEmail = 0;
		char* usernameArr = nullptr, * passwordArr = nullptr, * emailArr = nullptr;
		int age;

		ifstream file;
		file.open(UserClass::USERFILE, ios::in, ios::binary);
		if (file.is_open())
		{
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

				//reading size of email and email
				file.read((char*)&sizeEmail, sizeof(int));
				emailArr = new char[sizeEmail];
				file.read(emailArr, sizeof(char) * sizeEmail);

				//reading age
				file.read((char*)&age, sizeof(int));

				//checking if the log in credentials are correct
				if (strcmp((this->userName).c_str(), usernameArr) == 0 && strcmp(this->password, passwordArr) == 0)
				{
					this->type = UserTypes::BASIC;
					return;
				}

				delete[] usernameArr;
				delete[] passwordArr;
			}
		}
		else
			throw exception("Data file not found");

		file.close();
		throw exception("Invalid username or password!");
	}

	//Validate if username is valid and available
	bool UserClass::checkCredentialAvaliability(string newUser, string newEmail) {
		
		bool test = 0;
		int sizeUser = 0, sizePass = 0, sizeEmail = 0;
		char* usernameArr = nullptr, * passwordArr = nullptr, * emailArr = nullptr;
		int age;

		ifstream file;
		file.open(UserClass::USERFILE, ios::in, ios::binary);
		if (file.is_open())
		{
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

				//reading size of email and email
				file.read((char*)&sizeEmail, sizeof(int));
				emailArr = new char[sizeEmail];
				file.read(emailArr, sizeof(char) * sizeEmail);

				//reading age
				file.read((char*)&age, sizeof(int));

				//checking if the log in credentials are correct
				if (strcmp(newUser.c_str(), usernameArr) == 0)
				{
					//Username taken
					return 1;
				}
				if (strcmp(newEmail.c_str(), emailArr) == 0)
				{
					//Email taken
					return 1;
				}

			}
			file.close();
		}
		return 0;
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


	void UserClass::checkAdminPass() {
		if (strcmp(this->password, "Pass123") == 0)
		{
			this->userName = "Admin";
			this->type = UserTypes::ADMIN;
			
		}
		else
		{
			throw exception("Wrong admin password.");
		}
	}

	bool UserClass::checkEmail(string newEmail) {
		if (newEmail.length() < UserClass::MIN_EMAIL_SIZE || newEmail.length() > UserClass::MAX_EMAIL_SIZE || newEmail.find('@') == string::npos)
		{
			//invalid email
			return 1;
		}
		return 0;
	}

	void UserClass::printInfo() {
		if (this->type == UserTypes::BASIC)
		{
			system("cls");
			cout << endl << "--------------------------------" << endl;
			cout <<"Username: " << this->userName << endl << "Email: " << this->email << endl << "Age: " << this->age;
			cout << endl << "--------------------------------" << endl;
		}
		else
		{
			system("cls");
			cout << (this->type == UserTypes::ADMIN) ? "You are logged in as admin": "You are logged in as guest";
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
	}

	UserClass::UserClass(const string name, const char* pass) {
			this->setUserName(name);
			this->setPassword(pass);
	}

	UserClass::UserClass(const string name, const char* pass, const string email, int age) {
			this->setUserName(name);
			this->setPassword(pass);
			this->setEmail(email);
			this->age = age;
	}

	UserClass::UserClass(const UserClass* user) {
		delete[] this->password;
		if (user->password != nullptr)
		{
			this->password = new char[strlen(user->password) + 1];
			strcpy_s(this->password, strlen(user->password) + 1, user->password);
		}
		this->type = user->type;
		this->userName = user->userName;
		this->age = user->age;
		this->email = user->email;
	}

	void UserClass::operator=(UserClass source) {
		if (this == &source)
			return;
		this->userName = source.userName;
		this->type = source.type;
		this->email = source.email;
		this->age = source.age;
		delete[] this->password;
		if (source.password)
		{
			this->password = new char[strlen(source.password) + 1];
			strcpy_s(this->password, strlen(source.password) + 1, source.password);
		}
		else
			this->password = nullptr;

	}

	UserClass::~UserClass() {
		delete[]this->password;
	}

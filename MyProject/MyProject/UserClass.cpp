#include "UserClass.h"

int UserClass::noRegisteredUsers = 0;



void UserClass::setUserName(const string name) {
		this->userName = name;
}

void UserClass::setPassword(const char* pass) {
		delete[] this->password;
		this->password = new char[strlen(pass) + 1];
		strcpy_s(this->password, strlen(pass) + 1, pass);

}

void UserClass::setEmail(const string email) {
		this->email = email;

}

void UserClass::setAge(int age)
{
		this->age = age;
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


	string UserClass::getUsername() {
		return this->userName;
	}

	string UserClass::getEmail() {
		return this->email;
	}

	int UserClass::getAge() {
		return this->age;
	}

	UserTypes UserClass::getType() {
		return this->type;
		
	}

	UserClass::UserClass() {

	}


	UserClass::UserClass(const string name, const char* pass, const string email, int age) {
			this->setUserName(name);
			this->setPassword(pass);
			this->setEmail(email);
			this->age = age;
			this->type = UserTypes::BASIC;
	}

	UserClass::UserClass(const string name, const string email, const char* pass, int age) {
		this->setUserName(name);
		this->setPassword(pass);
		this->setEmail(email);
		this->setAge(age);
		this->type = UserTypes::BASIC;
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

	void operator<<(ostream& console, UserClass* user) {
		if (user->getType() == UserTypes::BASIC)
		{
			system("cls");
			cout << endl << "--------------------------------" << endl;
			cout << "Username: " << user->getUsername() << endl << "Email: " << user->getEmail() << endl << "Age: " << user->getAge();
			cout << endl << "--------------------------------" << endl;
		}
		else
		{
			system("cls");
			cout << endl << ((user->getType() == UserTypes::ADMIN) ? "You are logged in as admin" : "You are logged in as guest") << endl;
		}
	}


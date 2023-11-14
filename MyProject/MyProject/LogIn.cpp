#include "LogIn.h"


UserClass* LogIn::logIn(const string name, const char* password) {
	try 
	{
		checkUsername(name);
	}
	catch (InvalidUsernameException e1)
	{
		try 
		{
			checkEmail(name);
		}
		catch (InvalidEmailException e2) 
		{
			throw InvalidUsernameException();
		}
	}
	checkPassword(password);
	bool test = 0;
	int sizeUser = 0, sizePass = 0, sizeEmail = 0;
	char* usernameArr = nullptr, * passwordArr = nullptr, * emailArr = nullptr;
	int age = 0;
	UserClass* newUser = nullptr;

	ifstream file;
	file.open(LogIn::USERFILE, ios::in, ios::binary);
	if (file.is_open())
	{
		while (!file.eof())
		{
			//reading size of username and username
			file.read((char*)&sizeUser, sizeof(int));
			usernameArr = new char[sizeUser];
			file.read(usernameArr, sizeof(char) * sizeUser);

			//reading size of email and email
			file.read((char*)&sizeEmail, sizeof(int));
			emailArr = new char[sizeEmail];
			file.read(emailArr, sizeof(char) * sizeEmail);

			//reading size of password and password
			file.read((char*)&sizePass, sizeof(int));
			passwordArr = new char[sizePass];
			file.read(passwordArr, sizeof(char) * sizePass);

			//reading age
			file.read((char*)&age, sizeof(int));

			//checking if the log in credentials are correct
			if ((strcmp(name.c_str(), usernameArr) == 0 && strcmp(password, passwordArr) == 0) || (strcmp(name.c_str(), emailArr) == 0 && strcmp(password, passwordArr) == 0))
			{
				newUser = new UserClass(string(usernameArr), string(emailArr), passwordArr, age);
				delete[] usernameArr;
				delete[] passwordArr;
				delete[] emailArr;
				file.close();
				return newUser;
			}

			delete[] usernameArr;
			delete[] passwordArr;
			delete[] emailArr;
		}
	}
	else
	{
		throw DataFileNotFoundException();
	}

	file.close();
	throw InvalidCredentialsException();
}

UserClass* LogIn::adminLogIn(const char* password) {
	if (strcmp(password, "Pass123") == 0)
	{
		UserClass* newUser = new UserClass();
		newUser->userName = "Admin";
		newUser->type = UserTypes::ADMIN;
		return newUser;
	}
	else
	{
		throw InvalidPasswordException();
	}
}


#pragma once

#include <string>
#include <string.h>
#include <fstream>
#include <iostream>

#include "UserValidation.h"
#include "CreateAccount.h"
#include "LogIn.h"


using namespace std;

enum class UserTypes { ADMIN, BASIC, GUEST };
enum class AccountCommands {LOGIN, CREATE, ADMIN, GUEST};
enum class EventCommands {CREATE, VIEW, BUY, TICKET, QUIT};


class UserClass {

	friend class CreateAccount;
	friend class LogIn;

	string userName = "";
	string email = "";
	char* password = nullptr;
	UserTypes type = UserTypes::GUEST;
	int age = 0;

	static int noRegisteredUsers;

	//setter for username
	void setUserName(const string name);

	//setter for password
	void setPassword(const char* pass);

	//setter for email
	void setEmail(const string email);
	
	//setter for age
	void setAge(int age);

	UserClass();

	UserClass(const string name, const char* pass, const string email, int age);

	UserClass(const string name, const string email, const char* pass, int age);

public:

	//static UserClass readUserFromFile(ifstream file);

	string getUsername();

	string getEmail();

	int getAge();

	UserTypes getType();
	

	//cpy constructor
	UserClass(const UserClass* user);

	//destructor
	~UserClass();

	void operator=(UserClass source);
};

void operator<<(ostream& console, UserClass *user);

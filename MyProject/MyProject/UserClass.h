#pragma once

#include <string>
#include <string.h>
#include <fstream>
#include <iostream>
using namespace std;

enum class UserTypes { ADMIN, BASIC, GUEST };
enum class AccountCommands {LOGIN, CREATE};
enum class EventCommands {CREATE, VIEW, BUY, TICKET, QUIT};
class UserClass {

	string userName = "";
	char* password = nullptr;
	UserTypes type = UserTypes::GUEST;

	static const int MIN_USER_SIZE = 4;
	static const int MAX_USER_SIZE = 20;
	static const int MIN_PSWD_SIZE = 6;
	static const int MAX_PSWD_SIZE = 30;

	void setUserName(const string name);

	void setPassword(const char* pass);

	void saveUser(const string fileName);

	void checkUser(const string fileName);

	bool checkUserName(const string fileName);


public:
	UserTypes getType();

	UserClass();

	UserClass(const char* pass);

	UserClass(const string name, const char* pass, const string filename, AccountCommands command);

	UserClass(class UserClass* user);

	~UserClass();

	void operator=(UserClass source);
};

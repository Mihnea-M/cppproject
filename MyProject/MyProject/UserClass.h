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
	string email = "";
	char* password = nullptr;
	UserTypes type = UserTypes::GUEST;
	int age = 0;

	static int noRegisteredUsers;

public:
	//constexpr - ??
	static constexpr char USERFILE[] = "users.dat";
	static const int MIN_USER_SIZE = 4;
	static const int MAX_USER_SIZE = 20;
	static const int MIN_PSWD_SIZE = 6;
	static const int MAX_PSWD_SIZE = 30;

private:
	void setUserName(const string name);

	void setPassword(const char* pass);

public:
	void saveUser();

	void checkUser();

	static bool checkUserName(string newUser);

	static bool checkPassword(const char* pass);



	UserTypes getType();

	UserClass();

	UserClass(const char* pass);

	UserClass(const string name, const char* pass);

	UserClass(class UserClass* user);

	~UserClass();

	void operator=(UserClass source);
};
//int UserClass::noRegisteredUsers = 0;

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
enum class AccountCommands {LOGIN, CREATE};
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

public:
	static constexpr char USERFILE[] = "users.dat";
	static const int MIN_USER_SIZE = 4;
	static const int MAX_USER_SIZE = 20;
	static const int MIN_PSWD_SIZE = 6;
	static const int MAX_PSWD_SIZE = 30;
	static const int MIN_EMAIL_SIZE = 7;
	static const int MAX_EMAIL_SIZE = 30;
	static const int MIN_AGE = 14;
	static const int MAX_AGE = 120;
private:
	//setter for username
	void setUserName(const string name);

	//setter for password
	void setPassword(const char* pass);

	//setter for email
	void setEmail(const string email);
	
	//setter for age
	void setAge(int age);

public:
	//saving the user into the file + setting type to basic
	void saveUser();

	//checking if the user belongs to the file
	//if it does it changes the type to basic
	//if not it throws exception
	void checkUser();
	

	//checks if the username and email are already taken
	//returns 1 if not available
	//0 otherwise
	static bool checkCredentialAvaliability(string newUser, string newEmail);

	//validation for password
	// 1 - invalid password
	// 0 - good
	static bool checkPassword(const char* pass);

	//validation for email
	// 1 - invalid email
	// 0 - good
	static bool checkEmail(string newEmail);

	//checks if the users password matches to the extremely secret admin password
	//if it does user becomes admin
	//if not user becomes guest
	void checkAdminPass();

	//static UserClass readUserFromFile(ifstream file);

	string getUsername();

	string getEmail();

	int getAge();

	//returns the user type
	UserTypes getType();


	//Constructors

	UserClass();

	UserClass(const char* pass);

	UserClass(const string name, const char* pass);

	UserClass(const string name, const char* pass, const string email, int age);
private:
	//all constructors (besides the default constructors should be private)
	UserClass(const string name, const string email, const char* pass, int age);
public:
	UserClass(const UserClass* user);

	~UserClass();

	void operator=(UserClass source);
};

void operator<<(ostream& console, UserClass *user);

void operator<<(ofstream& file, UserClass* user);

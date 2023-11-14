#pragma once
#include <string>
#include <fstream>
#include "UserExceptions.h"

using namespace std;


class UserValidation
{
protected:
	static constexpr char USERFILE[] = "users.dat";
	static const int MIN_USER_SIZE = 4;
	static const int MAX_USER_SIZE = 20;
	static const int MIN_PSWD_SIZE = 6;
	static const int MAX_PSWD_SIZE = 30;
	static const int MIN_EMAIL_SIZE = 7;
	static const int MAX_EMAIL_SIZE = 30;
	static const int MIN_AGE = 14;
	static const int MAX_AGE = 120;

	//validation for username
	static void checkUsername(const string name);

	//validation for email
	static void checkEmail(const string email);

	//validation for password
	static void checkPassword(const char* pass);

	//validation for age
	static void checkAge(const int age);

	static void checkCredentialAvaliability(const string newUser, const string newEmail);
};


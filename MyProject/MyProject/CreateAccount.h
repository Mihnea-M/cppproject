#pragma once
#include "UserClass.h"

using namespace std;

class UserClass;

class CreateAccount : UserValidation {
public:
	static UserClass* newUser(const string username, const string email, const char* password, const int age);

};


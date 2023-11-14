#pragma once
#include "UserClass.h"
class UserClass;

class LogIn : UserValidation
{
public:
	static UserClass* logIn(const string name, const char* password);
};


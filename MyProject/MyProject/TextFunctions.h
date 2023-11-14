#pragma once
#include <string.h>
#include <iostream>
#include "UserClass.h"


using namespace std;



char* transformInput(const char* word);

UserClass* readUser(AccountCommands command);

void printIntroduction();

UserClass returnUser();

AccountCommands returnAccountCommands();

void printCommands(UserTypes type);

EventCommands getCommand(UserTypes type);


void operator>>(istream& console, UserClass** user);


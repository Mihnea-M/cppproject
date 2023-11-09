#pragma once
#include <string.h>
#include <iostream>
#include "UserClass.h"
using namespace std;



char* transformInput(const char* word);

UserClass readUser(UserTypes type, AccountCommands command);

void printIntroduction();

UserClass returnUser();

void printCommands(UserTypes type);

EventCommands getCommand(UserTypes type);
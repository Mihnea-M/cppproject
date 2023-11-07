#pragma once
#include <string.h>
#include <iostream>
#include "UserClass.h"
using namespace std;

const string USERFILE = "users.dat";

char* transformInput(const char* word);

void printIntroduction();

UserClass returnUser();

void printCommands(UserTypes type);

EventCommands getCommand(UserTypes type);
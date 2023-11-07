#include <iostream>
#include <fstream>
#include <string.h>
#include <string>

#include "UserClass.h"
#include "TextFunctions.h"
using namespace std;



int main()
{
	printIntroduction();
	UserClass user;
	user.operator=(returnUser());
	printCommands(user.getType());
}
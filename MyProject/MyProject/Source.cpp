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
	EventCommands command{};
	while(command != EventCommands::QUIT)
	{
		printCommands(user.getType());
		command = getCommand(user.getType());
	}
}
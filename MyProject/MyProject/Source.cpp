#include <iostream>
#include <fstream>
#include <string.h>
#include <string>

#include "UserClass.h"
#include "TextFunctions.h"
using namespace std;

//for future implementation - https://developers.google.com/maps/documentation/geocoding
//http://www.google.com/maps/place/lat,lng



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
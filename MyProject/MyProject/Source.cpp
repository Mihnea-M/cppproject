//#include <iostream>
//#include <fstream>
//#include <string.h>
//#include <string>
//#include "UserClass.h"
//#include "TextFunctions.h"
//#include "LocationClass.h"
//#include "EventClass.h"

#include "Console.h"
#include "LocationClass.h"
using namespace std;


//some of the operators are overloaded just for the purpose of the first phase
//TO DO: create classes for the seats, rows, zones
//create the user interface class


//print locations information

int main()
{

	/*ZoneClass zone;
	cin >> zone;
	ZoneClass* zones[1];
	zones[0] = &zone;

	LocationClass location("Sala palatului", 1, zones, "Sala palatului bucuresti");
	try {
		location.writeInfo();
	}
	catch (exception e) {
		cout << e.what();
	}*/
	LocationClass::printSavedLocations();
}

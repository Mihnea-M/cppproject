//#include <iostream>
//#include <fstream>
//#include <string.h>
//#include <string>
//#include "UserClass.h"
//#include "TextFunctions.h"
//#include "LocationClass.h"
//#include "EventClass.h"
#include "Console.h"
using namespace std;

//for future implementation - https://developers.google.com/maps/documentation/geocoding
//http://www.google.com/maps/place/lat,lng
//some of the operators are overloaded just for the purpose of the first phase
//TO DO: create classes for the seats, rows, zones
//create the user interface class


int main()
{
	Console console;
	console.start();
	
	/*
	string zones[] = { "Row 1", "Row 2" };
	int noSeats[] = { 10, 20 };
	LocationClass loc("stadium", 2, zones, noSeats, "Bucharest"); 
	loc.addZoze("Vip", 5);
	cout << loc;
	//cin >> loc;
	//cout << loc;
	cout << (int)loc << endl;
	cout << loc[2];

	EventClass event("Football game", "11.11.2023", "11:11", loc);
	cout << event;
	//cin >> event;
	//cout << event;
	loc.addZoze("Vip2", 3);
	EventClass event2("The other football game", "12.11.2023", "11:11", loc);
	if (event > event2)
		cout << event.getName() << " has more total seats than " << event2.getName();
	else
		cout << event2.getName() << " has more total seats than " << event.getName();
		*/
}

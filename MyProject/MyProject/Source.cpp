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



int main()
{
	
	LocationClass loc;
	string ad = "facultatea de cibernetica ase";
	loc.setCoord(ad);
	cout << loc.generateLink();

}

#include "Console.h"

using namespace std;

//to have admin privileges type admin and the password Pass123
//an aready existing account is Andrei with the password Andre1

// !!!!!!!!!!!!!
//Project wont work unless:
//set env variable API_KEY 
//download hpdf.h for libharu, curl/curl.h for the api call and nlohmann/json.hpp for json processing

int main()
{
	Console console;
	console.start();
}

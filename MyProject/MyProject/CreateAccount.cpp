#include "CreateAccount.h"

UserClass* CreateAccount::newUser(const string username,const string email, const char* password,const int age) {
	checkUsername(username);
	checkEmail(email);
	checkPassword(password);
	checkAge(age);

	checkCredentialAvaliability(username, email);

	UserClass* newUser = new UserClass(username, email, password, age);

	ofstream file;
	file.open(CreateAccount::USERFILE, ios::app, ios::binary);

	int nameSize = (username).size() + 1;
	int passSize = strlen(password) + 1;
	int emailSize = (email).size() + 1;

	//saving username size and username
	file.write((char*)&nameSize, sizeof(int));
	file.write((username).c_str(), nameSize);

	//saving emailsize and email
	file.write((char*)&emailSize, sizeof(int));
	file.write((email).c_str(), emailSize);

	//saving password size and password
	file.write((char*)&passSize, sizeof(int));
	file.write(password, passSize);

	//saving age
	file.write((char*)(&age), sizeof(int));

	file.close();

	return newUser;
}

UserClass* CreateAccount::createGuest(){
	UserClass* newUser = new UserClass();
	return newUser;
}
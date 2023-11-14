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

	int nameSize = (newUser->userName).size() + 1;
	int passSize = strlen(newUser->password) + 1;
	int emailSize = (newUser->email).size() + 1;

	//saving username size and username
	file.write((char*)&nameSize, sizeof(int));
	file.write((newUser->userName).c_str(), nameSize);

	//saving password size and password
	file.write((char*)&passSize, sizeof(int));
	file.write(newUser->password, passSize);

	//saving emailsize and email
	file.write((char*)&emailSize, sizeof(int));
	file.write((newUser->email).c_str(), emailSize);

	//saving age
	file.write((char*)(&newUser->age), sizeof(int));

	file.close();

	return newUser;
}
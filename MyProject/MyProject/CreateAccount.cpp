#include "CreateAccount.h"

UserClass* CreateAccount::newUser(const string username,const string email, const char* password,const int age) {
	checkUsername(username);
	checkEmail(email);
	checkPassword(password);
	checkAge(age);

	checkCredentialAvaliability(username, email);

	

	fstream file;
	file.open(CreateAccount::USERFILE, ios::out | ios::in, ios::binary);

	int nameSize = (username).size() + 1;
	int passSize = strlen(password) + 1;
	int emailSize = (email).size() + 1;

	int noOfUsers = 0;

	if (!file.is_open()) {
		file.open(CreateAccount::USERFILE, ios::out, ios::binary);
	}
	else{
		//reading the first integer from the file (total no of users)
		file.read((char*)&noOfUsers, sizeof(int));
	}

	//overwriting and incrementing the first integer
	noOfUsers++;
	file.write((char*)&noOfUsers, sizeof(int));
	file.seekp(0, ios::end);

	//saving the id of the last user
	file.write((char*)&noOfUsers, sizeof(int));

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

	UserClass* newUser = new UserClass(noOfUsers, username, email, password, age);
	return newUser;
}

UserClass* CreateAccount::createGuest(){
	UserClass* newUser = new UserClass();
	return newUser;
}
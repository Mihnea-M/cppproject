#include "UserValidation.h"

void UserValidation::checkUsername(const string name) {
	if (name.length() < UserValidation::MIN_USER_SIZE || name.length() > UserValidation::MAX_USER_SIZE || !((name[0] >= 'a' && name[0] <= 'z') || (name[0] >= 'A' && name[0] <= 'Z')))
	{
		throw InvalidUsernameException();
	}
}

void UserValidation::checkEmail(const string email) {
	if (email.length() < UserValidation::MIN_EMAIL_SIZE || email.length() > UserValidation::MAX_EMAIL_SIZE || email.find('@') == string::npos)
	{
		throw InvalidEmailException();
	}
}

void UserValidation::checkPassword(const char* password) {
	bool uppCaseChar = 0, lowCaseChar = 0, numChar = 0;

	if (strlen(password) < UserValidation::MIN_PSWD_SIZE || strlen(password) > UserValidation::MAX_PSWD_SIZE)
	{
		throw InvalidPasswordException();
	}

	if (!((password[0] >= 'a' && password[0] <= 'z') || (password[0] >= 'A' && password[0] <= 'Z') || (password[0] >= '0' && password[0] <= 9)))
	{
		throw InvalidPasswordException();
	}

	for (int i = 0;i <= strlen(password);i++) {
		if (password[i] >= 'A' && password[i] <= 'Z')
			uppCaseChar = 1;
		if (password[i] >= 'a' && password[i] <= 'z')
			lowCaseChar = 1;
		if (password[i] >= '0' && password[i] <= '9')
			numChar = 1;
	}
	if (!(numChar && lowCaseChar && uppCaseChar))
	{
		throw InvalidPasswordException();
	}
}

void UserValidation::checkAge(const int age) {
	if (age<UserValidation::MIN_AGE || age > UserValidation::MAX_AGE)
	{
		throw exception("Invalid age");
	}
}

void UserValidation::checkCredentialAvaliability(const string newUser, const string newEmail) {
	bool test = 0;
	int sizeUser = 0, sizePass = 0, sizeEmail = 0;
	char* usernameArr = nullptr, * passwordArr = nullptr, * emailArr = nullptr;
	int age;

	ifstream file;
	file.open(UserValidation::USERFILE, ios::in, ios::binary);
	if (file.is_open())
	{
		while (!file.eof())
		{
			//reading size of username and username
			file.read((char*)&sizeUser, sizeof(int));
			usernameArr = new char[sizeUser];
			file.read(usernameArr, sizeof(char) * sizeUser);

			//reading size of password and password
			file.read((char*)&sizePass, sizeof(int));
			passwordArr = new char[sizePass];
			file.read(passwordArr, sizeof(char) * sizePass);

			//reading size of email and email
			file.read((char*)&sizeEmail, sizeof(int));
			emailArr = new char[sizeEmail];
			file.read(emailArr, sizeof(char) * sizeEmail);

			//reading age
			file.read((char*)&age, sizeof(int));

			//checking if the log in credentials are correct
			if (strcmp(newUser.c_str(), usernameArr) == 0)
			{
				//Username taken
				delete[] usernameArr;
				delete[] passwordArr;
				delete[] emailArr;
				throw UsernameTakenException();
			}
			if (strcmp(newEmail.c_str(), emailArr) == 0)
			{
				//Email taken
				delete[] usernameArr;
				delete[] passwordArr;
				delete[] emailArr;
				throw EmailTakenException();
			}

		}
		file.close();
	}
	delete[] usernameArr;
	delete[] passwordArr;
	delete[] emailArr;
}
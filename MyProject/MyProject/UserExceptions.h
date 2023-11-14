#pragma once



class InvalidUsernameException : public std::exception {
public:
	InvalidUsernameException() : std::exception("Invalid Username!") {

	}
};

class InvalidPasswordException : public std::exception {
public:
	InvalidPasswordException() : std::exception("Invalid Password!") {

	}
};

class InvalidEmailException : public std::exception {
public:
	InvalidEmailException() : std::exception("Invalid Email!") {

	}
};

class InvalidAgeException : public std::exception {
public:
	InvalidAgeException() : std::exception("Invalid Age!") {

	}
};

class UsernameTakenException : public std::exception {
public:
	UsernameTakenException() : std::exception("Username already taken!") {

	}
};

class EmailTakenException : public std::exception {
public:
	EmailTakenException() : std::exception("Email already taken!") {

	}
};

class DataFileNotFoundException : public std::exception {
public:
	DataFileNotFoundException() : std::exception("Data file not found!") {

	}
};

class InvalidCredentialsException : public std::exception {
public:
	InvalidCredentialsException() : std::exception("Incorrect username or password!") {

	}
};
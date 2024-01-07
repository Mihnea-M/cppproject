#include "LocationLayout.h"

//Seat functions

void SeatClass::setOwner(int userId) {
	if (userId < 1)
		throw std::exception("Invalid user id");
	this->isOccupied = true;
	this->userId = userId;
}

void SeatClass::setUnoccupied() {
	this->isOccupied = false;
	this->userId = 0;
}

int SeatClass::getSeatOwner() {
	return this->userId;
}

bool SeatClass::isAvailable() {
	if (this->isOccupied == true)
		return false;
	else
		return true;
}

//Row functions

void RowClass::setNoSeats(int noSeats) {
	if (noSeats < 0)
		throw std::exception("invalid no of seats");
	this->noSeats = noSeats;
	delete[] this->seats;
	this->seats = new SeatClass[this->noSeats];
}

void RowClass::addSeat(SeatClass& seat) {
	this->noSeats++;
	SeatClass* newSeats = new SeatClass[this->noSeats];
	for (int i = 0;i < this->noSeats - 1;i++) {
		newSeats[i] = this->seats[i];
	}
	delete[] this->seats;
	newSeats[this->noSeats - 1] = seat;
	this->seats = newSeats;
}

int RowClass::getNoSeats() {
	return this->noSeats;
}

int RowClass::getNoOfFreeSeats() {
	int no = 0, i;
	for (i = 0;i < this->noSeats;i++) {
		if (this->seats[i].isAvailable() == true) {
			no++;
		}
	}
	return no;
}

void RowClass::buySeat(int seatNo, int userId) {
	if (seatNo > this->noSeats)
		throw std::exception("Invalid seat number.");
	this->seats[seatNo - 1].setOwner(userId);
}

RowClass::RowClass(int noSeats) {
	this->setNoSeats(noSeats);
	this->seats = new SeatClass[noSeats];
}

RowClass::~RowClass() {
	delete[] this->seats;
}

RowClass::RowClass(const RowClass& source) {
	if (this == &source) {
		return;
	}
	delete[] this->seats;
	this->noSeats = source.noSeats;
	this->seats = new SeatClass[this->noSeats];
	for (int i = 0;i < this->noSeats;i++) {
		this->seats[i] = source.seats[i];
	}
}

void RowClass::operator=(const RowClass& source) {
	if (this == &source) {
		return;
	}
	delete[] this->seats;
	this->noSeats = source.noSeats;
	this->seats = new SeatClass[this->noSeats];
	for (int i = 0;i < this->noSeats;i++) {
		this->seats[i] = source.seats[i];
	}
}

void operator>> (std::istream& console, RowClass& row) {
	std::cout << std::endl << "How many seats does this row have?";
	int no;
	console >> no;
	row.setNoSeats(no);
}

//Zone funtions

void ZoneClass::setName(std::string name) {
	if (name.length() < ZoneClass::MIN_NAME_SIZE || name.length() > ZoneClass::MAX_NAME_SIZE)
		throw std::exception("Invalid name");
	this->name = name;
}

std::string ZoneClass::getName() {
	return this->name;
}

void ZoneClass::setBasePricePerSeat(float price) {
	this->basePricePerSeat = price;
}

float ZoneClass::getBasePricePerSeat() {
	return this->basePricePerSeat;
}

void ZoneClass::setRows(int noRows, RowClass** rows) {
	if (noRows < 1)
		throw std::exception("Invalid no. of rows");
	delete[] this->rows;
	this->noRows = noRows;
	this->rows = new RowClass*[this->noRows];
	for (int i = 0;i < this->noRows;i++) {
		this->rows[i] = new RowClass(*rows[i]);
	}
}

void ZoneClass::addRow(RowClass& row) {
	RowClass** newRows = new RowClass*[this->noRows + 1];
	for (int i = 0;i < this->noRows;i++) {
		newRows[i] = this->rows[i];
	}
	this->noRows++;
	newRows[this->noRows - 1] = new RowClass(row);
	this->rows = newRows;
}

int ZoneClass::getNoOfFreeSeats() {
	int no = 0, i;
	for (i = 0;i < this->noRows;i++) {
		no += this->rows[i]->getNoOfFreeSeats();
	}
	return no;
}

void ZoneClass::buySeat(int rowNo, int seatNo, int userId) {
	if (rowNo > this->noRows)
		throw std::exception("Invalid row no.");
	this->rows[rowNo - 1]->buySeat(seatNo, userId);
}

ZoneClass::ZoneClass(std::string name, float price, int noRows, RowClass** rows) {
	this->setName(name);
	this->setBasePricePerSeat(price);
	this->setRows(noRows, rows);
}

ZoneClass::~ZoneClass() {
	for (int i = 0; i < this->noRows; i++) {
		delete rows[i];
	}
	delete[] rows;
}

ZoneClass::ZoneClass(const ZoneClass& source)
{
	if (this == &source)
		return;
	for (int i = 0; i < this->noRows; i++) {
		delete this->rows[i];
	}
	delete[] this->rows;
		this->rows = new RowClass * [source.noRows];
	for (int i = 0; i < source.noRows; ++i) {
		this->rows[i] = new RowClass(*source.rows[i]);
	}
}


void ZoneClass::operator= (const ZoneClass& source) {
	if (this == &source)
		return;
	for (int i = 0; i < this->noRows; i++) {
		delete this->rows[i];
	}
	delete[] this->rows;
	this->rows = new RowClass * [source.noRows];
	for (int i = 0; i < source.noRows; ++i) {
		this->rows[i] = new RowClass(*source.rows[i]);
	}
}


void operator>>(std::istream& console, ZoneClass& zone) {
	
		std::string name;
		float basePricePerSeat;
		int noRows, noSeatsInRow;

		std::cout << "Enter Zone Name: ";
		console.ignore();
		std::getline(console, name);
		zone.setName(name);
		console.clear();
		std::cout << "Enter Base Price Per Seat: ";
		console >> basePricePerSeat;
		zone.setBasePricePerSeat(basePricePerSeat);

		std::cout << "Enter Number of Rows: ";
		console >> noRows;

		RowClass** rows = new RowClass * [noRows];
		for (int i = 0; i < noRows; ++i) {
			std::cout << "Enter number of seats in row " << (i + 1) << ": ";
			console >> noSeatsInRow;

			rows[i] = new RowClass(noSeatsInRow); // Assuming RowClass has a constructor that takes noSeats as a parameter
			// Additional setup for RowClass if needed
		}
		zone.setRows(noRows, rows);

		// Note: Remember to manage the memory for rows array in ZoneClass appropriately


}

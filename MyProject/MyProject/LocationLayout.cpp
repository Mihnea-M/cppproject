#include "LocationLayout.h"

//Row functions

void RowClass::setNoSeats(int noSeats) {
	if (noSeats < 0)
		throw std::exception("invalid no of seats");
	this->noSeats = noSeats;	
}

int RowClass::getNoSeats() {
	return this->noSeats;
}

RowClass::RowClass(int noSeats) {
	this->setNoSeats(noSeats);
	
}

RowClass::~RowClass() {
	
}

RowClass::RowClass(const RowClass& source) {
	if (this == &source) {
		return;
	}
	this->noSeats = source.noSeats;
}

void RowClass::operator=(const RowClass& source) {
	if (this == &source) {
		return;
	}
	this->noSeats = source.noSeats;
	
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
	if (price < 0)
		throw std::exception("Invalid price.");
	this->basePricePerSeat = price;
}

float ZoneClass::getBasePricePerSeat() {
	return this->basePricePerSeat;
}

void ZoneClass::setRows(int noRows, RowClass** rows) {
	if (noRows < 1)
		throw std::exception("Invalid no. of rows");
	for (int i = 0;i < this->noRows;i++)
		delete this->rows[i];
	delete[] this->rows;
	this->noRows = noRows;
	this->rows = new RowClass * [this->noRows];
	for (int i = 0;i < this->noRows;i++) {
		this->rows[i] = new RowClass(*rows[i]);
	}
}

void ZoneClass::addRow(RowClass& row) {
	int i;
	RowClass** newRows = new RowClass * [this->noRows + 1];
	for (i = 0;i < this->noRows;i++) {
		newRows[i] = this->rows[i];
	}
	this->noRows++;
	newRows[this->noRows - 1] = new RowClass(row);
	for (i = 0; i < this->noRows; i++) {
		delete this->rows[i];
	}
	delete[] this->rows;
	this->rows = newRows;
}

int ZoneClass::getNoRows() {
	return this->noRows;
}

int ZoneClass::getNoSeats() {
	int no = 0;
	for (int i = 0;i < this->noRows;i++)
		no += this->rows[i]->getNoSeats();
	return no;
}

void ZoneClass::printRows(std::ostream& console) {
	for (int i = 0; i < this->getNoRows(); ++i) {
		console << "Row " << i + 1 << ": ";
		console << *(this->rows[i]);
		console << std::endl;
	}
}

void ZoneClass::writeToFile(std::fstream& file) {
	//write zone name size and name
	int size = name.length()+1;
	file.write((char*)&size, sizeof(int));
	file.write(name.c_str(), size);
	//price
	file.write((char*)&basePricePerSeat, sizeof(float));
	//write no of rows
	file.write((char*)&noRows, sizeof(int));
	for (int i = 0;i < noRows;i++) {
		int temp = this->rows[i]->getNoSeats();
		file.write((char*)&temp, sizeof(int));
	}
}


ZoneClass::ZoneClass() {

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
	this->name = source.name;
	this->basePricePerSeat = source.basePricePerSeat;
	this->noRows = source.noRows;
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
	this->name = source.name;
	this->basePricePerSeat = source.basePricePerSeat;
	this->noRows = source.noRows;
	this->rows = new RowClass * [source.noRows];
	for (int i = 0; i < source.noRows; ++i) {
		this->rows[i] = new RowClass(*source.rows[i]);
	}
}


void operator<<(std::ostream& console, RowClass& row) {
	console << "Number of Seats: " << row.getNoSeats();
}

void operator<<(std::ostream& console, ZoneClass& zone) {
	console << std::endl;
	console << "Zone Name: " << zone.getName();
	console << ", ";
	console << "Base Price Per Seat: " << zone.getBasePricePerSeat() << ", ";
	console << "Number of Rows: " << zone.getNoRows() << std::endl;
	zone.printRows(console);

}

void operator>> (std::istream& console, RowClass& row) {
	std::cout << std::endl << "How many seats does this row have?";
	int no;
	console >> no;
	row.setNoSeats(no);
}

void operator>>(std::istream& console, ZoneClass& zone) {

	char buffer[20];
	float basePricePerSeat;
	int noRows, noSeatsInRow;
	console.clear();
	while (1) {
		std::cout << std::endl << "Enter Zone Name: ";
		console.getline(buffer, 20);
		try {
			zone.setName(buffer);
			break;
		}
		catch (std::exception e) {
			system("cls");
			std::cout << e.what();
		}
	}
	while (1) {
		std::cout << std::endl << "Enter Base Price Per Seat: ";
		console >> basePricePerSeat;
		try {
			zone.setBasePricePerSeat(basePricePerSeat);
			break;
		}
		catch (std::exception e) {
			system("cls");
			std::cout << e.what();
			console.clear();
		}
	}
	while (1) {
		std::cout << std::endl << "Enter Number of Rows: ";
		console >> noRows;
		if (noRows < 1) {
			system("cls");
			std::cout << "Invalid no or rows";
		}
		else
			break;
	}
	RowClass** rows = new RowClass * [noRows];
	for (int i = 0; i < noRows; ++i) {
		while (1) {
			std::cout << std::endl << "Enter number of seats in row " << i + 1 << ": ";
			console >> noSeatsInRow;
			if (noSeatsInRow < 1) {
				system("cls");
				std::cout << "Invalid no of seats.";
			}
			else
				break;
		}
		rows[i] = new RowClass(noSeatsInRow);
	}
	zone.setRows(noRows, rows);
}
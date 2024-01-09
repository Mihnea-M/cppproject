#pragma once
#include <iostream>
#include <string>
#include <fstream>

class RowClass {
	int noSeats = 0;

public:

	void setNoSeats(int noSeats);

	int getNoSeats();

	RowClass(int noSeats);

	~RowClass();
	
	RowClass(const RowClass& source);

	void operator=(const RowClass& source);
};

void operator>>(std::istream& console, RowClass& row);

void operator<<(std::ostream& console, RowClass& row);

class ZoneClass
{
	std::string name = "";
	float basePricePerSeat = 0;
	int noRows = 0;
	RowClass** rows = nullptr;

	static const int MAX_NAME_SIZE = 20;
	static const int MIN_NAME_SIZE = 1;
	
public:
	void setName(std::string name);

	std::string getName();

	void setBasePricePerSeat(float price);

	float getBasePricePerSeat();

	void setRows(int noRows, RowClass** rows);

	void addRow(RowClass &row);

	int getNoRows();

	int getNoSeats();

	int getNoSeatOfRow(int rowNo);

	void printRows(std::ostream& console);

	void writeToFile(std::fstream& file);

	ZoneClass();

	ZoneClass(std::string name, float price, int noRows, RowClass** rows);

	~ZoneClass();

	ZoneClass(const ZoneClass& source);

	void operator= (const ZoneClass& source);
};

void operator>>(std::istream& console, ZoneClass& zone);

void operator<<(std::ostream& console, ZoneClass& zone);






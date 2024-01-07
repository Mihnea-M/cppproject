#pragma once
#include <iostream>
#include <string>

class SeatClass {
	bool isOccupied = false;
	int userId = 0;
public:

	void setOwner(int userId);

	void setUnoccupied();

	int getSeatOwner();

	bool isAvailable();
};


class RowClass {
	int noSeats = 0;
	SeatClass* seats = nullptr;
public:

	void setNoSeats(int noSeats);

	void addSeat(SeatClass& seat);

	int getNoSeats();

	int getNoOfFreeSeats();

	void buySeat(int seatNo, int userId);

	RowClass(int noSeats);

	~RowClass();
	
	RowClass(const RowClass& source);

	void operator=(const RowClass& source);
};

void operator>>(std::istream& console, RowClass& row);

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

	int getNoOfFreeSeats();

	void buySeat(int rowNo, int seatNo, int userId);

	ZoneClass(std::string name, float price, int noRows, RowClass** rows);

	~ZoneClass();

	ZoneClass(const ZoneClass& source);

	void operator= (const ZoneClass& source);
};

void operator>>(std::istream& console, ZoneClass& zone);
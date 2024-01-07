#pragma once
#include <iostream>

class SeatClass {
	bool isOccupied = false;
	int userId = 0;


};

class RowClass {
	int noSeats;
	SeatClass* seats = nullptr;
};


class ZoneClass
{
	std::string name = "";
	int noRows;
	RowClass* rows = nullptr;
	int pricePerSeat = 0;
};
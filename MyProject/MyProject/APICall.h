#pragma once
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <cstdlib>

struct Coordinates {
	float lon = 0;
	float lat = 0;
};

std::string apiCall(std::string address);

Coordinates extractCoord(const std::string& jsonResponse);

std::string eliminateSpaces(std::string address);


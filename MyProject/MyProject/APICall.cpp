#include "APICall.h"

size_t writeCallback(void* contents, size_t size, size_t nmemb, std::string* data) {
	data->append((char*)contents, size * nmemb);
	return size * nmemb;
}

std::string apiCall(std::string address) {

	//concatenate strings
	address = eliminateSpaces(address);
	std::string url1 = "https://maps.googleapis.com/maps/api/geocode/json?address=";
	std::string url2 = "&key=";

	//retriving apiKey (stored as env variable)
	char* apiKey = nullptr;
	size_t size = 0;
	_dupenv_s(&apiKey,&size, "API_KEY");
	if (apiKey != nullptr) {
		std::string finalUrl = url1 + address + url2 + apiKey;

		CURL* curl = curl_easy_init();
		std::string readBuffer;

		if (curl) {
			curl_easy_setopt(curl, CURLOPT_URL, finalUrl.c_str());
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

			CURLcode res = curl_easy_perform(curl);
			if (res != CURLE_OK) {
				std::cout << curl_easy_strerror(res);
			}
			curl_easy_cleanup(curl);
		}
		return readBuffer;
	}
	throw std::exception("Invalid api key");
}

Coordinates extractCoord(const std::string& jsonResponse) {
	Coordinates coords;
	auto json = nlohmann::json::parse(jsonResponse);
	coords.lat = json["results"][0]["geometry"]["location"]["lat"];
	coords.lon = json["results"][0]["geometry"]["location"]["lng"];
	return coords;
}

std::string eliminateSpaces(std::string address) {
	for (int i = 0; i < address.length();i++) {
		if (address[i] == ' ') {
			address[i] = '+';
		}
	}
	return address;
}
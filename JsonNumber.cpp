#include "pch.h"
#include "JsonNumber.h"


JsonNumber::JsonNumber(std::string text) : JsonText(text) {
	processNumber();
}

JsonNumber::~JsonNumber() {
}

/**
this method should be called with the number in the correct format, this check is done
during parsing so no error checking is needed 
*/
void JsonNumber::processNumber() {
	// this capitalizes e if any so avoids checking both upper and lower case
	transform(text.begin(), text.end(), text.begin(), toupper);
	unsigned int indexOfE = text.find('E');
	if (indexOfE == std::string::npos) {
		number = std::stold(text);
	} else {
		long double multiplier = std::stold(text.substr(0, indexOfE));
		long double power = std::stoi(text.substr(indexOfE + 1));
		number = multiplier * pow(10, power);
	}
}

double JsonNumber::getDouble() const {
	return static_cast<double>(number);
}

float JsonNumber::getFloat() const {
	return static_cast<float>(number);
}

int JsonNumber::getInt() const {
	return static_cast<int>(number);
}

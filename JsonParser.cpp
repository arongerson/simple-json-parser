/**

J -> [E] | {A}
E -> D | e
D -> 'k'B | "k"B | nB | [E]B | {A}B, n is a number 
B -> ,D | e
A -> 'k':V | "k":V
V -> JC | 'k'C | "k"C
C -> ,A | e

// e stands for epsilon, k is any identifier

*/

// TO-DO:
// escape \" and \'
// multiline json file
// searching to the end of the file 
#include "pch.h"
#include "JsonParser.h"

JsonParser::JsonParser(const std::string& json, bool showLogs) : 
	json(json), tokenFrom(0), showLogs(showLogs), parserDataStructure(nullptr) {
}

JsonParser::JsonParser(bool showLogs, const std::string filePath):
	tokenFrom(0), showLogs(showLogs), parserDataStructure(nullptr) {
	std::string msg = "reading the file";
	log(msg);
	json = readFile(filePath);
}

JsonParser::~JsonParser() {
	cleanUp();
}

void JsonParser::cleanUp() {
	delete parserDataStructure;
}

void JsonParser::log(std::string& msg) {
	if (showLogs)
		std::cout << msg << std::endl;
}

bool JsonParser::isExpectedToken(char expectedToken, bool consumable) {
	char token = json.at(tokenFrom);
	while (token == ' ' || token == '\n' || token == '\r') {
		tokenFrom++;
		token = json.at(tokenFrom);
	}
	if (token == expectedToken) {
		std::string msg = "token: " + token;
		log(msg);
		if (consumable) {
			tokenFrom++;
		}
		return true;
	}
	return false;
}

bool JsonParser::isNumeric() {
	char token = json.at(tokenFrom);
	while (token == ' ' || token == '\n' || token == '\r') {
		tokenFrom++;
		token = json.at(tokenFrom);
	}
	if ((token >= '0' && token <= '9') || token == '-') {
		std::string msg = "token: " + token;
		log(msg);
		return true;
	}
	return false;
}

std::string JsonParser::getError() {
	return error;
}

std::string JsonParser::getKeyToken() {
	char token = json.at(tokenFrom);
	token = toupper(token);
	if (!((token >= 'A' && token <= 'Z') || token == '_')) {
		std::string error = "identifier expected";
		logError(error); // this will half the program 
	}
	unsigned int start = tokenFrom;
	while ((token >= 'A' && token <= 'Z') || token == '_' || (token >= '0' && token <= '9')) {
		tokenFrom++;
		token = toupper(json.at(tokenFrom));
	}
	std::string msg = "key: " + json.substr(start, tokenFrom - start);
	log(msg);
	return json.substr(start, tokenFrom - start);
}

std::string JsonParser::getValueToken() {
	char token = json.at(tokenFrom);
	// the opening quote character is one position behind the current position of the pointer 
	char openToken = json.at(tokenFrom - 1); 
	unsigned int start = tokenFrom;
	while (token != openToken) {
		tokenFrom++;
		token = json.at(tokenFrom);
	}
	std::string msg = "value: " + json.substr(start, tokenFrom - start);
	log(msg);
	return json.substr(start, tokenFrom - start);
}

std::string JsonParser::getNumber() {
	unsigned int start = tokenFrom;
	char token = json.at(tokenFrom);
	// delimiters of a number: , ] } SPACE
	bool canAcceptDecimalPoint = false;
	bool canAcceptE = false;
	bool canAcceptMinus = true;
	unsigned int count = 0;
	while ((token >= '0' && token <= '9') || ((token == 'e' || token == 'E') && canAcceptE)
		|| (token == '-' && canAcceptMinus) || (token == '.' && canAcceptDecimalPoint)) {
		if (count == 0) {
			canAcceptDecimalPoint = true;
			canAcceptE = true;
			canAcceptMinus = false;
		}
		if (token == '.') {
			canAcceptDecimalPoint = false;
		} else if (token == 'e' || token == 'E') {
			canAcceptMinus = true;
			canAcceptE = false;
			canAcceptDecimalPoint = false;
		} else {
			canAcceptMinus = false;
		}
		tokenFrom++;
		token = json.at(tokenFrom);
		count++;
	}
	// a number can't end with a -, e or E
	char lastNumberCharacter = toupper(json.at(tokenFrom - 1));
	if (lastNumberCharacter == '-' || lastNumberCharacter == 'E') {
		throw("wrong number format");
	}
	return json.substr(start, tokenFrom - start);
}

unsigned int JsonParser::getClosestNumberDelimiter() {
	return 0;
}

void JsonParser::logError(std::string& message) {
	error = message;
	throw(message);
}

void JsonParser::J(JsonItem* parentObject, std::string key) {
	if (isExpectedToken('[', true)) {
		JsonItem* jsonArray = new JsonArray();
		if (parentObject == nullptr) {
			parserDataStructure = jsonArray;
		} else {
			parentObject->addItem(key, jsonArray);
		}
		E(jsonArray);
		if (!isExpectedToken(']', true)) {
			std::string error = "] expected";
			logError(error);
		}
	} else if (isExpectedToken('{', true)) {
		JsonItem* jsonObject = new JsonObject();
		if (parentObject == nullptr) {
			parserDataStructure = jsonObject;
		} else {
			parentObject->addItem(key, jsonObject);
		}
		A(jsonObject);
		if (!isExpectedToken('}', true)) {
			std::string error = "} expected ";
			error.append(std::to_string(tokenFrom)).append(" ,").append(json.substr(tokenFrom, tokenFrom + 20));
			logError(error);
		}
	}
}

void JsonParser::D(JsonItem* parentArray) {
	if (isExpectedToken('"', true)) {
		DQuote('"', parentArray);
	} else if (isExpectedToken('\'', true)) {
		DQuote('\'', parentArray);
	} else if (isNumeric()) {
		std::string number = getNumber();
		JsonItem* jsonNumber = new JsonNumber(number);
		parentArray->addItem(jsonNumber);
		B(parentArray);
	} else if (isExpectedToken('[', true)) {
		JsonItem* jsonArray = new JsonArray();
		E(jsonArray);
		if (isExpectedToken(']', true)) {
			parentArray->addItem(jsonArray);
			B(parentArray);
		} else {
			// new array object not added to the parse data structure, delete it right away,
			// otherwise the object will be cleaned recursively
			delete jsonArray;
			std::string error = "] expected";
			logError(error);
		}
	} else if (isExpectedToken('{', true)) {
		JsonItem* jsonObject = new JsonObject();
		A(jsonObject);
		if (isExpectedToken('}', true)) {
			parentArray->addItem(jsonObject);
			B(parentArray);
		} else {
			// new object not added to the parse data structure, delete it right away,
			// otherwise the object will be cleaned recursively
			delete jsonObject;
			std::string error = "} expected ";
			error.append(std::to_string(tokenFrom));
			logError(error);
		}
	} else {
		std::string error = "[ { \" ' ] } expected";
		logError(error);
	}
}

void JsonParser::DQuote(char token, JsonItem* parentArray) {
	std::string value = getValueToken();
	JsonItem* item;
	if (isExpectedToken(token, true)) {
		item = new JsonText(value);
		parentArray->addItem(item);
		B(parentArray);
	} else {
		std::string error = token + " expected";
		logError(error);
	}
}

/**
processes the key portion of the object item, AQuote is the helper method
refactored to avoid repeating the same code for single and double quotes
*/
void JsonParser::A(JsonItem* parentObject) {
	if (isExpectedToken('"', true)) {
		AQuote('"', parentObject);
	} else if (isExpectedToken('\'', true)) {
		AQuote('\'', parentObject);
	} else {
		// a key should start with a quote
		std::string error = "\" or ' expected";
		logError(error);
	}
}

/**
checks whether the key has a matching closing quote then proceeds to process the value of the key
*/
void JsonParser::AQuote(char token, JsonItem* parentObject) {
	std::string key = getKeyToken();
	if (isExpectedToken(token, true)) {
		if (isExpectedToken(':', true)) {
			V(parentObject, key);
		} else {
			std::string error = ": expected";
			logError(error);
		}
	} else {
		std::string error = token + " expected";
		logError(error);
	}
}

/**
ensures an array has a closing square bracket or the items are separated with a comma
*/
void JsonParser::B(JsonItem* parentArray) {
	if (isExpectedToken(']', false)) {
		// do nothing
	} else if (isExpectedToken(',', true)) {
		D(parentArray);
	} else {
		std::string error = "] or , expected";
		logError(error);
	}
}

/**
ensures the object has a closing brace or the items of the object are separated by a comma
*/
void JsonParser::C(JsonItem* parentObject, std::string key) {
	if (isExpectedToken('}', false)) {
		// do nothing 
	} else if (isExpectedToken(',', true)) {
		A(parentObject);
	} else {
		std::string error = "} or , expected";
		logError(error);
	}
}

/**
with this an empty array can be accepted as a valid JSON
*/
void JsonParser::E(JsonItem* parentArray) {
	if (isExpectedToken(']', false)) {
		// do nothing
	} else {
		D(parentArray);
	}
}

/**
ensures the value of an object is either a string in quotes, a number in the correct format, an object or an array
*/
void JsonParser::V(JsonItem* parentObject, std::string key) {
	if (isExpectedToken('\'', true)) {
		VQuote('\'', parentObject, key);
	} else if (isExpectedToken('\"', true)) {
		VQuote('"', parentObject, key);
	} else if (isNumeric()) {
		std::string number = getNumber();
		JsonItem* jsonNumber = new JsonNumber(number);
		parentObject->addItem(key, jsonNumber);
		C(parentObject, key);
	} else {
		J(parentObject, key);
		C(parentObject, key);
	}
}

void JsonParser::VQuote(char token, JsonItem* parentObject, std::string key) {
	std::string value = getValueToken();
	if (isExpectedToken(token, true)) {
		JsonItem* item = new JsonText(value);
		parentObject->addItem(key, item);
		C(parentObject, key);
	} else {
		std::string error = token + " expected";
		logError(error);
	}
}

std::string JsonParser::readFile(std::string filePath) {
	std::ifstream file;
	file.open(filePath);
	std::string line;
	std::string text = "";
	if (file.is_open()) {
		while (getline(file, line)) {
			text.append(line);
		}
		file.close();
	}
	return text;
}

const JsonItem* JsonParser::parse() {
	json = json.append("$");
	log(json);
	std::string dummyKey = "";
	J(parserDataStructure, dummyKey);
	if (isExpectedToken('$', true)) {
		std::string message = "success";
		log(message);
		return parserDataStructure;
	} else {
		std::string message = "fail";
		log(message);
		return nullptr;
	}
}
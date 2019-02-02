#pragma once
#include "pch.h"
#include <string>
#include <iostream>
#include <stdlib.h>
#include <ctype.h>
#include <fstream>
#include "JsonParser.h"
#include "JsonItem.h"
#include "JsonArray.h"
#include "JsonObject.h"
#include "JsonText.h"

class JsonParser {
private:
	std::string json;
	std::string error;
	unsigned int tokenFrom;
	JsonItem* parserDataStructure;
	
	void J(JsonItem* type, std::string key);
	void A(JsonItem* parentObject);
	void B(JsonItem* parentArray);
	void C(JsonItem* parentObject, std::string key);
	void D(JsonItem* parentArray);
	void E(JsonItem* parentArray);
	void V(JsonItem* parentObject, std::string key);
	void log(std::string&);
	void logError(std::string&);
	void cleanUp();
	bool isExpectedToken(char expectedToken, bool consumable);
	bool showLogs;
	std::string getKeyToken();
	std::string getValueToken();
	std::string getError();
	std::string readFile(std::string filePath);
public:
	JsonParser(const std::string& json, bool showLogs);
	JsonParser(bool showLogs, std::string filePath);
	JsonItem* parse();
	~JsonParser();
};


#include "pch.h"
#include "JsonArray.h"


JsonArray::JsonArray() {
}


JsonArray::~JsonArray() {
	cleanUp();
}

void JsonArray::cleanUp() {
	std::vector<JsonItem*>::iterator it;
	for (it = data.begin(); it != data.end(); it++) {
		JsonItem* type = *it;
		delete *it;
	}
}

JsonItem* JsonArray::getItem(unsigned int index) const {
	return data[index];
}

std::vector<JsonItem*> JsonArray::getItems() {
	return data;
}

void JsonArray::addItem(JsonItem* item) {
	data.push_back(item);
}

std::string JsonArray::getType() const {
	return "JsonArray";
}
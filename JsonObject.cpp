#include "pch.h"
#include "JsonObject.h"


JsonObject::JsonObject() {
}


JsonObject::~JsonObject() {
	cleanUp();
}

void JsonObject::cleanUp() {
	std::map<std::string, JsonItem*>::iterator it;
	for (it = data.begin(); it != data.end(); it++) {
		std::string key = it->first;
		delete it->second;
	}
}

void JsonObject::addItem(std::string key, JsonItem* value) {
	data[key] = value;
}

JsonItem* JsonObject::getItem(std::string key) const {
	std::map<std::string, JsonItem*>::const_iterator pos = data.find(key);
	if (pos == data.end()) {
		throw("key not found");
	} else {
		return pos->second;
	}
}

std::string JsonObject::getType() const {
	return "JsonObject";
}

unsigned int JsonObject::size() const {
	return data.size();
}
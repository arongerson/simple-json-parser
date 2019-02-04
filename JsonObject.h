#pragma once
#include "JsonItem.h"
#include <map>
#include <iostream>
class JsonObject :
	public JsonItem {
private:
	std::map<std::string, JsonItem*> data;
public:
	JsonObject();
	~JsonObject();
	virtual void addItem(std::string key, JsonItem* value);
	virtual JsonItem* getItem(std::string key) const;
	virtual std::string getType() const;
	virtual unsigned int size() const;
	void cleanUp();
};


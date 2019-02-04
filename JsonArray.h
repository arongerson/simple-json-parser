#pragma once
#include "JsonItem.h"
#include <vector>
#include <iostream>
class JsonArray :
	public JsonItem {
private:
	std::vector<JsonItem*> data;
public:
	JsonArray();
	~JsonArray();
	virtual JsonItem* getItem(unsigned int index) const;
	virtual std::vector<JsonItem*> getItems();
	virtual void addItem(JsonItem* item);
	virtual std::string getType() const;
	virtual unsigned int size() const;
	void cleanUp();

};


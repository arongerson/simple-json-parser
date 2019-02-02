#pragma once
#include "JsonItem.h"
#include <iostream>
class JsonText :
	public JsonItem {
private:
	std::string text;
public:
	JsonText(std::string text);
	~JsonText();
	virtual std::string getItem() const;
	virtual std::string getType() const;
};


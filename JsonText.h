#pragma once
#include "JsonItem.h"
#include <iostream>
class JsonText :
	public JsonItem {
protected:
	std::string text;
public:
	JsonText(std::string text);
	~JsonText();
	virtual std::string getText() const;
	virtual std::string getType() const;
};


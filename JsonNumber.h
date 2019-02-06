#pragma once
#include "JsonText.h"
#include <algorithm> 
#include <ctype.h>
class JsonNumber :
	public JsonText {
private:
	long double number;

	void processNumber();
public:
	JsonNumber(std::string text);
	~JsonNumber();
	virtual double getDouble() const;
	virtual float getFloat() const;
	virtual int getInt() const;
};


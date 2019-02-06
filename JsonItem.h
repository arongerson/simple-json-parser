#pragma once
#include <string>
#include <vector>
class JsonItem {
public:
	JsonItem();
	virtual ~JsonItem();
	virtual std::string getText() const;
	virtual double getDouble() const;
	virtual float getFloat() const;
	virtual int getInt() const;
	virtual JsonItem* getItem(unsigned int index) const;
	virtual JsonItem* getItem(const std::string key) const;
	virtual std::vector<JsonItem*> getItems();
	virtual void addItem(JsonItem* item);
	virtual void addItem(std::string key, JsonItem* value);
	virtual std::string getType() const;
	virtual unsigned int size() const;
};


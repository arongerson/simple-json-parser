#pragma once
#include <string>
#include <vector>
class JsonItem {
public:
	JsonItem();
	virtual ~JsonItem();
	virtual std::string getItem() const;
	virtual JsonItem* getItem(unsigned int index) const;
	virtual JsonItem* getItem(const std::string key) const;
	virtual std::vector<JsonItem*> getItems();
	virtual void addItem(JsonItem* item);
	virtual void addItem(std::string key, JsonItem* value);
	virtual std::string getType() const;
};


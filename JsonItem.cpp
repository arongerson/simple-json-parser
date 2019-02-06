#include "pch.h"
#include "JsonItem.h"


JsonItem::JsonItem() {
}


JsonItem::~JsonItem() {
}

std::string JsonItem::getText() const {
	throw("not allowed");
}

double JsonItem::getDouble() const {
	throw("not allowed");
}

float JsonItem::getFloat() const {
	throw("not allowed");
}

int JsonItem::getInt() const {
	throw("not allowed");
}

JsonItem* JsonItem::getItem(const std::string key) const {
	throw("not allowed");
}

JsonItem* JsonItem::getItem(unsigned int index) const {
	throw("not allowed");
}

std::vector<JsonItem*> JsonItem::getItems() {
	throw("not allowed");
}

void JsonItem::addItem(JsonItem* item) {
	throw("not allowed");
}

void JsonItem::addItem(std::string key, JsonItem* value) {
	throw("not allowed");
}

std::string JsonItem::getType() const {
	throw("not allowed");
}

unsigned int JsonItem::size() const {
	throw("not allowed");
}


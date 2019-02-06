#include "pch.h"
#include "JsonText.h"


JsonText::JsonText(std::string text):JsonItem(), text(text) {
}

JsonText::~JsonText() {
}

std::string JsonText::getText() const {
	return text;
}

std::string JsonText::getType() const {
	return "JsonText";
}

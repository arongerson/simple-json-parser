// JsonParser.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include "pch.h"
#include <iostream>
#include <string>
#include "JsonParser.h"

int main() {
	std::string text = "{'name' : 'aron'}";
	std::string filename = "json1.txt";
	try {
		JsonParser parser(false, filename);
		const JsonItem* ds = parser.parse();
		std::string title = ds->getItem("glossary")->getItem("GlossDiv")->
			getItem("GlossList")->getItem("GlossEntry")->getItem("GlossDef")->getItem("GlossSeeAlso")->getItem(0)->getText();
		int number = ds->getItem("glossary")->getItem("age")->getInt();
		std::cout << title << std::endl;
		std::cout << "number: " << number << std::endl;
		std::string firstTitle = ds->getItem("glossary")->getItem("title")->getText();
		std::cout << "first title: " << firstTitle << std::endl;
	} catch (const char* message) {
		std::cout << "error: " << message << std::endl;
	}
	
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file




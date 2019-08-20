<h1>Simple JSON parse</h1>

# Introduction
Class project in the theory of computation class to design the grammar and develop a JSON parser.

# Language
C++

# Example
```c++
bool SHOW_LOGS = FALSE;
std::string json = {"glossary": {"age": 20.1e2, "title": "example\"s glossary","GlossDiv": {"title": "S","GlossList": {"GlossEntry": {"ID": "SGML","SortAs": "SGML","GlossTerm": "Standard Generalized Markup Language","Acronym": "SGML","Abbrev": "ISO 8879:1986","GlossDef": {"para": "A meta-markup language, used to create markup languages such as DocBook.","GlossSeeAlso": ["GML", "XML"]},"GlossSee": "markup"}}}}}
JsonParser parser(json, SHOW_LOGS);
const JsonItem* parsedJson = parser.parse();
int number = parsedJson->getItem("glossary")->getItem("age")->getInt();
std::string firstTitle = parsedJson->getItem("glossary")->getItem("title")->getText();
std::cout << "Number: " << number << std::endl;
std::cout << "Title: " << firstTitle << std::endl;
```

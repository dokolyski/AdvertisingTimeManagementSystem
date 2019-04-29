#pragma once
#include "Table.h"
class MovingList
{
	std::vector <std::vector <sf::String>> * elements;
	int first;
	Table * tab;
public:
	MovingList(Table *);
	void move(bool updown);
	void actualizeTable();
	void setStrings(std::vector <std::vector <sf::String>> _el);
	void push(std::vector <sf::String> _el);
	void clear();
	int size() { return this->elements->size(); };
	std::vector <std::vector <sf::String>> returnList() { return *elements; };
	void operator+(std::vector <sf::String> _el);
};


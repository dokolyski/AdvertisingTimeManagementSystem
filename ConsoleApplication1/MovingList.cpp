#include "pch.h"
#include "MovingList.h"


MovingList::MovingList(Table * _tab)
{
	first = 0;
	tab = _tab;
	elements = new std::vector <std::vector <sf::String>>;
}

void MovingList::push(std::vector <sf::String> _el)
{
	elements->push_back(_el);
}

void MovingList::setStrings(std::vector <std::vector <sf::String>> _el)
{
	first = 0;
	*elements = _el;
	actualizeTable();
}

void MovingList::move(bool updown)
{
	if (updown)
	{
		if (first > 0)
		{
			first--;
			actualizeTable();
		}		
	}
	else
	{
		if (first < int(elements->size() - tab->getSize()[0] + tab->returnHasHeaders()[0]) )
		{
			first++;
			actualizeTable();
		}
	}
}

void MovingList::actualizeTable()
{
	int * size = tab->getSize();
	int x = elements->size();

	int h0 = tab->returnHasHeaders()[0];
	int h1 = tab->returnHasHeaders()[1];
	for (int i=0; i < size[0]-h0; i++)
	{
		int y = 0;
		if(i<x)
			y = (*elements)[i].size();
		for (int j=0; j < size[1]-h1; j++)
		{
			if ((j < y)&&(i<x))
				tab->returnElement(i + h0, j + h1)->setString((*elements)[i+first][j]);
			else
				tab->returnElement(i + h0, j + h1)->setString("");
		}
	}
}

void MovingList::clear()
{
	elements->clear();
	tab->clear();
	first = 0;
}

void MovingList::operator+(std::vector <sf::String> _el)
{
	this->push(_el);
}
#pragma once
#include "Item.h"
#include <vector>
class Table : public Stuff
{
	std::vector <std::vector <Item*> * > * Cells;
	int RowsNumber, ColsNumber;
	bool singlyClicked;
	bool * hasHeaders;
public:
	Table(int _rowsNumber, int _columnsNumber, int ox, int oy, std::vector < std::vector <sf::String> > strings, int x, int y, bool _hRows, bool _hCols, Style * _HeaderStyle, Style * _CellsStyle, int maxLen, bool _numOnly, bool _sC = false, bool _clickable = true, bool _editable = true);
	void draw(sf::RenderWindow&);
	void cursorHover(int, int);
	Stuff * clicked(int, int);
	bool input(sf::Uint32);
	Item * returnElement(int, int);
	bool isChosen(int, int);
	void unselect();
	sf::String getString(int x, int y);
	int * getSize();
	std::vector<std::vector<sf::String>> getAllStrings();
	bool * returnHasHeaders() { return hasHeaders; };
	void clear();
	void setEditable(bool);
};
#include "pch.h"
#include "Table.h"

Table::Table(int _rowsNumber, int _columnsNumber, int ox, int oy, std::vector < std::vector <sf::String> > strings, int x, int y, bool _hRows, bool _hCols, Style * _HeaderStyle, Style * _CellsStyle,int _maxLen, bool _numOnly, bool _sC, bool _clickable, bool _editable)
{
	this->RowsNumber = _rowsNumber;
	this->ColsNumber = _columnsNumber;
	this->Cells = new std::vector < std::vector <Item*> * >(RowsNumber);
	for (int i = 0; i < RowsNumber; i++)
	{
		(*Cells)[i] = new std::vector <Item*>(ColsNumber);
		for (int j = 0; j < ColsNumber; j++)
		{
			if((_hRows)&&(j==0))
				(*(*Cells)[i])[j] = new Item(strings[i][j], ox + 1 + j * (x + 1), oy + 1 + i * (y + 1), x, y, false, false, _HeaderStyle, _maxLen, _numOnly);
			else if((_hCols)&&(i==0))
				(*(*Cells)[i])[j] = new Item(strings[i][j], ox + 1 + j * (x + 1), oy + 1 + i * (y + 1), x, y, false, false, _HeaderStyle, _maxLen, _numOnly);
			else
				(*(*Cells)[i])[j] = new Item(strings[i][j], ox + 1 + j * (x + 1), oy + 1 + i * (y + 1), x, y, _clickable, _editable, _CellsStyle, _maxLen, _numOnly);
		}
	}
	this->Visible = false;
	this->singlyClicked = _sC;
	hasHeaders = new bool[2];
	hasHeaders[0] = _hCols;
	hasHeaders[1] = _hRows;
}

void Table::draw(sf::RenderWindow &window)
{
	if (Visible)
	{
		for (int i = 0; i < RowsNumber; i++)
		{
			for (int j = 0; j < ColsNumber; j++)
				(*(*Cells)[i])[j]->draw(window);
		}
	}
}

void Table::cursorHover(int x, int y)
{
	if (this->Visible)
	{
		for (int i = 0; i < RowsNumber; i++)
		{
			for (int j = 0; j < ColsNumber; j++)
				(*(*Cells)[i])[j]->cursorHover(x, y);
		}
	}
}

Stuff * Table::clicked(int x, int y)
{
	if (this->Visible)
	{
		for (int i = 0; i < RowsNumber; i++)
		{
			for (int j = 0; j < ColsNumber; j++)
			{
				if ((*(*Cells)[i])[j]->clicked(x, y))
				{
					if (this->singlyClicked)
					{
						if ((*(*Cells)[i])[j]->isChosen())
						{
							unselect();
							(*(*Cells)[i])[j]->select();
						}
						return this;
					}
					return (*(*Cells)[i])[j];
				}
			}
		}
	}
	return NULL;
}

bool Table::input(sf::Uint32 c)
{
	bool change = false;
	if (this->Visible)
	{
		for (int i = 0; i < RowsNumber; i++)
		{
			for (int j = 0; j < ColsNumber; j++)
			{
				if ((*(*Cells)[i])[j]->input(c))
					change = true;
			}
		}
	}
	return change;
}

Item * Table::returnElement(int x, int y)
{
	return (*(*Cells)[x])[y];
}

bool Table::isChosen(int x, int y)
{
	return (*(*Cells)[x])[y]->isChosen();
}

void Table::unselect()
{
	for (int i = 0; i < RowsNumber; i++)
	{
		for (int j = 0; j < ColsNumber; j++)
			(*(*Cells)[i])[j]->unselect();
	}
}

sf::String Table::getString(int x, int y)
{
	return (*(*Cells)[x])[y]->getString();
}

int * Table::getSize()
{
	int * size = new int[2];
	size[0] = this->Cells->size();
	size[1] = (*Cells)[0]->size();
	return size;
}

std::vector<std::vector<sf::String>> Table::getAllStrings()
{
	std::vector<std::vector<sf::String>> table;
	for (int i = 1; i < Cells->size(); i++)
	{
		std::vector<sf::String> str;
		for (int j = 1; j < (*Cells)[i]->size(); j++)
			str.push_back((*(*Cells)[i])[j]->getString());
		table.push_back(str);
	}
	return table;
}

void Table::clear()
{
	for (int i = hasHeaders[0]; i <this->getSize()[0] ; i++)
	{
		for (int j = hasHeaders[1]; j < this->getSize()[1] ; j++)
			this->returnElement(i, j)->setString("");
	}
}

void Table::setEditable(bool edt)
{
	this->Clickable = edt;
	this->Editable = edt;
	for (int i = hasHeaders[0]; i < this->getSize()[0]; i++)
	{
		for (int j = hasHeaders[1]; j < this->getSize()[1]; j++)
			this->returnElement(i,j)->setEditable(edt);
	}
}
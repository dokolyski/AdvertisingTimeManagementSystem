#pragma once
#include "pch.h"
#include "Item.h"
#include <iostream>

Item::Item(sf::String _Text, int ox, int oy, int x, int y, bool click, bool edit, Style * style, int _maxL, bool _numOnly)
{
	this->Text = new sf::Text(_Text, style->Font, int(2.5 * y / 3));
	this->Text->setPosition(ox + x * 0.03, oy );
	this->Text->setFillColor(style->TextColor);
	this->Rect = new sf::RectangleShape(sf::Vector2f(x, y));
	this->Rect->setPosition(sf::Vector2f(ox, oy));
	this->Rect->setFillColor(style->BackgroundColor);
	this->Rect->setOutlineThickness(1);
	this->Rect->setOutlineColor(style->BordersColor);
	this->Clickable = click;
	this->Editable = edit;
	this->Visible = true;
	this->ItemStyle = style;
	this->isCursorHover = false;
	this->isSelected = false;
	this->maxLength = _maxL;
	this->numbersOnly = _numOnly;
}

void Item::draw(sf::RenderWindow &window)
{
	if (Visible)
	{
		if (this->isSelected)
			this->Rect->setFillColor(this->ItemStyle->SelectingColor);
		else if (this->isCursorHover)
			this->Rect->setFillColor(this->ItemStyle->CursorHoveringColor);
		else
			this->Rect->setFillColor(this->ItemStyle->BackgroundColor);
		window.draw(*Rect);
		window.draw(*Text);
	}
}

void Item::cursorHover(int cursorX, int cursorY)
{
	if ((this->Visible) && (this->Clickable))
	{
		int x0 = this->Rect->getPosition().x, x2 = x0 + this->Rect->getSize().x;
		int y0 = this->Rect->getPosition().y, y2 = y0 + this->Rect->getSize().y;
		if ((cursorX > x0) && (cursorX < x2) && (cursorY > y0) && (cursorY < y2))
			this->isCursorHover = true;
		else
			this->isCursorHover = false;
	}
}

Stuff * Item::clicked(int cursorX, int cursorY)
{
	if ((this->Visible) && (this->Clickable))
	{
		int x0 = this->Rect->getPosition().x, x2 = x0 + this->Rect->getSize().x;
		int y0 = this->Rect->getPosition().y, y2 = y0 + this->Rect->getSize().y;
		if ((cursorX > x0) && (cursorX < x2) && (cursorY > y0) && (cursorY < y2))
		{
			if (this->isSelected)
				this->isSelected = false;	
			else
				this->isSelected = true;
			return this;
		}
	}
	return NULL;
}

bool Item::input(sf::Uint32 c)
{
	if ((this->isSelected) && (this->Editable) && (this->Clickable) && (this->Visible))
	{
		if (c == 8)
		{
			std::string str = Text->getString();
			int nm = str.length();
			if (nm)
			{
				sf::String str= this->Text->getString();
				str.erase(nm - 1, 1);
				this->Text->setString(str);
				return true;
			}
		}
		else
		{
			if (this->Text->getString().getSize() != this->maxLength)
			{
				if (((this->numbersOnly) && (c >= 48) && (c <= 57)) || (!this->numbersOnly))
				{
					this->Text->setString(this->Text->getString() + static_cast<char>(c));
					return true;
				}
					
			}
		}
	}
	return false;
}

void Item::setString(sf::String str)
{
	Text->setString(str);
}

void Item::setString(int str)
{
	Text->setString(std::to_string(str));
}

void Item::unselect()
{
	this->isSelected = false;
}

void Item::select()
{
	this->isSelected = true;
}

bool Item::isChosen(int x, int y)
{
	return this->isSelected;
}

sf::String Item::getString(int x, int y)
{
	return this->Text->getString();
}

Stuff * Item::returnElement(int x , int y)
{
	return this;
}
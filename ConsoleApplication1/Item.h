#pragma once
#include<string>
#include<SFML/Graphics.hpp>
#include "Stuff.h"
#include "Style.h"

class Item : public Stuff
{
public:
	Item(sf::String _Text, int ox, int oy, int x, int y, bool click, bool edit, Style * style, int _maxL, bool _numOnly);
	void draw(sf::RenderWindow&);
	void cursorHover(int x, int y);
	Stuff * clicked(int, int);
	bool input(sf::Uint32);
	sf::String getString(int = 0, int = 0);
	void setString(sf::String);
	void setString(int);
	void select();
	void unselect();
	bool isChosen(int = 0, int = 0);
	Stuff * returnElement(int = 0, int = 0);
private:
	sf::Text* Text;
	sf::Font* Font;
	sf::RectangleShape* Rect;
	Style* ItemStyle;
	int maxLength;
	bool numbersOnly;
	bool isCursorHover, isSelected;
};


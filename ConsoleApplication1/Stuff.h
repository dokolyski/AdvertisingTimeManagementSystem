#pragma once
#include <SFML/Graphics.hpp>

class Stuff 
{
protected:
	bool Visible;
	bool Clickable;
	bool Editable;
public:
	void doVisible();
	void doUnvisible();
	bool isVisible();
	void setEditable(bool x) { Clickable = x; Editable = x; }
	virtual bool isChosen(int x = 0, int y = 0) = 0;
	virtual Stuff * returnElement(int x = 0, int y = 0) = 0;
	virtual void draw(sf::RenderWindow&) = 0;
	virtual void cursorHover(int, int) = 0;
	virtual Stuff * clicked(int, int) = 0;
	virtual bool input(sf::Uint32) = 0;
	virtual void unselect() = 0;
	virtual sf::String getString(int x = 0, int y = 0) = 0;
};
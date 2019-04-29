#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Table.h"
#include "Style.h"
#include "StuffGroup.h"
#include "FilesManager.h"

class Form
{
private:
	std::vector <Stuff*> Content;
	sf::RectangleShape * Background;
	bool Visible;
	sf::RenderWindow * Window;

public:
	void windowService();
	bool hasFocus();
	Form(int w, int h, sf::String label, FilesManager * _fm, bool TitleBar = true);
	void newObject(Stuff*);
	void draw();
	void cursorHover();
	std::vector <Stuff*> click();
	std::vector <Stuff*> input(sf::Uint32);
	virtual void afterClick(Stuff *) = 0;
	virtual void afterInput(Stuff *) = 0;
	FilesManager * fm;
	bool isVisible();
	void setVisible(bool);
	virtual int getValue(int x, int y) = 0;
	virtual void afterVisible() = 0;
	virtual void afterUnvisible() = 0;
};
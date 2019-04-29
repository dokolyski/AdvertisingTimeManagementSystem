#pragma once
#include "Form.h"

class CzasForm :public Form
{
	Table * availableTime;
	Style * style;
	Style * style2;
	Style * style3;
public:
	CzasForm(int w, int h, sf::String label, FilesManager * _fm);
	void afterClick(Stuff *) {};
	void afterInput(Stuff * element) {};
	int getValue(int x, int y);
	void afterVisible();
	void afterUnvisible() {};
};

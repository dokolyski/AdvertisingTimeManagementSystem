#pragma once
#include "Form.h"

class CennikForm:public Form
{
	Table * cennik;
	Style * style;
	Style * style2;
	Style * style3;
public:
	CennikForm(int w, int h, sf::String label, FilesManager * _fm);
	void afterClick(Stuff *){};
	void afterInput(Stuff * element) {};
	int getValue(int x, int y);
	void afterVisible();
	void afterUnvisible() {};
};


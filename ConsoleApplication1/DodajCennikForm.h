#pragma once
#include "Form.h"

class DodajCennikForm: public Form
{
	Table * nazwa;
	Table * wart;
	Item * zatwierdz;
	Item * anuluj;
	StuffGroup * pola;
	Style * style;
	Style * style2;
	Style * style3;
public:
	DodajCennikForm(int w, int h, sf::String label, FilesManager * _fm);
	Form * nadawForm;
	void afterClick(Stuff *);
	void afterInput(Stuff * element) {};
	int getValue(int x, int y) { return 0; };
	void afterVisible();
	void afterUnvisible() {};
};


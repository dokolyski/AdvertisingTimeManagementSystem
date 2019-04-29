#pragma once
#include "Form.h"

class ZatwierdzForm: public Form
{
	Style * style2;
	Style * style3;
	Item * napis;
	Item * ostrz;
	Item * tak;
	Item * nie;
public:
	ZatwierdzForm(int w, int h, sf::String label, FilesManager * _fm);
	void afterClick(Stuff *);
	void afterInput(Stuff * element) {};
	int getValue(int x, int y);
	void afterVisible();
	void afterUnvisible();
	Form * reklForm;
};


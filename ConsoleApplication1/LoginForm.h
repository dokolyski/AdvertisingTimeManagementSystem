#pragma once
#include "Form.h"
class LoginForm: public Form
{
	Table * login;
	Table * reg;
	Table * wybor;
	Item * loginButton;
	Item * regButton;
	StuffGroup * loginGroup;
	StuffGroup * regGroup;
	Style * style;
	Style * style2;
	Style * style3;
public:
	LoginForm(int w, int h, sf::String label, FilesManager * _fm);
	void afterClick(Stuff *);
	void afterInput(Stuff * element) {};
	int getValue(int x, int y) { return 0; };
	Form * rForm;
	Form * nForm;
	//to close
	Form * cennikF;
	Form * czasDostF;
	//
	void afterVisible();
	void afterUnvisible() {};
};


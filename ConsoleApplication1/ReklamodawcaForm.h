#pragma once
#include "Form.h"
#include "MovingList.h"
#include "AutoCompletion.h"

class ReklamodawcaForm: public Form
{
	Table * menu;
	Table * tab;
	Table * tab2;
	Table * budzet;
	Table * autoPrzydz;
	Table * wyniki;
	Table * tabZamowienien;
	Table * tabWyb;
	Table * updown;
	Table * updown2;
	Table * mnozniki;
	Table * ostrzezenia;
	Item * zatwierdz;
	Item * wyczyscT;
	Item * odznaczT;
	StuffGroup * group1;
	StuffGroup * group2;
	MovingList * mList1;
	MovingList * mList2;
	Style * style;
	Style * style2;
	Style * style3;
	float timeSum();
	float priceSum();
public:
	ReklamodawcaForm(int w, int h, sf::String label, FilesManager * _fm);
	void afterClick(Stuff * element);
	void afterInput(Stuff * element);
	int getValue(int x, int y);
	Form * lForm;
	Form * cennik;
	Form * czasDost;
	Form * zatwForm;
	void afterVisible();
	void afterUnvisible() {};
};


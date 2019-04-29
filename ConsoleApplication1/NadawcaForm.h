#pragma once
#include "Form.h"
#include "MovingList.h"
class NadawcaForm: public Form
{
	Item * newC;
	Item * setAsActualC;
	Item * saveC;
	Item * editC;
	Item * odsw;
	Item * zatwU;
	Item * odrzU;
	Item * zakU;
	Item * usunR;
	Table * menu;
	Table * tabCennikow;
	Table * updownC;
	Table * tabC;
	Table * actualC;
	Table * rodzU;
	Table * listaU;
	Table * wybU;
	Table * updownU;
	Table * tabU;
	Table * tabP;
	Table * listaP;
	Table * updownP;
	Table * listaR;
	Table * updownR;
	Table * listaUmowyR;
	Table * updown2R;
	Table * tabR;
	MovingList * mListC;
	MovingList * mListU;
	MovingList * mListP;
	MovingList * mListR;
	MovingList * mList2R;
	StuffGroup * groupC;
	StuffGroup * groupU;
	StuffGroup * groupP;
	StuffGroup * groupR;
	Style * style;
	Style * style2;
	Style * style3;
public:
	NadawcaForm(int w, int h, sf::String label, FilesManager * _fm);
	void afterClick(Stuff * element);
	void afterInput(Stuff * element);
	int getValue(int x, int y) { return 0; };
	Form * dodajForm;
	Form * lForm;
	void afterVisible();
	void afterUnvisible() {};
};


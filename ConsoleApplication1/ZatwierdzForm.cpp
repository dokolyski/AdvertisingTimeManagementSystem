#include "pch.h"
#include "ZatwierdzForm.h"

ZatwierdzForm::ZatwierdzForm(int w, int h, sf::String label, FilesManager * _fm) : Form(w, h, label, _fm, 0)
{
	sf::Font font;
	font.loadFromFile("arial.ttf");
	this->style2 = new Style(sf::Color(255, 0, 0), sf::Color(0, 0, 0), sf::Color(255, 255, 255), sf::Color(255, 0, 0), sf::Color(255, 0, 0), font);
	this->style3 = new Style(sf::Color(236, 159, 174), sf::Color(0, 0, 0), sf::Color(0, 0, 0), sf::Color(250, 105, 163), sf::Color(138, 60, 198), font);

	napis = new Item(L"Czy napewno chcesz wys³aæ zamówienie?", 15, 15, 315, 20, false, 0, style3, 0, 0);
	ostrz = new Item("", 15, 40, 315, 20, false, 0, style2, 0, 0);
	ostrz->doUnvisible();
	tak = new Item("Tak", 115, 80, 40, 20, 1, 0, style3, 0, 0);
	nie = new Item("Nie", 190, 80, 40, 20, 1, 0, style3, 0, 0);

	newObject(napis);
	newObject(ostrz);
	newObject(tak);
	newObject(nie);
}

void ZatwierdzForm::afterClick(Stuff * element)
{
	setVisible(false);
	reklForm->setVisible(true);
}

void ZatwierdzForm::afterVisible()
{
	int l = reklForm->getValue(0,0);
	if (l)
	{
		ostrz->setString(L"Liczba wystêpuj¹cych ostrze¿eñ: " + to_wstring(l));
		ostrz->doVisible();
	}
}

void ZatwierdzForm::afterUnvisible()
{
	ostrz->doUnvisible();
}

int ZatwierdzForm::getValue(int x=0, int y = 0)
{
	if (tak->isChosen())
	{
		tak->unselect();
		return 1;
	}
	else if (nie->isChosen())
	{
		nie->unselect();
		return 0;
	}
	else
		return -1;
}
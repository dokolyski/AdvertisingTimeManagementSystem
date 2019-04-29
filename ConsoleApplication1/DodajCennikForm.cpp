#include "pch.h"
#include "DodajCennikForm.h"

DodajCennikForm::DodajCennikForm(int w, int h, sf::String label, FilesManager * _fm) : Form(w, h, label, _fm, 0)
{
	sf::Font font;
	font.loadFromFile("arial.ttf");
	this->style = new Style(sf::Color(148, 221, 255), sf::Color(0, 0, 0), sf::Color(0, 0, 0), sf::Color(148, 148, 255), sf::Color(138, 60, 198), font);
	this->style2 = new Style(sf::Color(123, 58, 74), sf::Color(0, 0, 0), sf::Color(255, 255, 255), sf::Color(148, 148, 255), sf::Color(138, 60, 198), font);
	this->style3 = new Style(sf::Color(236, 159, 174), sf::Color(0, 0, 0), sf::Color(0, 0, 0), sf::Color(250, 105, 163), sf::Color(138, 60, 198), font);

	vector <vector <sf::String>> tab(1);
	tab[0] = { "Nazwa","" };

	this->nazwa = new Table(1, 2, 15, 15, tab, 125, 20, true, false, style2, style3, 12, 0, 1);
	nazwa->doVisible();

	tab[0] = { L"Wart. domyúlna","" };

	this->wart = new Table(1, 2, 15, 40, tab, 125, 20, true, false, style2, style3, 6, 1, 1);
	wart->doVisible();

	this->anuluj = new Item("Anuluj", 130, 75, 90, 20, true, false, style3, 0, 0);
	this->zatwierdz = new Item(L"Zatwierdü", 35, 75, 90, 20, true, false, style3, 0, 0);

	vector <Stuff*> vecgroup1 = { nazwa, wart };

	pola = new StuffGroup(vecgroup1);

	newObject(nazwa);
	newObject(wart);
	newObject(anuluj);
	newObject(zatwierdz);
}

void DodajCennikForm::afterClick(Stuff * element)
{
	pola->unselectOther(element);
	if (element == anuluj)
	{
		zatwierdz->unselect();
		anuluj->unselect();
		this->setVisible(false);
		this->nadawForm->setVisible(true);
	}
	else if (element == zatwierdz)
	{
		zatwierdz->unselect();
		anuluj->unselect();

		int dw = 0;
		if (wart->getString(0, 1) != "")
			dw = stoi((string)wart->getString(0, 1));

		vector <vector <sf::String>> sendedtab(48);
		for (int i = 0; i < 48; i++)
		{
			sendedtab[i].resize(7,to_string(dw));
		}
		fm->tableToFile("cenniki/" + nazwa->getString(0, 1)+".txt",sendedtab);
		fm->addRecord(fm->PriceLists, "cenniki/" + nazwa->getString(0, 1) + ".txt");

		this->setVisible(false);
		this->nadawForm->setVisible(true);
	}
}

void DodajCennikForm::afterVisible()
{
	nazwa->clear();
	wart->clear();
	nazwa->unselect();
	wart->unselect();
}
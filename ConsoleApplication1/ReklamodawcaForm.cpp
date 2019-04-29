#include "pch.h"
#include "ReklamodawcaForm.h"

ReklamodawcaForm::ReklamodawcaForm(int w, int h, sf::String label, FilesManager * _fm) : Form(w, h, label, _fm)
{
	sf::Font font;
	font.loadFromFile("arial.ttf");
	this->style = new Style(sf::Color(148, 221, 255), sf::Color(0, 0, 0), sf::Color(0, 0, 0), sf::Color(148, 148, 255), sf::Color(138, 60, 198),font);
	this->style2 = new Style(sf::Color(123, 58, 74), sf::Color(0, 0, 0), sf::Color(255, 255, 255), sf::Color(148, 148, 255), sf::Color(138, 60, 198),font);
	this->style3 = new Style(sf::Color(236, 159, 174), sf::Color(0, 0, 0), sf::Color(0, 0, 0), sf::Color(250, 105, 163), sf::Color(138, 60, 198),font);

	///////////////////////////////////////////////MENU
	std::vector <std::vector <sf::String>> sMenu(1);
	sMenu[0] = { L"Wyœwietl cennik", L"Dostêpny czas", L"Nowe zamówienie", L"Twoje zamówienia", L"Wyloguj" };

	this->menu = new Table(1, 5, 0, 0, sMenu, 150, 20, false, false, NULL, style, 20, false, true, true, false);

	this->menu->doVisible();

	///////////////////////////////////////////////Nowe zamówienie
	std::vector <std::vector <sf::String>> sTab(49);
	sTab[0] = { "", L"poniedzia³ek", "wtorek", L"œroda", "czwartek", L"pi¹tek", "sobota", "niedziela" };

	for (int i = 1; i < 49; i++)
	{
		sTab[i].resize(8, "");
		sTab[i][0] = std::to_string((i - 1) / 20) + std::to_string(((i - 1) / 2) % 10) + ":" + std::to_string(3 * ((i - 1) % 2)) + "0 - " + std::to_string((i - 1) / 20) + std::to_string(((i - 1) / 2) % 10) + ":" + std::to_string(2 + 3 * (((i - 1) % 2))) + "9";
	}

	this->tab = new Table(49, 8, 230, 40, sTab, 70, 12, true, true, style2, style3, 3, true);

	std::vector <std::vector <sf::String>> sBud(1);
	sBud[0] = { L"Bud¿et","" };

	this->budzet = new Table(1, 2, 15, 40, sBud, 100, 20, true, false, style2, style3, 7, true);

	std::vector <std::vector <sf::String>> sAuto(3);
	sAuto[0] = { L"Przydzia³ automatyczny" };
	sAuto[1] = { L"Najwiêcej czasu" };
	sAuto[2] = { L"Najdro¿ej" };

	this->autoPrzydz = new Table(3, 1, 15, 70, sAuto, 201, 20, false, true, style2, style3, 20, false, true, true, false);

	std::vector <std::vector <sf::String>> sWyniki(2);
	sWyniki[0] = { "Koszt", "" };
	sWyniki[1] = { "Czas", "" };

	this->wyniki = new Table(2, 2, 15, 145, sWyniki, 100, 20, false, false, style2, style3, 20, false, false, false, false);

	this->zatwierdz = new Item(L"ZatwierdŸ", 15, 200, 201, 20, true, false, style3, 20, false);

	std::vector <std::vector <sf::String>> sMn(14);
	for (int i = 0; i < 14; i++)
		sMn[i].resize(2);
	sMn[0] = {L"D³ugoœæ", L"Mno¿nik"};

	std::vector <std::vector <sf::String>> wartMn = fm->loadTable(fm->Multipliers);

	for (int i = 1; i < 14; i++)
		sMn[i] = wartMn[i - 1];

	this->mnozniki = new Table(14, 2, 15, 383, sMn, 100, 20, false, true, style2, style3, 20, false, false, false, false);

	std::vector <std::vector <sf::String>> sOst(7);
	for (int i = 0; i < 7; i++)
		sOst[i].resize(1);

	sOst[0] = { L"Ostrze¿enia" };

	this->ostrzezenia = new Table(7, 1, 810, 40, sOst, 165, 15, false, true, style2, style3, 20, false, false, false, false);

	this->mList2 = new MovingList(ostrzezenia);

	std::vector <std::vector <sf::String>> sUD2(2);
	sUD2[0] = { " /\\" };
	sUD2[1] = { " \\/" };

	this->updown2 = new Table(2, 1, 976, 80, sUD2, 15, 15, false, false, style2, style3, 20, false, true, true, false);

	this->wyczyscT = new Item(L"Wyczyœæ wszystko",15,345,201,20,true,false,style3,0,0);
	wyczyscT->doUnvisible();
	this->odznaczT = new Item(L"Odznacz wszystko", 15, 320, 201, 20, true, false, style3, 0, 0);
	odznaczT->doUnvisible();
	/////////////////
	std::vector <Stuff*> group1Vec = {this->tab,this->zatwierdz,this->autoPrzydz,this->budzet,this->wyniki, mnozniki, ostrzezenia, updown2, wyczyscT, odznaczT};
	this->group1 = new StuffGroup(group1Vec);
	/////////////////
	this->zatwierdz->doUnvisible();


	/////////////////////////////////////////////////lista zamówieñ
	std::vector <std::vector <sf::String>> sLista(11);
	for (int i = 0; i < 11; i++)
		sLista[i].resize(3);
	sLista[0] = { L"Nr zamówienia", "Stan", "Kwota" };

	this->tabZamowienien = new Table(11, 3, 85, 40, sLista, 120, 20, false, true, style2, style3, 20, false, false, false, false);

	this->mList1 = new MovingList(tabZamowienien);

	std::vector <std::vector <sf::String>> sWZ(11);
	for (int i = 0; i < 11; i++)
		sWZ[i].resize(1);
	sWZ[0] = {"Wybierz"};

	this->tabWyb = new Table(11, 1, 15, 40, sWZ, 62, 20, false, true, style2, style3, 20, false, true, true, false);

	std::vector <std::vector <sf::String>> sUD(2);
	sUD[0] = { " /\\" };
	sUD[1] = { " \\/" };

	this->updown = new Table(2, 1, 454, 40, sUD, 20, 20, false, false, style2, style3, 20, false, true, true, false);

	std::vector <std::vector <sf::String>> sTab2(49);

	sTab2[0] = { "", L"poniedzia³ek", "wtorek", L"œroda", "czwartek", L"pi¹tek", "sobota", "niedziela" };

	for (int i = 1; i < 49; i++)
	{
		sTab2[i].resize(8, "");
		sTab2[i][0] = std::to_string((i - 1) / 20) + std::to_string(((i - 1) / 2) % 10) + ":" + std::to_string(3 * ((i - 1) % 2)) + "0 - " + std::to_string((i - 1) / 20) + std::to_string(((i - 1) / 2) % 10) + ":" + std::to_string(2 + 3 * (((i - 1) % 2))) + "9";
	}

	this->tab2 = new Table(49, 8, 500, 40, sTab2, 58, 11, true, true, style2, style3, 4, true, false, false, false);

	////////////////////////
	std::vector <Stuff*> group2Vec = { this->tabZamowienien,this->tabWyb,this->updown, tab2};
	this->group2 = new StuffGroup(group2Vec);

	////////////////////////
	this->newObject(menu);
	this->newObject(tab);
	this->newObject(budzet);
	this->newObject(autoPrzydz);
	this->newObject(wyniki);
	this->newObject(zatwierdz);
	this->newObject(tabZamowienien);
	this->newObject(tabWyb);
	this->newObject(updown);
	this->newObject(tab2);
	this->newObject(mnozniki);
	this->newObject(ostrzezenia);
	this->newObject(updown2);
	this->newObject(odznaczT);
	newObject(wyczyscT);
}

void ReklamodawcaForm::afterClick(Stuff * element)
{
	if (this->menu == element)
	{
		this->group1->doUnvisible();
		this->group2->doUnvisible();

		if (element->isChosen(0, 2))
			this->group1->doVisible();
			
		else if (element->isChosen(0, 0))
			this->cennik->setVisible(true);

		else if (element->isChosen(0, 4))
		{
			this->setVisible(false);
			this->group1->unselectAll();
			this->lForm->setVisible(true);
		}

		else if (element->isChosen(0, 3))
		{
			this->group2->doVisible();
			tab2->clear();
			tabWyb->unselect();
			vector <vector <sf::String>> loadedList = fm->loadTable(fm->Contracts);
			vector <vector <sf::String>> listaKontraktow;
			for (int i = 0; i < loadedList.size(); i++)
			{
				if (loadedList[i][1] == fm->ActualUser)
				{
					listaKontraktow.push_back(loadedList[i]);
					listaKontraktow[listaKontraktow.size()-1].erase(listaKontraktow[listaKontraktow.size() - 1].begin() + 1);
				}
			}
			mList1->setStrings(listaKontraktow);
		}
			
		else if (element->isChosen(0, 1))
			this->czasDost->setVisible(true);
	}

	else if(menu->isChosen(0, 3))
	{
		if (updown == element)
		{
			if (updown->isChosen(0, 0))
			{
				mList1->move(1);
				tab2->clear();
				tabWyb->unselect();
			}
			else if (updown->isChosen(1, 0))
			{
				mList1->move(0);
				tab2->clear();
				tabWyb->unselect();
			}
			updown->unselect();
		}
		else if (tabWyb == element)
		{
			tab2->clear();

			for (int i = 1; i < tabWyb->getSize()[0]; i++)
			{
				if (tabWyb->isChosen(i, 0))
				{
					std::string nr = tabZamowienien->getString(i, 0);
					if (nr != "")
					{
						vector <vector <sf::String>> loadedTab = fm->loadTable("kontrakty/" + nr + ".txt");
						for (int i = 0; i < loadedTab.size(); i++)
						{
							int wart[3];
							for (int j = 0; j < loadedTab[i].size(); j++)
							{
								wart[j] = stoi((string)loadedTab[i][j]);
							}
							tab2->returnElement(wart[0]+1, wart[1]+1)->setString(wart[2]);
						}
					}
					break;
				}
			}
		}
	}

	else if (menu->isChosen(0, 2))
	{
		if (zatwierdz == element)
		{
			if ((wyniki->getString(0, 1) != "") && (wyniki->getString(0, 1) != "0"))
			{
				this->setVisible(false);
				this->zatwForm->setVisible(true);
			}
			zatwierdz->unselect();
		}
		else if (updown2 == element)
		{
			if (updown2->isChosen(0, 0))
			{
				mList2->move(1);
			}
			else if (updown2->isChosen(1, 0))
			{
				mList2->move(0);
			}
			updown2->unselect();
		}
		else if (odznaczT == element)
		{
			odznaczT->unselect();
			tab->unselect();
		}
		else if (wyczyscT == element)
		{
			wyczyscT->unselect();
			tab->clear();
			mList2->clear();
			this->wyniki->returnElement(1, 1)->setString(timeSum());
			this->wyniki->returnElement(0, 1)->setString(priceSum());
		}
		else if (autoPrzydz == element)
		{
			if (budzet->getString(0,1) != "")
			{
				AutoCompletion au(fm->loadTable(fm->ActualPriceList), fm->loadTable(fm->AvailableTime), stoi((string)budzet->getString(0, 1)), tab);
				tab->clear();
				if (autoPrzydz->isChosen(1, 0))					
					au.calculate(1);
				else if (autoPrzydz->isChosen(2, 0))
					au.calculate(0);
				mList2->clear();
				this->wyniki->returnElement(1, 1)->setString(timeSum());
				this->wyniki->returnElement(0, 1)->setString(priceSum());
			}
			autoPrzydz->unselect();
		}
	}
}

void ReklamodawcaForm::afterInput(Stuff * element)
{
	if ((element == tab)||(element == budzet))
	{
		this->wyniki->returnElement(1, 1)->setString(timeSum());
		this->wyniki->returnElement(0, 1)->setString(priceSum());

		mList2->clear();
		std::vector<std::vector<sf::String>> loadCzas = fm->loadTable(fm->AvailableTime);

		if ((budzet->getString(0, 1) != "")&&(wyniki->returnElement(0, 1)->getString() != ""))
		{
			if (stoi((string)this->wyniki->returnElement(0, 1)->getString()) > stoi((string)budzet->getString(0, 1)))
			{
				std::vector<sf::String> record;
				record.push_back(L"Przekroczony bud¿et");
				mList2->push(record);
			}
		}

		for (int i = 1; i < tab->getSize()[0]; i++)
		{
			for (int j = 1; j < tab->getSize()[1]; j++)
			{
				if (tab->getString(i, j) != "")
				{
					if (stoi((string)tab->getString(i, j)) > stoi((string)loadCzas[i - 1][j - 1]))
					{
						std::vector<sf::String> record;
						record.push_back(tab->getString(0,j).substring(0,2) + " " + tab->getString(i,0) + " dost.cz." + loadCzas[i - 1][j - 1]);
						mList2->push(record);
					}
				}
			}
		}
		mList2->actualizeTable();
	}
}

float ReklamodawcaForm::timeSum()
{
	float sum = 0;
	int * size = tab->getSize();
	for (int i = 1; i < size[0]; i++)
	{
		for (int j = 1; j < size[1]; j++) {
			std::string str = tab->getString(i, j);
			if(str!="")
				sum += stof(str);
		}
			
	}
	return sum;
}

float ReklamodawcaForm::priceSum()
{
	float sum = 0;
	int * size = tab->getSize();
	for (int i = 1; i < size[0]; i++)
	{
		for (int j = 1; j < size[1]; j++) {
			std::string str = tab->getString(i, j);
			if (str != "")
				sum += costCalculate(stof(str),cennik->getValue(i,j));
		}

	}
	return sum;
}

void ReklamodawcaForm::afterVisible()
{
	int zm = zatwForm->getValue(0,0);
	if (zm == -1)
	{
		group1->unselectAll();
		group2->unselectAll();
		tab->clear();
		budzet->clear();
		wyniki->returnElement(0, 1)->setString("");
		wyniki->returnElement(1, 1)->setString("");
	}
	else if (zm == 1)
	{
		fm->sendNewContract(tab->getAllStrings(), stoi((string)wyniki->getString(0, 1)));
		group1->unselectAll();
		tab->clear();
		budzet->clear();
		wyniki->returnElement(0, 1)->setString("");
		wyniki->returnElement(1, 1)->setString("");
		mList2->clear();
	}
}

int ReklamodawcaForm::getValue(int x, int y)
{
	return mList2->size();
}
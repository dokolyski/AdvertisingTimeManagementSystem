#include "pch.h"
#include "NadawcaForm.h"

NadawcaForm::NadawcaForm(int w, int h, sf::String label, FilesManager * _fm): Form(w, h, label, _fm)
{
	sf::Font font;
	font.loadFromFile("arial.ttf");
	this->style = new Style(sf::Color(148, 221, 255), sf::Color(0, 0, 0), sf::Color(0, 0, 0), sf::Color(148, 148, 255), sf::Color(138, 60, 198), font);
	this->style2 = new Style(sf::Color(123, 58, 74), sf::Color(0, 0, 0), sf::Color(255, 255, 255), sf::Color(148, 148, 255), sf::Color(138, 60, 198), font);
	this->style3 = new Style(sf::Color(236, 159, 174), sf::Color(0, 0, 0), sf::Color(0, 0, 0), sf::Color(250, 105, 163), sf::Color(138, 60, 198), font);

	///////////////////////////////////////////////MENU
	std::vector <std::vector <sf::String>> sMenu(1);
	sMenu[0] = { L"Cenniki", L"Reklamodawcy", L"Plan reklamowy", L"Umowy", L"Wyloguj" };

	this->menu = new Table(1, 5, 0, 0, sMenu, 150, 20, false, false, NULL, style, 20, false, true, true, false);

	this->menu->doVisible();
	/////////////////////////////////////////////////Cenniki
	std::vector <std::vector <sf::String>> sLista(6);
	for (int i = 0; i < 6; i++)
		sLista[i].resize(1);
	sLista[0] = { L"Cenniki" };

	this->tabCennikow = new Table(6, 1, 15, 90, sLista, 200, 20, false, true, style2, style3, 20, false, true, true, false);

	this->mListC = new MovingList(tabCennikow);

	std::vector <std::vector <sf::String>> sUD(2);
	sUD[0] = { " /\\" };
	sUD[1] = { " \\/" };

	this->updownC = new Table(2, 1, 216, 142, sUD, 20, 20, false, false, style2, style3, 20, false, true, true, false);

	std::vector <std::vector <sf::String>> sTab2(49);
	sTab2[0] = { "", L"poniedzia³ek", "wtorek", L"œroda", "czwartek", L"pi¹tek", "sobota", "niedziela" };

	for (int i = 1; i < 49; i++)
	{
		sTab2[i].resize(8, "");
		sTab2[i][0] = std::to_string((i - 1) / 20) + std::to_string(((i - 1) / 2) % 10) + ":" + std::to_string(3 * ((i - 1) % 2)) + "0 - " + std::to_string((i - 1) / 20) + std::to_string(((i - 1) / 2) % 10) + ":" + std::to_string(2 + 3 * (((i - 1) % 2))) + "9";
	}

	this->tabC = new Table(49, 8, 500, 40, sTab2, 58, 11, true, true, style2, style3, 4, true, false, false, false);

	std::vector <std::vector <sf::String>> sAC(2);
	sAC[0] = { "Aktualny cennik" };
	sAC[1].resize(1, "");
	this->actualC = new Table(2,1,15,40,sAC,200,20,false,true,style2, style3, 4, false, false, true, false);

	this->newC = new Item("Dodaj nowy", 15, 230, 90, 20, true, false, style3, 0, 0);
	this->newC->doUnvisible();

	this->setAsActualC = new Item("Ustaw jako aktualny", 114, 230, 150, 20, true, false, style3, 0, 0);
	this->setAsActualC->doUnvisible();

	this->saveC = new Item("Zapisz", 720, 640, 90, 20, true, false, style3, 0, 0);
	this->saveC->doUnvisible();

	this->editC = new Item("Edytuj", 620, 640, 90, 20, true, false, style3, 0, 0);
	this->editC->doUnvisible();

	std::vector <Stuff*> group1Vec = {tabCennikow, tabC,updownC, actualC, newC, setAsActualC, saveC, editC};
	this->groupC = new StuffGroup(group1Vec);

	//////////////////////////////////////////////Umowy
	std::vector <std::vector <sf::String>> sRodzajeU(1);
	sRodzajeU[0] = { "Wszystkie", "Oczekujace", "Zatwierdzone", "Odrzucone", "Zakonczone" };

	rodzU = new Table(1,5,15,40,sRodzajeU,100,20,0,0,style2,style3,0,0,1,1,0);

	std::vector <std::vector <sf::String>> slistaU(11);
	slistaU[0] = { "Nr","Klient","Stan","Kwota" };
	for (int i = 1; i < 11; i++)
		slistaU[i].resize(4);

	listaU = new Table(11, 4, 80, 70, slistaU, 100, 20, 0, 1, style2, style3, 0, 0, 0, 0, 0);

	std::vector <std::vector <sf::String>> swybU(11);
	swybU[0] = { "Wybierz" };
	for (int i = 1; i < 11; i++)
		swybU[i].resize(1,"");

	wybU = new Table(11, 1, 15, 70, swybU, 65, 20, 0, 1, style2, style3, 0, 0, 1, 1, 0);

	updownU = new Table(2, 1, 484, 163, sUD, 20, 20, false, false, style2, style3, 20, false, true, true, false);

	tabU = new Table(49, 8, 515, 70, sTab2, 58, 11, true, true, style2, style3, 4, true, false, false, false);

	zatwU = new Item(L"ZatwierdŸ", 90, 320, 100, 20, 1, 0, style3, 0, 0);
	zatwU->doUnvisible();
	odrzU = new Item(L"Odrzuæ", 200, 320, 100, 20, 1, 0, style3, 0, 0);
	odrzU->doUnvisible();
	zakU = new Item(L"Zakoñcz", 310, 320, 100, 20, 1, 0, style3, 0, 0);
	zakU->doUnvisible();

	mListU = new MovingList(listaU);

	group1Vec = { rodzU, listaU,wybU,updownU,tabU, zatwU, odrzU, zakU};
	groupU = new StuffGroup(group1Vec);
	//////////////////////////////////////////////Plan
	tabP = new Table(49, 8, 15, 40, sTab2, 70, 12, true, true, style2, style3, 4, 1, 1, 1, 0);

	vector <vector<sf::String>> sListaP(11, { "","","" });
	sListaP[0] = { "Nr umowy","Klient",L"D³ugoœæ" };
	listaP = new Table(11, 3, 600, 40, sListaP, 100, 20, 0, 1, style2, style3, 0, 0, 0, 0, 0);

	updownP = new Table(2, 1, 903, 135, sUD, 20, 20, false, false, style2, style3, 20, false, true, true, false);
	mListP = new MovingList(listaP);

	group1Vec = { tabP, listaP , updownP};
	groupP = new StuffGroup(group1Vec);
	//////////////////////////////////////////////Reklamodawcy
	tabR = new Table(49, 8, 300, 40, sTab2, 58, 11, true, true, style2, style3, 4, true, false, false, false);

	vector <vector<sf::String>> sListaR(11, { "" });
	sListaR[0] = { "Nazwa" };
	listaR = new Table(11, 1, 36, 40, sListaR, 100, 20, 0, 1, style2, style3, 0, 0, 1, 1, 0);

	updownR = new Table(2, 1, 15, 135, sUD, 20, 20, false, false, style2, style3, 20, false, true, true, false);
	mListR = new MovingList(listaR);

	sListaR[0] = { "Umowa" };
	listaUmowyR = new Table(11, 1, 150, 40, sListaR, 100, 20, 0, 1, style2, style3, 0, 0, 1, 1, 0);

	updown2R = new Table(2, 1, 251, 135, sUD, 20, 20, false, false, style2, style3, 20, false, true, true, false);
	mList2R = new MovingList(listaUmowyR);

	usunR = new Item(L"Usuñ reklamodawcê", 65, 285, 150, 20, 1, 0, style2, 0, 0);
	usunR->doUnvisible();

	group1Vec = { tabR, listaR , updownR , listaUmowyR ,updown2R, usunR};
	groupR = new StuffGroup(group1Vec);
	////////////////////////////////////////////
	newObject(menu);
	newObject(tabC);
	newObject(tabCennikow);
	newObject(updownC);
	newObject(actualC);
	newObject(newC);
	newObject(setAsActualC);
	newObject(editC);
	newObject(saveC);
	newObject(rodzU);
	newObject(listaU);
	newObject(updownU);
	newObject(wybU);
	newObject(tabU);
	newObject(zatwU);
	newObject(odrzU);
	newObject(zakU);
	newObject(tabP);
	newObject(listaP);
	newObject(updownP);
	newObject(tabR);
	newObject(listaR);
	newObject(updownR);
	newObject(listaUmowyR);
	newObject(updown2R);
	newObject(usunR);
}

void NadawcaForm::afterClick(Stuff * element)
{
	if (this->menu == element)
	{
		this->groupC->doUnvisible();
		this->groupU->doUnvisible();
		this->groupP->doUnvisible();
		this->groupR->doUnvisible();

		if (element->isChosen(0, 0))
		{
			this->groupC->doVisible();
			this->actualC->returnElement(1, 0)->setString(fm->ActualPriceList);
			this->mListC->setStrings(fm->loadTable(fm->PriceLists));
			tabC->clear();
			tabC->unselect();
			editC->unselect();
			tabC->setEditable(false);
			tabCennikow->unselect();
		}

		else if (element->isChosen(0, 3))
		{
			groupU->doVisible();
			this->rodzU->unselect();
			tabU->clear();
			listaU->unselect();
			wybU->unselect();
			listaU->clear();
			mListU->clear();
		}

		else if (element->isChosen(0, 4))
		{
			this->setVisible(false);
			this->groupC->unselectAll();
			this->lForm->setVisible(true);
		}

		else if (element->isChosen(0, 2))
		{
			groupP->doVisible();
			tabP->unselect();
			mListP->clear();
			vector<vector <sf::String>> loadedTab = fm->loadTable(fm->AvailableTime);
			for (int i = 0; i < loadedTab.size(); i++)
			{
				for (int j = 0; j < loadedTab[i].size(); j++)
					tabP->returnElement(i + 1, j + 1)->setString(loadedTab[i][j]);
			}
		}

		else if (element->isChosen(0, 1))
		{
			groupR->doVisible();
			tabR->clear();
			listaR->unselect();
			listaUmowyR->unselect();
			listaUmowyR->clear();
			mListR->setStrings(fm->loadTable(fm->Users));
		}
	}

	else if (menu->isChosen(0, 0))
	{
		if (this->updownC == element)
		{
			if (updownC->isChosen(0, 0))
				this->mListC->move(1);
			else if (updownC->isChosen(1, 0))
				this->mListC->move(0);
			updownC->unselect();
		}

		else if (this->tabCennikow == element)
		{
			tabC->clear();
			editC->unselect();
			tabC->setEditable(false);
			tabC->unselect();
			for (int i = 1; i < tabCennikow->getSize()[0]; i++)
			{
				if (tabCennikow->isChosen(i, 0))
				{
					if (tabCennikow->getString(i, 0) != "")
					{
						vector <vector <sf::String>> loadedTab = fm->loadTable(tabCennikow->getString(i, 0));
						for (int j = 0; j < loadedTab.size(); j++)
						{
							for (int k = 0; k < loadedTab[i].size(); k++)
							{
								tabC->returnElement(j + 1, k + 1)->setString(loadedTab[j][k]);
							}
						}
					}
				}
			}
		}

		else if (newC == element)
		{
			this->setVisible(false);
			this->dodajForm->setVisible(true);
			element->unselect();
		}

		else if (editC == element)
		{
			if (editC->isChosen())
				tabC->setEditable(true);
			else
			{
				tabC->setEditable(false);
				tabC->unselect();
			}
		}

		else if (setAsActualC == element)
		{
			element->unselect();
			for (int i = 1; i < tabCennikow->getSize()[0]; i++)
			{
				if (tabCennikow->isChosen(i, 0))
				{
					if (tabCennikow->getString(i, 0) != "")
					{
						fm->setActualPricelist(tabCennikow->getString(i, 0));
						actualC->returnElement(1, 0)->setString(tabCennikow->getString(i, 0));
					}
				}
			}
		}

		else if (saveC == element)
		{
			vector < vector <sf::String>> tabToFile(48);
			for (int i = 0; i < 48; i++)
			{
				tabToFile[i].resize(7);
				for (int j = 0; j < 7; j++)
				{
					string a = tabC->getString(i + 1, j + 1);
					if (a == "")
						a = "0";
					tabToFile[i][j] = a;
				}
			}
			for (int i = 1; i < tabCennikow->getSize()[0]; i++)
			{
				if (tabCennikow->isChosen(i, 0))
				{
					fm->tableToFile(tabCennikow->getString(i, 0), tabToFile);
					break;
				}
			}
			saveC->unselect();
			editC->unselect();
			tabC->unselect();
			tabC->setEditable(false);
		}
	}

	else if (menu->isChosen(0, 3))
	{
		if (rodzU == element)
		{
			tabU->clear();
			wybU->unselect();
			mListU->clear();
			for (int i = 0; i < rodzU->getSize()[1]; i++)
			{
				if (rodzU->isChosen(0, i))
				{
					vector <vector<sf::String>> loadedTab = fm->loadTable(fm->Contracts);
					for (int j = 0; j < loadedTab.size(); j++)
					{
						if ((!(loadedTab[j][2] == rodzU->getString(0, i))) && (i != 0))
						{
							loadedTab.erase(loadedTab.begin() + j);
							j--;
						}
					}
					mListU->setStrings(loadedTab);
					break;
				}
			}
		}

		else if ((zatwU == element)||(odrzU == element))
		{
			element->unselect();
			for (int i = 1; i < wybU->getSize()[0]; i++)
			{
				if (wybU->isChosen(i, 0))
				{
					if (listaU->getString(i, 0) != "")
					{
						if (listaU->getString(i, 2) == "Oczekujace")
						{
							if((zatwU == element)&&(fm->confirm(listaU->getString(i,0))))
								fm->changeState(listaU->getString(i, 0), "Zatwierdzone");
							else if(odrzU == element)
								fm->changeState(listaU->getString(i, 0), "Odrzucone");
							mListU->setStrings(fm->loadTable(fm->Contracts));
							this->wybU->unselect();
							this->tabU->clear();
							this->listaU->clear();
							this->rodzU->unselect();
						}
					}
					break;
				}
			}
		}

		else if (zakU == element)
		{
			zakU->unselect();
			for (int i = 1; i < wybU->getSize()[0]; i++)
			{
				if (wybU->isChosen(i, 0))
				{
					if (listaU->getString(i, 0) != "")
					{
						if (listaU->getString(i, 2) == "Zatwierdzone")
						{
							fm->changeState(listaU->getString(i, 0), "Zakonczone");
							mListU->setStrings(fm->loadTable(fm->Contracts));
							fm->addTime(listaU->getString(i, 0));
							this->wybU->unselect();
							this->tabU->clear();
							this->listaU->clear();
							this->rodzU->unselect();
						}
					}
					break;
				}
			}
		}

		else if (updownU == element)
		{
			if (updownU->isChosen(0, 0))
				this->mListU->move(1);
			else if (updownU->isChosen(1, 0))
				this->mListU->move(0);
			updownU->unselect();
			tabU->clear();
			wybU->unselect();
		}

		else if (wybU == element)
		{
			tabU->clear();
			for (int i = 1; i < wybU->getSize()[0]; i++)
			{
				if ((wybU->isChosen(i, 0))&&(listaU->getString(i,0)!=""))
				{
					vector <vector<sf::String>> loadedTab = fm->loadTable("kontrakty/" + listaU->getString(i, 0) + ".txt");
					for (int j = 0; j < loadedTab.size(); j++)
					{
						tabU->returnElement(stoi((string)loadedTab[j][0])+1, stoi((string)loadedTab[j][1])+1)->setString(loadedTab[j][2]);
					}
					break;
				}
			}
		}
	}
	else if (menu->isChosen(0, 2))
	{
		if (tabP == element)
		{
			mListP->clear();
			for (int i = 1; i < tabP->getSize()[0]; i++)
			{
				for (int j = 1; j < tabP->getSize()[1]; j++)
				{
					if (tabP->isChosen(i, j))
						mListP->setStrings(fm->findContracts(i - 1, j - 1));
				}
			}
		}
		else if (updownP == element)
		{
			tabP->unselect();
			listaP->clear();
			if (updownP->isChosen(0, 0))
				this->mListP->move(1);
			else if (updownP->isChosen(1, 0))
				this->mListP->move(0);
			updownP->unselect();
		}
	}

	else if (menu->isChosen(0, 1))
	{
		if (usunR == element)
		{
			usunR->unselect();
			for (int i = 1; i < listaR->getSize()[0]; i++)
			{
				if (listaR->isChosen(i, 0))
				{
					if (mListR->size() >= i)
					{
						fm->removeUser(listaR->getString(i, 0), mList2R->returnList());
						tabR->clear();
						listaUmowyR->clear();
						listaR->unselect();
						listaUmowyR->unselect();
						mListR->setStrings(fm->loadTable(fm->Users));
					}
				}
			}
		}

		else if (listaR == element)
		{
			tabR->clear();
			listaUmowyR->clear();
			listaUmowyR->unselect();
			for (int i = 1; i < listaR->getSize()[0]; i++)
			{
				if ((listaR->isChosen(i, 0))&&(listaR->getString(i,0)!=""))
				{
					mList2R->setStrings(fm->findUserContracts(listaR->getString(i, 0)));
				}
			}
		}

		else if(listaUmowyR==element)
		{
			tabR->clear();
			for (int i = 1; i < listaUmowyR->getSize()[0]; i++)
			{
				if ((listaUmowyR->isChosen(i, 0))&&(listaUmowyR->getString(i,0)!=""))
				{
					vector <vector <sf::String>> loadedTab = fm->loadTable("kontrakty/" + (string)listaUmowyR->getString(i, 0) + ".txt");
					for (int i = 0; i < loadedTab.size(); i++)
					{
						tabR->returnElement(stoi((string)loadedTab[i][0])+1, stoi((string)loadedTab[i][1])+1)->setString(loadedTab[i][2]);
					}
				}
			}
		}

		else if (updownR == element)
		{
			if (updownR->isChosen(0, 0))
				this->mListR->move(1);
			else if (updownR->isChosen(1, 0))
				this->mListR->move(0);
			updownR->unselect();
			tabR->clear();
			listaUmowyR->clear();
			listaUmowyR->unselect();
			listaR->unselect();
		}

		else if (updown2R == element)
		{
			if (updown2R->isChosen(0, 0))
				this->mList2R->move(1);
			else if (updown2R->isChosen(1, 0))
				this->mList2R->move(0);
			updown2R->unselect();
			tabR->clear();
			listaUmowyR->unselect();
		}
	}
}

void NadawcaForm::afterInput(Stuff * element)
{

}

void NadawcaForm::afterVisible()
{
	this->mListC->setStrings(fm->loadTable(fm->PriceLists));
}
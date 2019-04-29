#include "pch.h"
#include "CennikForm.h"


CennikForm::CennikForm(int w, int h, sf::String label, FilesManager * _fm) : Form(w, h, label, _fm)
{
	sf::Font font;
	font.loadFromFile("arial.ttf");
	this->style = new Style(sf::Color(148, 221, 255), sf::Color(0, 0, 0), sf::Color(0, 0, 0), sf::Color(148, 148, 255), sf::Color(138, 60, 198),font);
	this->style2 = new Style(sf::Color(123, 58, 74), sf::Color(0, 0, 0), sf::Color(255, 255, 255), sf::Color(148, 148, 255), sf::Color(138, 60, 198),font);
	this->style3 = new Style(sf::Color(236, 159, 174), sf::Color(0, 0, 0), sf::Color(0, 0, 0), sf::Color(250, 105, 163), sf::Color(138, 60, 198),font);

	std::vector <std::vector <sf::String>> sCennik(49);
	std::vector <std::vector <sf::String>>  loadedT = this->fm->loadTable(fm->ActualPriceList);
	sCennik[0] = { "", L"poniedzia³ek", "wtorek", L"œroda", "czwartek", L"pi¹tek", "sobota", "niedziela" };

	for (int i = 1; i < 49; i++)
	{
		sCennik[i].resize(8, "");
		sCennik[i][0] = std::to_string((i - 1) / 20) + std::to_string(((i - 1) / 2) % 10) + ":" + std::to_string(3 * ((i - 1) % 2)) + "0 - " + std::to_string((i - 1) / 20) + std::to_string(((i - 1) / 2) % 10) + ":" + std::to_string(2 + 3 * (((i - 1) % 2))) + "9";
		for (int j = 0; j < 7; j++)
			sCennik[i][j + 1] = loadedT[i - 1][j];
	}

	this->cennik = new Table(49, 8, 0, 0, sCennik, 70, 12, true, true, style2, style3, 4, true, false, false, false);
	this->newObject(cennik);
	this->cennik->doVisible();
}

int CennikForm::getValue(int x, int y)
{
	return stoi((string)this->cennik->getString(x, y));
}

void CennikForm::afterVisible()
{
	std::vector <std::vector <sf::String>>  loadedT = this->fm->loadTable(fm->ActualPriceList);
	for (int i = 1; i < 49; i++)
	{
		for (int j = 1; j < 8; j++)
			cennik->returnElement(i,j)->setString(loadedT[i - 1][j-1]);
	}
}
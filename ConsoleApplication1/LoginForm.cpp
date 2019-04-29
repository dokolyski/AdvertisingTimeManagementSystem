#include "pch.h"
#include "LoginForm.h"


LoginForm::LoginForm(int w, int h, sf::String label, FilesManager * _fm) : Form(w,h,label, _fm)
{
	sf::Font font;
	font.loadFromFile("arial.ttf");
	this->style = new Style(sf::Color(148, 221, 255), sf::Color(0, 0, 0), sf::Color(0, 0, 0), sf::Color(148, 148, 255), sf::Color(138, 60, 198),font);
	this->style2 = new Style(sf::Color(123, 58, 74), sf::Color(0, 0, 0), sf::Color(255, 255, 255), sf::Color(148, 148, 255), sf::Color(138, 60, 198),font);
	this->style3 = new Style(sf::Color(236, 159, 174), sf::Color(0, 0, 0), sf::Color(0, 0, 0), sf::Color(250, 105, 163), sf::Color(138, 60, 198),font);

	std::vector <std::vector <sf::String>> sLogin(2);
	sLogin[0] = { "Login", "" };
	sLogin[1] = { L"Has³o", "" };

	this->login = new Table(2, 2, 145, 10, sLogin, 120, 20, true, false, style2, style3, 12, false, true);

	std::vector <std::vector <sf::String>> sReg(3);
	sReg[0] = { "Login", "" };
	sReg[1] = { L"Has³o", "" };
	sReg[2] = { L"Powtórz Has³o", "" };

	this->reg = new Table(3, 2, 145, 85, sReg, 120, 20, true, false, style2, style3, 12, false, true);

	std::vector <std::vector <sf::String>> sWybor(2);
	sWybor[0] = { "Reklamodawca" };
	sWybor[1] = { "Nadawca" };

	this->wybor = new Table(2, 1, 10, 10, sWybor, 120, 20, false, false, style2, style3, 0, false, true, true, false);
	wybor->doVisible();

	this->loginButton = new Item(L"Zaloguj siê", 146, 54, 241, 20, true, false, style3, 20, false);
	this->regButton = new Item(L"Zarejestruj siê", 146, 150, 241, 20, true, false, style3, 20, false);
	this->loginButton->doUnvisible();
	this->regButton->doUnvisible();

	std::vector<Stuff*> vectorloginGroup = { login,loginButton };
	std::vector<Stuff*> vectorregGroup = { reg,regButton };
	this->loginGroup = new StuffGroup(vectorloginGroup);
	this->regGroup = new StuffGroup(vectorregGroup);

	this->newObject(login);
	this->newObject(wybor);
	this->newObject(reg);
	this->newObject(loginButton);
	this->newObject(regButton);
}

void LoginForm::afterClick(Stuff * element)
{
	if (element == this->wybor)
	{
		regGroup->doUnvisible();
		loginGroup->doUnvisible();

		if (this->wybor->isChosen(0, 0))
		{
			loginGroup->doVisible();
			regGroup->doVisible();
		}
		else if (this->wybor->isChosen(1, 0))
		{
			loginGroup->doVisible();
		}
	}
	else if (element == this->loginButton)
	{
		if (this->wybor->isChosen(0, 0))
		{
			if (this->fm->checkPassword(this->login->getString(0, 1), this->login->getString(1, 1)))
			{
				this->setVisible(false);
				this->rForm->setVisible(true);
				this->fm->ActualUser = this->login->getString(0, 1);
			}
		}
		else if (this->wybor->isChosen(1, 0))
		{
			if (this->fm->adminLogin(this->login->getString(0, 1), this->login->getString(1, 1)))
			{
				this->setVisible(false);
				this->nForm->setVisible(true);
			}
		}
		this->loginButton->unselect();
	}
	else if (element == this->regButton)
	{
		this->regButton->unselect();
		if ((this->reg->getString(1, 1) == this->reg->getString(2, 1))&& (this->reg->getString(0, 1).getSize()>0))
		{
			if (this->fm->uniquenesOfLogin(this->reg->getString(0, 1)))
			{
				if (this->fm->registerUser(this->reg->getString(0, 1), this->reg->getString(1, 1)))
				{
					this->setVisible(false);
					this->rForm->setVisible(true);
					this->fm->ActualUser = this->reg->getString(0, 1);
				}
			}
		}
		this->regButton->unselect();
	}
}

void LoginForm::afterVisible() 
{
	this->reg->clear();
	this->login->clear();
	this->reg->unselect();
	this->login->unselect();
	this->cennikF->setVisible(false);
	this->czasDostF->setVisible(false);
}
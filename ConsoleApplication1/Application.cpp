#include "pch.h"
#include "Application.h"
#include <iostream>

Application::Application()
{
	//filemanager creation
	this->fm = new FilesManager;
	//forms creation
	this->reklForm = new ReklamodawcaForm(1000, 700, L"Profil reklamodawcy",fm);
	this->logForm = new LoginForm(400, 200, L"Zaloguj siê",fm);
	this->cenForm = new CennikForm(569, 638, L"Aktualny cennik", fm);
	this->cForm = new CzasForm(569, 638, L"Dostêpny czas", fm);
	this->nadawForm = new NadawcaForm(1000, 700, L"Profil nadawcy", fm);
	this->dodajForm = new DodajCennikForm(285, 120, L"Nowy cennik", fm);
	this->zatwForm = new ZatwierdzForm(346, 120, L"PotwierdŸ zamówienie", fm);

	//set all forms available from this forms
	logForm->rForm = reklForm;
	logForm->nForm = nadawForm;
	logForm->cennikF = cenForm;
	logForm->czasDostF = cForm;
	reklForm->lForm = logForm;
	reklForm->cennik = cenForm;
	reklForm->czasDost = cForm;
	reklForm->zatwForm = zatwForm;
	zatwForm->reklForm = reklForm;
	nadawForm->dodajForm = dodajForm;
	nadawForm->lForm = logForm;
	dodajForm->nadawForm = nadawForm;

	//set starting visibility and activity of your forms...
	this->cenForm->setVisible(false); 
	this->reklForm->setVisible(false);
	this->cForm->setVisible(false);
	this->nadawForm->setVisible(false);
	this->dodajForm->setVisible(false);
	this->zatwForm->setVisible(false);

	//add all forms to form list
	this->Forms.push_back(this->reklForm);
	this->Forms.push_back(this->logForm);
	this->Forms.push_back(this->cenForm);
	this->Forms.push_back(this->cForm);
	this->Forms.push_back(this->nadawForm);
	this->Forms.push_back(this->dodajForm);
	this->Forms.push_back(this->zatwForm);
}

void Application::setActiveWindow()
{
	int nOF = this->Forms.size();
	for (int i = 0; i < nOF; i++)
	{
		if (this->Forms[i]->hasFocus())
		{
			this->ActualForm = this->Forms[i];
			break;
		}
	}
}

bool Application::isWorking()
{
	int nOF = this->Forms.size();
	for (int i = 0; i < nOF; i++)
	{
		if (this->Forms[i]->isVisible())
			return true;
	}
	return false;
}

void Application::doApplication()
{
	//aplikacja dzia³a dopóki wszystkie okna nie zostan¹ zamkniête
	while (isWorking())
	{
		//oczekiwanie na aktywne okno
		setActiveWindow();
		//obs³uga aktywnego okna (tylko jedno okno mo¿e byæ aktywne w danym momencie) 
		this->ActualForm->windowService();
	}
}
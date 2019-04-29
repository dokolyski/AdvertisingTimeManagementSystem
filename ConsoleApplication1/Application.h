#pragma once
#include "ReklamodawcaForm.h"
#include "LoginForm.h"
#include "CennikForm.h"
#include "CzasForm.h"
#include "NadawcaForm.h"
#include "DodajCennikForm.h"
#include "ZatwierdzForm.h"

class Application
{
	Form * ActualForm;
	std::vector <Form*> Forms;
	ReklamodawcaForm * reklForm;
	LoginForm * logForm;
	CennikForm * cenForm;
	CzasForm * cForm;
	NadawcaForm * nadawForm;
	DodajCennikForm * dodajForm;
	ZatwierdzForm * zatwForm;
	FilesManager * fm;
	void setActiveWindow();
	bool isWorking();
public:
	Application();
	void doApplication();
};
#include "pch.h"
#include "Stuff.h"

void Stuff::doVisible()
{
	this->Visible = true;
}

void Stuff::doUnvisible()
{
	this->Visible = false;
}

bool Stuff::isVisible()
{
	return this->Visible;
}
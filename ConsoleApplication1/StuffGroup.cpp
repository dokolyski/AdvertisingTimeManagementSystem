#include "pch.h"
#include "StuffGroup.h"


StuffGroup::StuffGroup(std::vector <Stuff*> &_group)
{
	this->Group = _group;
}

void StuffGroup::doVisible()
{
	int size = this->Group.size();
	for (int i = 0; i < size; i++)
		this->Group[i]->doVisible();
}

void StuffGroup::doUnvisible()
{
	int size = this->Group.size();
	for (int i = 0; i < size; i++)
		this->Group[i]->doUnvisible();
}

void StuffGroup::unselectOther(Stuff * it)
{
	int size = this->Group.size();
	for (int i = 0; i < size; i++)
	{
		if (Group[i] == it)
			continue;
		this->Group[i]->unselect();
	}
}

void StuffGroup::unselectAll()
{
	int size = this->Group.size();
	for (int i = 0; i < size; i++)
		this->Group[i]->unselect();
}
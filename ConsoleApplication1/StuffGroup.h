#pragma once
#include "Stuff.h"
#include <vector>

class StuffGroup
{
	std::vector <Stuff*> Group;
public:
	StuffGroup(std::vector <Stuff*>&);
	void doUnvisible();
	void doVisible();
	void unselectOther(Stuff * it);
	void unselectAll();
};


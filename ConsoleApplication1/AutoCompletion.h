#pragma once
#include "Table.h"
#include <vector>
#include <algorithm>
using namespace std;

float costCalculate(int s, int cost30);

class AutoCompletion
{
	vector<vector<sf::String>> prices;
	vector<vector<sf::String>> avTime;
	Table * wyniki;
	int bud;
public:
	AutoCompletion(vector<vector<sf::String>> _p, vector<vector<sf::String>> _aT, int _bud, Table * _w);
	void calculate(bool x);
};
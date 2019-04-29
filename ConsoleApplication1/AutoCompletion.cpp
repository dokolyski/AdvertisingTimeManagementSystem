#include "pch.h"
#include "AutoCompletion.h"
#include <iostream>
using namespace std;

template <class T> bool inVector(vector <T> v, T e)
{
	for (int a = 0; a < v.size(); a++)
	{
		if (v[a] == e)
			return true;
	}
	return false;
}

void removeTail(vector <int> & v)
{
	if (v.size() > 0)
	{
		int i = v[v.size() - 1];
		while ((v.size() > 0) && (v[v.size() - 1] == i))
			v.pop_back();
	}
}

float costCalculate(int s, int cost30)
{
	if (s <= 5)
		return 0.3 * cost30;
	if (s <= 10)
		return 0.5 * cost30;
	if (s <= 15)
		return 0.7 * cost30;
	if (s <= 20)
		return 0.8 * cost30;
	if (s <= 25)
		return 0.9 * cost30;
	if (s <= 30)
		return 1.0 * cost30;
	if (s <= 35)
		return 1.1 * cost30;
	if (s <= 40)
		return 1.3 * cost30;
	if (s <= 45)
		return 1.5 * cost30;
	if (s <= 50)
		return 1.7 * cost30;
	if (s <= 55)
		return 1.9 * cost30;
	if (s <= 60)
		return 2.0 * cost30;

	return 2.0 * cost30 + costCalculate((s - 60), cost30);
}

AutoCompletion::AutoCompletion(vector<vector<sf::String>> _p, vector<vector<sf::String>> _aT, int _bud, Table * _w)
{
	avTime = _aT;
	prices = _p;
	bud = _bud;
	wyniki = _w;
}

void AutoCompletion::calculate(bool x)
{
	vector <int> ceny;
	vector <vector <int>> used;
	for (int i = 0; i < prices.size(); i++)
	{
		for (int j = 0; j < prices[i].size(); j++)
		{
			if(stoi((string)avTime[i][j]) >= 5)
				ceny.push_back(stoi((string)prices[i][j]));
		}
	}
	sort(ceny.begin(), ceny.end());
	int smallest = ceny[0];
	if (x)
		reverse(ceny.begin(), ceny.end());

	for (int k = ceny.size() - 1; k >= 0; k--)
	{
		if (bud < smallest * 0.3)
			break;
		for (int i = 0; i < prices.size(); i++)
		{
			for (int j = 0; j < prices[i].size(); j++)
			{
				int p = stoi((string)prices[i][j]);
				if ((p != ceny[k])||(stoi((string)avTime[i][j]) < 5) || (inVector(used, { i,j })))
					continue;
				// zaokr¹glamy liczbê dostêpnych sekund do 5;
				int dT = stoi((string)avTime[i][j]) - stoi((string)avTime[i][j])%5;
				int l;
				for (l = dT; l >= 5; l -= 5)
				{
					float c = costCalculate(l, p);
					if (c <= bud)
					{
						wyniki->returnElement(i + 1, j + 1)->setString(l);
						bud -= c;
						used.push_back({ i,j });
						break;
					}
				}
				if (l > 0)
				{
					i = prices.size();
					break;
				}
				else
				{
					int pom = ceny[ceny.size()-1];
					removeTail(ceny);
					if ((ceny.size()==0)||(pom == ceny[ceny.size() - 1]))
						return;
					i = 0;
					j = -1;
					k = ceny.size() - 1;
				}
			}
		}
		ceny.pop_back();
	}
}
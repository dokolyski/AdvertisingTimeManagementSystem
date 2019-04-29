#pragma once
#include <cstdio>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "SFML/Graphics.hpp"

using namespace std;

class FilesManager
{
public:
	string Users, Main, Contracts, ActualPriceList, AvailableTime, Multipliers, PriceLists;
	string ActualUser;
	FilesManager();
	bool adminLogin(string, string);
	bool checkPassword(string, string);
	bool registerUser(string, string);
	bool uniquenesOfLogin(string);
	vector <vector <sf::String>> loadTable(string filename);
	void sendNewContract(vector <vector <sf::String>> tab, int price);
	void tableToFile(string name, vector <vector <sf::String>> table);
	int readAndChange();
	void addRecord(string filename, string line);
	void addRecord(string filename, vector <string> line);
	void setActualPricelist(string cennik);
	void changeState(string nr, string newState);
	vector<vector<sf::String>> findContracts(int x, int y);
	void removeUser(string login, vector<vector<sf::String>> umowy);
	bool confirm(string nr);
	vector <vector <sf::String>> findUserContracts(string s);
	void addTime(string nr);
};

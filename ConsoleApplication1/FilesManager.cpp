#include "pch.h"
#include "FilesManager.h"
#include <iostream>

using namespace std;

FilesManager::FilesManager()
{
	Users = "kluczowe/users.txt";
	Main = "kluczowe/main.txt";
	Contracts = "kluczowe/contracts.txt";
	AvailableTime = "kluczowe/dostepnyczas.txt";
	Multipliers = "kluczowe/mnozniki.txt";
	PriceLists = "kluczowe/pricelists.txt";

	//wczytanie aktualnego cennika z pliku main
	string str;
	fstream plik(Main, ios::in);
	if (plik.good())
	{
		while (getline(plik, str))
		{
			if (str.substr(0, 3) == "ac:")
			{
				ActualPriceList = str.substr(3);
				break;
			}
		}
	}
	plik.close();
}

bool FilesManager::registerUser(string a, string b)
{
	string filename = a + ".txt";
	fstream plik(filename,ios::out);
	plik << "l:" << a << endl << "p:" << b << endl;
	fstream plik2(Users, ios::app);
	plik2 << a << endl;
	plik.close();
	plik2.close();
	return true;
}

bool FilesManager::uniquenesOfLogin(string a)
{
	fstream plik(Users, ios::in);
	if (plik.good())
	{
		string username;
		while (getline(plik, username))
		{
			if (username == a)
			{
				plik.close();
				return false;
			}
		}
		plik.close();
		return true;
	}
	plik.close();
	return false;
}

bool FilesManager::checkPassword(string a, string b)
{
	string filename = a + ".txt";
	fstream plik(filename, ios::in);
	if (plik.good())
	{
		string password;
		while (getline(plik, password))
		{
			if (password.substr(0, 2) == "p:")
			{
				if (password.substr(2) == b)
					return true;
				return false;
			}
		}
	}
	plik.close();
	return false;
}

vector <vector <sf::String>> FilesManager::loadTable(string a)
{
	vector <vector <sf::String>> retTab;
	string filename = a;
	fstream plik(filename, ios::in);
	if (plik.good())
	{
		string line;
		while (getline(plik, line))
		{
			int size = line.size();
			std::vector <sf::String> vectorLine;
			if (size>0)
			{
				int previous = 0;
				for (int i = 0; i < size; i++)
				{
					if (line[i] == ' ')
					{
						if (i != size - 1)
						{
							vectorLine.push_back(line.substr(previous, i - previous));
							previous = i + 1;
						}
					}
				}
				vectorLine.push_back(line.substr(previous, size));
				retTab.push_back(vectorLine);
			}
		}
	}
	plik.close();
	return retTab;
}

bool FilesManager::adminLogin(string a, string b)
{
	fstream plik(Main, ios::in);
	if (plik.good())
	{
		string str;
		while (getline(plik, str))
		{
			if (str.substr(0, 2) == "l:")
			{
				if (!(str.substr(2) == a))
					return false;
			}
			if (str.substr(0, 2) == "p:")
			{
				if (!(str.substr(2) == b))
					return false;
			}
		}
	}
	plik.close();
	return true;
}

int FilesManager::readAndChange()
{
	fstream plik(Main, ios::in);
	int returnValue = -1;
	vector <string> text;
	if (plik.good())
	{
		string str;
		while (getline(plik, str))
		{
			if (str.substr(0, 3) == "nk:")
			{
				returnValue = stoi(str.substr(3));
				text.push_back("nk:" + to_string(returnValue + 1));
			}
			else
				text.push_back(str);
		}
		plik.close();
	}
	plik.open(Main, ios::out);
	if (plik.good())
	{
		for (int i = 0; i < text.size(); i++)
		{
			plik << text[i] << "\n";
		}
	}
	plik.close();
	return returnValue;
}

void FilesManager::sendNewContract(vector <vector <sf::String>> tab, int price)
{
	int nr = readAndChange();
	fstream plik("kontrakty/" + to_string(nr) + ".txt", ios::out);
	fstream plik2(Contracts, ios::app);
	if ((plik.good()) && (plik2.good()))
	{
		plik2 << to_string(nr)<<" " << ActualUser << " Oczekujace "<< to_string(price)<<"\n";

		for (int i = 0; i < tab.size(); i++)
		{
			for (int j = 0; j < tab[i].size(); j++)
			{
				if (tab[i][j] != "")
					plik << to_string(i)<<" "<< to_string(j)<<" "<< (string)(tab[i][j])<<"\n";
			}
		}
	}
	plik.close();
	plik2.close();
}

void FilesManager::setActualPricelist(string cennik)
{
	vector <string> text;
	string str;
	fstream plik(Main, ios::in);
	if (plik.good())
	{
		while (getline(plik, str))
		{
			if (str.substr(0, 3) == "ac:")
			{
				str = "ac:" + cennik;
				this->ActualPriceList = str.substr(3);
			}
			text.push_back(str);
		}
	}
	plik.close();
	plik.open(Main, ios::out);
	if (plik.good())
	{
		for (int i = 0; i < text.size(); i++)
			plik << text[i]+"\n";
	}
}

void FilesManager::tableToFile(string name, vector <vector <sf::String>> table)
{
	fstream plik(name, ios::out);
	if (plik.good())
	{
		for (int i = 0; i < table.size(); i++)
		{
			for (int j = 0; j < table[i].size(); j++)
			{
				plik << (string)table[i][j];
				if (j < table[i].size()-1)
					plik << " ";
			}
				
			plik << "\n";
		}
	}
	plik.close();
}

void FilesManager::addRecord(string filename, string line)
{
	fstream plik(filename, ios::app);
	if (plik.good())
	{
		plik << line << "\n";
	}
	plik.close();
}

void FilesManager::addRecord(string filename, vector <string> line)
{
	fstream plik(filename, ios::app);
	if (plik.good())
	{
		for(int i=0; i<line.size(); i++)
			plik << line[i] << " ";
		plik << "\n";
	}
	plik.close();
}

void FilesManager::changeState(string nr, string newState)
{
	vector<string> text;
	fstream plik(Contracts, ios::in);
	if (plik.good())
	{
		string line;
		while (getline(plik, line))
		{
			for (int i = 0; i < line.size(); i++)
			{
				if (line[i] == ' ')
				{
					if (line.substr(0, i) == nr)
					{
						i++;
						while (line[i] != ' ')
							i++;
						int j = i+1;
						while (line[j] != ' ')
							j++;
						line = line.substr(0, i + 1) + newState + line.substr(j);
					}	
				}
			}
			text.push_back(line);
		}
	}
	plik.close();
	plik.open(Contracts, ios::out);
	if (plik.good())
	{
		for (int i = 0; i < text.size(); i++)
		{
			plik << text[i] << "\n";
		}
	}
	plik.close();
}

vector<vector<sf::String>> FilesManager::findContracts(int x, int y)
{
	vector<vector<sf::String>> retTab;
	vector<vector<sf::String>> allCon = this->loadTable(Contracts);
	for(int a=0; a<allCon.size(); a++)
	{
		fstream plik("kontrakty/" + (string)allCon[a][0] + ".txt", ios::in);
		vector <vector <sf::String>> loadedTab = this->loadTable("kontrakty/" + (string)allCon[a][0] + ".txt");
		for (int i = 0; i < loadedTab.size(); i++)
		{
			if ((stoi((string)loadedTab[i][0]) == x) && (stoi((string)loadedTab[i][1]) == y) && (allCon[a][2] == "Zatwierdzone"))
			{
				retTab.push_back({ allCon[a][0], allCon[a][1], loadedTab[i][2] });
				cout << (string)allCon[a][0] << " " << (string)allCon[a][1] << " " << (string)loadedTab[i][2]<<"\n";
				break;
			}
			else if(stoi((string)loadedTab[i][0]) > x)
				break;
		}
	}
	return retTab;
}

void FilesManager::removeUser(string login, vector<vector<sf::String>> umowy)
{
	fstream plik(Users, ios::in);
	vector <sf::String> text;
	if (plik.good())
	{
		string str;
		while (getline(plik, str))
		{
			if (str != login)
			{
				text.push_back(str);
			}
		}
	}
	plik.close();
	plik.open(Users, ios::out);
	if(plik.good())
	{
		for (int i = 0; i < text.size(); i++)
			plik << (string)text[i] << "\n";
	}
	remove(((string)login + ".txt").c_str());
	plik.close();

	plik.open(Contracts, ios::in);
	vector<string> text2;
	vector<vector <sf::String>> c = loadTable(Contracts);
	if(plik.good())
	{
		string str;
		while (getline(plik, str))
		{
			for (int i = 0; i < umowy.size(); i++)
			{
				if ((umowy[i][0] == str.substr(0, umowy[i][0].getSize())) && (str[umowy[i][0].getSize()] == ' '))
				{
					str = "";
					for (int j = 0; j < c.size(); j++)
					{
						if ((c[j][0] == umowy[i][0]) && (c[j][2] == "Zatwierdzone"))
							addTime(umowy[i][0]);
					}
					break;
				}
			}
			if (str != "")
				text2.push_back(str);
		}
	}
	plik.close();

	plik.open(Contracts, ios::out);
	if (plik.good())
	{
		for (int i = 0; i < text2.size(); i++)
		{
			plik << (string)text2[i] << "\n";
		}
	}
	plik.close();

	for (int i = 0; i < umowy.size(); i++)
		remove(((string)("kontrakty/" + umowy[i][0] + ".txt")).c_str());
}

bool FilesManager::confirm(string nr)
{
	vector <vector <sf::String>> loadedTab = loadTable(this->AvailableTime);
	vector <vector <sf::String>> kontrakt = loadTable("kontrakty/" + nr + ".txt");
	for (int i = 0; i < kontrakt.size(); i++)
	{
		if (stoi((string)loadedTab[stoi((string)kontrakt[i][0])][stoi((string)kontrakt[i][1])]) < stoi((string)kontrakt[i][2]))
			return false;
		else
			loadedTab[stoi((string)kontrakt[i][0])][stoi((string)kontrakt[i][1])] = to_string(stoi((string)loadedTab[stoi((string)kontrakt[i][0])][stoi((string)kontrakt[i][1])]) - stoi((string)kontrakt[i][2]));
	}
	this->tableToFile(AvailableTime, loadedTab);
	return true;
}

vector <vector <sf::String>> FilesManager::findUserContracts(string s)
{
	vector <vector <sf::String>> cont = this->loadTable(Contracts);
	vector <vector <sf::String>> ret;
	for (int i = 0; i < cont.size(); i++)
	{
		if ((string)cont[i][1] == s)
		{
			ret.push_back({ cont[i][0] });
		}
	}
	return ret;
}

void FilesManager::addTime(string nr)
{
	vector < vector <sf::String> > loadTab = this->loadTable("kontrakty/" + nr + ".txt");
	vector < vector <sf::String> > avTab = this->loadTable(AvailableTime);

	for (int i = 0; i < loadTab.size(); i++)
	{
		avTab[stoi((string)loadTab[i][0])][stoi((string)loadTab[i][1])] = to_string(stoi((string)avTab[stoi((string)loadTab[i][0])][stoi((string)loadTab[i][1])]) + stoi((string)loadTab[i][2]));
	}
	this->tableToFile(AvailableTime, avTab);
}
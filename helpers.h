#include<iostream>
#include <fstream>
#include "player.h"
#include "grue.h"
#include "prob.h"
#include "treasure.h"
#include "game.h"
#include "fixedobj.h"
#include <stdlib.h>
#include <time.h>
using namespace std;
inline string tolowerStr(string &x)
{
	for (int i = 0; i < x.size(); i++)
		x[i] = tolower(x[i]);
	return x;
}

inline bool findPlayer(vector<player> &y, Room* x)
{
	for (int i = 0; i < y.size(); i++)
		if (y[i].getPos() == x)
			return true;
	return false;
}

inline string getDirections()
{
	string x;
	cin >> x;
	x = tolowerStr(x);
	if (x == "north" || x == "south" || x == "east" || x == "west" ||
		x == "quit" || x == "attack" || x == "switch" || x == "pick" || x == "drop")
		return x;
	return "invalid";
}

inline void loadCords(int &length, int &width)
{
	fstream cords("cords.txt", ios::in);
	cords >> length;
	cords >> width;
	cords.close();
}

inline void printMap(vector<vector<Room>> &x, vector<player> &y, int z)
{
	int length, width;
	loadCords(length, width);
	for (int i = 0; i < length; i++)
	{
		cout << "  |";
		for (int j = 0; j < width; j++)
		{
			if (&x[i][j] == y[z].getPos())//law el current player
				cout << "O";
			else if (findPlayer(y, &x[i][j]))//bashof law el makan dah fe aye player
			{
				cout << "X";
			}
			else if (x[i][j].isFogged())
			{
				if (x[i][j].getType())
				{
					if (x[i][j].getSize() > 0)
						cout << x[i][j].getSize();
					else
						cout << " ";
				}
				else cout << "#";
			}
			else cout << "?";
		}
		cout << "|";
		cout << endl;
	}
}

inline void moveMobs(vector<grue*> &mobs)
{
	for (int i = 0; i < mobs.size(); i++)
		mobs[i]->act();
}

inline void spawnLoadMobs(vector<grue*> &mobs)
{
	int n, mobLevel; // Number of mobs,level
	int ix, jx; // Monster coordinates
	string mobName;

	// Read mob data from file
	fstream mobData("mobData.txt", ios::in);
	mobData >> n;
	for (int i = 0; i < n; i++)
	{
		mobData >> mobName;
		mobData >> mobLevel;
		mobData >> ix;
		mobData >> jx;
		grue* tmp = new grue(grue(mobName, &Game::rooms[ix][jx], mobLevel));
		mobs.emplace_back(tmp);
	}
	mobData.close();
}
inline void spawnLoadObjects(vector<objects*> &wep)
{
	int n;
	int damage, type;
	int ix, jx; //coordinates
	string name;
	fstream probData("probData.txt", ios::in);
	probData >> n; //ba5od el N mn el file
	for (int i = 0; i < n; i++)
	{
		probData >> name;
		probData >> type;
		probData >> damage;
		probData >> ix;
		probData >> jx;
		if (type == 1)
		{
			//Hay7sal hena memory leak ? #question
			objects* tmp = new prob(name, type, damage);
			wep.emplace_back(tmp);
		}
		if (type == 2)
		{
			//Hay7sal hena memory leak ? #question
			objects* tmp = new fixedobj(name, type, damage);
			wep.emplace_back(tmp);
		}
		if (type == 3)
		{
			//Hay7sal hena memory leak ? #question
			objects* tmp = new treasure(name, type, damage);
			wep.emplace_back(tmp);
		}
		Game::rooms[ix][jx].addObj(wep[wep.size() - 1]);
	}
	probData.close();
}




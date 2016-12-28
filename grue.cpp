#include "grue.h"
#include <stdlib.h>
#include <time.h>
#include "helpers.h"
#include <iostream>
using namespace std;
grue::grue(string nameX, Room* posX, int levelX) : Agent(nameX, posX, 0, levelX)
{

}
grue::~grue() {}

int grue::act(string path)
{
	if (cur_pos == NULL)
		return 0;
	if (getHealth() <= 0)
		return 0;
	attack();
	while (true) {
		// Performance
		int ranDirc = rand() % 5;
		if (ranDirc == 1 && move("north") ||
			ranDirc == 2 && move("south") ||
			ranDirc == 3 && move("east") ||
			ranDirc == 4 && move("west") ||
			ranDirc == 0) // Won't move. (in case all rooms are full too)
			return true;
	}
	return 0; //Never gonna reach here anyway.
}

string grue::status()
{
	cout << "Monster Name: " << name << ", Level: " << level << endl;
	if (cur_pos != NULL)
		cout << "at: " << cur_pos->getName() << endl;
	else
		cout << "Monster is not currently at any Room" << endl;
	return "";
}

void grue::attack()
{
	vector<Agent*> x = cur_pos->getSurroundAgent();
	for(int i=0; i<x.size(); i++)
	{
		if(x[i]->getType() == "player1" ||
		   x[i]->getType() == "player2")
			x[i]->setHealth(x[i]->getHealth()-getLevel());
	}
}

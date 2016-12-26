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
int grue::act()
{
	if (cur_pos == NULL)
		return 0;
	if (getHealth() <= 0)
		return 0;
	while (true) {
		int ranDirc = rand() % 5;
		if (ranDirc == 1 && move("north")) return true;
		else if (ranDirc == 2 && move("south")) return true;
		else if (ranDirc == 3 && move("east")) return true;
		else if (ranDirc == 4 && move("west")) return true;
		else if (ranDirc == 0) return true; //Won't move. (in case all rooms are full too)
	}
	return 0; //Never gonna reach here anyway.
}
void grue::status()
{
	cout << "Monster Name: " << name << ", Level: " << level << endl;
	if (cur_pos != NULL)
		cout << "at: " << cur_pos->getName() << endl;
	else cout << "Monster is not currently at any Room" << endl;
}

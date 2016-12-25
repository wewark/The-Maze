#include <iostream>
#include <iomanip>
#include <stdlib.h>
//#include <unistd.h>
#include <Windows.h>
#include <vector>
#include "room.h"
#include "Agent.h"
#include "player.h"
#include "grue.h"
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include "helpers.h"
using namespace std;

int main() {
	// SET-UP
	srand(time(NULL));
	int length, width; // Map size.
	loadCords(length, width); // Load from the file.

	//room** x = new room*[length]; //rooms 2D array.
	vector<vector<room>> rooms(length, vector<room>(width));
	vector<grue> mobs;

	// Link Rooms according to the file, And run the rooms/mobs constructor, Spawn the monsters too.
	linkMap(rooms);

	// Load Mobs data into vector, and spawn them + assign names.
	spawnLoadMobs(rooms, mobs);

	for (int i = 0; i < mobs.size(); i++)//////////////FIX VECTOR DESTRUCTOR BUG////////|
		mobs[i].getPos()->enter(&mobs[i]);/////////////////////////////////////////|

	player me("Sherif", &rooms[0][2], 1); //Our Player
	////////////////////////////////////
	cout << "           >>>> Welcome to Westworld's Maze <<<<" << endl;
	cout << "                                              -Dr.Ford\" " << endl;
	int nextStep; //flag

	while (true)
	{
		moveMobs(mobs);//Iterate over all mobs and act();
		printMap(rooms, &me, length, width);//Print The Map;
		cout << "---------Surrounded Monster---------" << endl;
		me.getPos()->printSurroundAgent(); //Print Player surrounding monsters
		cout << "------------------------------------" << endl;
		nextStep = me.act(); //Do the next step.
		if (nextStep == 0 || nextStep == 2 || nextStep == 3) // 0 = quit, 2 = WON, 3 = DEAD (Used after the while loop)
			break;
		system("CLS");
	}
	if (nextStep == 2) //The function act returned 2, Therefore the player WON.
		cout << ">> You WON BRO !" << endl;
	else if (nextStep == 3) //The function act returned 3, The Player died.
		cout << ">> You Died :/" << endl;
	else if (nextStep == 0)
		cout << "Game Quits." << endl; //The function act returned 0, The player typed "quit".
}

#include <iostream>
#include <iomanip>
#include <stdlib.h>
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
#include "prob.h"
using namespace std;
int main() {
	// SET-UP
	srand(time(NULL));
	int length, width; // Map size.
	loadCords(length, width); // Load from the file.
	//room** x = new room*[length]; //rooms 2D array.
	vector<grue*> mobs;
    vector<objects*> objectsX; //aw7ash esm fl koon
    vector<vector<room>> rooms(length, vector<room>(width));
	// Link Rooms according to the file, And run the rooms/mobs constructor, Spawn the monsters too.
	linkMap(rooms);
	// Load Mobs data into vector, and spawn them + assign names.
	spawnLoadMobs(rooms, mobs);
    // Load Objects data into vector, and spawn them + assign names.
    spawnLoadObjects(rooms,objectsX);
////////////////////////////////////GREETING MESSAGE/////////////////////////////////////
	cout << ">>>> Welcome to Westworld's Maze <<<<" << endl;
	cout << "                          -Dr.Ford" << endl;
	cout << ">> Press any key to continue...";
    cin.get();
    system("CLS");
    cout << "Your goal is to reach the treasure first, unfortunately the treasure is locked." << endl
    << "You have to find the treasure key, but beware of Dr.Ford's monsters!" << endl
    << "You can attack these monsters and they can attack you too!" << endl
    << "There are different chests which contain health potion that heals your HP" << endl
    << "But you have to find the key for these chests too." << endl
    << "There are different weapons on ground, pick a weapon to damage the monsters more effective" << endl;
    cout << endl << ">> Press Enter to continue" << endl;
    cin.get();
    system("CLS");

    int numberOfPlayers;
    cout << "Enter the number of players." << endl;
    cin >> numberOfPlayers;
    vector<player> me(numberOfPlayers,player());
    for(int i=0; i<numberOfPlayers; i++)
    {
        string name;
        cout << "Enter the name of Player " << i+1 << endl;
        cin >> name;
        me[i] = player(name, &rooms[0][2], 5); //Our Players
    }
//////////////////////////////////////THE GAME///////////////////////////////////////////
	int nextStep,i; //flags,PlayerTurn
    bool turn=true; //If Turn = false, Break and check flags to give the correct msg.
	while (true)
	{
	    turn = true;
        for(i=0; i<numberOfPlayers; i++){
            moveMobs(mobs);//Iterate over all mobs and act();
            printMap(rooms, me, i);//Print The Map;
            me[i].status();
            nextStep = me[i].act(); //Do the next step.
            if (nextStep == 0 || nextStep == 2 || nextStep == 3){ // 0 = quit, 2 = WON, 3 = DEAD (Used after the while loop)
                turn=false;
                break;
            }
            //system("CLS");
        }
        if(!turn)
            break;
	}
	if (nextStep == 2) //The function act returned 2, Therefore the player WON.
		cout << ">> You WON!, " << me[i].getName() << "!, Congratulations !" << endl;
	else if (nextStep == 3) //The function act returned 3, The Player died.
		cout << ">> You Died :/" << endl;
	else if (nextStep == 0)
		cout << "Game Quits." << endl; //The function act returned 0, The player typed "quit".
    return 0;
}

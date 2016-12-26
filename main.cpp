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
#include <QApplication>
#include "mainwindow.h"
#include "game.h"
using namespace std;

int main(int argc, char *argv[]) {
    srand(time(NULL));

    Room::initializeRooms();

    int numberOfPlayers = 1; // For now
    Game::me.push_back(new player("khaled", &Game::rooms[0][2], 5));

    // Load Mobs data into vector, and spawn them + assign names.
    spawnLoadMobs(Game::mobs);
    // Load Objects data into vector, and spawn them + assign names.
    spawnLoadObjects(Game::objectsX);


    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();

    /*
	//////////////////////////////////////THE GAME///////////////////////////////////////////
	int nextStep, i; //flags,PlayerTurn
	bool turn = true; //If Turn = false, Break and check flags to give the correct msg.
	while (true)
	{
		turn = true;
		for (i = 0; i < numberOfPlayers; i++) {
			moveMobs(mobs);//Iterate over all mobs and act();
			printMap(rooms, me, i);//Print The Map;
			me[i].status();
			nextStep = me[i].act(); //Do the next step.
			if (nextStep == 0 || nextStep == 2 || nextStep == 3) { // 0 = quit, 2 = WON, 3 = DEAD (Used after the while loop)
				turn = false;
				break;
			}
			//system("CLS");
		}
		if (!turn)
			break;
	}
	if (nextStep == 2) //The function act returned 2, Therefore the player WON.
		cout << ">> You WON!, " << me[i].getName() << "!, Congratulations !" << endl;
	else if (nextStep == 3) //The function act returned 3, The Player died.
		cout << ">> You Died :/" << endl;
	else if (nextStep == 0)
        cout << "Game Quits." << endl; //The function act returned 0, The player typed "quit".
	return 0;
*/
}

#include "player.h"
#include "helpers.h"
#include "prob.h"
#include "objects.h"  ///#refaie
#include <vector>  ///#refaie
#include <iostream>
using namespace std;


class objects;  ///#refaie
objects* defaultWep = new prob("Newbie-Sword", 1, 3); // DEFAULT WEAPON
player::player():Agent("Untitled",NULL,1,0)
{

}

player::player(string nameX, Room* posX, int levelX, int num, objects* wep) : Agent(nameX, posX, 1, levelX)
{
	health = 1000;
	type += num == 1 ? "1" : "2";
	if(wep != NULL)
		cur_held = wep;
	else
		cur_held = defaultWep;
	if(cur_pos != NULL)
		cur_pos->clearFog();
}

player::~player(){}

int player::act(string key)
{
	string command = "invalid";
	if (key == "w" || key == "u") command = "north";
	else if (key == "s" || key == "j") command = "south";
	else if (key == "d" || key == "k") command = "east";
	else if (key == "a" || key == "h") command = "west";
	else if (key == "e" || key == "i") command = "attack";
	else if (key == "q" || key == "y") command = "switch";
	else if (key == "f" || key == "l") command = "drop";
	else if (key == "r" || key == "o") command = "pick";
	cout << command << endl;
	cout << "health: " << health <<endl;

	// law mot yb2a enta keda 5sert, return 2 (2 = death)
	if( health <= 0 )
		return 2;

	if(command == "quit")
		return 0;

	else if(command == "drop")
	{
		if(weapons.size() > 0){
			printheld();
			printweapons();
			cout << "----------------------------------------" << endl;
			cout << "-Choose the preferred weapon: (1,2,3,..)" << endl;
			dropweapons();
			cout << "----------------------------------------" << endl;
			cout << ">> Dropped!"<<endl;
			return 1;
		}
	}

	else if(command == "switch")
	{
		if(weapons.size() > 0)
		{
			printheld();
			printweapons();
			cout << "----------------------------------------" << endl;
			cout << "-Choose the preferred weapon: (1,2,3,..)" << endl;
			switchweapons();
		}
	}

	else if(command == "pick")
	{
		// If nothing is here to pick
		if(cur_pos->cur_objs.size() == 0)
		{
			cout << "-------------------------------" << endl;
			cout << ">> There is no objects to pick." << endl;
		}

		// Something is here
		else
		{
			// If bag is full
			if(weapons.size() >= 5)
			{
				cout << "----------------------------------------"    << endl;
				cout << ">> You don't have enough space in your bag!" << endl;
			}

			// Bag is not full
			else
			{
				cur_pos->print_cur_objs();
				cout << "What do you want to pick ? (1,2,3,...)"<<endl;
				int i = 0;
				if(cur_pos->cur_objs[i]->act(this)) // Law 3reft t3mlo pick...
				{
					if(cur_pos->cur_objs[i]->getType() == 1){ //law prob
						cout << "----------------------------------------" << endl;
						cout << ">> You picked up " << cur_pos->cur_objs[i]->getName() << endl;
						cur_pos->cur_objs.erase(cur_pos->cur_objs.begin()+i);//emsa7o mn vector el room;
						return 1;
					}
					else if(cur_pos->cur_objs[i]->getType() == 2){ //law fixed
						cout << "----------------------------------------" << endl;
						cout << ">> You opened " << cur_pos->cur_objs[i]->getName() << " And gained +" << cur_pos->cur_objs[i]->getDamage() << "HP!." << endl;
						cur_pos->cur_objs[i]->setDamage(0);
						return 1;
					}
					else if(cur_pos->cur_objs[i]->getType() == 3){ //law treasure
						cout << "----------------------------------------" << endl;
						cout << ">> You picked up the treasure !!" << endl;
						return 2;
					}
				}
				else // law ma3rftsh te3mlo pick
				{
					cout << "----------------------------------------" << endl;
					cout << ">> You don't have a Key to Open this object." << endl;
				}
			}
		}
	}

	// Attack and return 1 ( 1 = game resumes)
	else if(command == "attack")
	{
		attack();
		cout << "----------------------------------------" << endl;
		cout << ">> You attacked all the monsters around you!" << endl;
		//system("PAUSE");
		//system("CLS");
		return 1;
	}

	// LAW YNF3 TT7ARK FE EL ROOM DEH E3ML KAZA...
	else if(move(command))
	{
		cout << "----------------------------------------" << endl;
		cout << ">> You moved " << command << "." << endl;
		cur_pos->clearFog(); //Clear the fog of WAR.
		return 1;
	}

	else if(cur_pos->getLinked(command) == NULL ||
			!cur_pos->getLinked(command)->isWall()) //LAW MA3rfsh yt7rak, check ma3rfsh leh.
	{

		cout << "----------------------------------------" << endl;
		cout << ">> There is a wall at the " << command << ", You can't move there.<<" << endl;
	}

	else
	{
		cout << "----------------------------------------" << endl;
		cout <<"The room is full, you can't enter this room at the moment."<<endl;
	}
}

string player::status()
{
	string ret = "";
	ret += "Name: " + name;
	ret += "\tLevel: " + to_string(level);
	ret += "\nHealth: " + to_string(health);
	ret += "\tDamage: " + to_string(cur_held->getDamage());
	ret += "\nWeapon: " + cur_held->getName();
	return ret;
	/*if(cur_pos != NULL){
		cur_pos->printCurrent();
		cur_pos->printOccupants();
		cout << "---------------Surroundings-------------" << endl;
		cur_pos->printSurroundAgent(); //Print Player surrounding monsters
		cur_pos->print_cur_objs();
		cur_pos->printLinked();
	}
	else cout << "You're not currently at any Room" << endl;*/
}

void player::attack()
{
	// Get all Surrounding agents and iterate through them
	vector<Agent*> surr = cur_pos->getSurroundAgent();
	for(int i = 0; i < surr.size(); i++)
		surr[i]->setHealth(surr[i]->getHealth() - (cur_held->getDamage()));
	//TODO: Damage should be according to current weapon
}

void player::printheld(){
	if(cur_held)
		cout<<"Your current weapon is "<<cur_held->getName()<<", Damage: " << cur_held->getDamage()<<endl;
}

void player::switchweapons(){
	// Appends the current one to the end of the vector
	weapons.push_back(cur_held);

	// Takes first weapon in the vector
	cur_held = weapons[0];
	weapons.erase(weapons.begin());
}

bool player::dropweapons(){
	if (weapons.size() > 0)
	{
		// Add the weapon to the room
		cur_pos->cur_objs.push_back(cur_held);

		// Take a weapon from the bag without adding the current one
		cur_held = weapons[0];
		weapons.erase(weapons.begin());
		return true;
	}
	return false;
}

void player::printweapons(){
	cout<<"Weapons in your bag are: ("<<weapons.size()<<")"<<endl;
	for(int i = 0; i < weapons.size(); i++){
		cout << "-> " << i+1 << " : " << weapons[i]->getName() << " - Damage: " << cur_held->getDamage()<<endl;
	}
}

void player::addObj(objects* x)
{
	if(x->getType() == 1)
		weapons.push_back(x);
}

#include "room.h"
#include "string"
#include "Agent.h"
#include "objects.h" ///#refaie
#include <iostream>
#include <fstream>
#include <vector>
#include "game.h"
using namespace std;

int Room::ID = 0;

Room::Room() {}

Room::Room(string nameX, string descX, bool typeX) {
	name = nameX;
	desc = descX;
	north = NULL;
	south = NULL;
	east = NULL;
	west = NULL;
    wall = typeX;
	roomSize = 0;
	roomID = ID++;
	fog = true;
	cur_obj = NULL;  ///#refaie
}

Room::~Room() { // UNLINKING all other rooms from the being deleted room.

}

string Room::getName() {
	if (this == NULL)
		return "Wall";
	return name;
}

string Room::getDescription() {
	if (this == NULL)
		return "Imtype Object";
	return desc;
}

void Room::printCurrent() {
	cout << "Your are now at " << name << ", " << desc << "." << endl;
}

void Room::printLinked() {
	cout << "Your Surroundings are: " << endl;
	if (north && north->getType()) {
		if (north->fog)
			cout << "-North: " << north->getName() << endl;
		else cout << "-North: ?" << endl;
	}
	else cout << "-North: Wall" << endl;

	if (south && south->getType()) {
		if (south->fog)
			cout << "-South: " << south->getName() << endl;
		else cout << "-South: ?" << endl;
	}
	else cout << "-South: Wall" << endl;

	if (west && west->getType()) {
		if (west->fog)
			cout << "-West: " << west->getName() << endl;
		else cout << "-West: ?" << endl;
	}
	else cout << "-West: Wall" << endl;

	if (east && east->getType()) {
		if (east->fog)
			cout << "-East: " << east->getName() << endl;
		else cout << "-East: ?" << endl;
	}
	else cout << "-East: Wall" << endl;
}

void Room::printOccupants()
{
	cout << "This room contains:" << endl;
	for (int i = 0; i < roomSize; i++) {
        if (occupants[i]->getType() == "monster") //law monster
			cout << i + 1 << ": " << occupants[i]->getName() << " :\tHealth: " << occupants[i]->getHealth() << " :\tMonster" << endl;
        else if (occupants[i]->getType() == "player")//Law Player
			cout << i + 1 << ": " << occupants[i]->getName() << " :\tHealth: " << occupants[i]->getHealth() << " :\tPlayer" << endl;

	}
}

void Room::link(Room* r, string direction) {
	if (r == NULL) return; //ensuring correct usage.
    else if (direction == "north") north = r;
    else if (direction == "south") south = r;
    else if (direction == "east") east = r;
    else if (direction == "west") west = r;
	return;
}

void Room::unlink(string direction) { //UNLINK BACK AND FORTH.
	if (direction == "north") { north->south = NULL; north = NULL; }
	else if (direction == "south") { south->north = NULL; south = NULL; }
	else if (direction == "east") { east->west = NULL; east = NULL; }
	else if (direction == "west") { west->east = NULL; west = NULL; }
	else if (direction == "all") {
		if (north != NULL)north->south = NULL; north = NULL;
		if (south != NULL)south->north = NULL; south = NULL;
		if (east != NULL)east->west = NULL; east = NULL;
		if (west != NULL)west->east = NULL; west = NULL;
	}
	else return;
}
Room* Room::getLinked(string direction) {
	if (direction == "north") return north;
	else if (direction == "south") return south;
	else if (direction == "east") return east;
	else if (direction == "west") return west;
	else return NULL;
}

bool Room::enter(Agent* x)
{
    if (roomSize < 5 && !wall) {
		occupants.push_back(x);
		roomSize++;
		return true;
	}
	return false;
}
bool Room::leave(Agent* x) {
	if (this == NULL) return false;
	for (int i = 0; i < roomSize; i++)
		if (occupants[i]->getIndex() == x->getIndex()) {
			occupants.erase(occupants.begin() + i);
			roomSize--;
			return true;
		}
}

void Room::clearFog() {
	// Clear current room's fog 
	fog = false;

	// Clear the 4 neighbors
	if (north) north->fog = false;
	if (south) south->fog = false;
	if (east) east->fog = false;
	if (west) west->fog = false;

	// The corners
	if (north && north->getLinked("east"))
		north->getLinked("east")->fog = false;
	if (north && north->getLinked("west"))
		north->getLinked("west")->fog = false;
	if (south && south->getLinked("east"))
		south->getLinked("east")->fog = false;
	if (south && south->getLinked("west"))
		south->getLinked("west")->fog = false;
}

vector<Room*> Room::getSurround() {
	vector<Room*> surr;
	//1:North 2:South 3:West 4:East //5:North/West 6:North/East 7:South/West 8:South/East
	//NULL if it doesn't exist.

	// The 4 neighbors
	if (north) surr.push_back(north);
	if (south) surr.push_back(south);
	if (east) surr.push_back(west);
	if (west) surr.push_back(west);
	
	// The corners
	if (north && north->getLinked("east"))
		surr.push_back(north->getLinked("east"));
	if (north && north->getLinked("west"))
			surr.push_back(north->getLinked("west"));
	if (south && south->getLinked("east"))
		surr.push_back(south->getLinked("east"));
	if (south && south->getLinked("west"))
		surr.push_back(south->getLinked("west"));
	return surr;
}

void Room::printSurroundRooms() {
	cout << name << endl;
	cout << "---" << endl;
	vector<Room*> surr = getSurround();
	for (int i = 0; i < surr.size(); i++)
		cout << surr[i]->getName() << endl;
}


vector<Agent*> Room::getSurroundAgent() {
	vector<Agent*> surr;
	vector<Room*> surrRooms = getSurround();
	for (int i = 0; i < surrRooms.size(); i++)
		for (int j = 0; j < surrRooms[i]->occupants.size(); j++)
			surr.push_back(surrRooms[i]->occupants[j]);
	return surr;
}

void Room::printSurroundAgent() {
	vector<Agent*> surr = getSurroundAgent();
	for (int i = 0; i < surr.size(); i++)
	{
		cout << i + 1 << " -> " << surr[i]->getName() << " : Health: " << surr[i]->getHealth() << endl;
	}
}

///#refaie
void Room::print_cur_obj() {
	cout << "----------------------------------------" << endl;
	if (cur_obj != NULL) {
		cout << "This room contains: ";
		if (cur_obj->getType() == 1) {
			if (cur_obj->getName() == "Chest-Key") cout << "Chest-Key" << endl;
			else if (cur_obj->getName() == "Treasure-Key") cout << "Treasure-Key" << endl;
			else cout << "Weapon: " << cur_obj->getName() << " , Damage: " << cur_obj->getDamage() << endl;
		}
		else if (cur_obj->getType() == 2) {
			cout << "Chest: " << cur_obj->getName() << " , Heals for: +" << cur_obj->getDamage() << "HP" << endl;
		}
		else if (cur_obj->getType() == 3) {
			cout << "THE TREASURE, " << cur_obj->getName() << endl;
		}
	}
	else {
		cout << "there are no objects here " << endl;
	}
	cout << "----------------------------------------" << endl;
}

void Room::setObj(objects* x)
{
	cur_obj = x;
}

bool Room::isFogged()
{
	return fog;
}

bool Room::isWall()
{
    return wall;
}

void Room::initializeRooms()
{
    vector<string> map;
    fstream roomData;
    fstream roomName;
    roomData.open("roomData.txt", ios::in);
    roomName.open("roomName.txt", ios::in);

    string temp;
    while (roomData >> temp)
        map.push_back(temp);

    Game::mapWidth = map[0].length();
    Game::mapHeight = map.size();

    // Resize rooms vector
    Game::rooms.assign(Game::mapHeight, vector<Room>(Game::mapWidth));

    string name;
    string desc = "Description: later to be added";

    for (int i = 0; i < Game::mapHeight; i++)
        for (int j = 0; j < Game::mapWidth; j++)
        {
            // Read room name
            roomName >> name;
            Game::rooms[i][j] = Room(name, desc, map[i][j] == '#');
        }

    // LINKINK
    for (int i = 0; i < Game::mapHeight; i++)
        for (int j = 0; j < Game::mapWidth; j++)
        {
            if (i > 0)
                Game::rooms[i][j].link(&Game::rooms[i - 1][j], "north");
            if (i < Game::mapHeight - 1)
                Game::rooms[i][j].link(&Game::rooms[i + 1][j], "south");
            if (j > 0)
                Game::rooms[i][j].link(&Game::rooms[i][j - 1], "west");
            if (j < Game::mapWidth - 1)
                Game::rooms[i][j].link(&Game::rooms[i][j + 1], "east");
        }
    roomData.close();
    roomName.close();
}

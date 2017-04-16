#include "agent.h"
#include "helpers.h"
#include <iostream>
using namespace std;

int Agent::TotalIndexs = 0; // Initialize IDs

Agent::Agent(string nameX = "Untitled", Room* posX = NULL, int typeX = 0, int levelX = 0)
{
	index = TotalIndexs++;
	type = typeX == 1 ? "player" : "monster";
	name = nameX;
	level = levelX;
	health = 10 * levelX;
	cur_pos = posX;
	if (cur_pos != NULL)
		cur_pos->enter(this); //Add Agent to Initialized room(if exist).
}

Agent::~Agent()
{
	if (cur_pos != NULL)//IF Agent is Currently in a room.
		cur_pos->leave(this); //Remove the Agent from the current room.
}

//GETTERS
int Agent::getIndex() { return index; }
string Agent::getName() { return name; }
string Agent::getType() { return type; }
int Agent::getHealth() { return health; }
Room* Agent::getPos() { return cur_pos; }

//SETTERS
void Agent::rename(string x) { name = x; }
void Agent::setHealth(int x)
{
	if (x <= 0 && health > 0)
		cur_pos->leave(this);
	health = x;
}

bool Agent::assignRoom(Room* x)
{
	if (!x) return false;
	if (x->enter(this))
	{
		cur_pos->leave(this);
		cur_pos = x;
		return true;
	}
	else return false;
}

bool Agent::move(string direction)
{
	Room* destination = cur_pos->getLinked(direction);
	if (destination && !destination->isWall() && destination->enter(this))
		{
			cur_pos->leave(this);
			cur_pos = destination;
			return true;
		}
	return false;
}

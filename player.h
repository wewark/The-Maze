#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include "Agent.h"
#include "objects.h"


class objects;

class player : public Agent
{
private:
	string warning;

public:
	player();
	player(string nameX, Room* posX, int levelX, int num, objects* wep=NULL);
	virtual ~player();
	int act(string key);
	string status();
	void attack();
	vector<objects*> weapons;
	objects *cur_held;
	void printheld();
	void switchweapons();
	bool dropweapons();
	void printweapons();
	void addObj(objects* x);
};

#endif // PLAYER_H

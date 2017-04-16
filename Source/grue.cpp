#include "grue.h"
#include <stdlib.h>
#include <time.h>
#include "helpers.h"
#include <iostream>
#include <queue>
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
	if (path == "random")
	{
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
	}
	else if (path == "chase")
	{
		// AI
		string direction = chase(cur_pos);
		if (direction != "wait")
			move(direction);
	}
	return 0; //Never gonna reach here anyway.
}

// AI
// Using breadth first search
string grue::chase(Room* cur)
{
	vis.assign(Game::mapHeight, vector<bool>(Game::mapWidth, false));
	queue<pair<string,pair<int,int>>> q;
	string dir[] = { "north", "south", "east", "west"};
	if (cur->containsPlayer())
		return "wait";
	for	(int i = 0; i < 4; i++)
	{
		if (cur->getLinked(dir[i]) &&
			!cur->getLinked(dir[i])->isWall())
			q.push(make_pair(dir[i], make_pair(cur->getLinked(dir[i])->getPosi(),
											   cur->getLinked(dir[i])->getPosj())));
		if (cur->getLinked(dir[i]) &&
			cur->getLinked(dir[i])->containsPlayer())
			return "wait";
	}
	vis[cur->getPosi()][cur->getPosj()] = true;
	while (!q.empty())
	{
		string cur_dir = q.front().first;
		int cur_i = q.front().second.first, cur_j = q.front().second.second;
		if (!vis[cur_i][cur_j])
		{
			vis[cur_i][cur_j] = true;
			if (Game::rooms[cur_i][cur_j].containsPlayer())
				return cur_dir;
			else
				for	(int i = 0; i < 4; i++)
					if (Game::rooms[cur_i][cur_j].getLinked(dir[i]) &&
						!Game::rooms[cur_i][cur_j].getLinked(dir[i])->isWall())
						q.push(make_pair(cur_dir, make_pair(Game::rooms[cur_i][cur_j].getLinked(dir[i])->getPosi(),
															Game::rooms[cur_i][cur_j].getLinked(dir[i])->getPosj())));
		}
		q.pop();
	}
	return "north";
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

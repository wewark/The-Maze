#ifndef AGENT_H
#define AGENT_H
#include<string>
#include "room.h"
using namespace std;

class Agent
{
    public:
		Agent(string nameX , Room* posX, int typeX,int level);
		virtual ~Agent();
		static int TotalIndexs; // Total Number of Agents in the program.

		//FUNCTIONS
		virtual int act(string) = 0;
		virtual string status() = 0; // Print Agent's current status and stats.
        bool move(string direction);

        //-Setters-//
        void rename(string x);
        void setHealth(int x);
        bool assignRoom(Room* x);

        //-Getters-//
        string getName();
        string getType();
        int getHealth();
        Room* getPos();
        int getIndex();
		int getLevel() { return level; }


    protected:
		int index; // Unique Identifier
        int health;
        int level;
		string type; // 1=Player, 0=Monster, 2,3,4... later.
        string name;
        Room* cur_pos;
};
#endif // AGENT_H

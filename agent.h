#ifndef AGENT_H
#define AGENT_H
#include<string>
#include "room.h"
using namespace std;

class Agent
{
    public:
        Agent(string nameX , Room* posX, int typeX,int level); //Constructor
        virtual ~Agent();//Destructor
        static int TotalIndexs; //Total Number of Agents in the program.
        //FUNCTIONS
        virtual int act() { return 0; };
        virtual int act(string) { return 0; };
        virtual void status() = 0;//Print Agent's current status and stats.
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

    protected:
        int index;//Unique Identifier
        int health;
        int level;
        string type; //1=Player, 0=Monster, 2,3,4... later.
        string name;
        Room* cur_pos;
};
#endif // AGENT_H

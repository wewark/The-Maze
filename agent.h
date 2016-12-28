#ifndef AGENT_H
#define AGENT_H
#include<string>
#include"room.h"
using namespace std;

class Agent
{
    public:
        Agent(string nameX , room* posX, int typeX,int level); //Constructor
        virtual ~Agent();//Destructor
        static int TotalIndexs; //Total Number of Agents in the program.
        //FUNCTIONS
        virtual int act() = 0;
        virtual void attack() = 0;
        virtual void status() = 0;//Print Agent's current status and stats.
        bool move(string direction);
        //-Setters-//
        void rename(string x);
        void setHealth(int x);
        bool assignRoom(room* x);
        //-Getters-//
        string getName();
        int getType();
        int getHealth();
        room* getPos();
        int getIndex();
        int getLevel(){return level;}

    protected:
        int index;//Unique Identifier
        int health;
        int level;
        int type; //1=Player, 0=Monster, 2,3,4... later.
        string name;
        room* cur_pos;
};
#endif // AGENT_H

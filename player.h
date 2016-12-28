#ifndef PLAYER_H
#define PLAYER_H
#include <vector>    ///#refaie
#include "Agent.h"
#include "objects.h"  ///#refaie


class objects;  ///#refaie


class player : public Agent
{
    public:
        player();
        player(string nameX, room* posX, int levelX, objects* wep=NULL);
        virtual ~player();
        int act();
        void attack();
        void status();
        void attackAround();
        vector<objects*> weapons;   ///#refaie
        objects *cur_held;          ///#refaie
        void printheld();           ///#refaie
        bool switchweapons(int w);///#refaie
        bool dropweapons(int w);
        void printweapons();        ///#refaie
        void addObj(objects* x);
    protected:

    private:
};

#endif // PLAYER_H

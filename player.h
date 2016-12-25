#ifndef PLAYER_H
#define PLAYER_H
#include <vector>    ///#refaie
#include "Agent.h"
#include "objects.h"  ///#refaie


class objects;  ///#refaie


class player : public Agent
{
    public:
        player(string nameX="Untitled", room* posX=NULL, int levelX=0);
        virtual ~player();
        int act();
        void status();
        void attackAround();
        vector<objects* >weapons;   ///#refaie
        objects *cur_held;          ///#refaie
        void printheld();           ///#refaie
        void switchweapons();       ///#refaie
        void printweapons();        ///#refaie
    protected:

    private:
};

#endif // PLAYER_H

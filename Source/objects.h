#ifndef OBJECTS_H
#define OBJECTS_H
#include "room.h"
#include "player.h"
#include <iostream>
using namespace std;

class player;

class objects
{
    public:
        objects(string nameX, int typeX, int damageX);
        string getName();
        void setName(string);
        int getType();
        void setType(int);
        void setDamage(int);
        int getDamage();
        virtual bool act(player *p)=0;

    protected:
        int type;   /// 1- prop  , 2-fixed  , 3- treasure
        string name;
        int damage;

};

#endif // OBJECTS_H

#ifndef OBJECTS_H
#define OBJECTS_H
#include "../room.h"
#include "../player.h"
#include <iostream>
using namespace std;

class player;

class objects
{
    public:
        string getname();
        void setname(string);
        int getcondition();
        void setcondition(int);
        virtual bool act(player *p)=0;

    protected:
        int condition;   /// 1- prop  , 2-fixed  , 3- treasure
        string name;

};

#endif // OBJECTS_H

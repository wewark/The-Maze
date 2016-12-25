#ifndef TREASURE_H
#define TREASURE_H
#include "objects.h"
#include "room.h"
#include "player.h"
#include <iostream>
using namespace std;

class treasure : public objects
{
    public:
        treasure(string x,int c);
        bool act(player *p);

    protected:

    private:
};

#endif // TREASURE_H

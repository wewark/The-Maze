#ifndef PROB_H
#define PROB_H
#include "objects.h"
#include "room.h"
#include "player.h"
#include <iostream>
using namespace std;

class prob : public objects
{
    public:
        prob(string x,int c);
        bool act(player *p);

    protected:

    private:
};

#endif // PROB_H

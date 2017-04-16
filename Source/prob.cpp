#include "prob.h"
#include "objects.h"
#include "room.h"
#include "player.h"
#include <iostream>
using namespace std;
prob::prob(string x,int c, int d):objects(x,c,d)
{
}

bool prob::act(player *p){
    p->weapons.push_back(this);
    return true;
}


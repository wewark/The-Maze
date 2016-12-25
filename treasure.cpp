#include "treasure.h"
#include "objects.h"
#include "../room.h"
#include "../player.h"
#include <iostream>
using namespace std;

treasure::treasure(string x, int c)
{
    condition=c;
    name=x;
}

bool treasure::act(player *p){

cout<<"congrats "<<p->getName()<<" you reached the Treasure "<<endl;
return true;

}


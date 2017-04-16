#include "treasure.h"
#include "objects.h"
#include "room.h"
#include "player.h"
#include <iostream>
using namespace std;
treasure::treasure(string x,int c,int d):objects(x,c,0)
{

}
bool treasure::act(player *p){
    for(int i=0;i<p->weapons.size();i++){
        if(p->weapons[i]->getName()=="Treasure-Key"){
            return true;
        }
    }
    return false;
}

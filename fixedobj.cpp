#include "fixedobj.h"
#include "objects.h"
#include "room.h"
#include "player.h"
#include <iostream>
using namespace std;
fixedobj::fixedobj(string x,int c,int d):objects(x,c,d)
{

}
bool fixedobj::act(player *p){
    for(int i=0;i<p->weapons.size();i++){
        if(p->weapons[i]->getName()=="Chest-Key"){
            p->setHealth(p->getHealth()+getDamage());
            return true;
        }
    }
    return false;
}

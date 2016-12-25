#include "fixedobj.h"
#include "objects.h"
#include "../room.h"
#include "../player.h"
#include <iostream>
using namespace std;

fixedobj::fixedobj(string x,int c)
{
    name=x;
    condition=c;
}

bool fixedobj::act(player *p){
bool check=false;
for(int i=0;i<p->weapons.size();i++){
    if(p->weapons[i]->getname()=="key"){
        p->setHealth(p->getHealth()+10);
        cout<<"YOU GOT THE RIGHT KEY TO OPEN "<<name<<endl;
        cout<<"YOU GAINED 10 HEALTH POINTS "<<p->getName()<<endl;
        check=true;
        break;
    }
}
if(check==false){
    cout<<"YOU DON'T HAVE THE RIGHT KEY TO OPEN "<<name<<endl;
}
return true;
}

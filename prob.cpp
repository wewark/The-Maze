#include "prob.h"
#include "objects.h"
#include "room.h"
#include "player.h"
#include <iostream>
using namespace std;

prob::prob(string x,int c)
{
    name=x;
    condition=c;
}

bool prob::act(player *p){
cout<<"type pick to put the prob in your weapons "<<endl;
string s;
cin>>s;
if(s=="pick"){
    cout<<"you have "<<name<<" now in your weapons"<<endl;
    p->weapons.push_back(this);
    return true;  /// the player picked the object so i should make the cur_obj in the room null
}
else {
    cout<<"invalid choice "<<endl;
    return false; /// the player didn't picked the object so i should leave the cur_obj in the room as it is
}


}


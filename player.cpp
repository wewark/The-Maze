#include "player.h"
#include "helpers.h"
#include "objects.h"  ///#refaie
#include <vector>  ///#refaie
#include <iostream>
using namespace std;


class objects;  ///#refaie



player::player(string nameX, room* posX, int levelX):Agent(nameX,posX,1,levelX)
{
    if(cur_pos != NULL)
        cur_pos->fogClear();
    cur_held= NULL; ///#refaie
}
player::~player(){}
int player::act()
{
    while(true){
        if( health <= 0 )//law mot yb2a enta keda 5sert, return 2 (2 = death)
            return 2;
        cout << "---------------YOUR STATS---------------" << endl;
        cout << "||Name: " << name << ", Level: " << level << " Health: " << health << "||" << endl;
        cout << "----------------------------------------" << endl;
        status(); //Print surrounding.
        cout << ">> Please Type(North,South,East,West) to move" << endl;
        cout << "or Type \"Attack\" to attack all the surrounding monsters" << endl;
        string command = getDirections(); //get direction and return lower-case command and Invalid if unwanted command.
        if(command == "quit") //Quit with flag = 0
            return 0;
        else if(command == "invalid") //Re-enter the while loop until a valid command.
        {
            system("CLS");
            cout << ">> Invalid Command" << endl;
            cout << "- Hint: type \"Quit\" to exit" << endl;
        }
        else if(command == "attack")//Attack and return 1 ( 1 = game resumes)
        {
            attackAround();
            return 1;
        }
        else if(move(command))//LAW YNF3 TT7ARK FE EL ROOM DEH E3ML KAZA...
        {
            cur_pos->fogClear(); //Clear the fog of WAR.
            return 1;
        }
        else if(cur_pos->getLinked(command)==NULL || cur_pos->getLinked(command)->getType() == 0 ) //LAW MA3rfsh yt7rak, check ma3rfsh leh.
        {
            system("CLS");
            cout << ">> There is a wall at the " << command << ", You can't move there.<<" << endl;
        }
        else cout <<"The room is full, you can't enter this room at the moment."<<endl;
    }
}
void player::status()
{
    if(cur_pos != NULL){
        cur_pos->printCurrent();
        cur_pos->printOccupants();
        cur_pos->printLinked();
    }
    else cout << "Not currently at any Room" << endl;

}

void player::attackAround()
{
    vector<Agent*> surr = cur_pos->getSurroundAgent(); //Get all Surrounding agents and iterate through them
    for(int i=0; i<surr.size(); i++)
    {
        if(surr[i]->getType()==0) //IF THE AGENT IS A MONSTER
            surr[i]->setHealth(surr[i]->getHealth()-10); //ATTACK, #TODO Damage should be according to current weapon(Implmented later)
    }
}

///#refaie all functions down there

void player::printheld(){
cout<<"your current weapon is "<<cur_held->getname()<<endl;
}

void player::switchweapons(){
cout<<"the weapons in your bag are "<<weapons.size()<<endl;
for(int i=0;i<weapons.size();i++){
    cout<<weapons[i]->getname()<<endl;
}
cout<<"type the name of the weapon you want to switch with "<<endl;
string w;
cin>>w;
objects *temp=cur_held;
bool check=false;
for(int i=0;i<weapons.size();i++){
    if(weapons[i]->getname()==w){
        cur_held=weapons[i];
        weapons[i]=temp;
        cout<<"you successfully switched the weapons"<<endl;
        check=true;
        printheld();
        break;
    }
}
if(check==false){
    cout<<"invalid choice"<<endl;
}

}

void player::printweapons(){
cout<<"the weapons in your bag are "<<weapons.size()<<endl;
for(int i=0;i<weapons.size();i++){
    cout<<weapons[i]->getname()<<endl;
}

}

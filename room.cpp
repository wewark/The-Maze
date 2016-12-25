#include "room.h"
#include "string"
#include "Agent.h"
#include "objects.h" ///#refaie
#include <iostream>
#include<vector>
using namespace std;
int room::ID = 0;
room::room(){}
room::room(string nameX, string descX, int typeX){
    name = nameX;
    desc = descX;
    north = NULL;
    south = NULL;
    east = NULL;
    west = NULL;
    type = typeX;
    roomSize = 0;
    roomID = ID++;
    fog = 1;
    cur_obj= NULL;  ///#refaie
}
room::~room(){//UNLINKING all other rooms from the being deleted room.

}
string room::getName(){
    if(this == NULL) return "Wall";
    else return name;
}
string room::getDescription(){
    if(this == NULL) return "Imtype Object";
    else return desc;
}

void room::printCurrent(){
    cout << "Your are now at " << name << ", " << desc << "." << endl;
}
void room::printLinked(){
    cout << "Your Surroundings are: " << endl;
    if(north!=NULL && north->getType()){
    	if(north->fog)
    		cout << "-North: " << north->getName() << endl;
    	else cout <<"-North: ?" <<endl;
    }
    else cout << "-North: Wall" << endl;

    if(south!=NULL && south->getType()){
    	if(south->fog)
    		cout << "-South: " << south->getName() << endl;
    	else cout <<"-South: ?" <<endl;
    }
    else cout << "-South: Wall" << endl;

    if(west!=NULL && west->getType()){
    	if(west->fog)
    		cout << "-West: " << west->getName() << endl;
    	else cout <<"-West: ?" <<endl;
    }
    else cout << "-West: Wall" << endl;

    if(east!=NULL && east->getType()){
    	if(east->fog)
    		cout << "-East: " << east->getName() << endl;
    	else cout <<"-East: ?" <<endl;
    }
    else cout << "-East: Wall" << endl;
}
void room::printOccupants()
{
    cout << "This room contains:" << endl;
    for(int i=0; i<roomSize; i++){
        if(occupants[i]->getType()==0) //law monster
        cout << i+1 << ": " << occupants[i]->getName() << " :\tHealth: " << occupants[i]->getHealth() << " :\tMonster" << endl;
        else if(occupants[i]->getType()==1)//Law Player
        cout << i+1 << ": " << occupants[i]->getName() << " :\tHealth: " << occupants[i]->getHealth() << " :\tPlayer" << endl;

    }
}
void room::link(room* r,string direction){
    if(r == NULL) return; //ensuring correct usage.
    else if (direction == "north") { north = r; north->south = this; } //back and forth linking
    else if (direction == "south") { south = r; south->north = this; } ////////////////////////
    else if (direction == "east") { east = r; east->west = this; }     ////////////////////////
    else if (direction == "west") { west = r; west->east = this; }     ////////////////////////
    return;
}

void room::unlink(string direction){ //UNLINK BACK AND FORTH.
   if (direction == "north") {north->south = NULL; north = NULL;}
   else if (direction == "south") { south->north = NULL; south = NULL;}
   else if (direction == "east") { east->west = NULL; east = NULL;}
   else if (direction == "west") { west->east = NULL; west = NULL;}
   else if (direction == "all") {
       if( north != NULL )north->south = NULL; north = NULL;
       if( south != NULL )south->north = NULL; south = NULL;
       if( east != NULL )east->west = NULL; east = NULL;
       if( west != NULL )west->east = NULL; west = NULL;
   }
   else return;
}
room* room::getLinked(string direction){
    if(direction == "north") return north;
    else if (direction == "south") return south;
    else if (direction == "east") return east;
    else if (direction == "west") return west;
    else return NULL;
}

bool room::enter(Agent* x)
{
    if(roomSize<5 && type >= 1){
        occupants.push_back(x);
        roomSize++;
        return true;
    }
    else return false;
}
bool room::leave(Agent* x){
    if(this == NULL) return false;
    for(int i=0; i<roomSize; i++)
    {
        if(occupants[i]->getIndex()==x->getIndex()){
            occupants.erase(occupants.begin()+i);
            roomSize--;
            return true;
            break;
        }
    }
}

void room::fogClear(){
    this->fog=1;
    if(this->getLinked("north")!=NULL){
        this->getLinked("north")->fog=1;
        if(this->getLinked("north")->getLinked("east")!=NULL)
            this->getLinked("north")->getLinked("east")->fog=1;
        if(this->getLinked("north")->getLinked("west")!=NULL)
            this->getLinked("north")->getLinked("west")->fog=1;
    }
    if(this->getLinked("south")!=NULL){
        this->getLinked("south")->fog=1;
            if(this->getLinked("south")->getLinked("east")!=NULL)
                this->getLinked("south")->getLinked("east")->fog=1;
            if(this->getLinked("south")->getLinked("west")!=NULL)
                this->getLinked("south")->getLinked("west")->fog=1;
    }

    if(this->getLinked("east")!=NULL){
        this->getLinked("east")->fog=1;
            if(this->getLinked("east")->getLinked("north")!=NULL)
                this->getLinked("east")->getLinked("north")->fog=1;
            if(this->getLinked("east")->getLinked("south")!=NULL)
                this->getLinked("east")->getLinked("south")->fog=1;
    }
    if(this->getLinked("west")!=NULL){
        this->getLinked("west")->fog=1;
            if(this->getLinked("west")->getLinked("north")!=NULL)
                this->getLinked("west")->getLinked("north")->fog=1;
            if(this->getLinked("west")->getLinked("south")!=NULL)
                this->getLinked("west")->getLinked("south")->fog=1;
    }
}

vector<room*> room::getSurround(){
    vector<room*> surr;
    //1:North 2:South 3:West 4:East //5:North/West 6:North/East 7:South/West 8:South/East
    //NULL if it doesn't exist.
        if(this->getLinked("north")!=NULL)
            surr.push_back(this->getLinked("north"));
        if(this->getLinked("south")!=NULL)
            surr.push_back(getLinked("south"));
        if(this->getLinked("west")!=NULL)
            surr.push_back(this->getLinked("west"));
        if(this->getLinked("east")!=NULL)
            surr.push_back(this->getLinked("east"));
        if(this->getLinked("north")!=NULL)
            if(this->getLinked("north")->getLinked("west")!=NULL)
                surr.push_back(this->getLinked("north")->getLinked("west"));
        if(this->getLinked("north")!=NULL)
            if(this->getLinked("north")->getLinked("east")!=NULL)
                surr.push_back(this->getLinked("north")->getLinked("east"));
        if(this->getLinked("south")!=NULL)
            if(this->getLinked("south")->getLinked("west")!=NULL)
                surr.push_back(this->getLinked("south")->getLinked("west"));
        if(this->getLinked("south")!=NULL)
            if(this->getLinked("south")->getLinked("east")!=NULL)
                surr.push_back(this->getLinked("south")->getLinked("east"));
    return surr;
}

void room::printSurroundRooms(){
        cout << this->getName() << endl;
        cout << "---" << endl;
        vector<room*> surr = this->getSurround();
        for(int i=0; i<surr.size(); i++)
                cout << surr[i]->getName() << endl;
}


vector<Agent*> room::getSurroundAgent(){
    vector<Agent*> surr;
    vector<room*> surrRooms = this->getSurround();
    for(int i=0; i<surrRooms.size(); i++)
    {
        for(int j=0; j<surrRooms[i]->occupants.size(); j++)
        {
            surr.push_back(surrRooms[i]->occupants[j]);
        }
    }
    return surr;
}

void room::printSurroundAgent(){
    vector<Agent*> surr=getSurroundAgent();
    for(int i=0; i<surr.size(); i++)
    {
        cout << surr[i]->getName() << " : Health: " << surr[i]->getHealth() << endl;
    }
}

///#refaie
void room::print_cur_obj(){
if(cur_obj!= NULL){
    if(cur_obj->getcondition()==1){
        cout<<"prob "<<cur_obj->getname()<<endl;
    }
    else if(cur_obj->getcondition()==2){
        cout<<"fixed object "<<cur_obj->getname()<<endl;
    }
    else if(cur_obj->getcondition()==3){
        cout<<"The treasure "<<endl;
    }
}
else {
    cout<<"there is no objects here "<<endl;
}

}

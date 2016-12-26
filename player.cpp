#include "player.h"
#include "helpers.h"
#include "prob.h"
#include "objects.h"  ///#refaie
#include <vector>  ///#refaie
#include <iostream>
using namespace std;


class objects;  ///#refaie
objects* defaultWep = new prob("Newbie-Sword", 1, 3); // DEFAULT WEAPON
player::player():Agent("Untitled",NULL,1,0)
{

}
player::player(string nameX, Room* posX, int levelX, objects* wep) : Agent(nameX, posX, 1, levelX)
{
    if(wep != NULL)
        cur_held = wep;
    else
        cur_held = defaultWep;
    if(cur_pos != NULL)
        cur_pos->clearFog();
}

player::~player(){}

int player::act(string key)
{
    string command = "invalid";
    if (key == "w") command = "north";
    else if (key == "s") command = "south";
    else if (key == "d") command = "east";
    else if (key == "a") command = "west";
    else if (key == "e") command = "attack";
    else if (key == "q") command = "switch";
    cout << "you did " << command << endl;

        if( health <= 0 ) return 2; // law mot yb2a enta keda 5sert, return 2 (2 = death)
        cout << endl;
        cout << ">> Please Type(North,South,East,West) to move." << endl;
        cout << ">> Type \"Attack\" to attack all the surrounding monsters." << endl;
        cout << ">> Type \"Pick\" to pick room's object\n>> Type \"Switch\" to switch between your weapons" << endl;
        //string command = getDirections(); //get direction and return lower-case command and Invalid if unwanted command.
        if(command == "quit"){//Quit with flag = 0
            system("CLS");
            return 0;
        }
        else if(command == "invalid") //Re-enter the while loop until a valid command.
        {
            cout << "----------------------------------------" << endl;
            cout << ">> Invalid Command" << endl;
            cout << "Hint: type \"Quit\" to exit" << endl;
        }
        else if(command == "switch")
        {
            if(weapons.size()==0){
                cout << "----------------------------------------" << endl;
                cout << ">> You don't have weapons in your bag\n\n" << endl;
            }
            else while(true){
            printheld();
            printweapons();
            cout << "----------------------------------------" << endl;
            cout << "-Choose the preferred weapon: (1,2,3,..)" << endl;
            int w;  cin >> w;
            if(switchweapons(w))
            {
                cout << "----------------------------------------" << endl;
                cout << ">> Switched!, You're currently holding " << cur_held->getName() << ", Damage: " << cur_held->getDamage() << endl <<endl;
                system ("PAUSE");
                system("CLS");
                return 1;
            }
            else
            {
                cout << "----------------------------------------" << endl;
                cout <<" >> You don't this item in your bag"<<endl;
            }
        }
        }
        else if(command == "pick")
        {
            if(cur_pos->cur_obj->act(this))//Law 3reft t3mlo pick...
            {
                if(cur_pos->cur_obj->getType()==1){ //law prob
                    cout << "----------------------------------------" << endl;
                    cout << ">> You picked up " << cur_pos->cur_obj->getName() << endl;
                    system("PAUSE");
                    system("CLS");
                    cur_pos->cur_obj=NULL;
                    return 1;
                }
                else if(cur_pos->cur_obj->getType()==2){ //law fixed
                    cout << "----------------------------------------" << endl;
                    cout << ">> You picked up " << cur_pos->cur_obj->getName() << endl;
                    system("PAUSE");
                    system("CLS");
                    cur_pos->cur_obj->setDamage(0);
                    return 1;
                }
                else if(cur_pos->cur_obj->getType()==3){ //law treasure
                    cout << "----------------------------------------" << endl;
                    cout << ">> You picked up the treasure !!" << endl;
                    system("PAUSE");
                    system("CLS");
                    return 2;
                }
            }
            else
            {
                cout << "----------------------------------------" << endl;
                cout << ">> You don't have a Key to Open this object." << endl;
            }
        }
        else if(command == "attack")//Attack and return 1 ( 1 = game resumes)
        {
            attackAround();
            cout << "----------------------------------------" << endl;
            cout << ">> You attacked all the monsters around you!" << endl;
            //system("PAUSE");
            //system("CLS");
            return 1;
        }
        else if(move(command))//LAW YNF3 TT7ARK FE EL ROOM DEH E3ML KAZA...
        {
            cout << "----------------------------------------" << endl;
            cout << ">> You moved " << command << "." << endl;
            //system("PAUSE");
            //system("CLS");
            cur_pos->clearFog(); //Clear the fog of WAR.
            return 1;
        }
        else if(cur_pos->getLinked(command)==NULL || !cur_pos->getLinked(command)->isWall()) //LAW MA3rfsh yt7rak, check ma3rfsh leh.
        {

            cout << "----------------------------------------" << endl;
            cout << ">> There is a wall at the " << command << ", You can't move there.<<" << endl;
        }
        else
        {
            cout << "----------------------------------------" << endl;
            cout <<"The room is full, you can't enter this room at the moment."<<endl;
        }
}

void player::status()
{
    cout << "---------------YOUR STATS---------------" << endl;
    cout << "Name: " << name << ", Level: " << level << " Health: " << health << " Weapon: " << cur_held->getName() << " ,Damage: " << cur_held->getDamage()  <<"||" << endl;
    cout << "----------------------------------------" << endl;
    if(cur_pos != NULL){
        cur_pos->printCurrent();
        cur_pos->printOccupants();
        cout << "---------------Surroundings-------------" << endl;
        cur_pos->printSurroundAgent(); //Print Player surrounding monsters
        cur_pos->print_cur_obj();
        cur_pos->printLinked();
    }
    else cout << "You're not currently at any Room" << endl;
}

void player::attackAround()
{
    vector<Agent*> surr = cur_pos->getSurroundAgent(); //Get all Surrounding agents and iterate through them
    for(int i=0; i<surr.size(); i++)
    {
        if(surr[i]->getType()=="monster") //IF THE AGENT IS A MONSTER
            surr[i]->setHealth(surr[i]->getHealth()-(cur_held->getDamage())); //ATTACK, #TODO Damage should be according to current weapon(Implmented later)
    }
}

///#refaie all functions down there

void player::printheld(){
    if(cur_held != NULL)
        cout<<"Your current weapon is "<<cur_held->getName()<<", Damage: " << cur_held->getDamage()<<endl;
}

bool player::switchweapons(int w){
    w--; //e7na 0 indexed.
    objects *temp=cur_held;
    if(w>=0 && w < weapons.size())
    {
        cur_held=weapons[w];
        weapons[w]=temp;
        return true;
    }
    return false;
}

void player::printweapons(){
cout<<"Weapons in your bag are: ("<<weapons.size()<<")"<<endl;
    for(int i=0;i<weapons.size();i++){
        cout << "-> " << i+1 << " : " << weapons[i]->getName() << " - Damage: " << cur_held->getDamage()<<endl;
    }
}

void player::addObj(objects* x)
{
    if(x->getType()==1)
        weapons.push_back(x);
}

#include "player.h"
#include "helpers.h"
#include "prob.h"
#include "objects.h"  ///#refaie
#include <vector>  ///#refaie
#include <iostream>
using namespace std;


class objects;  ///#refaie
objects* defaultWep = new prob("Newbie-Sword",1,3);//DEFAULT WEAPON
player::player():Agent("Untitled",NULL,1,0)
{

}
player::player(string nameX, room* posX, int levelX, objects* wep):Agent(nameX,posX,1,levelX)
{
    if(wep != NULL)
    cur_held = wep;
    else cur_held = defaultWep;
    if(cur_pos != NULL)
        cur_pos->fogClear();
}
player::~player()
{
}
int player::act()
{
    while(true){
        if( health <= 0 ) return 3;//law mot yb2a el team 5eser, return 3 (3 = death)
        cout << endl;
        cout << ">> Please Type(North,South,East,West) to move." << endl;
        cout << ">> Type \"Attack\" to attack all the surrounding monsters." << endl;
        cout << ">> Type \"Pick\" or \"Drop\"  to pick/drop objects." << endl;
        cout << ">> Type \"Switch\" to switch between your weapons." << endl;
        string command = getDirections(); //get direction and return lower-case command and Invalid if unwanted command.
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
        else if(command == "drop") //Re-enter the while loop until a valid command.
        {
            if(weapons.size()==0){
                cout << "----------------------------------------" << endl;
                cout << ">> You don't have weapons in your bag\n\n" << endl;
            }
            else while(true){
                system("CLS");
                printheld();
                printweapons();
                cout << "----------------------------------------" << endl;
                cout << "-Choose the preferred weapon: (1,2,3,..)" << endl;
                int w;  cin >> w;
                if(dropweapons(w))
                {
                    cout << "----------------------------------------" << endl;
                    cout << ">> Dropped!"<<endl;
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
        else if(command == "switch")
        {
            if(weapons.size()==0){
                cout << "----------------------------------------" << endl;
                cout << ">> You don't have weapons in your bag\n\n" << endl;
            }
            else while(true){
            system("CLS");
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
            system("CLS");
            if(cur_pos->cur_objs.size() == 0)//fe 7aga a3rf a3mlha pick ?
            {
                cout << "----------------------------------------" << endl;
                cout << ">> There is no objects to pick." << endl;
            }
            else //law fe..
            {
                if(weapons.size()>=5) //3ndy makan fl bag ?
                {
                    cout << "----------------------------------------"    << endl;
                    cout << ">> You don't have enough space in your bag!" << endl;
                }
                else //law ahh..
                {
                    cur_pos->print_cur_objs();
                    cout << "What do you want to pick ? (1,2,3,...)"<<endl;
                    int i; cin >> i;
                    while( i <= 0 || i > cur_pos->cur_objs.size())
                    {
                        cout << "----------------------------------------"    << endl;
                        cout << ">> Please select a valid number." << endl;
                        cin >> i;
                    }
                    i--; //To zero index.
                    if(cur_pos->cur_objs[i]->act(this))//Law 3reft t3mlo pick...
                    {
                        if(cur_pos->cur_objs[i]->getType()==1){ //law prob
                            cout << "----------------------------------------" << endl;
                            cout << ">> You picked up " << cur_pos->cur_objs[i]->getName() << endl;
                            system("PAUSE");
                            system("CLS");
                            cur_pos->cur_objs.erase(cur_pos->cur_objs.begin()+i);//emsa7o mn vector el room;
                            return 1;
                        }
                        else if(cur_pos->cur_objs[i]->getType()==2){ //law fixed
                            cout << "----------------------------------------" << endl;
                            cout << ">> You opened " << cur_pos->cur_objs[i]->getName() << " And gained +" << cur_pos->cur_objs[i]->getDamage() << "HP!." << endl;
                            system("PAUSE");
                            system("CLS");
                            cur_pos->cur_objs[i]->setDamage(0);
                            return 1;
                        }
                        else if(cur_pos->cur_objs[i]->getType()==3){ //law treasure
                            cout << "----------------------------------------" << endl;
                            cout << ">> You picked up the treasure !!" << endl;
                            system("PAUSE");
                            system("CLS");
                            return 2;
                        }
                    }
                    else //law ma3rftsh te3mlo pick
                    {
                        cout << "----------------------------------------" << endl;
                        cout << ">> You don't have a Key to Open this object." << endl;
                    }
                }
            }
        }
        else if(command == "attack")//Attack and return 1 ( 1 = game resumes)
        {
            attack();
            cout << "----------------------------------------" << endl;
            cout << ">> You attacked all the monsters around you!" << endl;
            system("PAUSE");
            system("CLS");
            return 1;
        }
        else if(move(command))//LAW YNF3 TT7ARK FE EL ROOM DEH E3ML KAZA...
        {
            cout << "----------------------------------------" << endl;
            cout << ">> You moved " << command << "." << endl;
            system("PAUSE");
            system("CLS");
            cur_pos->fogClear(); //Clear the fog of WAR.
            return 1;
        }
        else if(cur_pos->getLinked(command)==NULL || cur_pos->getLinked(command)->getType() == 0 ) //LAW MA3rfsh yt7rak, check ma3rfsh leh.
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
}
void player::status()
{
    cout << "---------------YOUR STATS---------------" << endl;
    cout << "Name: " << name << ", Level: " << level << " Health: " << health << ", Weapon: " << cur_held->getName() << ", Damage: " << cur_held->getDamage()  <<"||" << endl;
    cout << "----------------------------------------" << endl;
    if(cur_pos != NULL){
        cur_pos->printCurrent();
        cur_pos->printOccupants();
        cout << "---------------Surroundings-------------" << endl;
        cur_pos->printSurroundAgent(); //Print Player surrounding monsters
        cur_pos->print_cur_objs();
        cur_pos->printLinked();
    }
    else cout << "You're not currently at any Room" << endl;
}

void player::attack()
{
    vector<Agent*> surr = cur_pos->getSurroundAgent(); //Get all Surrounding agents and iterate through them
    for(int i=0; i<surr.size(); i++)
    {
        if(surr[i]->getType()==0) //IF THE AGENT IS A MONSTER
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

bool player::dropweapons(int w){
    w--; //e7na 0 indexed.
    if(w>=0 && w < weapons.size())
    {
        cur_pos->cur_objs.push_back(weapons[w]); //7ot el selected weapon fe el room tany.
        weapons.erase(weapons.begin()+w); //shelo mn el player.
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

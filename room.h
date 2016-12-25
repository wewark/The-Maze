#include<string>
#include<vector>
#ifndef ROOM_H
#define ROOM_H
//#include "objects.h"
class Agent;
class objects;  ///#refaie
using namespace std;
class room
{
    public:
        room();
        room(string nameX, string descX, int typeX);
        ~room();
        static int ID;
        //FUNCTIONS
        room* getLinked(string direction);
        void link(room* r,string direction); //Link rooms together.
        void unlink(string direction = "all"); //Unlink From a direction or ALL directions.
        bool enter(Agent* x); //Adds an Agent to room.
        bool leave(Agent* x); //Removes an Agent from room.
        void fogClear();
        //GETTERS
        string getName();
        string getDescription();
        int getSize(){return roomSize;}
        int getRoomID(){return roomID;}
        bool getType(){return type;}
        void printOccupants(); //Print Agents inside the Room.
        void printCurrent(); //Prints Name, Desc.
        void printLinked(); //Print all LinkedRooms.
        void printSurroundRooms(); //Print all Surrounding rooms.
        void printSurroundAgent(); //Print all surrounding Agents.
        vector<room*> getSurround();//Return an array of all surrounding available rooms.
        vector<Agent*> getSurroundAgent();//Return an array of all surrounding Agents.
        bool fog;
        objects *cur_obj;  ///#refaie
        void print_cur_obj(); ///#refaie
    private:
        string name;
        string desc;
        int roomSize;
        int roomID;
        int type; // 1+ for type, 0 for wall.
        room* north;
        room* south;
        room* west;
        room* east;
        vector<Agent*> occupants;
};
#endif // ROOM_H

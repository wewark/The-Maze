#include<string>
#ifndef ROOM_H
#define ROOM_H
using namespace std;

class room
{
    public:
        room();
        room(string nameX, string descX);
        ~room();
        string getName();
        string getDescription();
        room* getLinked(string direction);
        void link(room* r,string direction);
        void unlink(string direction = "all"); //Unlink From a direction or ALL directions.
        void printLinked();
        static bool moveRoom(room*& r, string direction); //Change address of a room to another room in the given direction (Passing ADDRESS by REFERENCE) (Because I want to change the address itself )
    private:
        room* north;
        room* south;
        room* west;
        room* east;
        string name;
        string desc;
};

#endif // ROOM_H

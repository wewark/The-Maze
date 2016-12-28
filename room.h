#ifndef ROOM_H
#define ROOM_H
#include <string>
#include <vector>
using namespace std;

class Agent;
class objects;

class Room
{
    public:
        Room();
		Room(string nameX, string descX, bool typeX);
        ~Room();
        static int ID;

        // FUNCTIONS
        Room* getLinked(string direction);
		void link(Room* r,string direction);
        void unlink(string direction = "all"); // Unlink From a direction or ALL directions.
		bool enter(Agent* x);
		bool leave(Agent* x);
        void clearFog();

        // GETTERS
        string getName();
        string getDescription();
        int getSize(){return roomSize;}
        int getRoomID(){return roomID;}
        bool getType(){return wall;}
        void printOccupants(); // Print Agents inside the Room.
        void printCurrent(); // Prints Name, Desc.
        void printLinked(); // Print all LinkedRooms.
        void printSurroundRooms(); // Print all Surrounding rooms.
        void printSurroundAgent(); // Print all surrounding Agents.
        vector<Room*> getSurround();// Return an array of all surrounding available rooms.
        vector<Agent*> getSurroundAgent();// Return an array of all surrounding Agents.
		vector<objects*> cur_objs;
		void print_cur_objs();
		void addObj(objects* x);
		bool isFogged();
        bool isWall();
        static void initializeRooms();
		vector<Agent*> occupants;

    private:
        string name;
        string desc;
        int roomSize;
        int roomID;
        Room* north;
        Room* south;
        Room* west;
        Room* east;
        bool fog;
        bool wall;
		int pos_i;
		int pos_j;
};
#endif // ROOM_H

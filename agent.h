#pragma once
#include "Room.h"
using namespace std;

class Room;

class Agent
{
protected:
    Room *currentRoom;
    string name;
public:
    virtual bool act() = 0;
    virtual char nextMove() { return 0; }
    virtual void startMoving() {}
    virtual void startChasing() {}
    virtual void stopMoving() {}
    virtual bool isChasing() { return 0; }
    Agent();
    Agent(string name, Room *startingRoom);
    ~Agent();
    Room *getCurrentRoom() const;
    string getName() { return name; }
    bool move(string direction);
};


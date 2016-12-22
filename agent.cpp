#include "Agent.h"


Agent::Agent()
{
}

Agent::Agent(string name, Room *startingRoom)
{
    this->name = name;
    currentRoom = startingRoom;
    currentRoom->enter(this);
}

Agent::~Agent()
{
}

Room * Agent::getCurrentRoom() const
{
    return currentRoom;
}

bool Agent::move(string direction)
{
    if (currentRoom->getLinked(direction) != NULL)
    {
        currentRoom->leave(this);
        currentRoom = currentRoom->getLinked(direction);
        currentRoom->enter(this);
        return true;
    }
    return false;
}

#include "Monster.h"


Monster::Monster(string name, Room * startingRoom) : Agent(name, startingRoom)
{
}

Monster::Monster(string name, Room * startingRoom, string * path, int pathSz) : Agent(name, startingRoom)
{
    this->pathSz = pathSz;
    this->path = new string[pathSz];
    pathStep = 0;
    moving = false;
    chasing = false;

    for (int i = 0; i < pathSz; i++)
        this->path[i] = path[i];
}

Monster::~Monster()
{
}

bool Monster::act()
{
    if (moving)
    {
        if (chasing)
        {
            string direction = chase();
            if (direction != "")
                move(direction);
        }
        else if (move(path[pathStep]))
            pathStep = (pathStep + 1) % pathSz;

        if (currentRoom->getOccupantsSize() > 1)
            return false;
    }
    return true;
}

void Monster::startMoving()
{
    moving = true;
}

void Monster::startChasing()
{
    chasing = true;
}

void Monster::stopMoving()
{
    moving = false;
}

bool Monster::isChasing()
{
    return chasing;
}

string Monster::chase()
{
    string direction[] = { "north","south","east","west" };
    string opDirection[] = { "south","north","west","east" };
    for (int i = 0; i < 4; i++)
        if (currentRoom->getLinked(direction[i]))
        {
            if (currentRoom->getLinked(direction[i])->getOccupantsSize() > 0)
                return direction[i];
            else
                for (int j = 0; j < 4; j++)
                    if (direction[j] != opDirection[i] &&
                        currentRoom->getLinked(direction[i])->getLinked(direction[j]) &&
                        currentRoom->getLinked(direction[i])->getLinked(direction[j])->getOccupantsSize() > 0)
                        return direction[i];
        }
    return "";
}

char Monster::nextMove()
{
    if (chasing)
    {
        string next = chase();
        return next == "" ? 'O' : toupper(next[0]);
    }
    if (path[pathStep] == "north")
        return 'N';
    else if (path[pathStep] == "south")
        return 'S';
    else if (path[pathStep] == "east")
        return 'E';
    else if (path[pathStep] == "west")
        return 'W';
    return 'F';
}

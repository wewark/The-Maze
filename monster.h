#pragma once
#include "Agent.h"
using namespace std;

class Room;

class Monster : public Agent
{
private:
    string *path;
    bool moving;
    bool chasing;
    int pathStep;
    int pathSz;
public:
    Monster(string name, Room *startingRoom);
    Monster(string name, Room *startingRoom, string *path, int pathSz);
    ~Monster();
    bool act();
    void startMoving();
    void startChasing();
    void stopMoving();
    bool isChasing();
    string chase();
    char nextMove();
};


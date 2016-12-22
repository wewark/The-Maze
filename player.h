#pragma once
#include "Agent.h"
#include <string>
using namespace std;

class Player : public Agent
{
private:
    static bool won;

public:
    Player(string name, Room *startingRoom);
    ~Player();
    bool act();
    static void playerEscaped();
    static bool playerWon();
};


#ifndef GAME_H
#define GAME_H
#include "player.h"
#include "grue.h"
#include "objects.h"

class Game
{
public:
    Game();
    static vector<vector<Room>> rooms;
    static vector<player*> me;
    static vector<grue*> mobs;
    static vector<objects*> objectsX;
    static int mapWidth;
    static int mapHeight;
};

#endif // GAME_H

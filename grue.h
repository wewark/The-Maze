#ifndef GRUE_H
#define GRUE_H
#include "Agent.h"

class grue : public Agent
{
    public:
        grue(string nameX="Untitled", room* posX=NULL, int levelX=0); //Constructor
        virtual ~grue(); //Destructor
        void status(); //Print Name/Level and Position.
        int act(); //Move Accordingly.
        void attack();
    protected:
        int level;
        int health;
        int mana;
        // int armor;
        // int magicResist;
        // weapon CurrWeapon("Ice-Sword",98);
};

#endif // GRUE_H

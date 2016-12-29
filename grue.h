#ifndef GRUE_H
#define GRUE_H
#include "Agent.h"

class grue : public Agent
{
    public:
		grue(string nameX="Untitled", Room* posX=NULL, int levelX=0);
		virtual ~grue();
		int act(string path = "chase");
		string status(); // Print Name/Level and Position.
		//int act(); // Move Accordingly.
		void attack();

    protected:
        int level;
        int health;
        int mana;
		string chase(Room* cur);
		vector<vector<bool>> vis;
        // int armor;
        // int magicResist;
        // weapon CurrWeapon("Ice-Sword",98);
};

#endif // GRUE_H

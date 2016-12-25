#include "objects.h"
#include "room.h"
#include "player.h"
#include <iostream>
using namespace std;
objects::objects(string nameX, int typeX, int damageX)
{
    name = nameX;
    type = typeX;
    damage = damageX;
}

string objects::getName() {
	return name;
}
void objects::setName(string x) {
	name = x;
}
int objects::getType() {
	return type;
}
void objects::setType(int y) {
	type = y;
}
void objects::setDamage(int y) {
	damage = y;
}
int objects::getDamage() {
	return damage;
}

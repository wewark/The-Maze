#include "objects.h"
#include "room.h"
#include "player.h"
#include <iostream>
using namespace std;

string objects::getname() {
	return name;
}
void objects::setname(string x) {
	name = x;
}
int objects::getcondition() {
	return condition;
}
void objects::setcondition(int y) {
	condition = y;
}

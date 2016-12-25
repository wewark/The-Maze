#ifndef FIXEDOBJ_H
#define FIXEDOBJ_H
#include "objects.h"
#include "../room.h"
#include "../player.h"
#include <iostream>
using namespace std;

class fixedobj : public objects
{
    public:
        fixedobj(string x,int c);
        bool act(player *p);

    protected:

    private:
};

#endif // FIXEDOBJ_H

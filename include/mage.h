#ifndef MAGE_H
#define MAGE_H

#include "character.h"

using namespace ijengine;

class Mage : public Character {
public:
	Mage(unsigned id, double x, double y)
        : Character("spritesheets/SpritesheetRedMagerWalk.png", id, x, y)
    {
    }

protected:
    bool on_event(const GameEvent& event);
};

#endif

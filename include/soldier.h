#ifndef SOLDIER_H
#define SOLDIER_H

#include "character.h"

using namespace ijengine;

class Soldier : public Character {
public:
    Soldier(unsigned id, double x, double y)
        : Character("spritesheets/SpritesheetRedSoldierWAlk.png", id, x, y)
    {
    }
};

#endif
#ifndef INFILTRATOR_H
#define INFILTRATOR_H

#include "character.h"

using namespace ijengine;

class Infiltrator : public Character {
public:
    Infiltrator(unsigned id, double x, double y)
        : Character("spritesheets/SpritesheetRedInfiltratorWAlk.png", id, x, y)
    {
    }
};

#endif
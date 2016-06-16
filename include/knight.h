#ifndef KNIGHT_H
#define KNIGHT_H

#include "character.h"

using namespace ijengine;

class Knight : public Character {
public:
    Knight(unsigned id, double x, double y)
        : Character("spritesheets/SpritesheetRedInfiltratorWAlk.png", id, x, y)
    {
    }
};

#endif
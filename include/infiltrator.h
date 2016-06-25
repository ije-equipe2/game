#ifndef INFILTRATOR_H
#define INFILTRATOR_H

#include "character.h"

using namespace ijengine;

class Infiltrator : public Character {
public:
    Infiltrator(vector<string> sprite_paths, unsigned id, double x, double y);
};

#endif
#ifndef SOLDIER_H
#define SOLDIER_H

#include "character.h"

using namespace ijengine;

class Soldier : public Character {
public:
    Soldier(vector<string> sprite_paths, unsigned id, double x, double y);
protected:
    bool on_event(const GameEvent& event);
};

#endif
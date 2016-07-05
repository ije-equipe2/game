#ifndef MAGE_H
#define MAGE_H

#include "character.h"

using namespace ijengine;

class Mage : public Character {
public:
	Mage(vector<string> sprite_paths, unsigned id, double x, double y);

protected:
    void heavy_attack();
};

#endif

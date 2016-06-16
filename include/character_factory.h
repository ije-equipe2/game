#ifndef CHARACTER_FACTORY_H
#define CHARACTER_FACTORY_H
#include "character.h"
#include "mage.h"
#include "infiltrator.h"
#include "soldier.h"
#include "knight.h"

class CharacterFactory {
public:
    CharacterFactory();
    ~CharacterFactory();

    enum {
        INFILTRATOR,
        MAGE,
        SOLDIER,
        KNIGHT
    };

    Character* make_character(int character_code, unsigned player_id, double x_pos, double y_pos);

};

#endif
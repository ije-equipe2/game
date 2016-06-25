#ifndef CHARACTER_FACTORY_H
#define CHARACTER_FACTORY_H

#include "character.h"
#include "mage.h"
#include "infiltrator.h"
#include "soldier.h"
#include "knight.h"

#include <vector>
#include <string>

using std::vector;
using std::string;

class CharacterFactory {
public:
    CharacterFactory();
    ~CharacterFactory();

    enum {
        KNIGHT,
        SOLDIER,
        MAGE,
        INFILTRATOR
    };

    Character* make_character(int character_code, unsigned player_id, double x_pos, double y_pos);

protected:
    typedef enum {IDLE_SPRITE, MOVING_SPRITE, LIGHT_ATTACK_SPRITE, HEAVY_ATTACK_SPRITE, SPECIAL_SPRITE,
        DEFENSE_SPRITE, NUMBER_OF_SPRITES} CharacterSprite;
    typedef enum {PLAYER_1, PLAYER_2, PLAYER_3, PLAYER_4} Players;

    vector<string> choose_sprite_path(int character_code, unsigned player_id);

protected:
    vector<string> m_sprites_paths;
};
#endif
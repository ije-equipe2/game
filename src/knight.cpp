#include "knight.h"
#include "ije02_game.h"

#define MAX_LIFE 300
Knight::Knight(vector<string> sprite_paths, unsigned id, double x, double y)
    : Character(sprite_paths, id, x, y, MAX_LIFE)
{
}

void
Knight::heavy_attack()
{

}

void
Knight::light_attack() {
    change_character_state(LIGHT_ATTACK_STATE);
}

void
Knight::defense() {
    change_character_state(DEFENSE_STATE);
}

void
Knight::special() {

}
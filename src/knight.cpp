#include "knight.h"
#include "ije02_game.h"

#define MAX_LIFE 300
Knight::Knight(vector<string> sprite_paths, unsigned id, double x, double y)
    : Character(sprite_paths, id, x, y, MAX_LIFE)
{
    m_life = MAX_LIFE;
    m_special_cooldown = 5000;
    m_heavy_attack_cooldown = 2000;
    m_light_attack_cooldown = 300;
    m_defense_cooldown = 300;
    m_last_used_special = -m_special_cooldown;
    m_last_used_heavy_attack = -m_heavy_attack_cooldown;
    m_last_used_light_attack = -m_light_attack_cooldown;
    m_last_used_defense = -m_defense_cooldown;
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
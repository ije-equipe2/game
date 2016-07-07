#include "soldier.h"
#include "spear.h"
#include "ije02_game.h"

#define MAX_LIFE 120

Soldier::Soldier(vector<string> sprite_paths, unsigned id, double x, double y)
    : Character(sprite_paths, id, x, y, MAX_LIFE)
{
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
Soldier::heavy_attack()
{
    auto p = parent();
    printf("p = %p\n", (void *) p);

    double spear_dx = 0.0;
    double spear_x_pos = 0.0;

    if(m_moving_state == MOVING_RIGHT) {
        spear_dx = 1.0;
        spear_x_pos = x() + 20;
    }
    else{
        spear_dx = -1.0;
        spear_x_pos = x() - 20;
    }
    p->add_child(new Spear(p, id(), spear_x_pos, y(), spear_dx, 0.0));

    change_character_state(HEAVY_ATTACK_STATE);
}

void
Soldier::light_attack() {
    change_character_state(LIGHT_ATTACK_STATE);
}

void
Soldier::defense() {
    change_character_state(DEFENSE_STATE);
}

void
Soldier::special() {
    change_character_state(SPECIAL_STATE);
}
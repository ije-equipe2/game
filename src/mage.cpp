#include "mage.h"
#include "fireball.h"
#include "ije02_game.h"
#include "skill.h"

#include <vector>
#include <string>

#define MAX_LIFE 100

using std::vector;
using std::string;

Mage::Mage(vector<string> sprite_paths, unsigned id, double x, double y)
    : Character(sprite_paths, id, x, y, MAX_LIFE)
{
    m_life = MAX_LIFE;
    m_heavy_attack_cooldown = 2000;
    m_defense_cooldown = 500;
    m_last_used_heavy_attack = -m_heavy_attack_cooldown;
}

void
Mage::heavy_attack()
{
    auto p = parent();
    printf("p = %p\n", (void *) p);

    double fireball_dx = 0.0;
    double fireball_x_pos = 0.0;
    
    if(m_moving_state == MOVING_RIGHT) {
        fireball_dx = 1.0;
        fireball_x_pos = x() + 20;
    }
    else{
        fireball_dx = -1.0;
        fireball_x_pos = x() - 20;
    }

    p->add_child(new Fireball(p, id(), fireball_x_pos, y(), fireball_dx, 0.0));

    change_character_state(HEAVY_ATTACK_STATE);
}

void
Mage::light_attack() {
    change_character_state(LIGHT_ATTACK_STATE);
}

void
Mage::defense() {
    change_character_state(DEFENSE_STATE);
}

void
Mage::special() {

}
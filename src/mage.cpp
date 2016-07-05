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
}

bool
Mage::on_event(const GameEvent& event)
{
    bool p1_heavy_attack_validation = event.id() == game_event::HEAVY_ATTACK_P1 && id() == 0;
    bool p2_heavy_attack_validation = event.id() == game_event::HEAVY_ATTACK_P2 && id() == 1;

    if (p1_heavy_attack_validation || p2_heavy_attack_validation)
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
        return true;
    }

    return Character::on_event(event);
}
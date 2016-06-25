#include "soldier.h"
#include "spear.h"
#include "ije02_game.h"

Soldier::Soldier(vector<string> sprite_paths, unsigned id, double x, double y)
    : Character(sprite_paths, id, x, y)
{
}

bool
Soldier::on_event(const GameEvent& event)
{

    bool p1_heavy_attack_validation = event.id() == game_event::HEAVY_ATTACK_P1 && id() == 0;
    bool p2_heavy_attack_validation = event.id() == game_event::HEAVY_ATTACK_P2 && id() == 1;

    if (p1_heavy_attack_validation || p2_heavy_attack_validation)
    {

        auto p = parent();
        printf("p = %p\n", (void *) p);

        double spear_dx = 0.0;
        double spear_x_pos = 0.0;

        if(m_state == MOVING_RIGHT) {
            spear_dx = 1.0;
            spear_x_pos = x() + 20;
        }
        else{
            spear_dx = -1.0;
            spear_x_pos = x() - 20;
        }
        p->add_child(new Spear(p, id(), spear_x_pos, y(), spear_dx, 0.0, 100));
        return true;
    }

    return Character::on_event(event);
}

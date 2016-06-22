#include "soldier.h"
#include "spear.h"
#include "ije02_game.h"

bool
Soldier::on_event(const GameEvent& event)
{
    if (event.id() == game_event::HEAVY_ATTACK_P2 && id() == 1)
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

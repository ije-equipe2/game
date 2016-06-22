#include "soldier.h"
#include "spear.h"
#include "ije02_game.h"

bool
Soldier::on_event(const GameEvent& event)
{

    bool p1_heavy_attack_validation = event.id() == game_event::HEAVY_ATTACK_P1 && id() == 0;
    bool p2_heavy_attack_validation = event.id() == game_event::HEAVY_ATTACK_P2 && id() == 1;

    if(p1_heavy_attack_validation)
        printf("p1 true\n");

    if(p2_heavy_attack_validation)
        printf("p2 true\n");

    if (p1_heavy_attack_validation || p2_heavy_attack_validation)
    {
        printf("posição do soldado: %.2f %.2f\n", x(), y());
        printf("Bounding box do soldado: %.2f %.2f\n", m_bounding_box.x(), m_bounding_box.y());

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

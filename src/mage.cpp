#include "mage.h"
#include "fireball.h"
#include "ije02_game.h"

bool
Mage::on_event(const GameEvent& event)
{
    if (event.id() == game_event::HEAVY_ATTACK_P2 && id() == 1)
    {
        auto p = parent();
printf("p = %p\n", (void *) p);
  //  SkillPool* skill_pool = SkillPool::get_instance();
        p->add_child(new Fireball(p, id(), x() - 50, y(), -1.0, 0.0, 100));
        //skill_pool->get_skill(p, id(), x() - 50, y(), -1.0, 0.0, 100));
        //
        return true;
    }

    return Character::on_event(event);
}

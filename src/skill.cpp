#include "skill.h"
#include "character.h"

#include <ijengine/engine.h>
#include <ijengine/rectangle.h>


Skill::Skill(GameObject *parent, double xp, double yp)
    : GameObject(parent, xp, yp)
{
    physics::register_object(this);
}

Skill::~Skill()
{
   physics::unregister_object(this);
}

int
Skill::damage() const {
    return m_damage;
}
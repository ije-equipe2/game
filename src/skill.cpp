#include "skill.h"
#include "character.h"

#include <ijengine/engine.h>
#include <ijengine/rectangle.h>


Skill::Skill(GameObject *parent, double xp, double yp)
    : GameObject(parent, xp, yp)
{
    printf("registrando skill nas fisica\n");
    physics::register_object(this);
}

Skill::~Skill()
{
    printf("desregistrando skill nas fisica\n");
    physics::unregister_object(this);
}

int
Skill::damage() const {
    return m_damage;
}
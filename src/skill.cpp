#include "skill.h"
#include "character.h"

#include <ijengine/engine.h>
#include <ijengine/rectangle.h>


Skill::Skill(GameObject *parent, double xp, double yp, int damage, int character_id)
    : GameObject(parent, xp, yp), m_character_id(character_id)
{
    printf("registrando skill nas fisica\n");
    m_damage = damage;
    physics::register_object(this);
}

Skill::~Skill()
{
    printf("desregistrando skill nas fisica\n");
    physics::unregister_object(this);
}
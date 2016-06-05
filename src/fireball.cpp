#include "fireball.h"
#include "character.h"

#include <ijengine/engine.h>
#include <ijengine/rectangle.h>
#include <ijengine/game_object.h>


using namespace std;
using namespace ijengine;


Fireball::Fireball(GameObject *parent, unsigned mage_id, double xp, double yp, double dx, double dy, int damage)
    : Skill(parent, xp, yp), m_character_id(mage_id), m_dx(dx/hypot(dx, dy)), m_dy(dy/hypot(dx, dy)), m_damage(damage), m_speed(100.0) 
{

}

Fireball::~Fireball()
{

}

void
Fireball::draw_self(Canvas *canvas, unsigned, unsigned)
{
    auto texture = ijengine::resources::get_texture("fireball.png");
    canvas->draw(texture.get(), x(), y()); 
}

void
Fireball::update_self(unsigned now, unsigned last)
{
    double new_y = y() + m_dy *  m_speed * (now - last) / 1000.0;
    double new_x = x() + m_dx *  m_speed * (now - last) / 1000.0;
    set_position(new_x, new_y);
}

void
Fireball::on_collision(const Collidable *who, const Rectangle& where, unsigned now, unsigned last) 
{
    const Character *c = dynamic_cast<const Character *>(who);

    if (c and c->id() != m_character_id)
    {
        invalidate();
    }
}

bool
Fireball::active() const
{
    return true;
}

const Rectangle& 
Fireball::bounding_box() const
{
    static Rectangle box;
    box = Rectangle(x(), y(), 32, 32);
    return box;
}

const list<Rectangle>&
Fireball::hit_boxes() const
{
    static list<Rectangle> hits;
    hits = { bounding_box() };

    return hits;
}

pair<double, double>
Fireball::direction() const
{
    return pair<double, double>(m_dx, m_dy);
}



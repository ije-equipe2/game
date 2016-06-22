#include "spear.h"
#include "character.h"

#include <ijengine/engine.h>
#include <ijengine/rectangle.h>
#include <ijengine/game_object.h>


using namespace std;
using namespace ijengine;


Spear::Spear(GameObject *parent, unsigned soldier_id, double xp, double yp, double dx,
    double dy, int damage)
    : Skill(parent, xp, yp), m_character_id(soldier_id), m_dx(dx/hypot(dx, dy)),
        m_dy(dy/hypot(dx, dy)), m_damage(damage), m_speed(100.0) 
{
    m_frame = 0;
    m_start = -1;
    m_texture = ijengine::resources::get_texture("spritesheets/spear_red.png");

    if(m_dx > 0) {
        m_state = MOVING_LEFT;
    }
    else {
        m_state = MOVING_RIGHT;
    }
}

Spear::~Spear()
{

}

void
Spear::draw_self(Canvas *canvas, unsigned, unsigned)
{
    Rectangle rect {(double) 32 * m_frame, (double) 32 * m_state, 32.00, 32.00};
    canvas->draw(m_texture.get(),rect, x(), y()); 
}

void
Spear::update_self(unsigned now, unsigned last)
{
    double new_y = y() + m_dy *  m_speed * (now - last) / 1000.0;
    double new_x = x() + m_dx *  m_speed * (now - last) / 1000.0;
    set_position(new_x, new_y);

    m_bounding_box.set_position(x(), y());

    if (now - m_start > 50)
    {
        m_start += 50;
        m_frame = (m_frame + 1) % (m_texture->w() / 32);
    }

    if(x() < -10.0 || x() > 330.0 || y() < -10.0 || y() > 240) {
        invalidate();
        printf("Saiu dos limites!\n");
    }
}

void
Spear::on_collision(const Collidable *who, const Rectangle& where, unsigned now, unsigned last) 
{
    const Character *c = dynamic_cast<const Character *>(who);

    if (c and c->id() != m_character_id)
    {
        invalidate();
    }

    printf("COLIDIU! É NOIS BRASIL!\n\n");
}

bool
Spear::active() const
{
    return true;
}

const Rectangle& 
Spear::bounding_box() const
{
    return m_bounding_box;
}

const list<Rectangle>&
Spear::hit_boxes() const {
    static list<Rectangle> boxes {m_bounding_box};
    return boxes;
}

pair<double, double>
Spear::direction() const
{
    return pair<double, double>(m_dx, m_dy);
}
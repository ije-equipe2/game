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
    m_start = 0;
    m_sprite_path = choose_sprite_path(soldier_id);
    m_texture = ijengine::resources::get_texture(m_sprite_path);
    m_x = xp;
    m_y = yp;
    m_bounding_box = Rectangle(m_x, m_y, 20, 20);

    printf("bounding_box original spear: %.2f %.2f\n", m_bounding_box.x(), m_bounding_box.y());

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
    update_time(now);
    if(m_current_time - m_start > 300){
        double new_y = y() + m_dy *  m_speed * (now - last) / 1000.0;
        double new_x = x() + m_dx *  m_speed * (now - last) / 1000.0;
        set_position(new_x, new_y);

        m_bounding_box.set_position(x(), y());
    }
}

void
Spear::on_collision(const Collidable *who, const Rectangle& where, unsigned now, unsigned last) 
{
    const Character *c = dynamic_cast<const Character *>(who);
    printf("entrou no on colision\n");

    if (c and c->id() != m_character_id)
    {
        printf("colidiu com: %d\nQuem invocou: %d\n", c->id(), m_character_id);
        printf("Spear invalidada!\n");
        invalidate();
    }
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

void
Spear::update_sprite_state()
{
    if(m_current_time - m_start < 300) {
        m_frame = (m_frame + 1) % (m_texture->w() / 32);
    }

    else if(m_current_time - m_start > 300 ) {
        m_frame = 3;
    }
}

void
Spear::update_time(unsigned now) 
{
    if(m_start == 0) {
        m_start = now;
        m_current_time = now;
    }

    if (now - m_current_time > 150)
    {
        m_current_time += 150;
        update_sprite_state();
    }

    if((m_current_time - m_start) > 5000) {
        printf("Acabou o tempo da spear");
        invalidate();
    }

}

string
Spear::choose_sprite_path(unsigned player_id)
{
    string directory = "Green";
    string sprite_path;

    switch(player_id) {
        case PLAYER_1:
            directory = "Green";
            break;

        case PLAYER_2:
            directory = "Blue";
            break;

        case PLAYER_3:
            directory = "Yellow";
            break;

        case PLAYER_4:
            directory = "Red";
            break;

        default:
            printf("Valor inválido na Spear\n");
            break;
    }

    sprite_path = "Spritesheets/" + directory + "/Spear" + directory + ".png";

    return sprite_path;
}
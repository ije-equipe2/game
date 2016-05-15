#include "character.h"
#include "ije02_game.h"

#include <ijengine/engine.h>
#include <ijengine/canvas.h>

Character::Character()
    : m_state(MOVING_DOWN), m_frame(0), m_start(-1), m_speed(0.03)
{
    m_texture = resources::get_texture("sprite.png");
    m_w = 64;
    m_h = 64;

    event::register_listener(this);
}

Character::~Character()
{
    event::unregister_listener(this);
}

void
Character::update_self(unsigned now, unsigned)
{
    if (m_start == -1)
        m_start = now;

    if (now - m_start > 500)
    {
        m_start += 500;
        m_frame = (m_frame + 1) % 4;
    }

    set_y(y() + m_speed);
}

void
Character::draw_self(Canvas *canvas, unsigned, unsigned)
{
    Rectangle rect {(double) m_w * m_frame, (double) m_h * m_state, (double) m_w, (double) m_h};
    canvas->draw(m_texture.get(), rect, x(), y());
}

bool
Character::on_event(const GameEvent& event)
{
    printf("Event = %d\n", event.type());
    if (event.type() == GAME_EVENT_MOVE_UP and m_state != MOVING_UP)
    {
        m_frame = 0;
        m_state = MOVING_UP;
        m_speed = -0.03;
        m_start = event.timestamp();
        return true;
    }

    if (event.type() == GAME_EVENT_MOVE_DOWN and m_state != MOVING_DOWN)
    {
        m_frame = 0;
        m_state = MOVING_DOWN;
        m_speed = 0.03;
        m_start = event.timestamp();
        return true;
    }

    return false;
}

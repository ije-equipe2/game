#include "character.h"
#include "ije02_game.h"

#include <ijengine/engine.h>
#include <ijengine/canvas.h>

#include <iostream>

using std::cout;
using std::endl;

Character::Character(string sprite_path, unsigned id, double x, double y)
    : m_state(MOVING_DOWN), m_frame(0), m_start(-1), m_x_speed(0.00), m_y_speed(0.00)
{
    m_id = id;
    m_x = x;
    m_y = y;
    m_texture = resources::get_texture(sprite_path);
    m_w = 64;
    m_h = 64;

    // starts going down
    m_speed_vector.emplace_back(0.00, 0.07);
    // starts going left
    m_speed_vector.emplace_back(-0.07, 0.00);
    // starts going right
    m_speed_vector.emplace_back(0.07, 0.00);
    // starts going up
    m_speed_vector.emplace_back(0.00, -0.07);
    // stops going down
    m_speed_vector.emplace_back(0.00, -0.07);
    // stops going left
    m_speed_vector.emplace_back(0.07, 0.00);
    // stops going right
    m_speed_vector.emplace_back(-0.07, 0.00);
    // stops going up
    m_speed_vector.emplace_back(0.00, 0.07);

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

    if(m_y_speed == 0.0 && m_x_speed == 0.0) {
        return;
    }

    set_y(y() + m_y_speed);
    set_x(x() + m_x_speed);

    vector< pair<double, double> > possible_speeds {{0.00, 0.07}, {-0.07, 0.00}, {0.07, 0.00}, {0.00, -0.07},
                                                    {0.07, 0.07}, {-0.07, 0.07}, {-0.07, -0.07}, {0.07, -0.07}};

    for(int i = 0; i < (int) possible_speeds.size(); i++) {
        if(m_x_speed == possible_speeds[i].first && m_y_speed == possible_speeds[i].second) {
            m_state = (State) i;
            break;
        }
    }
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
    for(int i = START_MOVING_DOWN; i <= STOP_MOVING_UP; i++) {
        if(event.type() == (m_id * NUMBER_OF_CHARACTER_EVENTS + i)) {
            m_frame = 0;
            m_x_speed += m_speed_vector[i].first;
            m_y_speed += m_speed_vector[i].second;
            m_start = event.timestamp();
            return true;
        }
    }

    return false;
}

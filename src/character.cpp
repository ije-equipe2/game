#include "character.h"
#include "ije02_game.h"

#include <ijengine/engine.h>
#include <ijengine/canvas.h>
#include <ijengine/rectangle.h>

#include <iostream>
#include <algorithm>
#include <cstdio>

using std::cout;
using std::endl;
using std::min;
using std::max;

const double SPEED = 268.8;

Character::Character(const string sprite_path, unsigned id, double x, double y, const vector<Event *> &controls)
    : m_state(MOVING_DOWN), m_frame(0), m_start(-1), m_x_speed(0.00), m_y_speed(0.00), m_bounding_box(0.0, 0.0, 0.0, 0.0)
{
    m_texture = resources::get_texture(sprite_path);
    m_id = id;
    m_x = x;
    m_y = y;
    m_controls = controls;

    m_w = 64;
    m_h = 64;
    
    m_bounding_box = Rectangle(m_x, m_y, m_w, m_h);

    // starts going down
    m_speed_vector.emplace_back(0.00, SPEED);
    // starts going left
    m_speed_vector.emplace_back(-SPEED, 0.00);
    // starts going right
    m_speed_vector.emplace_back(SPEED, 0.00);
    // starts going up
    m_speed_vector.emplace_back(0.00, -SPEED);
    // stops going down
    m_speed_vector.emplace_back(0.00, -SPEED);
    // stops going left
    m_speed_vector.emplace_back(SPEED, 0.00);
    // stops going right
    m_speed_vector.emplace_back(-SPEED, 0.00);
    // stops going up
    m_speed_vector.emplace_back(0.00, SPEED);

    event::register_listener(this);
    physics::register_object(this);
}

Character::~Character()
{
    physics::unregister_object(this);
    event::unregister_listener(this);
}

void
Character::update_self(unsigned now, unsigned last)
{
    if (m_start == -1)
        m_start = now;

    if (now - m_start > 250)
    {
        m_start += 250;
        m_frame = (m_frame + 1) % 4;
    }

    if(m_y_speed == 0.0 && m_x_speed == 0.0) {
        return;
    }
    
    double new_y = y() + m_y_speed * (now - last) / 1000.0;
    new_y = min(new_y, 10 * 64.0);
    new_y = max(new_y, 0.0);

    double new_x = x() + m_x_speed * (now - last) / 1000.0;
    new_x = min(new_x, 20 * 64.0);
    new_x = max(new_x, 0.0);

    set_y(new_y);
    set_x(new_x);

    m_bounding_box.set_position(x(), y());

    vector< pair<double, double> > possible_speeds {{0.00, SPEED}, {-SPEED, 0.00}, {SPEED, 0.00}, {0.00, -SPEED},
                                                    {SPEED, SPEED}, {-SPEED, SPEED}, {-SPEED, -SPEED}, {SPEED, -SPEED}};

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
        if(event.id() == (m_id * NUMBER_OF_CHARACTER_EVENTS + i)) {
            m_frame = 0;
            m_x_speed += m_speed_vector[i].first;
            m_y_speed += m_speed_vector[i].second;
            m_start = event.timestamp();
            return true;
        }
    }

    return false;
}

pair<double, double>
Character::direction() const {
    return pair<double, double>(m_x_speed, m_y_speed);
}

bool
Character::active() const {
    return true;
}

const Rectangle&
Character::bounding_box() const {
    return m_bounding_box;
}

const list<Rectangle>&
Character::hit_boxes() const {
    static list<Rectangle> boxes {m_bounding_box};
    return boxes;
}

void
Character::on_collision(const Collidable *who, const Rectangle& where) {
    printf("%p hit on %p\n", this, who);
}  
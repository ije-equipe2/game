#include "character.h"
#include "ije02_game.h"
#include "main_level.h"

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
    
    m_bounding_box = Rectangle(m_x, m_y, 32, 32);

    m_speed_vector["down"] = make_pair(0.00, SPEED);
    m_speed_vector["left"] = make_pair(-SPEED, 0.00);
    m_speed_vector["right"] = make_pair(SPEED, 0.00);
    m_speed_vector["up"] = make_pair(0.00, -SPEED);
    
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

    update_position(now, last);

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

inline void
Character::update_position(const unsigned &now, const unsigned &last, bool backwards) {
    int multiplier = (backwards) ? -1 : 1;

    double new_y = y() + multiplier * m_y_speed * (now - last) / 1000.0;
    new_y = min(new_y, (MAX_H - 1) * 64.0);
    new_y = max(new_y, 0.0);

    double new_x = x() + multiplier * m_x_speed * (now - last) / 1000.0;
    new_x = min(new_x, (MAX_W - 1) * 64.0);
    new_x = max(new_x, 0.0);

    set_y(new_y);
    set_x(new_x);
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
    if(event.id() == game_event::MOVEMENT) {
        string action = event.get_property<string>("action");
        string direction = event.get_property<string>("direction");
        pair<double, double> speed_pair = m_speed_vector[direction];
        if(action == "start") {
            m_x_speed += speed_pair.first;
            m_y_speed += speed_pair.second;
        }
        else {
            m_y_speed += -speed_pair.second;
            m_x_speed += -speed_pair.first;
        }

        return true;
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
Character::on_collision(const Collidable *who, const Rectangle& where, unsigned now, unsigned last) {
    update_position(now, last, true);
}  
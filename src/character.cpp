#include "character.h"
#include "ije02_game.h"
#include "main_level.h"
#include "skill.h"

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

const double SPEED = 80.00;

Character::Character(const vector<string> sprite_paths, unsigned id, double x, double y, int max_life)
    : m_moving_state(MOVING_RIGHT), m_frame(0), m_start(-1), m_x_speed(0.00), m_y_speed(0.00),
    m_life(max_life)
{
    for(int i = 0; i < min((int) sprite_paths.size(), (int) NUMBER_OF_STATES); i++) {
        m_textures.push_back(resources::get_texture(sprite_paths[i]));
    }
    m_state = nullptr;
    change_character_state(IDLE_STATE);
    m_freeze = false;

    m_id = id;
    m_x = x;
    m_y = y;

    m_w = 32;
    m_h = 32;

    m_bounding_box = Rectangle(m_x, m_y, 24, 24);

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
    handle_state();

    if (m_start == -1)
        m_start = now;

    if (now - m_start > m_state->refresh_rate())
    {
        m_start += m_state->refresh_rate();
        m_frame = (m_frame + 1) % (m_textures[m_state->current_state()]->w() / 32);
    }

    if(m_y_speed == 0.0 && m_x_speed == 0.0) {
        return;
    }

    update_position(now, last);

    m_bounding_box.set_position(x(), y());


}

inline void
Character::update_position(const unsigned &now, const unsigned &last, bool backwards) {
    int multiplier = (backwards) ? -1 : 1;
    if(not m_freeze) {
        double new_y = y() + multiplier * m_y_speed * (now - last) / 1000.0;
        new_y = min(new_y, SCREEN_HEIGHT - 32.00);
        new_y = max(new_y, 0.0);

        double new_x = x() + multiplier * m_x_speed * (now - last) / 1000.0;
        new_x = min(new_x, SCREEN_WIDTH - 32.00);
        new_x = max(new_x, 0.0);

        set_y(new_y);
        set_x(new_x);
    }
}

void
Character::draw_self(Canvas *canvas, unsigned, unsigned)
{
    Rectangle rect {(double) m_w * m_frame, (double) m_h * m_moving_state, (double) m_w, (double) m_h};
    canvas->draw(m_textures[m_state->current_state()].get(), rect, x(), y());
}

bool
Character::on_event(const GameEvent& event)
{
    bool p1_heavy_attack_validation = event.id() == game_event::HEAVY_ATTACK_P1 && id() == 0;
    bool p2_heavy_attack_validation = event.id() == game_event::HEAVY_ATTACK_P2 && id() == 1;
    bool p3_heavy_attack_validation = event.id() == game_event::HEAVY_ATTACK_P3 && id() == 2;
    bool p4_heavy_attack_validation = event.id() == game_event::HEAVY_ATTACK_P4 && id() == 3;

    bool p1_light_attack_validation = event.id() == game_event::LIGHT_ATTACK_P1 && id() == 0;
    bool p2_light_attack_validation = event.id() == game_event::LIGHT_ATTACK_P2 && id() == 1;
    bool p3_light_attack_validation = event.id() == game_event::LIGHT_ATTACK_P3 && id() == 2;
    bool p4_light_attack_validation = event.id() == game_event::LIGHT_ATTACK_P4 && id() == 3;

    bool p1_defense_validation = event.id() == game_event::DEFENSE_P1 && id() == 0;
    bool p2_defense_validation = event.id() == game_event::DEFENSE_P2 && id() == 1;
    bool p3_defense_validation = event.id() == game_event::DEFENSE_P3 && id() == 2;
    bool p4_defense_validation = event.id() == game_event::DEFENSE_P4 && id() == 3;

    bool p1_special_validation = event.id() == game_event::SPECIAL_P1 && id() == 0;
    bool p2_special_validation = event.id() == game_event::SPECIAL_P2 && id() == 1;
    bool p3_special_validation = event.id() == game_event::SPECIAL_P3 && id() == 2;
    bool p4_special_validation = event.id() == game_event::SPECIAL_P4 && id() == 3;

    if((event.id() == game_event::MOVEMENT_P1 && m_id == 0) ||
       (event.id() == game_event::MOVEMENT_P2 && m_id == 1) ||
       (event.id() == game_event::MOVEMENT_P3 && m_id == 2) ||
       (event.id() == game_event::MOVEMENT_P4 && m_id == 3)) {
        string axis = event.get_property<string>("axis");
        int value = event.get_property<int>("value");

        if(axis == "X") {
            m_x_speed = SPEED * ((double) value / 32768);
            if(value > 0) {
                m_moving_state = MOVING_RIGHT;
            }
            else if(value < 0) {
                m_moving_state = MOVING_LEFT;
            }
        } 
        else if(axis == "Y") {
            m_y_speed = SPEED * ((double) value / 32768);
        }

        return true;
    }
    else if((p1_heavy_attack_validation || p2_heavy_attack_validation || p3_heavy_attack_validation || p4_heavy_attack_validation) &&
        (m_start - m_last_used_heavy_attack > m_heavy_attack_cooldown))
    {
        m_last_used_heavy_attack = m_start;
        heavy_attack();
        return true;
    }
    else if((p1_light_attack_validation || p2_light_attack_validation || p3_light_attack_validation || p4_light_attack_validation) &&
        (m_start - m_last_used_light_attack > m_light_attack_cooldown))
    {
        m_last_used_light_attack = m_start;
        light_attack();
        return true;
    }
    else if((p1_defense_validation || p2_defense_validation || p3_defense_validation || p4_defense_validation) &&
        (m_start - m_last_used_defense > m_defense_cooldown))
    {   
        m_last_used_defense = m_start;
        defense();
        return true;
    }
    else if((p1_special_validation || p2_special_validation || p3_special_validation || p4_special_validation) &&
        (m_start - m_last_used_special > m_special_cooldown))
    {
        m_last_used_special = m_start;
        special();
        return true;
    }

    return false;
}

pair<double, double>
Character::direction() const
{
    return pair<double, double>(m_x_speed, m_y_speed);
}

bool
Character::active() const 
{
    return true;
}

const Rectangle&
Character::bounding_box() const 
{
    return m_bounding_box;
}

const list<Rectangle>&
Character::hit_boxes() const 
{
    static list<Rectangle> boxes {m_bounding_box};
    return boxes;
}

void
Character::on_collision(const Collidable *who, const Rectangle& where, unsigned now, unsigned last) 
{
    const Skill *s = dynamic_cast<const Skill *>(who);
    const Character *c = dynamic_cast<const Character *>(who);

    if(c) {
        printf("colidiu com um personagem!\n\n");
        update_position(now, last, true);
    }
    else if(s and s->character_id() != m_id) {
        printf("colidiu com alguma skill!\n\n");
        printf("colidiu com : %d\n", s->character_id());
        if(s->valid()) {
            printf("Dano causado: %d\n", s->damage());

            printf("Vida antes: %d\n", m_life);
            m_life -= s->damage();
            printf("Vida depois: %d\n", m_life);
        }
        else if(not s->valid()) {
            printf("Skill já colidiu!\n");
        }
    }
   
}

void
Character::change_character_state(State next_state) 
{
    if(m_state != nullptr and m_state->current_state() == DEATH_STATE) {
        return;
    }
    if(m_state != nullptr and next_state == m_state->current_state()) {
        return;
    }
    if(not m_freeze) {
        m_state = m_character_state_factory.change_character_state(next_state);
        m_frame = 0;
    }
}

void Character::handle_state()
{
    if(m_life <= 0) {
        change_character_state(DEATH_STATE);
    }

    if(m_state->current_state() == HEAVY_ATTACK_STATE) {
        m_freeze = true;
    }
    else {
        m_freeze = false;
    }

    if(m_state->current_state() == DEATH_STATE and 
        (m_frame + 1) % (m_textures[m_state->current_state()]->w() / 32) == 0) {
        invalidate();
    }

    if(m_state->current_state() != DEATH_STATE && m_state->current_state() != MOVING_STATE and
        (m_frame + 1) % (m_textures[m_state->current_state()]->w() / 32) == 0) {
        m_freeze = false;
        change_character_state(IDLE_STATE);
    }

    if(m_x_speed == 0.0 && m_y_speed == 0.0) {
        if(m_state->current_state() == MOVING_STATE || 
          (m_state->current_state() == IDLE_STATE && ((m_frame + 1) % (m_textures[IDLE_STATE]->w() / 32)) == 0)) {
            change_character_state(IDLE_STATE);
        }
    }
    else if(m_state->current_state() == IDLE_STATE) {
        change_character_state(MOVING_STATE);
    }
}

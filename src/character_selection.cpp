#include "character_selection.h"
#include "ije02_game.h"

#include <ijengine/engine.h>
#include <ijengine/canvas.h>
#include <ijengine/rectangle.h>

#include <cmath>

using namespace std;

CharacterSelection::CharacterSelection(const string sprite_path)
    : m_frame(0), m_start(-1), m_current_selection(KNIGHT)
{
    m_texture = resources::get_texture(sprite_path);
    m_w = 8;
    m_h = 9;


    event::register_listener(this);
    update_position();
}

CharacterSelection::~CharacterSelection() {
    event::unregister_listener(this);
}

void
CharacterSelection::update_self(unsigned now, unsigned last)
{
    if (m_start == -1)
        m_start = now;

    if (now - m_start > 100)
    {
        m_start += 100;
    }
}

void
CharacterSelection::update_position()
{
    switch(m_current_selection) {
        case KNIGHT:
            set_x(135);
            set_y(73);
            break;

        case SOLDIER:
            set_x(178);
            set_y(73);
            break;

        case MAGE:
            set_x(135);
            set_y(115);
            break;

        case INFILTRATOR:
            set_x(178);
            set_y(115);
            break;

        default:
            printf("Argumento inválido no update_position() do character_selection.cpp\n");
            break;
    }
}

void
CharacterSelection::draw_self(Canvas *canvas, unsigned, unsigned)
{
    Rectangle rect {0.0, 0.0, (double) m_w, (double) m_h};
    canvas->draw(m_texture.get(), rect, x(), y());
}

bool
CharacterSelection::on_event(const GameEvent &event)
{
    if(event.id() == game_event::MOVEMENT_P1)  {
        string key_pressed = event.get_property<string>("direction");

        if(event.get_property<string>("action") == "start") {
            if(key_pressed == "up") {
                m_current_selection = (m_current_selection - 2) % 4;
                return true;
            }
            else if(key_pressed == "down") {
                m_current_selection = (m_current_selection + 2) % 4;
                return true;
            }
            else if(key_pressed == "left") {
                m_current_selection = (m_current_selection -1) % 4;
                return true;
            }
            else if(key_pressed == "right") {
                m_current_selection = (m_current_selection + 1) % 4;
                return true;
            }
        }
        
        if(m_current_selection < 0) {
            m_current_selection += 4;
        }
        update_position();
    }

    return false;
}
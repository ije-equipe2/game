#include "menu_level.h"
#include "engine.h"
#include "character.h"
#include "ije02_game.h"

#include <ijengine/canvas.h>
#include <ijengine/keyboard_event.h>
#include <cstdlib>

using namespace std;

MenuLevel::MenuLevel(const string& next_level)
    :m_done(false), m_next(next_level), m_start(-1)
{
    m_textures.push_back(resources::get_texture("inicial.png"));
    event::register_listener(this);

}

MenuLevel::~MenuLevel() {
    event::unregister_listener(this);
}

bool
MenuLevel::done() const
{
    return m_done;
}

string
MenuLevel::next() const
{
    return m_next;
}

string
MenuLevel::audio() const {
    return ".";
}

void
MenuLevel::update_self(unsigned now, unsigned)
{
    if (m_start == -1)
        m_start = now;
}

void
MenuLevel::draw_self(Canvas *canvas, unsigned, unsigned)
{
    canvas->clear();
    
    canvas->draw(m_textures[0].get(), 0, 0);
}

bool
MenuLevel::on_event(const GameEvent& event) {
    if(event.id() == game_event::ENTER_GAME) {
        m_done = true;
        return true;
    }
    return false;
}

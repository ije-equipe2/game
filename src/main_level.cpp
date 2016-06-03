#include "main_level.h"
#include "engine.h"
#include "character.h"
#include "ije02_game.h"

#include <ijengine/canvas.h>
#include <ijengine/keyboard_event.h>
#include <cstdlib>

using namespace std;
using namespace ijengine;

MainLevel::MainLevel(const string& next_level)
    : m_done(false), m_next(next_level), m_start(-1)
{
    m_textures.push_back(resources::get_texture("map/Map002.jpg"));

    for (int i = 0; i < MAX_W; ++i)
        for (int j = 0; j < MAX_H; ++j)
            m_map[i][j] = 1;

    m_map[0][0] = 0;
    m_map[0][MAX_H - 1] = 0;
    m_map[MAX_W - 1][0] = 0;
    m_map[MAX_W - 1][MAX_H - 1] = 0;    

    add_child(new Character("spritesheets/SpritesheetRedSoldierWAlk.png", 0, 0.0, 0.0));
    add_child(new Character("spritesheets/SpritesheetRedMagerWalk.png", 1, (double) SCREEN_WIDTH - 32.0, 0.0));
}

MainLevel::~MainLevel() {
    
}

bool
MainLevel::done() const
{
    return m_done;
}

string
MainLevel::next() const
{
    return m_next;
}

string
MainLevel::audio() const {
    return ".";
}

void
MainLevel::update_self(unsigned now, unsigned)
{
    if (m_start == -1)
        m_start = now;

    if (now - m_start > 10000000)
        m_done = true;
}

void
MainLevel::draw_self(Canvas *canvas, unsigned, unsigned)
{
    canvas->clear();
    
    canvas->draw(m_textures[0].get(), 0, 0);
}

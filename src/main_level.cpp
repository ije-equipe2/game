#include "main_level.h"
#include "engine.h"
#include "character.h"

#include <ijengine/canvas.h>
#include <cstdlib>

using namespace std;
using namespace ijengine;

MainLevel::MainLevel(int r, int g, int b, const string& next_level)
    : m_r(r), m_g(g), m_b(b), m_done(false), m_next(next_level), m_start(-1)
{
    m_textures.push_back(resources::get_texture("graminha01.jpg"));
    m_textures.push_back(resources::get_texture("graminha02.png"));
    m_textures.push_back(resources::get_texture("chaozinho01.png"));
    m_textures.push_back(resources::get_texture("chaozinho02.png"));

    for (int i = 0; i < MAX_W; ++i)
        for (int j = 0; j < MAX_H; ++j)
            m_map[i][j] = rand() % m_textures.size();

    add_children(new Character("sprite.png", 0, 0.0, 0.0));
    add_children(new Character("sprite.png", 1, 576.0, 0.0));
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

void
MainLevel::update_self(unsigned now, unsigned)
{
    if (m_start == -1)
        m_start = now;

    if (now - m_start > 1000000)
        m_done = true;
}

void
MainLevel::draw_self(Canvas *canvas, unsigned, unsigned)
{
    canvas->clear();
    
    for (int i = 0; i < MAX_W; ++i)
        for (int j = 0; j < MAX_H; ++j)
        {
            auto texture = m_textures[m_map[i][j]].get(); 
            canvas->draw(texture, i * texture->w(), j * texture->h());
        }
}

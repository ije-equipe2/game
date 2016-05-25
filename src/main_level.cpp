#include "main_level.h"
#include "engine.h"
#include "character.h"

#include <ijengine/canvas.h>
#include <ijengine/keyboard_event.h>
#include <cstdlib>

using namespace std;
using namespace ijengine;

MainLevel::MainLevel(int r, int g, int b, const string& next_level)
    : m_r(r), m_g(g), m_b(b), m_done(false), m_next(next_level), m_start(-1)
{
    // m_textures.push_back(resources::get_texture("Map002.jpg"));
    m_textures.push_back(resources::get_texture("graminha01.jpg"));
    m_textures.push_back(resources::get_texture("chaozinho01.png"));
    m_textures.push_back(resources::get_texture("graminha02.png"));
    m_textures.push_back(resources::get_texture("chaozinho02.png"));

    for (int i = 0; i < MAX_W; ++i)
        for (int j = 0; j < MAX_H; ++j)
            m_map[i][j] = 1;

    m_map[0][0] = 0;
    m_map[0][MAX_H - 1] = 0;
    m_map[MAX_W - 1][0] = 0;
    m_map[MAX_W - 1][MAX_H - 1] = 0;    

    vector< vector<Event *> > controls = define_controls();

    for(int i = 0; i < (int) controls.size(); i++) {
        
    }

    add_child(new Character("sprite.png", 0, 0.0, 0.0, controls[0]));
    add_child(new Character("sprite.png", 1, (MAX_W - 1) * 64.00, 0.0, controls[1]));
}

MainLevel::~MainLevel() {
    
}

inline vector< vector<Event *> > 
MainLevel::define_controls() {
    vector<KeyboardEvent::Key> keys0 {KeyboardEvent::DOWN, KeyboardEvent::LEFT, KeyboardEvent::RIGHT, KeyboardEvent::UP,
                                      KeyboardEvent::DOWN, KeyboardEvent::LEFT, KeyboardEvent::RIGHT, KeyboardEvent::UP,
                                      KeyboardEvent::V, KeyboardEvent::B, KeyboardEvent::N, KeyboardEvent::M};

    vector<KeyboardEvent::Key> keys1 {KeyboardEvent::S, KeyboardEvent::A, KeyboardEvent::D, KeyboardEvent::W,
                                      KeyboardEvent::S, KeyboardEvent::A, KeyboardEvent::D, KeyboardEvent::W,
                                      KeyboardEvent::U, KeyboardEvent::I, KeyboardEvent::O, KeyboardEvent::P};

    vector< vector<KeyboardEvent::Key> > keys {keys0, keys1};

    vector<KeyboardEvent::State> state0 {KeyboardEvent::PRESSED, KeyboardEvent::PRESSED, KeyboardEvent::PRESSED, KeyboardEvent::PRESSED,
                                         KeyboardEvent::RELEASED, KeyboardEvent::RELEASED, KeyboardEvent::RELEASED, KeyboardEvent::RELEASED,
                                         KeyboardEvent::PRESSED, KeyboardEvent::PRESSED, KeyboardEvent::PRESSED, KeyboardEvent::PRESSED};

    vector< vector<KeyboardEvent::State> > states {state0, state0};

    vector< vector<Event *> > controls;
    for(int character_id = 0; character_id < 2; character_id++) {
        vector<Event *> current_control;
        for(int event_id = 0; event_id < Character::NUMBER_OF_CHARACTER_EVENTS; event_id++) {
                current_control.push_back(new KeyboardEvent(0, states[character_id][event_id],
                                                            keys[character_id][event_id], KeyboardEvent::NONE));
        }
        controls.push_back(current_control);
    }

    return controls;
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
    
    //canvas->draw(m_textures[0].get(), 0, 0);
    for (int i = 0; i < MAX_W; ++i)
    {
        for (int j = 0; j < MAX_H; ++j)
        {
            auto texture = m_textures[m_map[i][j]].get(); 
            canvas->draw(texture, i * texture->w(), j * texture->h());
        }
    }
}

#include "ije02_game.h"
#include "character.h"

#include <ijengine/system_event.h>
#include <ijengine/keyboard_event.h>

#include <iostream>
#include <cstdio>

using std::cout;
using std::endl;

namespace ijengine
{
    namespace game_event
    {
        unsigned MOVEMENT_P1 = GameEvent::assign_id();
        unsigned MOVEMENT_P2 = GameEvent::assign_id();
        unsigned MOTION = GameEvent::assign_id();
        unsigned CLICK = GameEvent::assign_id();
        unsigned ENTER_GAME = GameEvent::assign_id();
    }
}


Ije02Game::Ije02Game(const string& title, int w, int h, double scale)
    : m_game(title, w, h, scale), m_engine(), m_level_factory()
{
    event::register_translator(&m_translator);

    level::register_factory(&m_level_factory);
    resources::set_textures_dir("res/images");

    physics::set_collision_mode(physics::Mode::ALL_TO_ALL, nullptr);
}

Ije02Game::~Ije02Game()
{
    level::unregister_factory();
    event::unregister_translator(&m_translator);
}

int
Ije02Game::run(const string& level_id)
{
    return m_game.run(level_id);
}

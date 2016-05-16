#include "ije02_game.h"
#include "character.h"

#include <ijengine/system_event.h>
#include <ijengine/keyboard_event.h>

#include <iostream>
#include <cstdio>

using std::cout;
using std::endl;

Ije02Game::Ije02Game(const string& title, int w, int h)
    : m_game(title, w, h), m_engine(), m_level_factory()
{
    m_translator.add_translation(SystemEvent(0, SystemEvent::QUIT),
        GameEvent(GAME_EVENT_QUIT));

    vector<KeyboardEvent::Key> keys {KeyboardEvent::DOWN, KeyboardEvent::LEFT, KeyboardEvent::RIGHT, KeyboardEvent::UP,
                                     KeyboardEvent::S, KeyboardEvent::A, KeyboardEvent::D, KeyboardEvent::W};

    for(int id = 0; id <= 1; id++) {
        for(int i = Character::START_MOVING_DOWN; i <= Character::START_MOVING_UP; i++) {
            m_translator.add_translation(KeyboardEvent(0, KeyboardEvent::PRESSED,
                keys[i + id * 4], KeyboardEvent::NONE),
                GameEvent(Character::NUMBER_OF_CHARACTER_EVENTS * id + i));
        }
        for(int i = Character::STOP_MOVING_DOWN; i <= Character::STOP_MOVING_UP; i++) {
            m_translator.add_translation(KeyboardEvent(0, KeyboardEvent::RELEASED,
                keys[(i % 4) + id * 4], KeyboardEvent::NONE),
                GameEvent(Character::NUMBER_OF_CHARACTER_EVENTS * id + i));   
        }
    }

    event::register_translator(&m_translator);

    level::register_factory(&m_level_factory);
    resources::set_textures_dir("res/images");
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

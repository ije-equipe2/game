#include "ije02_game.h"

#include <ijengine/system_event.h>
#include <ijengine/keyboard_event.h>

Ije02Game::Ije02Game(const string& title, int w, int h)
    : m_game(title, w, h), m_engine(), m_level_factory()
{
    m_translator.add_translation(SystemEvent(0, SystemEvent::QUIT),
        GameEvent(GAME_EVENT_QUIT));

    m_translator.add_translation(KeyboardEvent(0, KeyboardEvent::PRESSED,
        KeyboardEvent::DOWN, KeyboardEvent::NONE),
        GameEvent(GAME_EVENT_MOVE_DOWN));

    m_translator.add_translation(KeyboardEvent(0, KeyboardEvent::PRESSED,
        KeyboardEvent::UP, KeyboardEvent::NONE),
        GameEvent(GAME_EVENT_MOVE_UP));

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

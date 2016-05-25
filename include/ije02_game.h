#ifndef IJE02_GAME_H
#define IJE02_GAME_H

#include "translator.h"

#include <ijengine/game.h>
#include <ijengine/engine.h>
#include <ijengine/mouse_event.h>
#include <ijengine/system_event.h>
#include <ijengine/keyboard_event.h>
#include <ijengine/events_translator.h>

#include "test_level_factory.h"
#include <iostream>

using namespace ijengine;
using namespace std;

namespace ijengine
{
    namespace game_event
    {
        extern unsigned MOVEMENT;
        extern unsigned MOTION;
        extern unsigned CLICK;
    }
}

class Ije02Game {
public:
    Ije02Game(const string& title, int w, int h);
    ~Ije02Game();

    int run(const string& level_id);

private:
	Game m_game;
	Engine m_engine;
	Translator m_translator;
	TestLevelFactory m_level_factory;
};

#endif

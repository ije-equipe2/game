#ifndef IJE02_GAME_H
#define IJE02_GAME_H

#include <ijengine/game.h>
#include <ijengine/engine.h>
#include <ijengine/events_translator.h>

#include "test_level_factory.h"

using namespace ijengine;

class Ije02Game {
public:
	Ije02Game(const string& title, int w, int h);
	~Ije02Game();

	int run(const string& level_id);

private:
	Game m_game;
	Engine m_engine;
	EventsTranslator m_translator;
	TestLevelFactory m_level_factory;
};

#endif

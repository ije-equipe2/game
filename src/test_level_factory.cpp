#include "main_level.h"
#include "menu_level.h"
#include "test_level_factory.h"
#include "character_choose_level.h"
#include "ije02_game.h"

#include <iostream>

using std::cout;

namespace ijengine
{
    namespace character_selection
    {
        vector<int> players_characters = vector<int>();
    }
}


Level *
TestLevelFactory::make_level(const string& level_id)
{
    if (level_id == "red")
        return new MenuLevel("green");
    else if (level_id == "green")
        return new CharacterChooseLevel("blue");
    else if (level_id == "blue") {
        return new MainLevel("", character_selection::players_characters);
    }
    else
        return nullptr;
}

void
TestLevelFactory::release(Level *level)
{
    delete level;
}


#include "main_level.h"
#include "menu_level.h"
#include "winner_level.h"
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
    namespace winner
    {
        int winner_player = 0;
    }
}


Level *
TestLevelFactory::make_level(const string& level_id)
{
    if (level_id == "menu"){
        return new MenuLevel("choose-character");
    }
    else if (level_id == "choose-character") {
        return new CharacterChooseLevel("arena");
    }
    else if (level_id == "arena") {
        return new MainLevel("winner", character_selection::players_characters);
    }
    else if (level_id == "winner") {
        return new WinnerLevel("menu", winner::winner_player);
    }
    else
        return nullptr;
}

void
TestLevelFactory::release(Level *level)
{
    delete level;
}


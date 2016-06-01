#include "main_level.h"
#include "menu_level.h"
#include "test_level_factory.h"

Level *
TestLevelFactory::make_level(const string& level_id)
{
    if (level_id == "red")
        return new MenuLevel("green");
    else if (level_id == "green")
        return new MainLevel("blue");
    else if (level_id == "blue")
        return new MainLevel();
    else
        return nullptr;
}

void
TestLevelFactory::release(Level *level)
{
    delete level;
}


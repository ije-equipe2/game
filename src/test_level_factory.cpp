#include "main_level.h"
#include "test_level_factory.h"

Level *
TestLevelFactory::make_level(const string& level_id)
{
    if (level_id == "red")
        return new MainLevel(255, 0, 0, "green");
    else if (level_id == "green")
        return new MainLevel(0, 255, 0, "blue");
    else if (level_id == "blue")
        return new MainLevel(0, 0, 255);
    else
        return nullptr;
}

void
TestLevelFactory::release(Level *level)
{
    delete level;
}


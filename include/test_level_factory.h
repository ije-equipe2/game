#ifndef TEST_LEVEL_FACTORY_H
#define TEST_LEVEL_FACTORY_H

#include <ijengine/level_factory.h>

#include <vector>

using std::vector;

using namespace ijengine;

namespace ijengine
{
    namespace character_selection
    {
        extern vector<int> players_characters;
    }
}

class TestLevelFactory : public LevelFactory {
public:
    Level * make_level(const string& level_id);
    void release(Level *level);

private:
};

#endif

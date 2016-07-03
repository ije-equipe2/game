#ifndef CHARACTER_STATE_H
#define CHARACTER_STATE_H

#include <memory>
#include <vector>

using std::shared_ptr;
using std::vector;

using namespace ijengine;

class CharacterState {
public:
    CharacterState();
    ~CharacterState();

    typedef enum {IDLE_STATE, MOVING_STATE, LIGHT_ATTACK_STATE, HEAVY_ATTACK_STATE, SPECIAL_STATE,
        DEFENSE_STATE, NUMBER_OF_STATES} State;

    State m_current_sprite;
    unsigned m_refresh_rate;

};

#endif
#ifndef CHARACTER_STATE_FACTORY_H
#define CHARACTER_STATE_FACTORY_H

#include "character_state.h"
#include "idle_state.h"
#include "moving_state.h"

class CharacterStateFactory {
public:
    CharacterStateFactory();
    ~CharacterStateFactory();

    typedef enum {IDLE_STATE, MOVING_STATE, LIGHT_ATTACK_STATE, HEAVY_ATTACK_STATE, SPECIAL_STATE,
        DEFENSE_STATE, NUMBER_OF_STATES} State;

    CharacterState* change_character_state(int next_state);

protected:
    
};

#endif
#ifndef UTIL_H
#define UTIL_H

namespace util
{
    typedef enum { IDLE_STATE, MOVING_STATE, DEATH_STATE, LIGHT_ATTACK_STATE, HEAVY_ATTACK_STATE, SPECIAL_STATE,
        DEFENSE_STATE, NUMBER_OF_STATES} State;

    typedef enum { PLAYER_1, PLAYER_2, PLAYER_3, PLAYER_4
    } Players;

    typedef enum { BALLS_8, BALLS_7, BALLS_6, BALLS_5, BALLS_4, BALLS_3, BALLS_2, BALLS_1, DESTROYED
    } BaseStatus;
}

#endif
#include "character_state_factory.h"

CharacterStateFactory::CharacterStateFactory() 
{

}

CharacterStateFactory::~CharacterStateFactory()
{

}

CharacterState*
CharacterStateFactory::change_character_state(int next_state)
{
    switch(next_state) {
        case IDLE_STATE:
            return new IdleState();
            break;

        case MOVING_STATE:
            return new MovingState();
            break;

        default:
            printf("error on character_state_factory!\n");
            return nullptr;
    }
}
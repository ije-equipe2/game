#include "idle_state.h"

IdleState::IdleState()
    :CharacterState()
{
    m_current_sprite = IDLE_STATE;
    m_refresh_rate = 275;
}
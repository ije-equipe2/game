#include "knight.h"
#include "ije02_game.h"

#define MAX_LIFE 300
#define EFFECTS_VOLUME 100

Knight::Knight(vector<string> sprite_paths, unsigned id, double x, double y, int character_code)
    : Character(sprite_paths, id, x, y, MAX_LIFE, character_code)
{
    m_special_cooldown = 5000;
    m_heavy_attack_cooldown = 2000;
    m_light_attack_cooldown = 300;
    m_defense_cooldown = 300;
    m_last_used_special = -m_special_cooldown;
    m_last_used_heavy_attack = -m_heavy_attack_cooldown;
    m_last_used_light_attack = -m_light_attack_cooldown;
    m_last_used_defense = -m_defense_cooldown;
}

void
Knight::heavy_attack()
{
    audio::play_sound_effect("res/sound/fx/pesadao_heavy.ogg", EFFECTS_VOLUME, 0);
    change_character_state(HEAVY_ATTACK_STATE);
}

void
Knight::light_attack() {
    audio::play_sound_effect("res/sound/fx/pesadao_light.ogg", EFFECTS_VOLUME, 0);
    change_character_state(LIGHT_ATTACK_STATE);
}

void
Knight::defense() {
    audio::play_sound_effect("res/sound/fx/pesadao_block.ogg", EFFECTS_VOLUME, 0);
    change_character_state(DEFENSE_STATE);
}

void
Knight::special() {
    change_character_state(SPECIAL_STATE);
}
#include "main_level.h"
#include "menu_level.h"
#include "test_level_factory.h"

Level *
TestLevelFactory::make_level(const string& level_id)
{
    if (level_id == "red")
        return new MenuLevel("green");
    else if (level_id == "green"){
        m_character_choose_level = new CharacterChooseLevel("blue");
        return m_character_choose_level;
    }
    else if (level_id == "blue"){
        printf("Antes da chamada da MainLevel\n");
        printf("Primeiro Jogador: %d %d\n", m_character_choose_level->players_characters()[0].first,m_character_choose_level->players_characters()[0].second);
        printf("Segundo Jogador: %d %d\n", m_character_choose_level->players_characters()[1].first,m_character_choose_level->players_characters()[1].second);
        return new MainLevel("", m_character_choose_level->players_characters());
    }
    else
        return nullptr;
}

void
TestLevelFactory::release(Level *level)
{
    delete level;
}


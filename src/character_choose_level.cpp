#include "character_choose_level.h"
#include "engine.h"
#include "character.h"
#include "ije02_game.h"

#include <ijengine/canvas.h>
#include <ijengine/keyboard_event.h>
#include <ijengine/rectangle.h>
#include <cstdlib>
#include <vector>

using namespace std;
using namespace ijengine;
using std::vector;

CharacterChooseLevel::CharacterChooseLevel(const string& next_level)
    : m_done(false), m_next(next_level), m_start(-1)
{
    m_textures.push_back(resources::get_texture("character_selection/character_selection_background.png"));
    m_textures.push_back(resources::get_texture("character_selection/CharacterPortraits.png"));
    m_textures.push_back(resources::get_texture("character_selection/Icons.png"));

    m_selected_character = INFILTRATOR;
    m_number_of_players = 2;
    m_current_player = 1;
    m_frame = 0;
    m_current_character_selection = new CharacterSelection("character_selection/Pointers.png");

    printf("antes de add o filho\n");
    add_child(m_current_character_selection);
    printf("depois de add o filho\n");
    fflush(stdout);

    event::register_listener(this);
}

CharacterChooseLevel::~CharacterChooseLevel() {
    event::unregister_listener(this);
}

bool
CharacterChooseLevel::done() const
{
    return m_done;
}

string
CharacterChooseLevel::next() const
{
    return m_next;
}

string
CharacterChooseLevel::audio() const {
    return ".";
}

void
CharacterChooseLevel::update_self(unsigned now, unsigned)
{
    if (m_start == -1)
        m_start = now;

    if (now - m_start > 100)
    {
        m_start += 100;
        m_frame = (m_frame + 1) % (m_textures[0]->w() / 32);
    }


    if(m_current_player > m_number_of_players) {
        printf("Primeiro jogador: %d\n", m_players_characters[0]);
        printf("Segundo jogador: %d\n", m_players_characters[1]);
        //Ije02Game::m_players_characters = m_players_characters;
        m_done = true;

    }

    m_selected_character = m_current_character_selection->current_selection();
}

void
CharacterChooseLevel::draw_self(Canvas *canvas, unsigned, unsigned)
{
    canvas->clear();
    // background
    canvas->draw(m_textures[0].get(), 0, 0);

    Rectangle p1_portrait_rect {(double) m_current_character_selection->current_selection() * 100, 0.0, 100, 100};
    canvas->draw(m_textures[1].get(), p1_portrait_rect, 12, 12);
    
    vector< pair<double, double> > icons_start_coordinates {{122.4, 83.33}, {122.4, 126.66}, {165.6, 83.83},
        {165.6, 126.66}};
    for(int i = 0; i < 4; i++) {
        Rectangle rect {(double) 32 * i, 0.0, 32, 32};
        canvas->draw(m_textures[2].get(), rect, icons_start_coordinates[i].first, icons_start_coordinates[i].second);
    }
}

bool
CharacterChooseLevel::on_event(const GameEvent& event) {
    if(event.id() == game_event::CHOOSE_CHARACTER) {
        m_current_player_character = m_selected_character;

        m_players_characters.push_back(m_current_player_character);

        m_current_player++;
        return true;
    }
    return false;
}
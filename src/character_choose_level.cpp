#include "character_choose_level.h"
#include "engine.h"
#include "character.h"
#include "ije02_game.h"

#include <ijengine/canvas.h>
#include <ijengine/keyboard_event.h>
#include <ijengine/rectangle.h>
#include <cstdlib>
using namespace std;
using namespace ijengine;

CharacterChooseLevel::CharacterChooseLevel(const string& next_level)
    : m_done(false), m_next(next_level), m_start(-1)
{
    m_textures.push_back(resources::get_texture("background_choose_character.jpg"));
    m_textures.push_back(resources::get_texture("selection.png"));
    m_textures.push_back(resources::get_texture("spritesheets/SpritesheetRedInfiltratorWAlk.png"));
    m_textures.push_back(resources::get_texture("spritesheets/SpritesheetRedMagerWalk.png"));
    m_textures.push_back(resources::get_texture("spritesheets/SpritesheetRedSoldierWAlk.png"));

    m_selected_character = INFILTRATOR;
    m_number_of_players = 2;
    m_current_player = 1;
    m_frame = 0;
    m_current_character_selection = new CharacterSelection("selection.png");

    add_child(m_current_character_selection);

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
    Rectangle rect_left {(double) 32 * m_frame, 0.0, 32.00, 32.00};
    Rectangle rect_right {(double) 32 * m_frame, 32.00, 32.00, 32.00};
    canvas->draw(m_textures[BACKGROUND].get(), 0, 0);
    canvas->draw(m_textures[INFILTRATOR].get(), rect_left, 0, 0);
    canvas->draw(m_textures[MAGE].get(), rect_right,  SCREEN_WIDTH - 35, 0);
    canvas->draw(m_textures[SOLDIER].get(), rect_left, 0, SCREEN_HEIGHT - 35);
    //canvas->draw(m_textures[KNIGHT].get(), rect, SCREEN_WIDTH - 35, SCREEN_HEIGHT - 35);
   // printf("%d, %d\n", SCREEN_SCALED_HEIGHT, SCREEN_SCALED_WIDTH);
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
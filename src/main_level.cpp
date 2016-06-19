#include "main_level.h"
#include "engine.h"
#include "character.h"
#include "ije02_game.h"
#include "mage.h"

#include <ijengine/canvas.h>
#include <ijengine/keyboard_event.h>
#include <cstdlib>

using namespace std;
using namespace ijengine;

MainLevel::MainLevel(const string& next_level, vector < int > players_characters)
    : m_done(false), m_next(next_level), m_start(-1)
{
    m_textures.push_back(resources::get_texture("map/Map002.jpg"));

    for (int i = 0; i < MAX_W; ++i)
        for (int j = 0; j < MAX_H; ++j)
            m_map[i][j] = 1;

    m_map[0][0] = 0;
    m_map[0][MAX_H - 1] = 0;
    m_map[MAX_W - 1][0] = 0;
    m_map[MAX_W - 1][MAX_H - 1] = 0;    

    m_players_characters = players_characters;
    double x =0.0;
    double y = 0.0;
    unsigned player_id = 0;

    for(const int &current_player_character : m_players_characters) {
        set_players_characters_position(player_id, x, y);
        add_child(m_character_factory.make_character(current_player_character, player_id, x, y));
        player_id++;
    }
}

MainLevel::~MainLevel() {
    
}

bool
MainLevel::done() const
{
    return m_done;
}

string
MainLevel::next() const
{
    return m_next;
}

string
MainLevel::audio() const {
    return ".";
}

void
MainLevel::update_self(unsigned now, unsigned)
{
    if (m_start == -1)
        m_start = now;

    if (now - m_start > 10000000)
        m_done = true;
}

void
MainLevel::draw_self(Canvas *canvas, unsigned, unsigned)
{
    canvas->clear();
    
    canvas->draw(m_textures[0].get(), 0, 0);
}

void
MainLevel::set_players_characters_position(unsigned player_id, double& x_pos, double& y_pos)
{
    switch(player_id) {
        case PLAYER_1:
            x_pos = 0.0;
            y_pos = 0.0;
            break;

        case PLAYER_2:
            x_pos = (double) SCREEN_WIDTH - 32.0;
            y_pos = 0.0;
            break;

        case PLAYER_3:
            x_pos = 0.0;
            y_pos = (double) SCREEN_HEIGHT - 32.0;
            break;

        case PLAYER_4:
            x_pos = (double) SCREEN_WIDTH - 32.0;
            y_pos = (double) SCREEN_HEIGHT - 32.0;
            break;

        default:
            printf("Valor errado no set_players_characters_position!\n");
            printf("player_id: %d", player_id);
            break;
    }
}

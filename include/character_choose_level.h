#ifndef CHARACTER_CHOOSE_LEVEL_h
#define CHARACTER_CHOOSE_LEVEL_h

#include <ijengine/level.h>
#include <ijengine/texture.h>
#include <ijengine/event.h>
#include <ijengine/game_events_listener.h>
#include "character_selection.h"

#include <string>
#include <memory>
#include <vector>
#include <utility>

using std::pair;
using std::string;
using std::vector;
using std::shared_ptr;

using namespace ijengine;

class CharacterChooseLevel : public Level, public GameEventsListener {
public:
    CharacterChooseLevel(const string& next = "");
    ~CharacterChooseLevel();

    enum {
        BACKGROUND,
        SELECTION,
        INFILTRATOR,
        MAGE,
        SOLDIER,
        KNIGHT
    };

    bool done() const;
    string next() const;
    string audio() const;
    vector < pair<int, int> > players_characters() const { return m_players_characters; }

protected:
    void update_self(unsigned now, unsigned last);
    void draw_self(Canvas *canvas, unsigned now, unsigned last);
    bool on_event(const GameEvent& event);


private:
    bool m_done;
    string m_next;
    int m_start;
    int m_frame;
    int m_selected_character;
    int m_current_player;
    int m_number_of_players;
    CharacterSelection *m_current_character_selection;
    vector < pair<int, int> > m_players_characters = {};
    pair <int, int> m_current_player_character;

    vector< shared_ptr<Texture> > m_textures;

};

#endif
#ifndef CHARACTER_SELECTION_H
#define CHARACTER_SELECTION_H

#include <ijengine/game_object.h>
#include <ijengine/game_events_listener.h>
#include <ijengine/texture.h>
#include <ijengine/rectangle.h>
#include <ijengine/event.h>

#include <memory>
#include <string>

using std::shared_ptr;
using std::string;
using namespace ijengine;

class CharacterSelection : public GameObject, GameEventsListener {
public:
    CharacterSelection(const string sprite_path);
    ~CharacterSelection();

    enum {
        INFILTRATOR,
        MAGE,
        SOLDIER,
        KNIGHT
    };

    int current_selection() const { return m_current_selection; }

protected:
    void update_self(unsigned now, unsigned last);
    void draw_self(Canvas *canvas, unsigned now, unsigned last);
    bool on_event(const GameEvent& event);
    void update_position();

private:
    int m_frame;
    int m_start;
    int m_current_selection;
    int m_w;
    int m_h;
    shared_ptr<Texture> m_texture;
};

#endif
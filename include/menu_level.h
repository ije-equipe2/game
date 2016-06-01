#ifndef MENU_LEVEL_H
#define MENU_LEVEL_H

#include <ijengine/level.h>
#include <ijengine/texture.h>
#include <ijengine/event.h>
#include <ijengine/game_events_listener.h>

#include <string>
#include <memory>
#include <vector>

using std::string;
using std::vector;
using std::shared_ptr;

using ijengine::Level;
using ijengine::Canvas;
using ijengine::Texture;
using ijengine::Event;

using namespace ijengine;

#define MAX_W 16
#define MAX_H 12

class MenuLevel : public Level, public GameEventsListener {
public:
    MenuLevel(const string& next = "");
    ~MenuLevel();
    
    bool done() const;
    string next() const;
    string audio() const;

protected:
    void update_self(unsigned now, unsigned last);
    void draw_self(Canvas *canvas, unsigned now, unsigned last);
    bool on_event(const GameEvent& event);

private:
    bool m_done;
    string m_next;
    int m_start;

    vector< shared_ptr<Texture> > m_textures;
};

#endif

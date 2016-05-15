#ifndef CHARACTER_H
#define CHARACTER_H

#include <ijengine/gameobject.h>
#include <ijengine/game_events_listener.h>
#include <ijengine/texture.h>

#include <memory>

using std::shared_ptr;
using namespace ijengine;

class Character : public GameObject, public GameEventsListener {
public:
	Character();
	~Character();

protected:
	void update_self(unsigned now, unsigned last);
	void draw_self(Canvas *canvas, unsigned now, unsigned last);

    typedef enum { MOVING_DOWN, MOVING_LEFT, MOVING_RIGHT, MOVING_UP } State;

    bool on_event(const GameEvent& event);

private:
    State m_state;
    int m_frame;
    int m_start;
    double m_speed;
    int m_w, m_h;
    shared_ptr<Texture> m_texture;
};

#endif

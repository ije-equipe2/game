#ifndef CHARACTER_H
#define CHARACTER_H

#include <ijengine/gameobject.h>
#include <ijengine/game_events_listener.h>
#include <ijengine/texture.h>

#include <memory>
#include <vector>
#include <utility>
#include <string>

using std::shared_ptr;
using std::vector;
using std::pair;
using std::string;
using namespace ijengine;


class Character : public GameObject, public GameEventsListener {
public:
	Character(string sprite_path, unsigned id, double x, double y);
	~Character();
    
    enum {
        START_MOVING_DOWN,
        START_MOVING_LEFT,
        START_MOVING_RIGHT,
        START_MOVING_UP, 
        STOP_MOVING_DOWN,
        STOP_MOVING_LEFT,
        STOP_MOVING_RIGHT,
        STOP_MOVING_UP,
        NUMBER_OF_CHARACTER_EVENTS
    };

protected:
    void update_self(unsigned now, unsigned last);
    void draw_self(Canvas *canvas, unsigned now, unsigned last);

    typedef enum {MOVING_DOWN, MOVING_LEFT, MOVING_RIGHT, MOVING_UP, MOVING_DOWN_RIGHT, MOVING_DOWN_LEFT, MOVING_UP_LEFT, MOVING_UP_RIGHT} State;

    bool on_event(const GameEvent& event);

private:
    unsigned m_id;
    State m_state;
    int m_frame;
    int m_start;
    int m_w;
    int m_h;
    double m_x_speed;
    double m_y_speed;
    shared_ptr<Texture> m_texture;
    vector< pair<double, double> > m_speed_vector;
};

#endif

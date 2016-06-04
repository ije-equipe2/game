#ifndef CHARACTER_H
#define CHARACTER_H

#include <ijengine/game_object.h>
#include <ijengine/game_events_listener.h>
#include <ijengine/texture.h>
#include <ijengine/collidable.h>
#include <ijengine/rectangle.h>
#include <ijengine/event.h>

#include <memory>
#include <vector>
#include <utility>
#include <string>
#include <unordered_map>

using std::shared_ptr;
using std::vector;
using std::pair;
using std::string;
using std::unordered_map;
using namespace ijengine;


class Character : public GameObject, public GameEventsListener, public Collidable {
public:
	Character(const string sprite_path, unsigned id, double x, double y);
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
        LIGHT_ATTACK,
        HEAVY_ATTACK,
        BLOCK,
        SPECIAL,
        NUMBER_OF_CHARACTER_EVENTS
    };

    bool active() const;
    const Rectangle& bounding_box() const;
    const list<Rectangle>& hit_boxes() const;

    void on_collision(const Collidable *who, const Rectangle& where, unsigned now, unsigned last);
    pair<double, double> direction() const;

    unsigned id() const { return m_id; }

protected:
    void update_self(unsigned now, unsigned last);
    void draw_self(Canvas *canvas, unsigned now, unsigned last);

    typedef enum {MOVING_RIGHT, MOVING_LEFT} State;

    bool on_event(const GameEvent& event);

protected:
    unsigned m_id;
    State m_state;
    int m_frame;
    int m_start;
    int m_w;
    int m_h;
    double m_x_speed;
    double m_y_speed;
    double m_speed;
    shared_ptr<Texture> m_texture;
    unordered_map<string, pair<double, double> > m_speed_vector;
    Rectangle m_bounding_box;

    inline void update_position(const unsigned &now, const unsigned &last, bool backwards = false);
};

#endif

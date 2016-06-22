#ifndef SPEAR_H
#define SPEAR_H

#include "skill.h"

#include <cmath>
#include <ijengine/game_object.h>
#include <ijengine/rectangle.h>
#include <ijengine/color.h>
#include <ijengine/canvas.h>
#include <ijengine/collidable.h>
#include <ijengine/engine.h>

#include <memory>
#include <vector>

using std::shared_ptr;
using std::vector;

using namespace std;
using namespace ijengine;

class Spear : public Skill {
public:
    Spear(GameObject *parent, unsigned soldier_id, double xp, double yp,
        double dx, double dy, int damage);

    ~Spear();
    bool active() const;
    const Rectangle& bounding_box() const;
    const list<Rectangle>& hit_boxes() const;
    pair<double, double> direction() const;

    void on_collision(const Collidable *who, const Rectangle& where, unsigned now, unsigned last);

protected:
    void update_self(unsigned now, unsigned last);
    void draw_self(Canvas *canvas, unsigned, unsigned);
    unsigned m_character_id;
    typedef enum { MOVING_LEFT, MOVING_RIGHT} State;
    State m_state;
    double m_dx, m_dy;
    int m_damage;
    double m_speed;
    int m_frame;
    int m_start;
    shared_ptr<Texture> m_texture;
    Rectangle m_bounding_box;


//    bool on_event(const GameEvent& event);
};

#endif

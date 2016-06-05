#ifndef FIREBALL_H
#define FIREBALL_H

#include "skill.h"

#include <cmath>
#include <ijengine/game_object.h>
#include <ijengine/rectangle.h>
#include <ijengine/color.h>
#include <ijengine/canvas.h>
#include <ijengine/collidable.h>
#include <ijengine/engine.h>

using namespace std;
using namespace ijengine;

class Fireball : public Skill {
public:
	Fireball(GameObject *parent, unsigned mage_id, double xp, double yp, double dx, double dy, int damage);

    ~Fireball();
    bool active() const;
    const Rectangle& bounding_box() const;
    const list<Rectangle>& hit_boxes() const;
    pair<double, double> direction() const;

    void on_collision(const Collidable *who, const Rectangle& where, unsigned now, unsigned last);

protected:
    void update_self(unsigned now, unsigned last);
    void draw_self(Canvas *canvas, unsigned, unsigned);
    unsigned m_character_id;
    double m_dx, m_dy;
    int m_damage;
    double m_speed;

//    bool on_event(const GameEvent& event);
};

#endif

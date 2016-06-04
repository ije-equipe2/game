#ifndef FIREBALL_H
#define FIREBALL_H

#include <cmath>
#include <ijengine/game_object.h>
#include <ijengine/rectangle.h>
#include <ijengine/color.h>
#include <ijengine/canvas.h>
#include <ijengine/collidable.h>
#include <ijengine/engine.h>

using namespace std;
using namespace ijengine;

class Fireball : public GameObject, public Collidable {
public:
	Fireball(GameObject *parent, unsigned mage_id, double xp, double yp, double dx, double dy, int damage)
        : GameObject(parent, xp, yp), m_mage_id(mage_id), m_dx(dx/hypot(dx, dy)), m_dy(dy/hypot(dx, dy)), m_damage(damage), m_speed(100.0)

    {
        physics::register_object(this);
    }

    ~Fireball()
    {
        physics::unregister_object(this);
    }

    bool active() const;
    const Rectangle& bounding_box() const;
    const list<Rectangle>& hit_boxes() const;
    pair<double, double> direction() const;


    int damage() const { return m_damage; }

    void on_collision(const Collidable *who, const Rectangle& where, unsigned now, unsigned last);
protected:
    unsigned m_mage_id;
    double m_dx, m_dy;
    int m_damage;
    double m_speed;

    void update_self(unsigned now, unsigned last);
    void draw_self(Canvas *canvas, unsigned, unsigned);

//    bool on_event(const GameEvent& event);
};

#endif

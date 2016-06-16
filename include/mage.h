#ifndef MAGE_H
#define MAGE_H

#include "character.h"

using namespace ijengine;

class Mage : public Character {
public:
	Mage(unsigned id, double x, double y)
        : Character("spritesheets/SpritesheetRedMagerWalk.png", id, x, y)
    {
    }

protected:
//    void update_self(unsigned now, unsigned last);
 //   void draw_self(Canvas *canvas, unsigned now, unsigned last);

  //  typedef enum {MOVING_RIGHT, MOVING_LEFT} State;

    bool on_event(const GameEvent& event);
};

#endif

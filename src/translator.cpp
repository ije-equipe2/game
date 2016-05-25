#include "translator.h"
#include "ije02_game.h"

bool
Translator::translate(GameEvent& to, const MouseEvent& from)
{
    to.set_timestamp(from.timestamp());
    to.set_property<double>("x", from.x());
    to.set_property<double>("y", from.y());

    if (from.state() == MouseEvent::MOTION)
        to.set_id(game_event::MOTION);
    else
        to.set_id(game_event::CLICK);

    return true;
}

bool
Translator::translate(GameEvent& to, const SystemEvent& from)
{
    if (from.action() == SystemEvent::QUIT)
    {
        to.set_timestamp(from.timestamp());
        to.set_id(game_event::QUIT);

        return true;
    }

    return false;
}

bool
Translator::translate(GameEvent& to, const KeyboardEvent& from)
{
    to.set_timestamp(from.timestamp());

    bool done = true;
    int id = 0;

    if(from.key() == KeyboardEvent::ESCAPE) {
        id = game_event::QUIT;
    }
    else if(from.key() >= KeyboardEvent::LEFT && from.key() <= KeyboardEvent::DOWN) {
        id = game_event::MOVEMENT;
        
        if(from.state() == KeyboardEvent::PRESSED) {
            to.set_property<string>("action", "start");
        }
        else if(from.state() == KeyboardEvent::RELEASED) {
            to.set_property<string>("action", "stop");
        }

        switch(from.key()) {
        case KeyboardEvent::LEFT:
            to.set_property<string>("direction", "left");
            break;
        case KeyboardEvent::RIGHT:
            to.set_property<string>("direction", "right");
            break;
        case KeyboardEvent::UP:
            to.set_property<string>("direction", "up");
            break;
        case KeyboardEvent::DOWN:
            to.set_property<string>("direction", "down");
            break;
        default:
            break;
        }
    }
    else {
        done = false;
    }

    to.set_id(id);

    return done;
}
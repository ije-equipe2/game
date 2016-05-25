#ifndef IJE02_TRANSLATOR_H
#define IJE02_TRANSLATOR_H

#include <ijengine/mouse_event.h>
#include <ijengine/system_event.h>
#include <ijengine/keyboard_event.h>
#include <ijengine/events_translator.h>

using namespace ijengine;
using namespace std;

class Translator : public EventsTranslator
{
public:
    bool translate(GameEvent& to, const MouseEvent& from);
    bool translate(GameEvent& to, const SystemEvent& from);
    virtual bool translate(GameEvent& to, const KeyboardEvent& from);
};

#endif

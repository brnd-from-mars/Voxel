//
// Created by Brendan Berg on 30.03.19.
//

#include "KeyboardEvent.hpp"


KeyboardEvent::KeyboardEvent (EventType type, int key)
    : Event(EventCategory::Keyboard, type), m_Key (key)
{ }


EventData KeyboardEvent::GetData ()
{
    EventData result;
    result.keyboardData.key = m_Key;
    return result;
}

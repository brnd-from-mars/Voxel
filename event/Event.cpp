//
// Created by Brendan Berg on 30.03.19.
//

#include "Event.hpp"


Event::Event (EventCategory category, EventType type)
    : m_Category(category), m_Type(type)
{ }


EventCategory Event::GetCategory ()
{
    return m_Category;
}


EventType Event::GetType ()
{
    return m_Type;
}

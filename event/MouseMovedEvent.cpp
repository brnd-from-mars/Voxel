//
// Created by Brendan Berg on 10.04.19.
//

#include "MouseMovedEvent.hpp"


MouseMovedEvent::MouseMovedEvent (EventType type, float posX, float posY)
    : Event(EventCategory::MouseMoved, type), m_PosX(posX), m_PosY(posY)
{ }


EventData MouseMovedEvent::GetData ()
{
    EventData result;
    result.mouseMovedData.posX = m_PosX;
    result.mouseMovedData.posY = m_PosY;
    return result;
}

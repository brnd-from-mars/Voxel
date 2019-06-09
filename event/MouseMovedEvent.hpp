//
// Created by Brendan Berg on 10.04.19.
//

#ifndef VOXEL_MOUSEMOVEDEVENT_HPP
#define VOXEL_MOUSEMOVEDEVENT_HPP

#include "Event.hpp"


class MouseMovedEvent : public Event
{
public:

    MouseMovedEvent (EventType type, float posX, float posY);

    EventData GetData () override;


private:

    float m_PosX;

    float m_PosY;


};


#endif //VOXEL_MOUSEMOVEDEVENT_HPP

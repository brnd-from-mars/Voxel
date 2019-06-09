//
// Created by Brendan Berg on 30.03.19.
//

#ifndef VOXEL_KEYBOARDEVENT_HPP
#define VOXEL_KEYBOARDEVENT_HPP

#include "../graphics/Graphics.hpp"

#include "Event.hpp"
#include "KeyCodes.hpp"



class KeyboardEvent : public Event
{
public:

    KeyboardEvent (EventType type, int key);

    EventData GetData () override;


private:

    int m_Key;


};


#endif //VOXEL_KEYBOARDEVENT_HPP

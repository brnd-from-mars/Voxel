//
// Created by Brendan Berg on 30.03.19.
//

#ifndef VOXEL_EVENT_HPP
#define VOXEL_EVENT_HPP


enum class EventCategory
{
    Null, Keyboard, MouseMoved, MouseButton
};


enum class EventType
{
    Null,
    KeyboardPressed, KeyboardReleased,
    MouseMoved,
    MouseButtonPressed, MouseButtonReleased
};


union EventData
{
    struct KeyboardData
    {
        int key;
    } keyboardData;

    struct MouseMovedData
    {
        float posX;
        float posY;
    } mouseMovedData;
};


class Event
{
public:

    EventCategory GetCategory ();

    EventType GetType ();

    virtual EventData GetData () = 0;


protected:

    Event (EventCategory category, EventType type);

    EventCategory m_Category;

    EventType m_Type;


};


#endif //VOXEL_EVENT_HPP

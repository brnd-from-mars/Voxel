//
// Created by Brendan Berg on 30.03.19.
//

#ifndef VOXEL_EVENTDISPATCHER_HPP
#define VOXEL_EVENTDISPATCHER_HPP

#include <memory>
#include <functional>
#include <vector>

#include "../graphics/Graphics.hpp"

#include "Event.hpp"
#include "KeyboardEvent.hpp"
#include "MouseMovedEvent.hpp"


typedef std::function<bool (Event&)> EventHandlerFunction;

typedef std::pair<EventCategory, EventHandlerFunction> EventHandlerEntry;


class EventDispatcher
{
public:

    explicit EventDispatcher (std::shared_ptr<Graphics>& graphics);

    void RegisterHandler (EventCategory category,
                          EventHandlerFunction& handler);


private:

    void SetKeyboardCallback ();

    void SetMouseMovedCallback ();

    // TODO: outsource
    void RegisterKeyboardEventHandler ();

    // TODO: outsource
    bool KeyboardEventHandler (Event& event);

    void DispatchEvent (Event& event);

    static EventDispatcher* GetEventDispatcher (GLFWwindow* window);

    std::shared_ptr<Graphics> m_Graphics;

    std::vector<EventHandlerEntry> m_Handlers;


};


#endif //VOXEL_EVENTDISPATCHER_HPP

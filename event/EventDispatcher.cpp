//
// Created by Brendan Berg on 30.03.19.
//

#include "EventDispatcher.hpp"


EventDispatcher::EventDispatcher (std::shared_ptr<Graphics>& graphics)
    : m_Graphics(graphics)
{
    m_Graphics->SetWindowUserPointer(this);
    SetKeyboardCallback();
    SetMouseMovedCallback();

    RegisterKeyboardEventHandler();
}


void EventDispatcher::RegisterHandler (EventCategory category,
                                       EventHandlerFunction& handler)
{
    m_Handlers.emplace_back(category, handler);
}


void EventDispatcher::SetKeyboardCallback ()
{
    glfwSetKeyCallback(
        m_Graphics->GetWindow(),
        [](GLFWwindow* window, int key, int, int action, int)
        {
            EventType type;
            switch (action)
            {
                case GLFW_PRESS:
                    type = EventType::KeyboardPressed;
                    break;
                case GLFW_RELEASE:
                    type = EventType::KeyboardReleased;
                    break;
                default:
                    return;
            }
            KeyboardEvent event(type, key);
            GetEventDispatcher(window)->DispatchEvent(event);
        });
}


void EventDispatcher::SetMouseMovedCallback ()
{
    glfwSetCursorPosCallback(
        m_Graphics->GetWindow(),
        [](GLFWwindow* window, double posX, double posY)
        {
            MouseMovedEvent event(EventType::MouseMoved,
                                  static_cast<float>(posX),
                                  static_cast<float>(posY));
            GetEventDispatcher(window)->DispatchEvent(event);

            if (!GetEventDispatcher(window)->m_Graphics->GetGUIMode())
            {
                glfwSetCursorPos(window, 0.0, 0.0);
            }
        });
}


void EventDispatcher::RegisterKeyboardEventHandler ()
{
    EventHandlerFunction handler = std::bind(
        &EventDispatcher::KeyboardEventHandler, this, std::placeholders::_1);
    RegisterHandler(EventCategory::Keyboard, handler);
}


bool EventDispatcher::KeyboardEventHandler (Event& event)
{
    if (event.GetType() != EventType::KeyboardPressed)
    {
        return false;
    }

    auto key = event.GetData().keyboardData.key;

    switch (key)
    {
        case EVENT_KEY_P:
            m_Graphics->SwitchGUIMode();
            return true;
        case EVENT_KEY_ESCAPE:
            // TODO: close game
            return true;
        default:
            return false;
    }
}


void EventDispatcher::DispatchEvent (Event& event)
{
    for (auto& [category, handler] : m_Handlers)
    {
        if (event.GetCategory() == category
            || event.GetCategory() == EventCategory::Null
            || category == EventCategory::Null)
        {
            if (handler(event))
            {
                return;
            }
        }
    }
}


EventDispatcher* EventDispatcher::GetEventDispatcher (GLFWwindow* window)
{
    return static_cast<EventDispatcher*>(glfwGetWindowUserPointer(window));
}

//
// Created by Brendan Berg on 08.04.19.
//

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>

#include "PlayerMovable.hpp"


PlayerMovable::PlayerMovable (EventDispatcher& eventDispatcher,
                              std::shared_ptr<Graphics>& graphics)
    : m_Position(0.0f, 100.0f, 0.0f), m_ViewDirection(1.0f, 0.0f, 0.0f),
    m_FrontDirection(1.0f, 0.0f, 0.0f), m_RightDirection(0.0f),
    m_UpDirection(0.0f, 1.0f, 0.0f), m_Graphics(graphics)
{
    InitMoveButtons();
    RegisterKeyboardEventHandler(eventDispatcher);
    RegisterMouseMovedEventHandler(eventDispatcher);
    GenerateMoveDirections();
}


void PlayerMovable::Update (double time)
{
    glm::vec3 velocity(0.0f);

    for (unsigned int dir = 0; dir < m_MoveButtons.size(); ++dir)
    {
        if (m_MoveButtonStates[dir])
        {
            auto [vector, d] = m_MoveOperations[dir];
            velocity += d * vector;
        }
    }

    if (velocity == glm::vec3(0.0f))
    {
        return;
    }

    velocity = 4.0f * glm::normalize(velocity);
    m_Position += velocity * static_cast<float>(time);
}


glm::vec3 PlayerMovable::GetPosition ()
{
    return m_Position;
}


glm::mat4 PlayerMovable::GetViewMatrix ()
{
    return glm::lookAt(
        m_Position, m_Position + m_ViewDirection, glm::vec3(0.0, 1.0, 0.0));
}


void PlayerMovable::InitMoveButtons ()
{
    m_MoveButtonStates.resize(6, false);

    m_MoveButtons.emplace_back(EVENT_KEY_W, 0);
    m_MoveButtons.emplace_back(EVENT_KEY_D, 1);
    m_MoveButtons.emplace_back(EVENT_KEY_S, 2);
    m_MoveButtons.emplace_back(EVENT_KEY_A, 3);
    m_MoveButtons.emplace_back(EVENT_KEY_SPACE, 4);
    m_MoveButtons.emplace_back(EVENT_KEY_LEFT_SHIFT, 5);

    m_MoveOperations.emplace_back(m_FrontDirection, 1.0f);
    m_MoveOperations.emplace_back(m_RightDirection, 1.0f);
    m_MoveOperations.emplace_back(m_FrontDirection, -1.0f);
    m_MoveOperations.emplace_back(m_RightDirection, -1.0f);
    m_MoveOperations.emplace_back(m_UpDirection, 1.0f);
    m_MoveOperations.emplace_back(m_UpDirection, -1.0f);
}


void
PlayerMovable::RegisterKeyboardEventHandler (EventDispatcher& eventDispatcher)
{
    EventHandlerFunction handler = std::bind(
        &PlayerMovable::KeyboardEventHandler, this, std::placeholders::_1);
    eventDispatcher.RegisterHandler(EventCategory::Keyboard, handler);
}


void
PlayerMovable::RegisterMouseMovedEventHandler (EventDispatcher& eventDispatcher)
{
    EventHandlerFunction handler = std::bind(
        &PlayerMovable::MouseMovedEventHandler, this, std::placeholders::_1);
    eventDispatcher.RegisterHandler(EventCategory::MouseMoved, handler);
}


bool PlayerMovable::KeyboardEventHandler (Event& event)
{
    auto key = event.GetData().keyboardData.key;

    for (auto [keycode, dir] : m_MoveButtons)
    {
        if (keycode == key)
        {
            m_MoveButtonStates[dir] =
                (event.GetType() == EventType::KeyboardPressed);
            return true;
        }
    }

    return false;
}


bool PlayerMovable::MouseMovedEventHandler (Event& event)
{
    if (m_Graphics->GetGUIMode() || (event.GetType() != EventType::MouseMoved))
    {
        return false;
    }

    auto [dAzimuth, dElevation] = event.GetData().mouseMovedData;
    dAzimuth *= -0.5f;
    dElevation *= -0.5f;

    auto newElevation = glm::degrees(glm::asin(m_ViewDirection.y)) + dElevation;

    if (-89.0f < newElevation && newElevation < 89.0f)
    {
        m_ViewDirection = glm::rotate(m_ViewDirection, glm::radians(dElevation),
                                      m_RightDirection);
    }

    m_ViewDirection = glm::rotateY(m_ViewDirection, glm::radians(dAzimuth));

    GenerateMoveDirections();

    return true;
}


void PlayerMovable::GenerateMoveDirections ()
{
    m_ViewDirection = glm::normalize(m_ViewDirection);
    m_FrontDirection = m_ViewDirection;
    m_FrontDirection.y = 0.0f;
    m_FrontDirection = glm::normalize(m_FrontDirection);
    m_RightDirection = glm::rotateY(m_FrontDirection, glm::radians(-90.0f));
}

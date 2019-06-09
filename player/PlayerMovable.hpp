//
// Created by Brendan Berg on 08.04.19.
//

#ifndef VOXEL_PLAYERMOVABLE_HPP
#define VOXEL_PLAYERMOVABLE_HPP

#include <memory>

#include <glm/glm.hpp>

#include "../graphics/Graphics.hpp"

#include "../event/EventDispatcher.hpp"


class PlayerMovable
{
public:

    PlayerMovable (EventDispatcher& eventDispatcher,
                   std::shared_ptr<Graphics>& graphics);

    void Update (double time);

    glm::vec3 GetPosition ();

    // TODO: outsource to player renderable
    glm::mat4 GetViewMatrix ();


private:

    void InitMoveButtons ();

    void RegisterKeyboardEventHandler (EventDispatcher& eventDispatcher);

    void RegisterMouseMovedEventHandler (EventDispatcher& eventDispatcher);

    bool KeyboardEventHandler (Event& event);

    bool MouseMovedEventHandler (Event& event);

    void GenerateMoveDirections ();

    std::vector<bool> m_MoveButtonStates;

    std::vector<std::pair<int, unsigned int>> m_MoveButtons;

    std::vector<std::pair<glm::vec3&, float>> m_MoveOperations;

    glm::vec3 m_Position;

    glm::vec3 m_ViewDirection;

    glm::vec3 m_FrontDirection;

    glm::vec3 m_RightDirection;

    glm::vec3 m_UpDirection;

    std::shared_ptr<Graphics>& m_Graphics;


};


#endif //VOXEL_PLAYERMOVABLE_HPP

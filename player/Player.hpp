//
// Created by Brendan Berg on 18.03.19.
//

#ifndef VOXEL_PLAYER_HPP
#define VOXEL_PLAYER_HPP

#include <memory>

#include <glm/glm.hpp>

#include "../graphics/Graphics.hpp"
#include "../event/EventDispatcher.hpp"

#include "PlayerMovable.hpp"


class Player
{
public:

    explicit Player (std::unique_ptr<PlayerMovable>&& playerMovable);

    void Update (double time);

    std::unique_ptr<PlayerMovable>& GetMovable ();


private:

    std::unique_ptr<PlayerMovable> m_PlayerMovable;


};


#endif //VOXEL_PLAYER_HPP

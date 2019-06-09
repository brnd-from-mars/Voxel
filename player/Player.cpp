//
// Created by Brendan Berg on 18.03.19.
//

#include <iostream>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Player.hpp"


Player::Player (std::unique_ptr<PlayerMovable>&& playerMovable)
    : m_PlayerMovable(std::move(playerMovable))
{ }


void Player::Update (double time)
{
    m_PlayerMovable->Update(time);
}


std::unique_ptr<PlayerMovable>& Player::GetMovable ()
{
    return m_PlayerMovable;
}

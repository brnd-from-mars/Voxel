//
// Created by Brendan Berg on 14.03.19.
//

#include <algorithm>

#include "BlockColumn.hpp"


BlockColumn::BlockColumn (unsigned int height)
    : m_Height(height)
{
    m_Blocks.resize(MAX_HEIGHT, BLOCK_AIR);
    std::fill(m_Blocks.begin(), m_Blocks.begin() + height, BLOCK_STONE);
}


unsigned int& BlockColumn::GetBlock (unsigned int y)
{
    return m_Blocks.at(y);
}

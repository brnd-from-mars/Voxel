//
// Created by Brendan Berg on 14.03.19.
//

#include <algorithm>

#include "BlockColumn.hpp"


BlockColumn::BlockColumn (unsigned int height)
    : m_Height(height)
{
    m_Blocks.resize(CHUNK_HEIGHT, 0);
    std::fill(m_Blocks.begin(), m_Blocks.begin() + height, 1);
}


unsigned int& BlockColumn::GetBlock (unsigned int y)
{
    return m_Blocks.at(y);
}

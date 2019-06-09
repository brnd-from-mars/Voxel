//
// Created by Brendan Berg on 14.03.19.
//

#include <algorithm>

#include "BlockColumn.hpp"


BlockColumn::BlockColumn (char* data)
{
    m_Blocks.resize(CHUNK_HEIGHT, 0);
    memcpy(m_Blocks.data(), data, CHUNK_HEIGHT);
}


BlockColumn::BlockColumn (unsigned int height)
{
    m_Blocks.resize(CHUNK_HEIGHT, 0);
    height = std::min(height, static_cast<unsigned int>(CHUNK_HEIGHT - 1));
    std::fill(m_Blocks.begin(), m_Blocks.begin() + height, 1);
}


char* BlockColumn::GetData ()
{
    return m_Blocks.data();
}


char& BlockColumn::GetBlock (unsigned int y)
{
    return m_Blocks.at(y);
}


void BlockColumn::SetBlock (unsigned int y, char id)
{
    GetBlock(y) = id;
}

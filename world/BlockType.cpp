//
// Created by Brendan Berg on 16.03.19.
//

#include "BlockType.hpp"


BlockType::BlockType (unsigned int blockID, const std::string& name)
    : m_BlockID(blockID), m_Name(name)
{
    m_SideToTexture.resize(6, 0);
}


BlockType::BlockType ()
    : BlockType(0, "")
{ }


unsigned int BlockType::AddTexture (
    const std::pair<glm::vec2, glm::vec2>& tile)
{
    m_TextureTiles.push_back(tile);
    return static_cast<unsigned int>(m_TextureTiles.size() - 1);
}


void BlockType::SetSideTexture (BlockSide side, unsigned int texture)
{
    m_SideToTexture[static_cast<int>(side)] = texture;
}


void BlockType::SetSolid ()
{
    m_Solid = true;
}


void BlockType::SetOpaque ()
{
    m_Opaque = true;
}


glm::vec2
BlockType::GetTextureCoordinate (BlockSide side, unsigned int vertex) const
{
    auto texture = m_TextureTiles[m_SideToTexture[static_cast<int>(side)]];
    switch (vertex)
    {
        case 0:
            return texture.first;
        case 1:
            return glm::vec2(texture.second.x, texture.first.y);
        case 2:
            return texture.second;
        case 3:
        default:
            return glm::vec2(texture.first.x, texture.second.y);
    }
}


bool BlockType::IsSolid () const
{
    return m_Solid;
}


bool BlockType::IsOpaque () const
{
    return m_Opaque;
}

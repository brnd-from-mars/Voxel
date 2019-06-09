//
// Created by Brendan Berg on 16.03.19.
//

#ifndef VOXEL_BLOCKTYPE_HPP
#define VOXEL_BLOCKTYPE_HPP

#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "BlockUtility.hpp"


class BlockType
{
public:

    BlockType (unsigned int blockID, const std::string& name);

    BlockType ();

    unsigned int AddTexture (const std::pair<glm::vec2, glm::vec2>& tile);

    void SetSideTexture (BlockSide side, unsigned int texture);

    void SetSolid ();

    void SetOpaque ();

    glm::vec2 GetTextureCoordinate (BlockSide side, unsigned int vertex) const;

    bool IsSolid () const;

    bool IsOpaque () const;


private:

    unsigned int m_BlockID;

    std::string m_Name;

    std::vector<std::pair<glm::vec2, glm::vec2>> m_TextureTiles;

    std::vector<int> m_SideToTexture;

    bool m_Solid;

    bool m_Opaque;


};


#endif //VOXEL_BLOCKTYPE_HPP

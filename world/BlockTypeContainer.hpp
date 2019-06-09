//
// Created by Brendan Berg on 16.03.19.
//

#ifndef VOXEL_BLOCKTYPECONTAINER_HPP
#define VOXEL_BLOCKTYPECONTAINER_HPP

#include "../utility/ConfigParser.hpp"

#include "BlockUtility.hpp"
#include "BlockType.hpp"


class BlockTypeContainer
{
public:

    explicit BlockTypeContainer (const std::string& filePath);

    const BlockType& GetBlock(unsigned int id) const;


private:

    void SetBlockDataBase (const CommandParameters& parameters);

    void SetBlockTexture (const CommandParameters& parameters);

    void AddBlockType (const CommandParameters& parameters);

    unsigned int AddBlockTypeTexture (unsigned int id,
                                      const std::string& parameter);

    std::vector<BlockType> m_BlockTypes;

    std::string m_TextureFileName;

    glm::vec2 m_TextureTileSize;
};


#endif //VOXEL_BLOCKTYPECONTAINER_HPP

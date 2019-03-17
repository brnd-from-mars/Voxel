//
// Created by Brendan Berg on 16.03.19.
//

#ifndef VOXEL_BLOCKTYPECONTAINER_HPP
#define VOXEL_BLOCKTYPECONTAINER_HPP

#include "../utility/ConfigParser.hpp"

#include "BlockType.hpp"


class BlockTypeContainer
{
public:

    explicit BlockTypeContainer (const std::string& filePath);


private:

    void SetBlockCount (const CommandParameters& parameters);

    void AddBlockType (const CommandParameters& parameters);

    std::vector<BlockType> m_BlockTypes;


};


#endif //VOXEL_BLOCKTYPECONTAINER_HPP

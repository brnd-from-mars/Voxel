//
// Created by Brendan Berg on 16.03.19.
//

#ifndef VOXEL_BLOCKTYPE_HPP
#define VOXEL_BLOCKTYPE_HPP

#include <string>

#include <glm/glm.hpp>


class BlockType
{
public:

    explicit BlockType (unsigned int blockID);

    BlockType ();


private:

    unsigned int m_BlockID;


};


#endif //VOXEL_BLOCKTYPE_HPP

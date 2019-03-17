//
// Created by Brendan Berg on 17.03.19.
//

#ifndef VOXEL_BLOCKCHUNKBLOCKS_HPP
#define VOXEL_BLOCKCHUNKBLOCKS_HPP

#include <vector>

#include <glm/glm.hpp>

#include "BlockColumn.hpp"


class BlockChunkBlocks
{
public:

    explicit BlockChunkBlocks ();

    unsigned int& GetBlock (const glm::ivec3& internalPos);

    void GetVisibleSides (const glm::ivec3& internalPos,
                          std::vector<BlockSide>& output);


private:

    unsigned int GetColumnIndex (const glm::ivec3& internalPos);

    BlockColumn& GetColumn (const glm::ivec3& internalPos);

    unsigned int GetNeighborOnSide (const glm::ivec3& internalPos,
                                    BlockSide side);

    std::vector<BlockColumn> m_Blocks;


};


#endif //VOXEL_BLOCKCHUNKBLOCKS_HPP

//
// Created by Brendan Berg on 17.03.19.
//

#ifndef VOXEL_BLOCKCHUNKBLOCKS_HPP
#define VOXEL_BLOCKCHUNKBLOCKS_HPP

#include <vector>
#include <memory>

#include <glm/glm.hpp>

#include "BlockColumn.hpp"
#include "BlockTypeContainer.hpp"
#include "WorldGenerator.hpp"
#include "ChunkLoader.hpp"


class BlockChunkBlocks
{
public:

    BlockChunkBlocks (std::unique_ptr<ChunkLoader>& chunkLoader,
                      const BlockTypeContainer& blockTypeContainer,
                      glm::ivec3 chunkPos, bool generate);

    char& GetBlock (const glm::ivec3& internalPos);

    void GetVisibleSides (const glm::ivec3& internalPos,
                          std::vector<BlockSide>& output);


private:

    unsigned int GetColumnIndex (const glm::ivec3& internalPos);

    BlockColumn& GetColumn (const glm::ivec3& internalPos);

    char GetNeighborOnSide (const glm::ivec3& internalPos, BlockSide side);

    std::vector<BlockColumn> m_Blocks;

    std::unique_ptr<ChunkLoader> m_ChunkLoader;

    const BlockTypeContainer& m_BlockTypeContainer;

    glm::ivec3 m_ChunkPos;


};


#endif //VOXEL_BLOCKCHUNKBLOCKS_HPP

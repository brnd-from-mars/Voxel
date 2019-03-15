//
// Created by Brendan Berg on 14.03.19.
//

#ifndef VOXEL_BLOCKCHUNK_HPP
#define VOXEL_BLOCKCHUNK_HPP

#include <vector>

#include <glm/glm.hpp>

#include "BlockColumn.hpp"
#include "BlockChunkRenderable.hpp"

#define CHUNK_SIZE 16


class BlockChunk
{
public:

    explicit BlockChunk (glm::ivec3 chunkPos, Graphics& graphics);

    BlockColumn& GetColumn (glm::ivec3 internalPos);

    unsigned int& GetBlock (glm::ivec3 internalPos);

    void GenerateMesh ();

    BlockChunkRenderable& GetRenderable ();


private:

    unsigned int GetColumnIndex (glm::ivec3 internalPos);

    void GetVisibleSides (glm::ivec3 internalPos,
                          std::vector<BlockSide>& output);

    unsigned int GetNeighborOnSide (glm::ivec3 internalPos, BlockSide side);

    glm::ivec3 m_ChunkPos;

    std::vector<BlockColumn> m_Blocks;

    BlockChunkRenderable m_BlockChunckRenderable;


};


#endif //VOXEL_BLOCKCHUNK_HPP

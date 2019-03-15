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

    explicit BlockChunk (glm::ivec3 chunkPos);

    BlockColumn& GetColumn (glm::uvec3 internalPos);

    unsigned int& GetBlock (glm::uvec3 internalPos);


private:

    unsigned int GetColumnIndex (glm::uvec3 internalPos);

    glm::ivec3 m_ChunkPos;

    std::vector<BlockColumn> m_Blocks;

    BlockChunkRenderable m_BlockChunckRenderable;


};


#endif //VOXEL_BLOCKCHUNK_HPP

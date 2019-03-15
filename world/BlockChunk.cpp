//
// Created by Brendan Berg on 14.03.19.
//

#include "BlockChunk.hpp"


BlockChunk::BlockChunk (glm::ivec3 chunkPos)
    : m_ChunkPos(chunkPos)
{
    m_Blocks.reserve(256);

    for (unsigned int y = 0; y < CHUNK_SIZE; ++y)
    {
        for (unsigned int x = 0; x < CHUNK_SIZE; ++x)
        {
            m_Blocks.emplace_back(64 + x + y);
        }
    }

    glm::uvec3 k(0, 0, 0);
    m_BlockChunckRenderable.AddFace(BLOCK_STONE, BlockSide::West, k);
}


BlockColumn& BlockChunk::GetColumn (glm::uvec3 internalPos)
{
    return m_Blocks.at(GetColumnIndex(internalPos));
}


unsigned int&
BlockChunk::GetBlock (glm::uvec3 internalPos)
{
    return GetColumn(internalPos).GetBlock(internalPos.y);
}


unsigned int BlockChunk::GetColumnIndex (glm::uvec3 internalPos)
{
    return internalPos.x + CHUNK_SIZE * internalPos.z;
}

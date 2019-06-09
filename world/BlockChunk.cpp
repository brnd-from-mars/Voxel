//
// Created by Brendan Berg on 14.03.19.
//

#include "BlockChunk.hpp"


BlockChunk::BlockChunk (const glm::ivec3& chunkPos,
                        std::unique_ptr<BlockChunkBlocks>&& blocks,
                        std::unique_ptr<BlockChunkRenderable>&& renderable)
    : m_ChunkPos(chunkPos), m_Blocks(std::move(blocks)),
    m_Renderable(std::move(renderable))
{
    m_Renderable->GenerateMesh(m_Blocks);
    m_Renderable->SetChunkPos(chunkPos);
}


std::unique_ptr<BlockChunkRenderable>& BlockChunk::GetRenderable ()
{
    return m_Renderable;
}


glm::ivec3 BlockChunk::GetPosition () const
{
    return m_ChunkPos;
}

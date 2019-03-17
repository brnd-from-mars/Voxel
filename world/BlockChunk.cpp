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
    GenerateMesh();
    m_Renderable->SetChunkPos(chunkPos);
}


std::unique_ptr<BlockChunkRenderable>& BlockChunk::GetRenderable ()
{
    return m_Renderable;
}


void BlockChunk::GenerateMesh ()
{
    for (unsigned int y = 0; y < CHUNK_HEIGHT; ++y)
    {
        for (unsigned int z = 0; z < CHUNK_SIZE; ++z)
        {
            for (unsigned int x = 0; x < CHUNK_SIZE; ++x)
            {
                auto internalPos = glm::ivec3(x, y, z);
                unsigned int block = m_Blocks->GetBlock(internalPos);
                if (block != 0)
                {
                    std::vector<BlockSide> neighbors;
                    m_Blocks->GetVisibleSides(internalPos, neighbors);
                    for (auto& side : neighbors)
                    {
                        m_Renderable->AddFace(
                            glm::vec4(internalPos, 1.0f), side, block);
                    }
                }
            }
        }
    }

    m_Renderable->UpdateData();
}

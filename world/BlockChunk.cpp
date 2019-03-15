//
// Created by Brendan Berg on 14.03.19.
//

#include <iostream>

#include "BlockChunk.hpp"


BlockChunk::BlockChunk (glm::ivec3 chunkPos, Graphics& graphics)
    : m_ChunkPos(chunkPos), m_BlockChunckRenderable(graphics)
{
    m_Blocks.reserve(256);

    for (unsigned int z = 0; z < CHUNK_SIZE; ++z)
    {
        for (unsigned int x = 0; x < CHUNK_SIZE; ++x)
        {
            m_Blocks.emplace_back(64 + x + z);
        }
    }
}


BlockColumn& BlockChunk::GetColumn (glm::ivec3 internalPos)
{
    return m_Blocks.at(GetColumnIndex(internalPos));
}


unsigned int&
BlockChunk::GetBlock (glm::ivec3 internalPos)
{
    return GetColumn(internalPos).GetBlock(
        static_cast<unsigned int>(internalPos.y));
}


void BlockChunk::GenerateMesh ()
{
    for (unsigned int y = 0; y < MAX_HEIGHT; ++y)
    {
        for (unsigned int z = 0; z < CHUNK_SIZE; ++z)
        {
            for (unsigned int x = 0; x < CHUNK_SIZE; ++x)
            {
                auto internalPos = glm::ivec3(x, y, z);
                unsigned int block = GetBlock(internalPos);
                if (block != 0)
                {
                    std::vector<BlockSide> neighbors;
                    GetVisibleSides(internalPos, neighbors);
                    for (auto& side : neighbors)
                    {
                        m_BlockChunckRenderable.AddFace(internalPos, side, block);
                    }
                }
            }
        }
    }

    m_BlockChunckRenderable.UpdateData();
}


BlockChunkRenderable& BlockChunk::GetRenderable ()
{
    return m_BlockChunckRenderable;
}


unsigned int BlockChunk::GetColumnIndex (glm::ivec3 internalPos)
{
    return static_cast<unsigned int>(
        internalPos.x + CHUNK_SIZE * internalPos.z);
}


void BlockChunk::GetVisibleSides (glm::ivec3 internalPos,
                                  std::vector<BlockSide>& output)
{
    for (unsigned int side = 0; side < 6; ++side)
    {
        auto blockSide = static_cast<BlockSide>(side);

        if (GetNeighborOnSide(internalPos, blockSide) == 0)
        {
            output.push_back(blockSide);
        }
    }
}


unsigned int
BlockChunk::GetNeighborOnSide (glm::ivec3 internalPos, BlockSide side)
{
    switch (side)
    {
        case BlockSide::Top:
            internalPos += glm::ivec3(0, 1, 0);
            break;
        case BlockSide::North:
            internalPos += glm::ivec3(1, 0, 0);
            break;
        case BlockSide::West:
            internalPos += glm::ivec3(0, 0, -1);
            break;
        case BlockSide::South:
            internalPos += glm::ivec3(-1, 1, 0);
            break;
        case BlockSide::East:
            internalPos += glm::ivec3(0, 1, 1);
            break;
        case BlockSide::Bottom:
            internalPos += glm::ivec3(0, -1, 0);
            break;
    }

    if (!(0 <= internalPos.x && internalPos.x < CHUNK_SIZE
        && 0 <= internalPos.z && internalPos.z < CHUNK_SIZE
        && 0 <= internalPos.y && internalPos.y < MAX_HEIGHT))
    {
        return 0;
    }

    return GetBlock(internalPos);
}

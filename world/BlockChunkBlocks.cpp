//
// Created by Brendan Berg on 17.03.19.
//

#include "BlockChunkBlocks.hpp"


BlockChunkBlocks::BlockChunkBlocks ()
{
    m_Blocks.reserve(CHUNK_SIZE * CHUNK_SIZE);

    for (unsigned int z = 0; z < CHUNK_SIZE; ++z)
    {
        for (unsigned int x = 0; x < CHUNK_SIZE; ++x)
        {
            m_Blocks.emplace_back(64 + x + z);
        }
    }
}


unsigned int& BlockChunkBlocks::GetBlock (const glm::ivec3& internalPos)
{
    return GetColumn(internalPos).GetBlock(
        static_cast<unsigned int>(internalPos.y));
}


void BlockChunkBlocks::GetVisibleSides (const glm::ivec3& internalPos,
                                        std::vector<BlockSide>& output)
{
    for (unsigned int side = 0; side < 6; ++side)
    {
        auto blockSide = static_cast<BlockSide>(side);

        // TODO: Check if not opaque
        if (GetNeighborOnSide(internalPos, blockSide) == 0)
        {
            output.push_back(blockSide);
        }
    }
}


unsigned int BlockChunkBlocks::GetColumnIndex (const glm::ivec3& internalPos)
{
    return static_cast<unsigned int>(
        internalPos.x + CHUNK_SIZE * internalPos.z);
}


BlockColumn& BlockChunkBlocks::GetColumn (const glm::ivec3& internalPos)
{
    return m_Blocks.at(GetColumnIndex(internalPos));
}


unsigned int
BlockChunkBlocks::GetNeighborOnSide (const glm::ivec3& internalPos,
                                     BlockSide side)
{
    auto neighborPos = BlockUtility::GetNeighbor(internalPos, side);

    if (!BlockUtility::InsideChunk(neighborPos))
    {
        return 0;
    }

    return GetBlock(neighborPos);
}

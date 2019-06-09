//
// Created by Brendan Berg on 17.03.19.
//

#include "BlockChunkBlocks.hpp"


BlockChunkBlocks::BlockChunkBlocks (std::unique_ptr<ChunkLoader>& chunkLoader,
                                    const BlockTypeContainer&
                                    blockTypeContainer,
                                    glm::ivec3 chunkPos, bool generate)
    : m_ChunkLoader(std::move(chunkLoader)),
    m_BlockTypeContainer(blockTypeContainer), m_ChunkPos(chunkPos)
{
    m_Blocks.reserve(CHUNK_SIZE * CHUNK_SIZE);

    auto data = new char [CHUNK_HEIGHT];

    if (generate)
    {
        for (unsigned int z = 0; z < CHUNK_SIZE; ++z)
        {
            for (unsigned int x = 0; x < CHUNK_SIZE; ++x)
            {
                auto height = WorldGenerator::GetColumnHeight(chunkPos.x,
                                                              chunkPos.z,
                                                              x, z);
                m_Blocks.emplace_back(height);
                memcpy(data, m_Blocks.back().GetData(), CHUNK_HEIGHT);

                auto index = GetColumnIndex(glm::ivec3(x, 0,z));
                m_ChunkLoader->AppendColumn(index, data);
            }
        }
    }
    else
    {
        for (unsigned int z = 0; z < CHUNK_SIZE; ++z)
        {
            for (unsigned int x = 0; x < CHUNK_SIZE; ++x)
            {
                auto index = GetColumnIndex(glm::ivec3(x, 0,z));
                m_ChunkLoader->GetColumn(index, data);
                m_Blocks.emplace_back(data);
            }
        }
    }

    delete[] data;
}


char& BlockChunkBlocks::GetBlock (const glm::ivec3& internalPos)
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
        auto blockType = GetNeighborOnSide(internalPos, blockSide);

        if (!m_BlockTypeContainer.GetBlock(blockType).IsOpaque())
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


char
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

//
// Created by Brendan Berg on 17.03.19.
//

#include "BlockUtility.hpp"


glm::ivec3 BlockUtility::GetNeighbor (glm::ivec3 internalPos, BlockSide side)
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

    return internalPos;
}


bool BlockUtility::InsideChunk (glm::ivec3 internalPos)
{
    return (0 <= internalPos.x) && (internalPos.x < CHUNK_SIZE)
           && (0 <= internalPos.z) && (internalPos.z < CHUNK_SIZE)
           && (0 <= internalPos.y) && (internalPos.y < CHUNK_HEIGHT);
}


glm::vec3 BlockUtility::GetChunkCenter (glm::ivec3 chunkPos)
{
    auto chunkSize = static_cast<float>(CHUNK_SIZE);
    return glm::vec3(chunkPos) * glm::vec3(chunkSize, 0.0f, chunkSize) +
           glm::vec3(chunkSize / 2.0f, 0.0f, chunkSize / 2.0f);
}


glm::vec3 BlockUtility::GetChunkCenter (int x, int z)
{
    return GetChunkCenter(glm::ivec3(x, 0, z));
}


glm::ivec3 BlockUtility::PlayerPositionToChunk (glm::vec3 playerPosition)
{
    auto chunkSize = static_cast<float>(CHUNK_SIZE);
    auto result = static_cast<glm::ivec3>(
        playerPosition / glm::vec3(chunkSize, 1.0f, chunkSize));
    result.y = 0;
    return result;
}


bool BlockUtility::Equal (glm::ivec3 a, glm::ivec3 b)
{
    return (a.x == b.x) && (a.y == b.y) && (a.z == b.z);
}

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

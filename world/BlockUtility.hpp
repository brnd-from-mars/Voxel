//
// Created by Brendan Berg on 17.03.19.
//

#ifndef VOXEL_BLOCKUTILITY_HPP
#define VOXEL_BLOCKUTILITY_HPP

#include <glm/glm.hpp>

#define CHUNK_HEIGHT 128
#define CHUNK_SIZE 16


enum class BlockSide
{
    Top = 0,
    North = 1,
    East = 2,
    South = 3,
    West = 4,
    Bottom = 5
};


class BlockUtility
{
public:

    static glm::ivec3 GetNeighbor (glm::ivec3 internalPos, BlockSide side);

    static bool InsideChunk (glm::ivec3 internalPos);


};


#endif //VOXEL_BLOCKUTILITY_HPP

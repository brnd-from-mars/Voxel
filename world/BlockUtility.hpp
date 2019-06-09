//
// Created by Brendan Berg on 17.03.19.
//

#ifndef VOXEL_BLOCKUTILITY_HPP
#define VOXEL_BLOCKUTILITY_HPP

#include <glm/glm.hpp>

#define CHUNK_HEIGHT 128
#define CHUNK_SIZE 16
#define CHUNK_LOAD_DISTANCE 80.0f


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

    static glm::vec3 GetChunkCenter (glm::ivec3 chunkPos);

    static glm::vec3 GetChunkCenter (int x, int z);

    static glm::ivec3 PlayerPositionToChunk (glm::vec3 playerPosition);

    static bool Equal (glm::ivec3 a, glm::ivec3 b);


};


#endif //VOXEL_BLOCKUTILITY_HPP

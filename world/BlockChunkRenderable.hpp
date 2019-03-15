//
// Created by Brendan Berg on 14.03.19.
//

#ifndef VOXEL_BLOCKCHUNKRENDERABLE_HPP
#define VOXEL_BLOCKCHUNKRENDERABLE_HPP

#include <vector>

#include <glm/glm.hpp>

#include "../graphics/Renderable.hpp"


// TODO: outsource
enum class BlockSide
{
    Top = 0,
    North = 1,
    East = 2,
    South = 3,
    West = 4,
    Bottom = 5
};


class BlockChunkRenderable : public Renderable
{
public:

    explicit BlockChunkRenderable (Graphics& graphics);

    void AddFace (glm::ivec3 internalPos,
                  BlockSide side,
                  unsigned int blockType);

    unsigned int AddVertex (glm::vec4 vertexPosition,
                            glm::vec4 normalVector,
                            unsigned int blockType);


};


#endif //VOXEL_BLOCKCHUNKRENDERABLE_HPP

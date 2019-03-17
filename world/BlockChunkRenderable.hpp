//
// Created by Brendan Berg on 14.03.19.
//

#ifndef VOXEL_BLOCKCHUNKRENDERABLE_HPP
#define VOXEL_BLOCKCHUNKRENDERABLE_HPP

#include <vector>

#include <glm/glm.hpp>

#include "../graphics/Renderable.hpp"

#include "BlockUtility.hpp"


class BlockChunkRenderable : public Renderable
{
public:

    BlockChunkRenderable (Graphics& graphics,
                          Shader& shader,
                          const glm::vec3& chunkPos);

    BlockChunkRenderable (Graphics& graphics,
                          Shader& shader);

    void SetChunkPos (const glm::vec3& chunkPos);

    void AddFace (const glm::vec4& blockPosition,
                  BlockSide side,
                  unsigned int blockType);


private:

    unsigned int AddVertex (glm::vec4 vertexPosition,
                            glm::vec4 normalVector,
                            unsigned int vertex);


};


#endif //VOXEL_BLOCKCHUNKRENDERABLE_HPP

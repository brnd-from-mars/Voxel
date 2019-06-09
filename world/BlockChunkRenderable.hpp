//
// Created by Brendan Berg on 14.03.19.
//

#ifndef VOXEL_BLOCKCHUNKRENDERABLE_HPP
#define VOXEL_BLOCKCHUNKRENDERABLE_HPP

#include <vector>
#include <memory>

#include <glm/glm.hpp>

#include "../graphics/Renderable.hpp"

#include "BlockUtility.hpp"
#include "BlockChunkBlocks.hpp"
#include "BlockTypeContainer.hpp"


class BlockChunkRenderable : public Renderable
{
public:

    BlockChunkRenderable (std::shared_ptr<Graphics>& graphics,
                          Shader& shader,
                          const BlockTypeContainer& blockTypeContainer,
                          const glm::vec3& chunkPos);

    BlockChunkRenderable (std::shared_ptr<Graphics>& graphics,
                          Shader& shader,
                          const BlockTypeContainer& blockTypeContainer);

    void SetChunkPos (const glm::vec3& chunkPos);

    void GenerateMesh (std::unique_ptr<BlockChunkBlocks>& blocks);


private:

    void AddFace (const glm::vec4& blockPosition,
                  BlockSide side,
                  unsigned int blockType);

    unsigned int AddVertex (glm::vec4 vertexPosition,
                            glm::vec4 normalVector,
                            BlockSide side,
                            unsigned int blockType,
                            unsigned int vertex);

    const BlockTypeContainer& m_BlockTypeContainer;


};


#endif //VOXEL_BLOCKCHUNKRENDERABLE_HPP

//
// Created by Brendan Berg on 14.03.19.
//

#ifndef VOXEL_BLOCKCHUNK_HPP
#define VOXEL_BLOCKCHUNK_HPP

#include <vector>

#include <glm/glm.hpp>

#include "BlockChunkBlocks.hpp"
#include "BlockChunkRenderable.hpp"


class BlockChunk
{
public:

    BlockChunk (const glm::ivec3& chunkPos,
                std::unique_ptr<BlockChunkBlocks>&& blocks,
                std::unique_ptr<BlockChunkRenderable>&& renderable);

    std::unique_ptr<BlockChunkRenderable>& GetRenderable ();


private:

    void GenerateMesh ();

    glm::ivec3 m_ChunkPos;

    std::unique_ptr<BlockChunkBlocks> m_Blocks;

    std::unique_ptr<BlockChunkRenderable> m_Renderable;


};


#endif //VOXEL_BLOCKCHUNK_HPP

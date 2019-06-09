//
// Created by Brendan Berg on 2019-05-21.
//

#include <iostream>

#include "World.hpp"


World::World (std::shared_ptr<Graphics>& graphics, Shader& shader,
              const std::string& blockConfigFilePath)
    : m_Graphics(graphics), m_Shader(shader),
    m_WorldLoader("world"), m_BlockTypeContainer(blockConfigFilePath)
{ }


void World::GenerateChunk (int x, int z)
{
    auto generate = !m_WorldLoader.CheckChunk(x, z);
    auto chunkLoader = m_WorldLoader.GetChunkLoader(x, z);

    m_BlockChunkContainer.emplace_back(
        glm::ivec3(x, 0, z),
        std::make_unique<BlockChunkBlocks>(chunkLoader, m_BlockTypeContainer,
                                           glm::ivec3(x, 0, z), generate),
        std::make_unique<BlockChunkRenderable>(m_Graphics, m_Shader,
                                               m_BlockTypeContainer));
}


// TODO: use center coordinates
void World::Update (glm::vec3 playerPosition)
{
    auto playerPosFlat = playerPosition;
    playerPosFlat.y = 0.0f;

    m_BlockChunkContainer.remove_if(
        [playerPosFlat, this](const BlockChunk& chunk)
        {
            auto chunkPos = BlockUtility::GetChunkCenter(chunk.GetPosition());
            auto dist = glm::distance(playerPosFlat, chunkPos);
            auto remove = (dist > CHUNK_LOAD_DISTANCE);
            if (remove)
            {
                this->m_LoadedChunks.erase(
                    std::make_pair(chunk.GetPosition().x,
                                   chunk.GetPosition().z));
            }
            return remove;
        });

    auto currentChunk = BlockUtility::PlayerPositionToChunk(playerPosFlat);

    for (int x = -4; x < 5; ++x)
    {
        for (int z = -4; z < 4; ++z)
        {
            auto chunkI = glm::ivec3(x, 0, z) + currentChunk;
            auto chunkPos = BlockUtility::GetChunkCenter(chunkI);
            auto dist = glm::distance(playerPosFlat, chunkPos);
            if (dist < CHUNK_LOAD_DISTANCE)
            {
                auto p = std::make_pair(chunkI.x, chunkI.z);
                if (m_LoadedChunks.find(p) == m_LoadedChunks.end())
                {
                    GenerateChunk(chunkI.x, chunkI.z);
                    m_LoadedChunks.emplace(p);
                }
            }
        }
    }
}


void World::Draw ()
{
    for (auto& blockChunk : m_BlockChunkContainer)
    {
        blockChunk.GetRenderable()->Draw();
    }
}

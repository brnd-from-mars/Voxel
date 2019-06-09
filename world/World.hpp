//
// Created by Brendan Berg on 2019-05-21.
//

#ifndef VOXEL_WORLD_HPP
#define VOXEL_WORLD_HPP

#include <list>
#include <set>
#include <memory>

#include <glm/glm.hpp>

#include "../graphics/Graphics.hpp"
#include "../graphics/Shader.hpp"

#include "BlockTypeContainer.hpp"
#include "BlockChunk.hpp"
#include "WorldLoader.hpp"


class World
{
public:

    World (std::shared_ptr<Graphics>& graphics, Shader& shader,
           const std::string& blockConfigFilePath);

    void GenerateChunk (int x, int z);

    void Update (glm::vec3 playerPosition);

    void Draw ();


private:

    std::shared_ptr<Graphics> m_Graphics;

    Shader& m_Shader;

    WorldLoader m_WorldLoader;

    BlockTypeContainer m_BlockTypeContainer;

    std::list<BlockChunk> m_BlockChunkContainer;

    std::set<std::pair<int, int>> m_LoadedChunks;


};


#endif //VOXEL_WORLD_HPP

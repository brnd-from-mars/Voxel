//
// Created by Brendan Berg on 2019-06-05.
//

#ifndef VOXEL_WORLDLOADER_HPP
#define VOXEL_WORLDLOADER_HPP

#include <string>
#include <memory>

#include "ChunkLoader.hpp"


class WorldLoader
{
public:

    explicit WorldLoader (std::string worldName);

    bool CheckChunk (int x, int z);

    std::unique_ptr<ChunkLoader> GetChunkLoader (int x, int z);


private:

    std::string m_WorldName;

    std::string m_WorldPath;

    void CheckDirectory (const std::string& directoryPath);

    bool CheckFile (const std::string& fileName);

    static std::string SerializeInteger (int integer);


};


#endif //VOXEL_WORLDLOADER_HPP

//
// Created by Brendan Berg on 2019-06-05.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fstream>

#include "WorldLoader.hpp"


WorldLoader::WorldLoader (std::string worldName)
    : m_WorldName(std::move(worldName)), m_WorldPath("saves/")
{
    CheckDirectory(m_WorldPath);
    m_WorldPath += m_WorldName + "/";
    CheckDirectory(m_WorldPath);
}


bool WorldLoader::CheckChunk (int x, int z)
{
    std::string fileName = "chunk_";
    fileName += SerializeInteger(x);
    fileName += "_";
    fileName += SerializeInteger(z);
    fileName += ".dat";

    return CheckFile(fileName);
}


// TODO: cleanup
std::unique_ptr<ChunkLoader> WorldLoader::GetChunkLoader (int x, int z)
{
    std::string fileName = "chunk_";
    fileName += SerializeInteger(x);
    fileName += "_";
    fileName += SerializeInteger(z);
    fileName += ".dat";
    auto filePath = m_WorldPath + fileName;

    auto ptr = std::make_unique<ChunkLoader>(filePath);
    return ptr;
}


void WorldLoader::CheckDirectory (const std::string& directoryPath)
{
    struct stat directoryStat {};
    auto error = stat(directoryPath.c_str(), &directoryStat);

    if (error != 0)
    {
        mode_t mode = 0777;
        mkdir(m_WorldPath.c_str(), mode);
    }
}


bool WorldLoader::CheckFile (const std::string& fileName)
{
    auto filePath = m_WorldPath + fileName;

    struct stat fileStat {};
    auto error = stat(filePath.c_str(), &fileStat);

    if (error != 0)
    {
        std::ofstream file(filePath, std::ios::binary);
        file.close();
        return false;
    }

    return true;
}


std::string WorldLoader::SerializeInteger (int integer)
{
    std::string result;

    if (integer < 0)
    {
        result += "n";
    }
    result += std::to_string(abs(integer));

    return result;
}

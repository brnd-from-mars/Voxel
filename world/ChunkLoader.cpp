//
// Created by Brendan Berg on 2019-06-06.
//

#include "BlockUtility.hpp"

#include "ChunkLoader.hpp"


ChunkLoader::ChunkLoader (std::string filePath)
    : m_FilePath(std::move(filePath))
{
    m_File.open(m_FilePath, std::ios::binary | std::ios::out | std::ios::in);
}


ChunkLoader::~ChunkLoader ()
{
    m_File.close();
}


void ChunkLoader::GetColumn (unsigned int columnIndex, char* data)
{
    m_File.seekg(columnIndex * CHUNK_HEIGHT);
    m_File.read(data, CHUNK_HEIGHT);
}


void ChunkLoader::AppendColumn (unsigned int columnIndex, char* data)
{
    m_File.seekp(columnIndex * CHUNK_HEIGHT);
    m_File.write(data, CHUNK_HEIGHT);
}

//
// Created by Brendan Berg on 2019-06-06.
//

#ifndef VOXEL_CHUNKLOADER_HPP
#define VOXEL_CHUNKLOADER_HPP

#include <fstream>


class ChunkLoader
{
public:

    explicit ChunkLoader (std::string filePath);

    ~ChunkLoader ();

    void GetColumn (unsigned int columnIndex, char* data);

    void AppendColumn (unsigned int columnIndex, char* data);


private:

    std::string m_FilePath;

    std::fstream m_File;


};


#endif //VOXEL_CHUNKLOADER_HPP

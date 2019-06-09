//
// Created by Brendan Berg on 14.03.19.
//

#ifndef VOXEL_BLOCKCOLUMN_HPP
#define VOXEL_BLOCKCOLUMN_HPP

#include <vector>

#include "BlockUtility.hpp"


class BlockColumn
{
public:

    explicit BlockColumn (char* data);

    explicit BlockColumn (unsigned int height);

    char* GetData ();

    char& GetBlock (unsigned int y);

    void SetBlock (unsigned int y, char id);


private:

    std::vector<char> m_Blocks;


};


#endif //VOXEL_BLOCKCOLUMN_HPP

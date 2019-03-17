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

    explicit BlockColumn (unsigned int height);

    unsigned int& GetBlock (unsigned int y);


private:

    std::vector<unsigned int> m_Blocks;

    unsigned int m_Height;


};


#endif //VOXEL_BLOCKCOLUMN_HPP

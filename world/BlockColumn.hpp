//
// Created by Brendan Berg on 14.03.19.
//

#ifndef VOXEL_BLOCKCOLUMN_HPP
#define VOXEL_BLOCKCOLUMN_HPP

#define MAX_HEIGHT 128
#define BLOCK_AIR 0
#define BLOCK_STONE 1

#include <vector>


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

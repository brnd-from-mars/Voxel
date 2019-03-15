//
// Created by Brendan Berg on 14.03.19.
//

#ifndef VOXEL_INDEXBUFFEROBJECT_HPP
#define VOXEL_INDEXBUFFEROBJECT_HPP

#include <vector>

#include "Graphics.hpp"


class IndexBufferObject
{
public:

    IndexBufferObject ();

    IndexBufferObject (const unsigned int* data, unsigned int count);

    explicit IndexBufferObject (const std::vector<unsigned int>& data);

    ~IndexBufferObject ();

    void SetData (const unsigned int* data, unsigned int count);

    void SetData (const std::vector<unsigned int>& data);

    void Bind ();

    void Unbind ();


private:

    unsigned int m_IBOAddress;


};


#endif //VOXEL_INDEXBUFFEROBJECT_HPP

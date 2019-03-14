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

    explicit IndexBufferObject (bool bind);

    IndexBufferObject (bool bind, const unsigned int* data, unsigned int count);

    IndexBufferObject (bool bind, const std::vector<unsigned int>& data);

    ~IndexBufferObject ();

    void SetData (const unsigned int* data, unsigned int count);

    void SetData (const std::vector<unsigned int>& data);

    void SetBoundState (bool bind);

    void Bind ();

    void Unbind ();


private:

    unsigned int m_IBOAddress;

    bool m_Bound;

    unsigned int m_Count;


};


#endif //VOXEL_INDEXBUFFEROBJECT_HPP

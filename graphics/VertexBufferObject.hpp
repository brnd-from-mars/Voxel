//
// Created by Brendan Berg on 14.03.19.
//

#ifndef VOXEL_VERTEXBUFFEROBJECT_HPP
#define VOXEL_VERTEXBUFFEROBJECT_HPP

#include "Graphics.hpp"


class VertexBufferObject
{
public:

    explicit VertexBufferObject (bool bind);

    VertexBufferObject (bool bind, const void* data, unsigned int size);

    ~VertexBufferObject ();

    void Bind();

    void Unbind();


private:

    unsigned int m_VBOAddress;

    bool m_Bound;


};


#endif //VOXEL_VERTEXBUFFEROBJECT_HPP

//
// Created by Brendan Berg on 14.03.19.
//

#ifndef VOXEL_VERTEXBUFFEROBJECT_HPP
#define VOXEL_VERTEXBUFFEROBJECT_HPP

#include <vector>

#include "Graphics.hpp"


class VertexBufferObject
{
public:

    VertexBufferObject ();

    VertexBufferObject (const void* data, unsigned int size);

    explicit VertexBufferObject (const std::vector<unsigned char>& data);

    ~VertexBufferObject ();

    void SetData (const void* data, unsigned int size);

    void SetData (const std::vector<unsigned char>& data);

    void Bind ();

    void Unbind ();


private:

    unsigned int m_VBOAddress;


};


#endif //VOXEL_VERTEXBUFFEROBJECT_HPP

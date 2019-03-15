//
// Created by Brendan Berg on 14.03.19.
//

#ifndef VOXEL_VERTEXARRAYOBJECT_HPP
#define VOXEL_VERTEXARRAYOBJECT_HPP

#include "Graphics.hpp"
#include "VertexBufferObject.hpp"
#include "VertexBufferLayout.hpp"


class VertexArrayObject
{
public:

    VertexArrayObject ();

    ~VertexArrayObject ();

    void AddBuffer (VertexBufferObject& vbo, VertexBufferLayout& vbl);

    void Bind ();

    void Unbind ();


private:

    unsigned int m_VAOAddress;


};


#endif //VOXEL_VERTEXARRAYOBJECT_HPP

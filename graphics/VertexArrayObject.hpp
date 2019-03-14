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

    explicit VertexArrayObject (bool bind);

    ~VertexArrayObject ();

    void AddBuffer (VertexBufferObject& vbo, VertexBufferLayout& vbl);

    void SetBoundState (bool bind);

    void Bind ();

    void Unbind ();


private:

    unsigned int m_VAOAddress;

    bool m_Bound;

};


#endif //VOXEL_VERTEXARRAYOBJECT_HPP

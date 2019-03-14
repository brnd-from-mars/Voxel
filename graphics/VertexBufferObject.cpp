//
// Created by Brendan Berg on 14.03.19.
//

#include "VertexBufferObject.hpp"


VertexBufferObject::VertexBufferObject (bool bind)
    : m_VBOAddress(0), m_Bound(bind)
{
    GLCall(glGenBuffers(1, &m_VBOAddress));
    if (bind)
    {
        Bind();
    }
}


VertexBufferObject::VertexBufferObject (bool bind, const void* data,
                                        unsigned int size)
    : VertexBufferObject(true)
{
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));

    if (!bind)
    {
        Unbind();
    }
}


VertexBufferObject::~VertexBufferObject ()
{
    GLCall(glDeleteBuffers(1, &m_VBOAddress));
}


void VertexBufferObject::Bind ()
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_VBOAddress));
}


void VertexBufferObject::Unbind ()
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

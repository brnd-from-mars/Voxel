//
// Created by Brendan Berg on 14.03.19.
//

#include "VertexBufferObject.hpp"


VertexBufferObject::VertexBufferObject ()
    : m_VBOAddress(0)
{
    GLCall(glGenBuffers(1, &m_VBOAddress));
    Bind();
}


VertexBufferObject::VertexBufferObject (const void* data, unsigned int size)
    : VertexBufferObject()
{
    SetData(data, size);
}


VertexBufferObject::VertexBufferObject (const std::vector<unsigned char>& data)
    : VertexBufferObject()
{
    SetData(data);
}


VertexBufferObject::~VertexBufferObject ()
{
    GLCall(glDeleteBuffers(1, &m_VBOAddress));
}


void VertexBufferObject::SetData (const void* data, unsigned int size)
{
    Bind();
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}


void VertexBufferObject::SetData (const std::vector<unsigned char>& data)
{
    SetData(static_cast<const void*>(data.data()),
            static_cast<unsigned int>(data.size()));
}


void VertexBufferObject::Bind ()
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_VBOAddress));
}


void VertexBufferObject::Unbind ()
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}



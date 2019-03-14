//
// Created by Brendan Berg on 14.03.19.
//

#include "VertexBufferObject.hpp"


VertexBufferObject::VertexBufferObject (bool bind)
    : m_VBOAddress(0), m_Bound(bind)
{
    GLCall(glGenBuffers(1, &m_VBOAddress));
    SetBoundState(bind);
}


VertexBufferObject::VertexBufferObject (bool bind, const void* data,
                                        unsigned int size)
    : VertexBufferObject(true)
{
    SetData(data, size);
    SetBoundState(bind);
}


VertexBufferObject::VertexBufferObject (bool bind,
                                        const std::vector<unsigned char>& data)
    : VertexBufferObject(true)
{
    SetData(data);
    SetBoundState(bind);
}


VertexBufferObject::~VertexBufferObject ()
{
    GLCall(glDeleteBuffers(1, &m_VBOAddress));
}


void VertexBufferObject::SetData (const void* data, unsigned int size)
{
    auto state = m_Bound;
    Bind();
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
    SetBoundState(state);
}


void VertexBufferObject::SetData (const std::vector<unsigned char>& data)
{
    SetData(static_cast<const void*>(data.data()),
            static_cast<unsigned int>(data.size()));
}


void VertexBufferObject::SetBoundState (bool bind)
{
    if (bind)
    {
        Bind();
    }
    else
    {
        Unbind();
    }
}


void VertexBufferObject::Bind ()
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_VBOAddress));
    m_Bound = true;
}


void VertexBufferObject::Unbind ()
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    m_Bound = false;
}



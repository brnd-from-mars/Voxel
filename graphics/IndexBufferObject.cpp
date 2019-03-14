//
// Created by Brendan Berg on 14.03.19.
//

#include "IndexBufferObject.hpp"


IndexBufferObject::IndexBufferObject (bool bind)
    : m_IBOAddress(0), m_Bound(bind), m_Count(0)
{
    GLCall(glGenBuffers(1, &m_IBOAddress));
    SetBoundState(bind);
}


IndexBufferObject::IndexBufferObject (bool bind, const unsigned int* data,
                                      unsigned int count)
    : IndexBufferObject(true)
{
    SetData(data, count);
    SetBoundState(bind);
}


IndexBufferObject::IndexBufferObject (bool bind,
                                      const std::vector<unsigned int>& data)
{
    SetData(data);
    SetBoundState(bind);
}


IndexBufferObject::~IndexBufferObject ()
{
    GLCall(glDeleteBuffers(1, &m_IBOAddress));
}


void IndexBufferObject::SetData (const unsigned int* data, unsigned int count)
{
    auto state = m_Bound;
    Bind();
    m_Count = count;
    auto size = m_Count * sizeof(unsigned int);
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
    SetBoundState(state);
}


void IndexBufferObject::SetData (const std::vector<unsigned int>& data)
{
    SetData(data.data(), static_cast<unsigned int>(data.size()));
}


void IndexBufferObject::SetBoundState (bool bind)
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


void IndexBufferObject::Bind ()
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBOAddress));
    m_Bound = true;
}


void IndexBufferObject::Unbind ()
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    m_Bound = false;
}

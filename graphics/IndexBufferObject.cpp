//
// Created by Brendan Berg on 14.03.19.
//

#include "IndexBufferObject.hpp"


IndexBufferObject::IndexBufferObject ()
    : m_IBOAddress(0), m_Count(0)
{
    GLCall(glGenBuffers(1, &m_IBOAddress));
    Bind();
}


IndexBufferObject::IndexBufferObject (const unsigned int* data,
                                      unsigned int count)
    : IndexBufferObject()
{
    SetData(data, count);
}


IndexBufferObject::IndexBufferObject (const std::vector<unsigned int>& data)
    : IndexBufferObject()
{
    SetData(data);
}


IndexBufferObject::~IndexBufferObject ()
{
    GLCall(glDeleteBuffers(1, &m_IBOAddress));
}


void IndexBufferObject::SetData (const unsigned int* data, unsigned int count)
{
    Bind();
    auto size = count * sizeof(unsigned int);
    m_Count = count;
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}


void IndexBufferObject::SetData (const std::vector<unsigned int>& data)
{
    SetData(data.data(), static_cast<unsigned int>(data.size()));
}


void IndexBufferObject::Bind ()
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBOAddress));
}


void IndexBufferObject::Unbind ()
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}


unsigned int IndexBufferObject::GetCount ()
{
    return m_Count;
}

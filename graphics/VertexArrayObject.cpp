//
// Created by Brendan Berg on 14.03.19.
//

#include "VertexArrayObject.hpp"


VertexArrayObject::VertexArrayObject (bool bind)
    : m_VAOAddress(0), m_Bound(bind)
{
    GLCall(glGenVertexArrays(1, &m_VAOAddress));
    SetBoundState(bind);
}


VertexArrayObject::~VertexArrayObject ()
{
    GLCall(glDeleteVertexArrays(1, &m_VAOAddress));
}


void VertexArrayObject::AddBuffer (VertexBufferObject& vbo,
                                   VertexBufferLayout& vbl)
{
    auto state = m_Bound;
    Bind();
    vbo.Bind();
    const auto& elements = vbl.GetElements();
    unsigned int offset = 0;
    auto stride = vbl.GetStride();
    for (unsigned int i = 0; i < elements.size(); ++i)
    {
        const auto& element = elements[i];
        GLCall(glEnableVertexAttribArray(i));
        GLCall(glVertexAttribPointer(i,
            element.count, element.type, element.normalized,
            stride, reinterpret_cast<const void*>(offset)));
        offset += VertexBufferElement::GetSize(element.type) * element.count;
    }
    SetBoundState(state);
}


void VertexArrayObject::SetBoundState (bool bind)
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


void VertexArrayObject::Bind ()
{
    GLCall(glBindVertexArray(m_VAOAddress));
    m_Bound = true;
}


void VertexArrayObject::Unbind ()
{
    GLCall(glBindVertexArray(0));
    m_Bound = false;
}



//
// Created by Brendan Berg on 14.03.19.
//

#include "VertexBufferLayout.hpp"


VertexBufferLayout::VertexBufferLayout ()
    : m_Stride(0)
{ }


template <>
void VertexBufferLayout::Push<float> (unsigned int count)
{
    m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
    m_Stride += VertexBufferElement::GetSize(GL_FLOAT) * count;
}


template <>
void VertexBufferLayout::Push<unsigned int> (unsigned int count)
{
    m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
    m_Stride += VertexBufferElement::GetSize(GL_UNSIGNED_INT) * count;
}


template <>
void VertexBufferLayout::Push<unsigned char> (unsigned int count)
{
    m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_FALSE });
    m_Stride += VertexBufferElement::GetSize(GL_UNSIGNED_BYTE) * count;
}


const std::vector<VertexBufferElement>& VertexBufferLayout::GetElements ()
{
    return m_Elements;
}


unsigned int VertexBufferLayout::GetStride ()
{
    return m_Stride;
}
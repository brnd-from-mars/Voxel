//
// Created by Brendan Berg on 14.03.19.
//

#ifndef VOXEL_VERTEXBUFFERLAYOUT_HPP
#define VOXEL_VERTEXBUFFERLAYOUT_HPP

#include <vector>

#include "Graphics.hpp"


struct VertexBufferElement
{
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int GetSize (unsigned int type)
    {
        switch (type)
        {
            case GL_FLOAT: return sizeof(float);
            case GL_UNSIGNED_INT: return sizeof(unsigned int);
            case GL_UNSIGNED_BYTE: return sizeof(unsigned char);
            default: return 0;
        }
    }
};


class VertexBufferLayout
{
public:

    VertexBufferLayout ();

    template <typename T>
    void Push (unsigned int count);

    const std::vector<VertexBufferElement>& GetElements ();

    unsigned int GetStride ();


private:

    std::vector<VertexBufferElement> m_Elements;

    unsigned int m_Stride;


};


template <>
void VertexBufferLayout::Push<float> (unsigned int count);

template <>
void VertexBufferLayout::Push<unsigned int> (unsigned int count);

template <>
void VertexBufferLayout::Push<unsigned char> (unsigned int count);


#endif //VOXEL_VERTEXBUFFERLAYOUT_HPP

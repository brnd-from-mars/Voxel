//
// Created by Brendan Berg on 15.03.19.
//

#ifndef VOXEL_RENDERABLE_HPP
#define VOXEL_RENDERABLE_HPP

#include <iostream>

#include "Graphics.hpp"
#include "IndexBufferObject.hpp"
#include "VertexBufferObject.hpp"
#include "VertexArrayObject.hpp"
#include "VertexBufferLayout.hpp"
#include "Shader.hpp"


template <typename T>
union VertexConstructor
{
    T attr;
    unsigned char bytes[sizeof(T)];

    explicit VertexConstructor (T t)
    {
        attr = t;
    }
};


class Renderable
{
public:

    explicit Renderable (Graphics& graphics);

    void UpdateData ();

    void Draw ();

    template <typename T>
    unsigned int AddVertex (T vertexStruct)
    {
        auto vertex = m_NextVertex;
        ++m_NextVertex;

        VertexConstructor vc(vertexStruct);

        for (unsigned char byte : vc.bytes)
        {
            m_Vertices.push_back(byte);
        }

        return vertex;
    }


protected:

    Graphics& m_Graphics;

    VertexArrayObject m_VAO;

    VertexBufferObject m_VBO;

    IndexBufferObject m_IBO;

    std::vector<unsigned char> m_Vertices;

    std::vector<unsigned int> m_Indices;

    unsigned int m_NextVertex;


};


#endif //VOXEL_RENDERABLE_HPP

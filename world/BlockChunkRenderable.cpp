//
// Created by Brendan Berg on 14.03.19.
//

#include <algorithm>
#include <iterator>

#include "BlockChunkRenderable.hpp"


union BlockVertex
{
    struct
    {
        glm::vec4 position;
        glm::vec4 normal;
        glm::vec4 color;
    };

    unsigned char bytes[3 * sizeof(glm::vec4)];

    static int faceOrientation[6][4];

    static glm::vec4 faceNormals[6];

    static glm::vec4 vertexOffsets[8];

    static unsigned int faceIndices[2][3];
};


int BlockVertex::faceOrientation[6][4] = {
    { 4, 5, 6, 7 },
    { 1, 2, 6, 5 },
    { 2, 3, 7, 6 },
    { 3, 0, 4, 7 },
    { 0, 1, 5, 4 },
    { 3, 2, 1, 0 }
};


glm::vec4 BlockVertex::faceNormals[6] = {
    {  0.0f,  1.0f,  0.0f, 0.0f },
    {  1.0f,  0.0f,  0.0f, 0.0f },
    {  0.0f,  0.0f,  1.0f, 0.0f },
    { -1.0f,  0.0f,  0.0f, 0.0f },
    {  0.0f,  0.0f, -1.0f, 0.0f },
    {  0.0f, -1.0f,  0.0f, 0.0f }
};


glm::vec4 BlockVertex::vertexOffsets[8] = {
    { 0.0f, 0.0f, 0.0f, 1.0f },
    { 1.0f, 0.0f, 0.0f, 1.0f },
    { 1.0f, 0.0f, 1.0f, 1.0f },
    { 0.0f, 0.0f, 1.0f, 1.0f },
    { 0.0f, 1.0f, 0.0f, 1.0f },
    { 1.0f, 1.0f, 0.0f, 1.0f },
    { 1.0f, 1.0f, 1.0f, 1.0f },
    { 0.0f, 1.0f, 1.0f, 1.0f }
};


unsigned int BlockVertex::faceIndices[2][3] = {
    { 0, 1, 2 },
    { 0, 2, 3 }
};


BlockChunkRenderable::BlockChunkRenderable ()
    : m_NextVertex(0), m_VAO(), m_VBO(), m_IBO()
{
    auto layout = VertexBufferLayout();
    layout.Push<float>(4);
    layout.Push<float>(4);
    layout.Push<float>(4);

    m_VAO.AddBuffer(m_VBO, layout);
}


void BlockChunkRenderable::AddFace (unsigned int block, BlockSide side,
                                    glm::uvec3 internalPos)
{
    glm::vec4 normal = BlockVertex::faceNormals[static_cast<int>(side)];

    glm::vec4 blockPosition(static_cast<float>(internalPos.x),
                            static_cast<float>(internalPos.y),
                            static_cast<float>(internalPos.z),
                            0.0f);

    unsigned int newVertexIndices[4];

    for (unsigned int i = 0; i < 4; ++i)
    {
        glm::vec4 vertexPosition = BlockVertex::vertexOffsets[
            BlockVertex::faceOrientation[
                static_cast<int>(side)][i]
            ] + blockPosition;
        newVertexIndices[i] = AddVertex(block, vertexPosition, normal);

    }

    for (unsigned int i = 0; i < 2; ++i)
    {
        for (unsigned int j = 0; j < 3; ++j)
        {
            m_Indices.push_back(newVertexIndices[
                BlockVertex::faceIndices[i][j]]);
        }
    }
}


unsigned int
BlockChunkRenderable::AddVertex (unsigned int block, glm::vec4 vertexPosition,
                                 glm::vec4 normal)
{
    auto vertex = m_NextVertex;
    ++m_NextVertex;

    BlockVertex bv;
    bv.position = vertexPosition;
    bv.normal = normal;
    bv.color = glm::vec4(0.6f, 0.4f, 0.1f, 1.0f);

    for (unsigned char byte : bv.bytes)
    {
        m_Vertices.push_back(byte);
    }

    return vertex;
}


void BlockChunkRenderable::SetData ()
{
    m_VBO.SetData(m_Vertices);
    m_IBO.SetData(m_Indices);
}


void BlockChunkRenderable::Draw ()
{
    m_VAO.Bind();
    m_VBO.Bind();
    m_IBO.Bind();
}

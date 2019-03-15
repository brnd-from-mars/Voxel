//
// Created by Brendan Berg on 14.03.19.
//

#include <algorithm>
#include <iterator>
#include <iostream>

#include <glm/gtc/type_ptr.hpp>

#include "BlockChunkRenderable.hpp"


struct BlockVertex
{
    glm::vec4 position;
    glm::vec4 normal;
    glm::vec4 color;

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
    {  0.0f,  0.0f, -1.0f, 0.0f },
    { -1.0f,  0.0f,  0.0f, 0.0f },
    {  0.0f,  0.0f,  1.0f, 0.0f },
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


BlockChunkRenderable::BlockChunkRenderable (Graphics& graphics)
    : Renderable::Renderable(graphics)
{
    auto layout = VertexBufferLayout();
    layout.Push<float>(4);
    layout.Push<float>(4);
    layout.Push<float>(4);

    m_VAO.AddBuffer(m_VBO, layout);
}


void BlockChunkRenderable::AddFace (glm::ivec3 internalPos,
                                    BlockSide side,
                                    unsigned int blockType)
{
    glm::vec4 normal = BlockVertex::faceNormals[static_cast<int>(side)];

    glm::vec4 blockPosition(0.0f);
    std::transform(glm::value_ptr(internalPos),
                   glm::value_ptr(internalPos) + 3,
                   glm::value_ptr(blockPosition),
                   [](int x)
                   {
                       return static_cast<float>(x);
                   });

    unsigned int newVertexIndices[4];

    for (unsigned int i = 0; i < 4; ++i)
    {
        glm::vec4 vertexPosition =
            BlockVertex::vertexOffsets[BlockVertex::faceOrientation[
                static_cast<int>(side)][i]]
            + blockPosition;
        newVertexIndices[i] = AddVertex(vertexPosition, normal, blockType);
    }

    for (auto& face : BlockVertex::faceIndices)
    {
        for (unsigned int index : face)
        {
            m_Indices.push_back(newVertexIndices[index]);
        }
    }
}


unsigned int BlockChunkRenderable::AddVertex (glm::vec4 vertexPosition,
                                              glm::vec4 normalVector,
                                              unsigned int blockType)
{
    BlockVertex bv {
        vertexPosition,
        normalVector,
        glm::vec4(0.8f, 0.6f, 0.8f, 1.0f)
    };

    return Renderable::AddVertex<BlockVertex>(bv);
}

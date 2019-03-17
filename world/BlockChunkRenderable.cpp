//
// Created by Brendan Berg on 14.03.19.
//

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "BlockChunkRenderable.hpp"


struct BlockVertex
{
    glm::vec4 position;
    glm::vec4 normal;
    glm::vec2 textureCoordinates;

    static int faceOrientation[6][4];

    static glm::vec4 faceNormals[6];

    static glm::vec4 vertexOffsets[8];

    static glm::vec2 textureIndices[4];

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
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 1.0f, 0.0f, 0.0f, 0.0f },
    { 1.0f, 0.0f, 1.0f, 0.0f },
    { 0.0f, 0.0f, 1.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f, 0.0f },
    { 1.0f, 1.0f, 0.0f, 0.0f },
    { 1.0f, 1.0f, 1.0f, 0.0f },
    { 0.0f, 1.0f, 1.0f, 0.0f }
};


glm::vec2 BlockVertex::textureIndices[4] = {
    { 0.0000f, 0.0000f },
    { 0.0625f, 0.0000f },
    { 0.0625f, 0.0625f },
    { 0.0000f, 0.0625f }
};


unsigned int BlockVertex::faceIndices[2][3] = {
    { 0, 1, 2 },
    { 0, 2, 3 }
};


BlockChunkRenderable::BlockChunkRenderable (Graphics& graphics,
                                            Shader& shader,
                                            const glm::vec3& chunkPos)
    : Renderable::Renderable(graphics, shader)
{
    auto layout = VertexBufferLayout();
    layout.Push<float>(4);
    layout.Push<float>(4);
    layout.Push<float>(2);

    m_VAO.AddBuffer(m_VBO, layout);

    SetChunkPos(chunkPos);
}


BlockChunkRenderable::BlockChunkRenderable (Graphics& graphics, Shader& shader)
    : BlockChunkRenderable(graphics, shader, glm::vec3(0.0, 0.0, 0.0))
{ }


void BlockChunkRenderable::SetChunkPos (const glm::vec3& chunkPos)
{
    SetMatrixModel(glm::translate(glm::mat4(1.0f), chunkPos * 16.0f));
}


void BlockChunkRenderable::AddFace (const glm::vec4& blockPosition,
                                    BlockSide side,
                                    unsigned int blockType)
{
    glm::vec4 normal = BlockVertex::faceNormals[static_cast<int>(side)];

    unsigned int newVertexIndices[4];

    for (unsigned int i = 0; i < 4; ++i)
    {
        glm::vec4 vertexPosition =
            BlockVertex::vertexOffsets[BlockVertex::faceOrientation[
                static_cast<int>(side)][i]]
            + blockPosition;
        newVertexIndices[i] = AddVertex(vertexPosition, normal, i);
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
                                              unsigned int vertex)
{
    BlockVertex bv {
        vertexPosition,
        normalVector,
        BlockVertex::textureIndices[vertex]
    };

    return Renderable::AddVertex<BlockVertex>(bv);
}

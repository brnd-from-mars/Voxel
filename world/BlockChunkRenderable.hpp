//
// Created by Brendan Berg on 14.03.19.
//

#ifndef VOXEL_BLOCKCHUNKRENDERABLE_HPP
#define VOXEL_BLOCKCHUNKRENDERABLE_HPP

#include <vector>

#include <glm/glm.hpp>

#include "../graphics/Graphics.hpp"
#include "../graphics/VertexBufferObject.hpp"
#include "../graphics/IndexBufferObject.hpp"
#include "../graphics/VertexBufferLayout.hpp"
#include "../graphics/VertexArrayObject.hpp"


enum class BlockSide
{
    Top = 0,
    North = 1,
    East = 2,
    South = 3,
    West = 4,
    Bottom = 5
};


class BlockChunkRenderable
{
public:

    BlockChunkRenderable ();

    void AddFace (unsigned int block, BlockSide side, glm::uvec3 internalPos);

    unsigned int AddVertex (unsigned int block, glm::vec4 vertexPosition,
                            glm::vec4 normal);

    void SetData ();

    void Draw ();


private:

    std::vector<unsigned char> m_Vertices;

    std::vector<unsigned int> m_Indices;

    unsigned int m_NextVertex;

    VertexArrayObject m_VAO;

    VertexBufferObject m_VBO;

    IndexBufferObject m_IBO;


};


#endif //VOXEL_BLOCKCHUNKRENDERABLE_HPP

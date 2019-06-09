//
// Created by Brendan Berg on 15.03.19.
//

#ifndef VOXEL_RENDERABLE_HPP
#define VOXEL_RENDERABLE_HPP

#include <memory>

#include <glm/glm.hpp>

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

    Renderable (std::shared_ptr<Graphics>& graphics,
                Shader &shader,
                const glm::mat4 &matrixModel);

    Renderable (std::shared_ptr<Graphics>& graphics, Shader &shader);

    void SetMatrixModel (const glm::mat4 &matrixModel);

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

    std::shared_ptr<Graphics> m_Graphics;

    Shader& m_Shader;

    glm::mat4 m_MatrixModel;

    VertexArrayObject m_VAO;

    VertexBufferObject m_VBO;

    IndexBufferObject m_IBO;

    std::vector<unsigned char> m_Vertices;

    std::vector<unsigned int> m_Indices;

    unsigned int m_NextVertex;


};


#endif //VOXEL_RENDERABLE_HPP

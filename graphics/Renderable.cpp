//
// Created by Brendan Berg on 15.03.19.
//

#include "Renderable.hpp"


Renderable::Renderable (Graphics& graphics,
                        Shader &shader,
                        const glm::mat4& matrixModel)
    : m_Graphics(graphics), m_Shader(shader), m_MatrixModel(matrixModel),
    m_VAO(), m_VBO(), m_IBO(), m_NextVertex()
{ }


Renderable::Renderable (Graphics& graphics, Shader& shader)
    : Renderable(graphics, shader, glm::mat4(0.0f))
{ }


void Renderable::SetMatrixModel (const glm::mat4& matrixModel)
{
    m_MatrixModel = matrixModel;
}


void Renderable::UpdateData ()
{
    m_VBO.SetData(m_Vertices);
    m_IBO.SetData(m_Indices);
}



void Renderable::Draw ()
{
    m_VAO.Bind();
    m_VBO.Bind();
    m_IBO.Bind();

    m_Shader.SetUniformMatrix("u_MatrixModel", m_MatrixModel);

    m_Graphics.Draw(m_IBO.GetCount());
}

//
// Created by Brendan Berg on 15.03.19.
//

#include "Renderable.hpp"


Renderable::Renderable (Graphics& graphics)
    : m_Graphics(graphics), m_VAO(), m_VBO(), m_IBO(), m_NextVertex()
{ }


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
    m_Graphics.Draw(m_IBO.GetCount());
}

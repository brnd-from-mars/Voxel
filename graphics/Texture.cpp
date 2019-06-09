//
// Created by Brendan Berg on 16.03.19.
//

#include "Texture.hpp"


Texture::Texture (const std::string& filePath)
    : m_TextureAddress(0), m_TextureSlot(0),
    m_Width(0), m_Height(0), m_BitsPerPixel()
{
    //stbi_set_flip_vertically_on_load(1);
    auto buffer = stbi_load(filePath.c_str(),
        &m_Width, &m_Height, &m_BitsPerPixel, 4);

    GLCall(glGenTextures(1, &m_TextureAddress));
    Bind();

    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0,
        GL_RGBA, GL_UNSIGNED_BYTE, buffer));

    stbi_image_free(buffer);

    Unbind();
}


Texture::~Texture ()
{
    GLCall(glDeleteBuffers(1, &m_TextureAddress));
}


int Texture::GetSlot ()
{
    return m_TextureSlot;
}


void Texture::Bind (int slot)
{
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_TextureAddress));
    m_TextureSlot = slot;
}


void Texture::Unbind ()
{
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

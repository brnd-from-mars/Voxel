//
// Created by Brendan Berg on 16.03.19.
//

#ifndef VOXEL_TEXTURE_HPP
#define VOXEL_TEXTURE_HPP

#include <string>

#include "../vendor/stb/stb_image.h"

#include "Graphics.hpp"


class Texture
{
public:

    explicit Texture (const std::string& filePath);

    ~Texture ();

    void Bind (unsigned int slot = 0);

    void Unbind ();


private:

    unsigned int m_TextureAddress;

    int m_Width;

    int m_Height;

    int m_BitsPerPixel;


};


#endif //VOXEL_TEXTURE_HPP

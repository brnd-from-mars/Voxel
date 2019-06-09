//
// Created by Brendan Berg on 2019-05-21.
//

#define STB_PERLIN_IMPLEMENTATION
#include "../vendor/stb/stb_perlin.h"

#include "WorldGenerator.hpp"

#include <iostream>


unsigned int WorldGenerator::GetColumnHeight (int chunkX, int chunkZ,
                                              int internalX, int internalZ)
{
    auto floatX = static_cast<float>((16 * chunkX + internalX) / 64.0f);
    auto floatY = 0.1f;
    auto floatZ = static_cast<float>((16 * chunkZ + internalZ) / 64.0f);

    auto noise = stb_perlin_fbm_noise3(
        floatX, floatY, floatZ, 2.0f, 0.5f, 5);

    auto offset = static_cast<int>((noise - 0.5f) * 16.0f);

    return 72 + offset;
}

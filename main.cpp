#include <iostream>

#include "graphics/Graphics.hpp"


int main ()
{
    auto graphics = Graphics(4, 1, true, 640, 480, "Voxel");

    while (graphics.Active())
    {
        graphics.Update();
    }

    return 0;
}

#include <iostream>

#include "graphics/Graphics.hpp"
#include "graphics/VertexBufferObject.hpp"
#include "graphics/VertexBufferLayout.hpp"
#include "graphics/VertexArrayObject.hpp"
#include "graphics/IndexBufferObject.hpp"
#include "graphics/Shader.hpp"


int main ()
{
    float positions[20] = {
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, 0.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, 0.0f, 1.0f, 0.0f
    };

    unsigned int indices[6] = {
        0, 1, 2,
        0, 2, 3
    };

    auto graphics = Graphics(4, 1, true, 640, 480, "Voxel");
    auto vao = VertexArrayObject(true);

    auto vbo = VertexBufferObject(true, positions, 20 * sizeof(float));

    {
        auto vbl = VertexBufferLayout();
        vbl.Push<float>(2);
        vbl.Push<float>(3);
        vao.AddBuffer(vbo, vbl);
    }

    auto ibo = IndexBufferObject(true, indices, 6);

    auto shader = Shader("shader/shader.vs", "shader/shader.fs");

    while (graphics.Active())
    {
        graphics.Update();
    }

    return 0;
}

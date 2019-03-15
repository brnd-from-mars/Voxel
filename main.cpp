#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "graphics/Graphics.hpp"
#include "graphics/Shader.hpp"

#include "world/BlockChunk.hpp"


int main ()
{
    auto graphics = Graphics(4, 1, true, 640, 480, "Voxel");

    auto blockChunk = BlockChunk(glm::ivec3(0, 0, 0), graphics);
    blockChunk.GenerateMesh();

    auto shader = Shader("shader/shader.vs", "shader/shader.fs");

    auto projection = glm::perspective(glm::radians(45.0f),
                                       640.0f / 480.0f,
                                       0.1f,
                                       100.0f);

    auto view = glm::lookAt(glm::vec3(-20.0f, 100.0f, -20.0f),
                            glm::vec3(8.0f, 70.0f, 8.0f),
                            glm::vec3(0.0f, 1.0f, 0.0f));

    auto model = glm::mat4(1.0f);

    auto mvp = projection * view * model;

    auto v = glm::vec4(-60.0f, 100.0, -20.0, 1.0);

    while (graphics.Active())
    {
        graphics.ClearWindow();

        auto u1 = shader.GetUniformLocation("mvpMatrix");
        GLCall(glUniformMatrix4fv(u1, 1, GL_FALSE, glm::value_ptr(mvp)));
        auto u2 = shader.GetUniformLocation("lightPosition");
        GLCall(glUniform4fv(u2, 1, glm::value_ptr(v)));

        blockChunk.GetRenderable().Draw();

        graphics.UpdateWindow();
    }

    return 0;
}

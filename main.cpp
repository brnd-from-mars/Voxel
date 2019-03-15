#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "graphics/Graphics.hpp"
#include "graphics/VertexBufferObject.hpp"
#include "graphics/VertexBufferLayout.hpp"
#include "graphics/VertexArrayObject.hpp"
#include "graphics/IndexBufferObject.hpp"
#include "graphics/Shader.hpp"

#include "world/BlockChunkRenderable.hpp"


int main ()
{
    auto graphics = Graphics(4, 1, true, 640, 480, "Voxel");

    BlockChunkRenderable bcr;
    bcr.AddFace(1, BlockSide::West, glm::uvec3(0, 0, 0));
    bcr.AddFace(1, BlockSide::Top, glm::uvec3(0, 0, 0));
    bcr.SetData();

    auto shader = Shader("shader/shader.vs", "shader/shader.fs");

    auto projection = glm::perspective(glm::radians(45.0f), 640.0f / 480.0f, 0.1f, 100.0f);

    auto view = glm::lookAt(glm::vec3(4.0f, 3.0f, 3.0f),
                            glm::vec3(0.0f, 0.0f, 0.0f),
                            glm::vec3(0.0f, 1.0f, 0.0f));

    auto model = glm::mat4(1.0f);

    auto mvp = projection * view * model;

    auto v = glm::vec4(-3.0f, 3.0, -3.0, 1.0);

    while (graphics.Active())
    {
        graphics.ClearWindow();
        auto u1 = shader.GetUniformLocation("mvpMatrix");
        auto u2 = shader.GetUniformLocation("lightPosition");
        GLCall(glUniformMatrix4fv(u1, 1, GL_FALSE, glm::value_ptr(mvp)));
        GLCall(glUniform4fv(u2, 1, glm::value_ptr(v)));
        graphics.Draw(12);
        graphics.UpdateWindow();
    }

    return 0;
}

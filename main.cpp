#include <iostream>
#include <vector>
#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "utility/ConfigParser.hpp"

#include "graphics/Graphics.hpp"
#include "graphics/Shader.hpp"
#include "graphics/Texture.hpp"

#include "world/BlockChunk.hpp"
#include "world/BlockTypeContainer.hpp"

//#define WIDTH 1280
//#define HEIGHT 720

#define WIDTH 960
#define HEIGHT 540


int main ()
{
    auto graphics = Graphics(4, 1, true, WIDTH, HEIGHT, "Voxel");

    auto shader = Shader("resources/shader/shader.vs",
                         "resources/shader/shader.fs");

    auto matrixProjection = glm::perspective(glm::radians(45.0f),
                                             static_cast<float>(WIDTH) /
                                                 static_cast<float>(HEIGHT),
                                             0.1f,
                                             100.0f);


    auto matrixView = glm::lookAt(glm::vec3(0.0f, 80.0f, -10.0f),
                                  glm::vec3(16.0f, 70.0f, 8.0f),
                                  glm::vec3(0.0f, 1.0f, 0.0f));

    auto lightPosition = glm::vec4(-20.0f, 120.0, -8.0, 1.0);

    BlockTypeContainer btc("resources/config/blocks.cfg");

    Texture texture("resources/textures/blocks.png");
    texture.Bind();

    std::vector<BlockChunk> bcc;
    bcc.emplace_back(glm::ivec3(0.0, 0.0, 0.0),
                     std::make_unique<BlockChunkBlocks>(),
                     std::make_unique<BlockChunkRenderable>(graphics, shader));
    bcc.emplace_back(glm::ivec3(1.0, 0.0, 0.0),
                     std::make_unique<BlockChunkBlocks>(),
                     std::make_unique<BlockChunkRenderable>(graphics, shader));

    while (graphics.Active())
    {
        graphics.ClearWindow();

        shader.SetUniformValue("u_Texture", 0);
        shader.SetUniformVector("u_lightPosition", lightPosition);
        shader.SetUniformMatrix("u_MatrixProjection", matrixProjection);
        shader.SetUniformMatrix("u_MatrixView", matrixView);

        for (auto& bc : bcc)
        {
            bc.GetRenderable()->Draw();
        }

        graphics.UpdateWindow();
    }

    return 0;
}

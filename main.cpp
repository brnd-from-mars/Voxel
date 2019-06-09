#include <iostream>
#include <vector>
#include <memory>

#include <glm/glm.hpp>

#include "utility/ConfigParser.hpp"

#include "graphics/Graphics.hpp"
#include "graphics/Shader.hpp"
#include "graphics/Texture.hpp"

#include "event/EventDispatcher.hpp"

#include "world/BlockChunk.hpp"
#include "world/World.hpp"

#include "player/Player.hpp"

#define WIDTH 960
#define HEIGHT 540


int main ()
{
    auto graphics = std::make_shared<Graphics>(
        4, 1, true, WIDTH, HEIGHT, "Voxel");

    EventDispatcher eventDispatcher(graphics);

    Shader shader ("resources/shader/shader.vs", "resources/shader/shader.fs");

    Player player(std::make_unique<PlayerMovable>(eventDispatcher, graphics));

    Texture texture("resources/textures/blocks.png");
    texture.Bind();

    World world(graphics, shader, "resources/config/blocks.cfg");

    auto lightPosition = glm::vec4(0.0f, 120.0, 0.0, 1.0);

    while (graphics->Active())
    {
        graphics->ClearWindow();

        player.Update(graphics->GetFrameDuration());
        world.Update(player.GetMovable()->GetPosition());

        shader.SetUniformValue("u_Texture", texture.GetSlot());
        shader.SetUniformVector("u_lightPosition", lightPosition);
        shader.SetUniformMatrix("u_MatrixProjection", graphics->GetProjectionMatrix());
        shader.SetUniformMatrix("u_MatrixView", player.GetMovable()->GetViewMatrix());

        world.Draw();

        graphics->UpdateWindow();
    }

    return 0;
}

//
// Created by Brendan Berg on 13.03.19.
//

#ifndef VOXEL_GRAPHICS_HPP
#define VOXEL_GRAPHICS_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLCall(x) Graphics::ClearError();\
    x;\
    Graphics::LogError(#x, __FILE__, __LINE__)


class Graphics
{
public:

    Graphics (int major, int minor, bool core,
              int width, int height, const char* title);

    ~Graphics ();

    bool Active ();

    void Update ();

    GLFWwindow* GetWindow();

    static void ClearError ();

    static void LogError (const char* function, const char* filename, int line);


private:

    void InitGlfw ();

    void InitVersion (int major, int minor, bool core);

    void InitWindow (int width, int height, const char* title);

    void InitGlew ();

    GLFWwindow* m_Window = nullptr;


};


#endif //VOXEL_GRAPHICS_HPP

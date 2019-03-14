//
// Created by Brendan Berg on 13.03.19.
//

#include <iostream>

#include "Graphics.hpp"


Graphics::Graphics (int major, int minor, bool core,
                    int width, int height, const char* title)
{
    InitGlfw();
    InitVersion(major, minor, core);
    InitWindow(width, height, title);
    InitGlew();
}


Graphics::~Graphics ()
{
    glfwTerminate();
}


bool Graphics::Active ()
{
    return !glfwWindowShouldClose(m_Window);
}


void Graphics::Update ()
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
    // TODO: specialize draw call
    GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
    glfwSwapBuffers(m_Window);
    glfwPollEvents();
}


GLFWwindow* Graphics::GetWindow ()
{
    return m_Window;
}


void Graphics::ClearError ()
{
    while (glGetError());
}


void Graphics::LogError (const char* function, const char* filename, int line)
{
    while (auto error = glGetError())
    {
        std::cerr << "[OpenGL Error] "
                  << "0x" << std::hex << error << std::dec << " "
                  << "in function " << function << " "
                  << filename << ":" << line << std::endl;
    }
}


void Graphics::InitGlfw ()
{
    if (!glfwInit())
    {
        std::cerr << "[Graphics Error] glfw init failed in"
                  << __FILE__ << ":" << __LINE__ << std::endl;
    }
}


void Graphics::InitVersion (int major, int minor, bool core)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
    if (core)
    {
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    }
}


void Graphics::InitWindow (int width, int height, const char* title)
{
    m_Window = glfwCreateWindow(width, height, title, nullptr, nullptr);

    if (m_Window)
    {
        glfwMakeContextCurrent(m_Window);
    }
    else
    {
        glfwTerminate();
        std::cerr << "[Graphics Error] glfw window creation failed in"
                  << __FILE__ << ":" << __LINE__ << std::endl;
    }
}


void Graphics::InitGlew ()
{
    auto error = glewInit();

    if (error != GLEW_OK)
    {
        std::cerr << "[Graphics Error] glew init failed in"
                  << __FILE__ << ":" << __LINE__ << std::endl;
    }
}

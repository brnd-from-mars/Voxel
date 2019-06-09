//
// Created by Brendan Berg on 13.03.19.
//

#include <iostream>

#include <glm/gtc/matrix_transform.hpp>

#include "Graphics.hpp"


Graphics::Graphics (int major, int minor, bool core,
                    int width, int height, const char* title)
    : m_PreviousFrameTime(0), m_CurrentFrameTime(0), m_FrameDuration(0),
    m_GUIMode(true)
{
    InitGlfw();
    InitVersion(major, minor, core);
    InitWindow(width, height, title);
    InitGlew();
    InitOpenGL();
    InitProjection(width, height);
}


Graphics::~Graphics ()
{
    glfwTerminate();
}


bool Graphics::Active ()
{
    m_PreviousFrameTime = m_CurrentFrameTime;
    m_CurrentFrameTime = glfwGetTime();
    m_FrameDuration = m_CurrentFrameTime - m_PreviousFrameTime;
    return !glfwWindowShouldClose(m_Window);
}


void Graphics::ClearWindow ()
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}


void Graphics::Draw (unsigned int elementCount)
{
    GLCall(glDrawElements(GL_TRIANGLES, elementCount,
                          GL_UNSIGNED_INT, nullptr));
}


void Graphics::UpdateWindow ()
{
    glfwSwapBuffers(m_Window);
    glfwPollEvents();
}


void Graphics::SetWindowUserPointer (void* pointer)
{
    glfwSetWindowUserPointer(m_Window, pointer);
}


void Graphics::SwitchGUIMode ()
{
    m_GUIMode = !m_GUIMode;
    glfwSetInputMode(m_Window,
                     GLFW_CURSOR,
                     m_GUIMode ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
}


GLFWwindow* Graphics::GetWindow ()
{
    return m_Window;
}


bool Graphics::GetGUIMode ()
{
    return m_GUIMode;
}


glm::mat4 Graphics::GetProjectionMatrix ()
{
    return m_ProjectionMatrix;
}


double Graphics::GetFrameDuration ()
{
    return m_FrameDuration;
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

    m_CurrentFrameTime = glfwGetTime();
}


void Graphics::InitVersion (int major, int minor, bool core)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
    glfwWindowHint(GLFW_SAMPLES, 4);
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


void Graphics::InitOpenGL ()
{
    GLCall(glEnable(GL_DEPTH_TEST));
    GLCall(glEnable(GL_MULTISAMPLE));
    GLCall(glEnable(GL_CULL_FACE));
    GLCall(glCullFace(GL_FRONT));
}


void Graphics::InitProjection (int width, int height)
{
    m_ProjectionMatrix = glm::perspective(
        glm::radians(45.0f),
        static_cast<float>(width) / static_cast<float>(height),
        0.1f, 180.0f);
}

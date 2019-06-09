//
// Created by Brendan Berg on 13.03.19.
//

#ifndef VOXEL_GRAPHICS_HPP
#define VOXEL_GRAPHICS_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

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

    void ClearWindow ();

    void Draw (unsigned int elementCount);

    void UpdateWindow ();

    void SetWindowUserPointer (void* pointer);

    void SwitchGUIMode ();

    GLFWwindow* GetWindow ();

    bool GetGUIMode ();

    glm::mat4 GetProjectionMatrix ();

    double GetFrameDuration ();

    static void ClearError ();

    static void LogError (const char* function, const char* filename, int line);


private:

    void InitGlfw ();

    void InitVersion (int major, int minor, bool core);

    void InitWindow (int width, int height, const char* title);

    void InitGlew ();

    void InitOpenGL ();

    void InitProjection (int width, int height);

    GLFWwindow* m_Window = nullptr;

    glm::mat4 m_ProjectionMatrix;

    double m_PreviousFrameTime;

    double m_CurrentFrameTime;

    double m_FrameDuration;

    bool m_GUIMode;


};


#endif //VOXEL_GRAPHICS_HPP

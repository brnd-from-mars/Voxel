add_library(graphics
        Graphics.cpp
        Shader.cpp
        VertexBufferObject.cpp
)

find_package(glfw3 3.2 REQUIRED)
include_directories(${GLFW_INCLUDE_DIRS})
link_libraries(${GLFW_LIBRARY_DIRS})

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

target_link_libraries(graphics
        glfw
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
)

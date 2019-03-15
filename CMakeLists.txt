cmake_minimum_required(VERSION 3.12)
project(Voxel)

set(CMAKE_CXX_STANDARD 17)

add_executable(Voxel main.cpp)

add_subdirectory(graphics)
add_subdirectory(world)
target_link_libraries(Voxel graphics world)

add_custom_command(
        TARGET Voxel
        POST_BUILD
        WORKING_DIRECTORY
            ${CMAKE_CURRENT_SOURCE_DIR}
        COMMAND
            ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/shader
        COMMAND
            ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_CURRENT_SOURCE_DIR}/shader
                ${CMAKE_BINARY_DIR}/shader
)

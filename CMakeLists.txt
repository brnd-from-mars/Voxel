cmake_minimum_required(VERSION 3.12)
project(Voxel)

set(CMAKE_CXX_STANDARD 17)

add_executable(Voxel main.cpp)

include_directories(vendor)

add_subdirectory(utility)
add_subdirectory(graphics)
add_subdirectory(world)
add_subdirectory(event)
add_subdirectory(player)
add_subdirectory(vendor)
target_link_libraries(Voxel utility graphics world event player)

add_custom_command(
        TARGET Voxel
        POST_BUILD
        WORKING_DIRECTORY
            ${CMAKE_CURRENT_SOURCE_DIR}
        COMMAND
            ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/resources
        COMMAND
            ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_CURRENT_SOURCE_DIR}/resources
                ${CMAKE_BINARY_DIR}/resources
)

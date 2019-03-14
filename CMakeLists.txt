cmake_minimum_required(VERSION 3.12)
project(Voxel)

set(CMAKE_CXX_STANDARD 17)

add_executable(Voxel main.cpp)

add_subdirectory(graphics)
target_link_libraries(Voxel graphics)

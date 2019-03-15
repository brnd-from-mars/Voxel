add_library(world
        BlockColumn.cpp
        BlockChunk.cpp
        BlockChunkRenderable.cpp
)

target_link_libraries(world graphics)

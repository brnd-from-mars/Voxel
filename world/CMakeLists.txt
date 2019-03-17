add_library(world
        BlockUtility.cpp
        BlockColumn.cpp
        BlockChunkBlocks.cpp
        BlockChunkRenderable.cpp
        BlockChunk.cpp
        BlockType.cpp
        BlockTypeContainer.cpp
)

target_link_libraries(world utility graphics)

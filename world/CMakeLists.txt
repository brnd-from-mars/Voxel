add_library(world
        BlockUtility.cpp
        BlockColumn.cpp
        BlockChunkBlocks.cpp
        BlockChunkRenderable.cpp
        BlockChunk.cpp
        BlockType.cpp
        BlockTypeContainer.cpp
        World.cpp
        WorldGenerator.cpp
        WorldLoader.cpp
        ChunkLoader.cpp
)

target_link_libraries(world utility graphics)

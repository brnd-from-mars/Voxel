add_library(event
        Event.cpp
        KeyboardEvent.cpp
        MouseMovedEvent.cpp
        EventDispatcher.cpp
)

target_link_libraries(event
        graphics
)

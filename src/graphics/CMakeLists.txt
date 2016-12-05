set(Graphics_SOURCES
    Window.cpp)

add_library(Graphics ${Graphics_SOURCES})
target_link_libraries(Graphics ${SDL2_LIBRARY})

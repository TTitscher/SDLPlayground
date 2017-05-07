cmake_minimum_required(VERSION 3.1)
project(SDLPlayground)

set(CMAKE_CXX_STANDARD 14) # use this if cmake_minimum_required(VERSION 3.1)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(/usr/include/eigen3)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
find_package(SDL2 REQUIRED)
include_directories(${SDL_INCLUDE_DIR})

enable_testing()
add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(benchmark)
add_subdirectory(application)

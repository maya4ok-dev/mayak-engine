cmake_minimum_required(VERSION 3.30)
project(mayak-engine)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# С++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SDL_SHARED OFF CACHE BOOL "Build SDL shared library")
set(SDL_STATIC ON CACHE BOOL "Build SDL static library")

# Sources
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Dependencies
add_subdirectory(external/SDL)
add_subdirectory(external/box2d)

add_library(mayak-engine STATIC ${SOURCES})

# Catch extra errors
target_compile_options(mayak-engine PRIVATE -Wall -Wextra -Werror)

# Header-only dependencies + engine
target_include_directories(
    mayak-engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/external/SDL/include
    ${CMAKE_CURRENT_SOURCE_DIR}/external/stb
    ${CMAKE_CURRENT_SOURCE_DIR}/external/sol2/include
    ${CMAKE_CURRENT_SOURCE_DIR}/external/mayak-logger
    ${CMAKE_CURRENT_SOURCE_DIR}/external/glm
    ${CMAKE_CURRENT_SOURCE_DIR}/external/box2d/include
)

target_link_libraries(
    mayak-engine PUBLIC
    SDL3
    lua
    box2d
)

add_subdirectory(game)